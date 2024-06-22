/**
 * @file LinearScan.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 使用线性扫描进行寄存器分配 声明：参考 https://blog.csdn.net/sexyluna/article/details/132287291
 * @version 1.0
 * @date 2024-05-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "LinearScan.h"
#include "ActiveVariableAnalysis.h"
#include <iostream>
#include <fstream>
#include "PlatformArm32.h"

//********************************** interval ****************************************
/// @brief 创建智能指针对象 并根据参数计算出start end
/// @param _def
/// @param uses
/// @param _isPreAlloca
/// @return
IntervalPtr Interval::get(const MOperaPtr &_def, const std::unordered_set<MOperaPtr> &uses,
                          bool _isPreAlloca)
{
    // _isUncerntainDef 和 _isArgDef 不能同时为真
    assert(_def != nullptr);
    // 创建对象
    IntervalPtr inter = std::make_shared<Interval>();
    inter->def = _def;
    for (auto &use : uses)
    {
        inter->uses.insert(use);
    }
    inter->isPreAlloca = _isPreAlloca;
    // 下面根据参数情况计算该interval的的 start end(只是进行初始化 后面还需修正)
    if (!_isPreAlloca)
    {
        // 不是预分配的类型  是虚拟寄存器类型 按照
        inter->start = _def->getParent()->getNo(); // 起始是 def 位置
        inter->end = inter->start;
        if (inter->uses.size() > 0)
        {
            // uses按照从小到大排序
            auto riter = inter->uses.rbegin();
            inter->end = std::max(inter->end, (int)(*riter)->getParent()->getNo());
        }
    }
    else
    {
        // 是预分配的物理寄存器r0-r3
        if (!_def->isInitArg())
        { // 不是函数初始状态形参
            inter->start = _def->getParent()->getNo();
            inter->end = inter->start;
            if (inter->uses.size() > 0)
            {
                auto riter = inter->uses.rbegin();
                inter->end = std::max(inter->end, (int)(*riter)->getParent()->getNo());
            }
        }
        else
        {
            // 是函数初始状态形参
            inter->start = 0;
            inter->end = inter->start;
            if (inter->uses.size() > 0)
            {
                auto riter = inter->uses.rbegin();
                inter->end = std::max(inter->end, (int)(*riter)->getParent()->getNo());
            }
        }
    }
    return inter;
}

//**************************** regsPool寄存器池 ************************************
/// @brief 构造函数
RegsPool::RegsPool()
{
    for (int i = 0; i < 11; i++)
    {
        regsCanUse.insert(i);
        regIntersMap.emplace(i, nullptr);
    }
}

/// @brief 重置寄存器池
void RegsPool::resetRegsPool()
{
    regIntersMap.clear();
    regsLastUse.clear();
    regsCanUse.clear();
    for (int i = 0; i < 11; i++)
    {
        regsCanUse.insert(i);
        regIntersMap.emplace(i, nullptr);
    }
}

/// @brief 回收已经结束的间隔占用的寄存器
void RegsPool::empireOldIntervals(IntervalPtr inter)
{
    for (auto &elem : regIntersMap)
    {
        int regno = elem.first;
        IntervalPtr interval = elem.second;
        if (interval != nullptr)
        {
            if (interval->end < inter->start)
            {
                regIntersMap[regno] = nullptr;
                regsCanUse.insert(regno);
                regsLastUse[regno] = interval->end;
            }
            else if (interval->end == inter->start)
            {
                if (interval->uses.size() != 0)
                {
                    regIntersMap[regno] = nullptr;
                    regsCanUse.insert(regno);
                    regsLastUse[regno] = interval->end;
                }
            }
        }
    }
}

/// @brief 判断某一号寄存器是否可以使用
/// @param regNo
/// @return
bool RegsPool::isAvailable(int regNo)
{
    assert(regNo >= 0 && regNo < 11);
    if (regIntersMap[regNo] == nullptr)
    {
        assert(regsCanUse.find(regNo) != regsCanUse.end());
        return true;
    }
    else
    {
        assert(regsCanUse.find(regNo) == regsCanUse.end());
        return false;
    }
}

/// @brief 溢出指定间隔
/// @param inter
void RegsPool::spillAtInterval(IntervalPtr inter)
{
    int regNo = inter->reg;
    assert(regNo != -1 && regIntersMap[regNo] == inter);
    regIntersMap[regNo] = nullptr;
    regsCanUse.insert(regNo);
    inter->reg = -1;
}

/// @brief 为间隔分配指定寄存器
/// @param inter
/// @param regNo
void RegsPool::allocaReg(IntervalPtr inter, int regNo)
{
    assert(isAvailable(regNo));
    regIntersMap[regNo] = inter;
    inter->reg = regNo;
    regsCanUse.erase(regNo);
}

/// @brief 返回占用寄存器的间隔
/// @return
std::vector<IntervalPtr> RegsPool::getActive()
{
    std::vector<IntervalPtr> res;
    for (auto &elem : regIntersMap)
    {
        IntervalPtr &interval = elem.second;
        if (interval != nullptr)
        {
            res.push_back(interval);
        }
    }
    return res;
}

/// @brief 获取间隔可以切换的寄存器编号
/// @param inter
/// @return
int RegsPool::getSwitchReg(IntervalPtr inter)
{
    int res = -1;
    for (int reg : regsCanUse)
    {
        auto iter = regsLastUse.find(reg);
        if (iter == regsLastUse.end())
        {
            // 说明没有被使用过
            res = reg;
            break;
        }
        else
        {
            if (regsLastUse[reg] <= inter->start)
            {
                res = reg;
                break;
            }
        }
    }
    return res;
}

//************************************ LinearScan ********************************************************
/// @brief 计算 fun的虚拟寄存器 物理寄存器的 def-use chain
/// @param fun
void LinearScan::computeDefUseChain(MFuncPtr fun)
{
    // 根据liveOut 出口活跃变量分析建立def_use chain
    // 根据IR 结构 即使插入溢出处理代码也不会出现 一个 use 对应多个def的情况(时间不够 没有phi节点)
    // 先清空
    defUseChains.clear();
    // 先计算这个函数的liveIn  liveOut
    ActiveVariAnalysis LiveAnalysis;
    LiveAnalysis.computeLiveVariInfun(fun);
    std::cout << "计算完毕def-use chian" << std::endl;
    // fun 中 AllUsesInFun 列表记录
    auto &allUsesOfFun = LiveAnalysis.AllUsesInfun;
    std::list<MBlockPtr> &blockList = fun->getBlockList();
    int instNo = 0; // 设置编号
    int i = 0;      // 每个块末尾的编号
                    // 用于记录虚拟寄存器类型和物理寄存器类型在每个block的出口活跃记录(按照名字分类)
    std::map<MachineOperand, std::set<MOperaPtr>> liveReg;
    for (auto &blk : blockList)
    {
        liveReg.clear(); // 每个块不一样
        for (auto &live : blk->getLiveOut())
        { // 获取 基本块 中 r0-r3 的出口活跃记录
            if (live->isVReg())
            {
                // 记录物理寄存器以及虚拟寄存器的活跃记录
                liveReg[*live].insert(live);
            }
            else if (live->isReg())
            {
                if (live->getRegNo() >= 0 && live->getRegNo() <= 3)
                {
                    liveReg[*live].insert(live);
                }
            }
        }
        std::list<MInstPtr> &instList = blk->getInstList();
        i = instList.size() + i; // 当前块 末尾的编号
        instNo = i;              // 当前指令编号
        // 逆序遍历指令列表
        for (auto riter = instList.rbegin(); riter != instList.rend(); riter++)
        {
            auto &inst = *riter;
            inst->setNo(instNo--);
            auto &defs = inst->getDef();
            for (auto &def : defs)
            {
                if (def->isVReg())
                {
                    // 是虚拟寄存器或者物理寄存器类型
                    auto &uses = liveReg[*def];
                    defUseChains[def].insert(uses.begin(), uses.end());

                    auto &kill = allUsesOfFun[*def];
                    std::set<MOperaPtr> res;
                    set_difference(uses.begin(), uses.end(), kill.begin(), kill.end(), inserter(res, res.end()));
                    liveReg[*def] = res;
                    // liveReg[*def].clear(); // 定值已经到达 清除
                }
                else if (def->isReg())
                {
                    if (def->getRegNo() >= 0 && def->getRegNo() <= 3)
                    {
                        if (def->getParent()->isBranch())
                        {
                            std::cout << "跳转的标签为:" << def->getParent()->getUse()[0]->getLabel() << std::endl;
                            std::cout << "def size 为:" << def->getParent()->getDef().size() << std::endl;
                            std::cout << "line: " << def->getParent()->getNo() << std::endl;
                        }

                        auto &uses = liveReg[*def];
                        defUseChains[def].insert(uses.begin(), uses.end());
                        liveReg[*def].clear(); // 定值已经到达 清除
                    }
                }
            }
            for (auto &use : inst->getUse())
            {
                // 遍历use  只记录 r0-r3
                if (use->isVReg())
                {
                    // 插入使用变量 (可能和上逆序上前的指令的def 形成 def-use chain)
                    liveReg[*use].insert(use);
                }
                else if (use->isReg())
                {
                    if (use->getRegNo() >= 0 && use->getRegNo() <= 3)
                    {
                        liveReg[*use].insert(use);
                    }
                }
            }
        }
        if (blk == blockList.front())
        {
            for (auto &elem : liveReg)
            {
                // 最后这一段剩余的 是 函数形参的初值
                auto &op = elem.first;
                if (op.isReg() && elem.second.size() > 0)
                {
                    int regno = op.getRegNo();
                    if (regno >= 0 && regno <= 3)
                    {
                        MOperaPtr initArg = MachineOperand::createReg(regno);
                        initArg->setInitArg();
                        defUseChains[initArg].insert(elem.second.begin(), elem.second.end());
                        std::cout << "initArg:" << initArg->toStr() << std::endl;
                    }
                }
            }
        }
    }

    // std::ofstream file1("../tests/liveInOut.txt", std::ios_base::app);
    // file1 << "\n*****************" << fun->getFuncName() << "***********************\n";
    // for (auto &blk : blockList)
    // {
    //     file1 << "block: " << blk->getLabelName() << "--------------\n";
    //     file<<"liveIn"
    // }

    // std::ofstream file("../tests/log_line.txt", std::ios_base::app);
    // file << "\n*****************" << fun->getFuncName() << "***********************\n";
    // for (auto &blk : blockList)
    // {
    //     for (auto &inst : blk->getInstList())
    //     {
    //         file << "line: ";
    //         file << std::to_string(inst->getNo()) << " ";
    //         file << inst->toStr() << "\n";
    //     }
    // }
}

/// @brief 计算活跃间隔(仅对 虚拟寄存器而言)
/// @param fun
void LinearScan::computeIntervals(MFuncPtr fun)
{
    intervals.clear();
    // 根据def-Use chain 获取 interval;
    for (auto &defUse : defUseChains)
    {
        auto def = defUse.first;
        auto &uses = defUse.second;
        if (def->isVReg())
        {
            IntervalPtr inter = Interval::get(def, uses);
            intervals.push_back(inter);
        }
        else
        {
            // 物理寄存器 r0-r3
            assert(def->getRegNo() >= 0 && def->getRegNo() <= 3);
            IntervalPtr inter = Interval::get(def, uses, true);
            intervals.push_back(inter);
        }
    }
    // 下面计算活跃间隔的 start end 根据活跃变量分析
    for (auto &interval : intervals)
    {
        auto &uses = interval->uses;
        auto begin = interval->start;
        auto end = interval->end;
        for (auto &block : fun->getBlockList())
        {
            auto &instList = block->getInstList();
            auto &liveIn = block->getLiveIn();
            auto &liveOut = block->getLiveOut();
            bool in = false;
            bool out = false;
            for (auto &use : uses)
            {
                if (liveIn.find(use) != liveIn.end())
                { // 入口活跃
                    in = true;
                    break;
                }
            }
            for (auto &use : uses)
            {
                if (liveOut.find(use) != liveOut.end())
                { // 出口活跃
                    out = true;
                    break;
                }
            }
            if (in && out)
            { // 入口出口都活跃
                begin = std::min(begin, (int)(*instList.begin())->getNo());
                end = std::max(end, (int)(*instList.rbegin())->getNo());
            }
            else if (!in && out)
            { // 入口不活跃出口活跃
                for (auto &inst : instList)
                    if (inst->getDef().size() > 0 &&
                        inst->getDef()[0] == *(uses.begin()))
                    {
                        begin = std::min(begin, (int)inst->getNo());
                        break;
                    }
                end = std::max(end, (int)(*(instList.rbegin()))->getNo());
            }
            else if (in && !out)
            { // 入口活跃出口不活跃
                begin = std::min(begin, (int)(*(instList.begin()))->getNo());
                int temp = 0;
                for (auto use : uses)
                    if (use->getParent()->getParent() == block)
                        temp = std::max(temp, (int)use->getParent()->getNo());
                end = std::max(temp, end);
            }
        }
        if (interval->start != begin)
        {
            std::cout << "start改变了" << std::endl;
        }
        interval->start = begin;
        if (interval->end != end)
        {
            std::cout << "start改变了" << std::endl;
        }
        interval->end = end;
    }

    // 根据起始位置排序
    sort(intervals.begin(), intervals.end(), Interval::cmpLtStart);

    // std::ofstream file("../tests/log.txt", std::ios_base::app);
    // file << "\n*****************" << fun->getFuncName() << "***********************\n";
    // for (auto &interval : intervals)
    // {
    //     file << "def: ";
    //     file << interval->def->toStr() << "\n";
    //     file << "uses: ";
    //     for (auto &use : interval->uses)
    //     {
    //         file << use->toStr() << ", ";
    //     }
    //     file << "\n";
    //     file << "start: " << interval->start;
    //     file << ", end: " << interval->end << "\n";
    //     file << "isInit: " << interval->def->isInitArg() << std::endl;
    //     // file << "is Uncertain: " << interval->isUncertainDef << "\n";
    //     file << "-----------------\n";
    // }
}

/// @brief 插入溢出时的代码 def后使用 str, 在firstUsePos前插入ldr
/// @param inter 活跃间隔
void LinearScan::genSpillCode(IntervalPtr interSpilled)
{
    assert(!interSpilled->isPreAlloca);
    MOperaPtr &def = interSpilled->def;
    auto &uses = interSpilled->uses;
    assert(interSpilled->uses.size() != 0);

    // 产生溢出代码
    MInstPtr &defInst = def->getParent();                 // def 对应属于的指令
    MFuncPtr &curFun = defInst->getParent()->getParent(); // 当前函数

    std::unordered_set<MInstPtr> record; // 记录已经在前面插入了 load指令的指令 防止重复插入(重复插入的原因是可能两个use来自于同一条指令)
    auto &instUses = defInst->getUse();
    if (defInst->isLoad())
    {
        // def 来自load指令 要么是从内存中取数 要么是取整数
        // 因此拷贝该指令 将其加入到每一条use 前面即可 不用开辟溢出内存
        for (auto &use : uses)
        {
            MOperaPtr dst = MachineOperand::copy(defInst->getDef()[0]);
            MBlockPtr &useblk = use->getParent()->getParent(); // 需要插入指令的基本块
            if (instUses.size() == 2)
            {
                MInstPtr &atFront = use->getParent();
                if (record.find(atFront) == record.end())
                { // 无记录
                    MOperaPtr src1 = MachineOperand::copy(instUses[0]);
                    MOperaPtr offset = MachineOperand::copy(instUses[1]);
                    MLoadInstPtr ldr = MLoadInst::get(useblk, MachineInst::LDR, dst, src1, offset);
                    useblk->insertInstBefore(atFront, ldr); // 插入在使用前
                    std::cout << "插入溢出已有代码ldr: " << ldr->toStr() << std::endl;
                    if (defInst->isNeedToAdjust())
                    { // 由于是拷贝 如果 defInst需要矫正 这条拷贝的也需要矫正
                        curFun->addAdjustInst(ldr);
                    }
                    record.insert(atFront);
                }
            }
            else
            {
                assert(instUses.size() == 1);
                MInstPtr &atFront = use->getParent();
                if (record.find(atFront) == record.end())
                {
                    MOperaPtr src1 = MachineOperand::copy(instUses[0]);
                    MLoadInstPtr ldr = MLoadInst::get(useblk, MachineInst::LDR, dst, src1);
                    useblk->insertInstBefore(atFront, ldr);
                    std::cout << "插入溢出已有代码ldr: " << ldr->toStr() << std::endl;
                    if (defInst->isNeedToAdjust())
                    {
                        curFun->addAdjustInst(ldr);
                    }
                    record.insert(atFront);
                }
            }
        }
    }
    else
    {
        // 其他类型 则开辟空间
        MOperaPtr offsetImm = nullptr;
        MBlockPtr &defBlock = defInst->getParent(); // def语句对应的块
        auto findIter = vregSpillOffset.find(def->getRegNo());
        if (findIter == vregSpillOffset.end())
        {
            // 没找到相关记录 则开辟溢出空间
            int offset = -(curFun->AllocaStack(4)); // 相对于fp的 偏移
            offsetImm = MachineOperand::get(MachineOperand::IMM, offset);
            vregSpillOffset.emplace(def->getRegNo(), offsetImm); // 插入记录
            if (!Arm32::isLegalDisp(offset))
            {
                // 如果不是合法偏移 则需要使用ldr伪指令
                MOperaPtr vreg = MachineOperand::get(MachineOperand::VREG, curFun->genSpillLoadVregNo()); // 生成寄存器
                MLoadInstPtr ldr = MLoadInst::get(defBlock, MachineInst::LDR, vreg, offsetImm);
                defBlock->insertInstAfter(defInst, ldr);
                MStorePtr str = MStore::get(defBlock, MachineInst::STR, MachineOperand::copy(def), MachineOperand::createReg(11), MachineOperand::copy(vreg));
                defBlock->insertInstAfter(ldr, str);
            }
            else
            {
                // 是合法偏移
                MStorePtr str = MStore::get(defBlock, MachineInst::STR, MachineOperand::copy(def), MachineOperand::createReg(11), offsetImm);
                defBlock->insertInstAfter(defInst, str);
            }
        }
        else
        {
            // 找到相关记录 复用空间
            offsetImm = MachineOperand::copy(findIter->second);
            if (!Arm32::isLegalDisp(offsetImm->getVal()))
            {
                MOperaPtr vreg = MachineOperand::get(MachineOperand::VREG, curFun->genSpillLoadVregNo()); // 生成寄存器
                MLoadInstPtr ldr = MLoadInst::get(defBlock, MachineInst::LDR, vreg, MachineOperand::copy(offsetImm));
                defBlock->insertInstAfter(defInst, ldr);
                MStorePtr str = MStore::get(defBlock, MachineInst::STR, MachineOperand::copy(def), MachineOperand::createReg(11), MachineOperand::copy(vreg));
                defBlock->insertInstAfter(ldr, str);
            }
            else
            {
                // 偏移合法
                MStorePtr str = MStore::get(defBlock, MachineInst::STR, MachineOperand::copy(def), MachineOperand::createReg(11), MachineOperand::copy(offsetImm));
                defBlock->insertInstAfter(defInst, str);
            }
        }
        // 在def 后插入 store指令
        // MStorePtr str = MStore::get(defBlock, MachineInst::STR, MachineOperand::copy(def), MachineOperand::createReg(11), offsetImm);
        // defBlock->insertInstAfter(defInst, str);
        // 在每个 uses前插入 ldr
        for (auto &use : uses)
        {
            MInstPtr &atFront = use->getParent();
            if (record.find(atFront) == record.end())
            {
                MBlockPtr &useBlk = atFront->getParent();
                MOperaPtr dst = MachineOperand::copy(def);

                if (!Arm32::isLegalDisp(offsetImm->getVal()))
                {
                    // 偏移非法
                    MOperaPtr vreg = MachineOperand::get(MachineOperand::VREG, curFun->genSpillLoadVregNo()); // 生成寄存器
                    MLoadInstPtr ldr1 = MLoadInst::get(useBlk, MachineInst::LDR, vreg, MachineOperand::copy(offsetImm));
                    useBlk->insertInstBefore(atFront, ldr1);
                    MLoadInstPtr ldr2 = MLoadInst::get(useBlk, MachineInst::LDR, dst, MachineOperand::createReg(11), MachineOperand::copy(vreg));
                    useBlk->insertInstBefore(atFront, ldr2);
                    record.insert(atFront);
                }
                else
                {
                    MLoadInstPtr ldr = MLoadInst::get(useBlk, MachineInst::LDR, dst, MachineOperand::createReg(11), MachineOperand::copy(offsetImm));
                    useBlk->insertInstBefore(atFront, ldr);
                    std::cout << "插入溢出代码ldr: " << ldr->toStr() << std::endl;
                    record.insert(atFront);
                }
            }
        }
        std::cout << "----------------------------" << std::endl;
    }
}

/// @brief 更新寄存器池
/// @param inter
bool LinearScan::updateRegsPool(IntervalPtr inter)
{
    bool res = false;
    pool.empireOldIntervals(inter);
    if (inter->isPreAlloca)
    {
        int needReg = inter->def->getRegNo();
        bool avail = pool.isAvailable(needReg);
        if (avail)
        {
            assert(pool.isAvailable(needReg));
            pool.allocaReg(inter, needReg);
        }
        else
        {
            IntervalPtr occupy = pool.getInterval(needReg);
            assert(occupy != nullptr);
            pool.spillAtInterval(occupy); // 溢出该间隔
            assert(pool.isAvailable(needReg));
            pool.allocaReg(inter, needReg); // 分配
            int swichReg = pool.getSwitchReg(occupy);
            if (swichReg == -1)
            {
                // 没有切换的寄存器
                genSpillCode(occupy);
                res = true;
            }
            else
            {
                assert(pool.isAvailable(swichReg));
                pool.allocaReg(occupy, swichReg);
            }
        }
    }
    else
    {
        auto &canUse = pool.getRegsCanUse();
        if (!canUse.empty())
        {
            int firstReg = *(canUse.begin());
            assert(pool.isAvailable(firstReg));
            pool.allocaReg(inter, firstReg);
        }
        else
        {
            // 没有可用寄存器
            auto actvie = pool.getActive();
            sort(actvie.begin(), actvie.end(), Interval::cmpGtEnd);
            // 对于预分配的不溢出
            for (auto &occopy : actvie)
            {
                if (!occopy->isPreAlloca)
                {
                    int occupyEnd = occopy->end;
                    if (occupyEnd >= inter->end)
                    {
                        int occupyReg = occopy->reg;
                        pool.spillAtInterval(occopy);
                        genSpillCode(occopy);
                        res = true;
                        assert(pool.isAvailable(occupyReg));
                        pool.allocaReg(inter, occupyReg);
                        break;
                    }
                    else
                    {
                        genSpillCode(inter);
                        res = true;
                        break;
                    }
                }
            }
        }
    }

    // std::vector<int> occopyRegs;

    return res;
}

/// @brief 线性扫描 进行寄存器 分配 一个 epoch 返回 true 则表示 fun分配完毕
/// @param fun
/// @return 是否所有 interval 都分配完毕 没有溢出
bool LinearScan::LinearScanPassEpoch(MFuncPtr fun)
{
    bool res = true;
    pool.resetRegsPool();
    intervals.clear();
    defUseChains.clear(); // 清空这些 因为插入溢出后 迭代结果不一样
    // 计算def-use chain
    computeDefUseChain(fun);
    std::cout << "计算完毕def-use chian" << std::endl;
    // 计算活跃间隔
    computeIntervals(fun);
    for (auto &inter : intervals)
    {
        bool temp = updateRegsPool(inter); // 是否有溢出 true
        res = res && (!temp);
    }
    return res;
}

/// @brief 将活跃间隔中的def use 虚拟寄存器操作数 映射为对应的物理寄存器
/// @param inter
void LinearScan::MapIntervalToReg(IntervalPtr inter)
{

    std::cout << inter->def->toStr() << std::endl;
    std::cout << "start: " << inter->start << " end: " << inter->end << std::endl;

    assert(inter->reg != -1);

    std::cout << "--------------reg 是:" << inter->reg << std::endl;
    std::cout << "----------------- isPreAlloca: " << inter->isPreAlloca << std::endl;
    inter->def->setReg(inter->reg);
    std::cout << "def reg:------------------:" << -inter->def->getRegNo() << std::endl;
    for (auto &use : inter->uses)
    {
        use->setReg(inter->reg);
        assert(inter->reg != -1);
        assert(use->getRegNo() != -1);
        std::cout << "use reg:------------------:" << use->getRegNo() << std::endl;
    }
}

/// @brief 寄存器分配
void LinearScan::allocateReg()
{
    std::vector<MFuncPtr> &funList = machineModule->getFuncList();
    for (auto &fun : funList)
    {
        std::cout << fun->getFuncName() << std::endl;
        bool issucces = false;
        // dealWithVregsAndRealRegs(fun);
        // computeIntervals(fun);
        vregSpillOffset.clear(); // 清空前一个函数的记录
        while (!issucces)
        {
            issucces = LinearScanPassEpoch(fun);
            std::cout << "false!" << std::endl;
        }
        // std::cout << fun->getFuncName() << std::endl;
        // 成功后 为每个interval设置好对应的物理寄存器
        for (auto &inter : intervals)
        {
            // assert(inter->end >= inter->start);

            // if (inter->end == inter->start)
            // {
            //     std::cout << "end==start" << inter->end << std::endl;
            // }

            MapIntervalToReg(inter);
            // 添加 savedRegs
            if (inter->reg > 3)
            {
                fun->addSaveReg(inter->reg);
            }
            // std::cout << fun->getFuncName() << std::endl;
            // std::cout << "alloca interval" << std::endl;
        }
        // std::cout << fun->getFuncName() << std::endl;
    }
}
