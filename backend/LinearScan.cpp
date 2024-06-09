/**
 * @file LinearScan.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 使用线性扫描进行寄存器分配 声明：实现参考学习自2023编译实现赛中南开大学212相关代码，但不完全
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

    std::ofstream file("../tests/log_line.txt", std::ios_base::app);
    file << "\n*****************" << fun->getFuncName() << "***********************\n";
    for (auto &blk : blockList)
    {
        for (auto &inst : blk->getInstList())
        {
            file << "line: ";
            file << std::to_string(inst->getNo()) << " ";
            file << inst->toStr() << "\n";
        }
    }
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
            intervals.insert(inter);
        }
        else
        {
            // 物理寄存器 r0-r3
            assert(def->getRegNo() >= 0 && def->getRegNo() <= 3);
            IntervalPtr inter = Interval::get(def, uses, true);
            intervals.insert(inter);
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
    bool change;
    change = true;
    while (change)
    {
        change = false;
        // std::vector<Interval *> t(intervals.begin(), intervals.end());
        // for (size_t i = 0; i < intervals.size(); i++)
        //     for (size_t j = i + 1; j < intervals.size(); j++)
        for (auto it1 = intervals.begin(); it1 != intervals.end(); it1++)
            for (auto it2 = std::next(it1); it2 != intervals.end(); it2++)
            {
                IntervalPtr w1 = *it1;
                IntervalPtr w2 = *it2;

                if (*(w1->def) == *(w2->def))
                {
                    std::set<MOperaPtr> temp;
                    std::set_intersection(w1->uses.begin(), w1->uses.end(), w2->uses.begin(), w2->uses.end(), inserter(temp, temp.end()));
                    if (!temp.empty())
                    {
                        change = true;
                        // w1->defs.insert(w2->defs.begin(), w2->defs.end());
                        // w1->uses.insert(w2->uses.begin(), w2->uses.end());
                        // // w1->start = std::min(w1->start, w2->start);
                        // // w1->end = std::max(w1->end, w2->end);
                        // auto w1Min = std::min(w1->start, w1->end);
                        // auto w1Max = std::max(w1->start, w1->end);
                        // auto w2Min = std::min(w2->start, w2->end);
                        // auto w2Max = std::max(w2->start, w2->end);
                        // w1->start = std::min(w1Min, w2Min);
                        // w1->end = std::max(w1Max, w2Max);
                        // // auto it = std::find(intervals.begin(), intervals.end(), w2);
                        // // if (it != intervals.end())
                        // //     intervals.erase(it);
                        // it2 = intervals.erase(it2);
                        // it2--;
                        std::cout << "检测到交汇值-----------------------------------" << std::endl;
                        assert(0);
                    }
                }
            }
    }

    std::ofstream file("../tests/log.txt", std::ios_base::app);
    file << "\n*****************" << fun->getFuncName() << "***********************\n";
    for (auto &interval : intervals)
    {
        file << "def: ";
        file << interval->def->toStr() << "\n";
        file << "uses: ";
        for (auto &use : interval->uses)
        {
            file << use->toStr() << ", ";
        }
        file << "\n";
        file << "start: " << interval->start;
        file << ", end: " << interval->end << "\n";
        file << "isInit: " << interval->def->isInitArg() << std::endl;
        // file << "is Uncertain: " << interval->isUncertainDef << "\n";
        file << "-----------------\n";
    }
}

/// @brief 从当前 active表中释放可以结束的间隔
/// @param curInter
void LinearScan::freeRegsfromActive(IntervalPtr curInter)
{
    int start = curInter->start;
    for (auto riter = active.rbegin(); riter != active.rend();)
    {
        // 从后往前遍历 因为 active按照结束位置从小到达存放
        if ((*riter)->end < start)
        {
            auto iter = std::prev(riter.base()); // 获取正序迭代器
            // 恢复 该 internal 占用的寄存器
            regs.insert((*riter)->reg);
            oldTime.emplace((*riter)->reg, (*riter)->end); // 旧时间线已经确认使用的寄存器
            std::cout << "结束间隔: \n"
                      << (*riter)->def->toStr() << " start: " << (*riter)->start << " end: " << (*riter)->end << " 分配的寄存器: " << (*riter)->reg << std::endl;
            active.erase(iter);
        }
        else if ((*riter)->end == start)
        {
            if ((*riter)->uses.size() == 0)
            {
                // 说明 (*riter)->end 为 def 现在无法释放
                riter++;
            }
            else
            {
                // 不为0  说明是 use 可以释放
                auto iter = std::prev(riter.base()); // 获取正序迭代器
                // 恢复 该 internal 占用的寄存器
                regs.insert((*riter)->reg);
                oldTime.emplace((*riter)->reg, (*riter)->end); // 旧时间线已经确认使用的寄存器
                std::cout << "结束间隔: \n"
                          << (*riter)->def->toStr() << " start: " << (*iter)->start << " end: " << (*iter)->end << " 分配的寄存器:" << (*iter)->reg << std::endl;
                active.erase(iter);
            }
        }
        else
        {
            break;
        }
    }
}

/// @brief 自动处理冲突(和active表中已经分配寄存器的活跃间隔比较)  如果有的话 自动更新active表
/// @param curInter 当前扫描的活跃间隔
void LinearScan::AutoUpdateActive(IntervalPtr curInter)
{
    freeRegsfromActive(curInter); // 先释放可以释放的寄存器
    // 查看当前 寄存器池中是否有寄存器可用 如果没有 则查找冲突 溢出本身或者溢出其他间隔
    if (curInter->isPreAlloca)
    {
        // 间隔需要指定的寄存器
        int needRegNo = curInter->def->getRegNo();
        auto iter = regs.find(needRegNo);
        if (iter != regs.end())
        {
            // 能找到 该寄存器 则分配
            curInter->reg = needRegNo;
            regs.erase(needRegNo);
            std::cout << "插入间隔: \n"
                      << curInter->def->toStr() << "start: " << curInter->start << " end: " << curInter->end << " 占用寄存器:" << needRegNo << std::endl;

            active.insert(curInter);
        }
        else
        {
            // 需要的寄存器目前不可用 查找 active表中占用该寄存器的间隔
            // 经过一定设计 预分配的r0-r3物理寄存器间是不会有冲突的 基本上一定是只有一条def语句
            for (auto iter = active.begin(); iter != active.end(); iter++)
            {
                if ((*iter)->reg == needRegNo)
                {
                    std::cout << "active中的def:" << (*iter)->def->toStr() << std::endl;
                    std::cout << "active中的use数目:" << (*iter)->uses.size() << std::endl;
                    std::cout << "start:" << (*iter)->start << std::endl;
                    std::cout << "end:" << (*iter)->end << std::endl;
                    std::cout << "是否是init:" << (*iter)->def->isInitArg() << std::endl;

                    std::cout << "当前的def:" << curInter->def->toStr() << std::endl;
                    std::cout << "curInter中的use数目:" << curInter->uses.size() << std::endl;
                    std::cout << "start:" << curInter->start << std::endl;
                    std::cout << "end:" << curInter->end << std::endl;
                    std::cout << "是否是init:" << curInter->def->isInitArg() << std::endl;

                    assert(!(*iter)->isPreAlloca);
                    if (!regs.empty())
                    {
                        // 更换寄存器 更换时不能使用已经结束间隔的寄存器
                        // auto first = *(regs.begin());
                        // (*iter)->reg = first;
                        std::set<int> canSwitchRegs; // 可以更换的寄存器
                        for (auto reg : regs)
                        {
                            auto find = oldTime.find(reg);
                            if (find == oldTime.end())
                            {
                                // 没找到相关记录 说明该寄存器还不被使用过
                                canSwitchRegs.insert(reg);
                            }
                            else
                            {
                                // 查找到了 说明用过 但已经结束
                                if (find->second <= (*iter)->start)
                                { // 使用无重叠
                                    canSwitchRegs.insert(reg);
                                }
                            }
                        }
                        if (!canSwitchRegs.empty())
                        {
                            // 有可以切换的寄存器
                            auto first = *(canSwitchRegs.begin());
                            regs.erase(first);
                            curInter->reg = needRegNo;
                            active.insert(curInter);
                            break;
                        }
                        else
                        {
                            // 没有可以切换的寄存器 溢出该间隔
                            (*iter)->reg = -1;
                            successAllocaRegs = false;
                            genSpillCode((*iter));
                            curInter->reg = needRegNo;
                            active.erase(iter); // 删除该间隔
                            active.insert(curInter);
                            break;
                        }
                    }
                    else
                    {
                        // 如果没有寄存器可用 则溢出该间隔
                        (*iter)->reg = -1;
                        successAllocaRegs = false;
                        genSpillCode((*iter)); // 产生溢出代码
                        curInter->reg = needRegNo;
                        active.erase(iter);
                        active.insert(curInter);
                        break;
                    }
                }
            }
        }
    }
    else
    {
        // 不是预分配 是虚拟寄存器
        if (!regs.empty())
        {
            // 还有寄存器可用
            auto first = *(regs.begin());
            curInter->reg = first;
            regs.erase(first);
            std::cout << "插入间隔：" << curInter->def->toStr() << " start: " << curInter->start << " end: " << curInter->end << " 占用的寄存器:" << first << std::endl;

            active.insert(curInter);
        }
        else
        {
            // 没有寄存器可用
            for (auto iter = active.begin(); iter != active.end(); iter++)
            {
                if (!(*iter)->isPreAlloca)
                {
                    // 预分配的不可溢出
                    if (curInter->end > (*iter)->end)
                    {
                        // 溢出当前
                        successAllocaRegs = false;
                        curInter->reg = -1;
                        std::cout << "溢出间隔: \n"
                                  << "start: " << curInter->start << " end: " << curInter->end << std::endl;

                        genSpillCode(curInter);
                        break;
                    }
                    else
                    {
                        // 溢出该间隔
                        successAllocaRegs = false;
                        int regno = (*iter)->reg;
                        (*iter)->reg = -1;

                        std::cout << "溢出间隔: \n"
                                  << "start: " << (*iter)->start << " end: " << (*iter)->end << std::endl;

                        std::cout << "插入间隔: \n"
                                  << "start: " << curInter->start << " end: " << curInter->end << std::endl;
                        genSpillCode(*iter);
                        curInter->reg = regno;
                        active.erase(iter);
                        active.insert(curInter);
                        break;
                    }
                }
            }
        }
    }
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

    std::unordered_set<MInstPtr> record; // 记录已经在前面插入了 load指令的指令 防止重复插入
    auto &instUses = defInst->getUse();
    bool canReuse = true;
    // if (defInst->isLoad())
    // {
    //     // def 来自load指令 要么是从内存中取数 要么是取整数
    //     // 因此拷贝该指令 将其加入到每一条use 前面即可 不用开辟溢出内存
    //     for (auto &use : uses)
    //     {
    //         MOperaPtr dst = MachineOperand::copy(defInst->getDef()[0]);
    //         MBlockPtr &useblk = use->getParent()->getParent(); // 需要插入指令的基本块
    //         if (instUses.size() == 2)
    //         {
    //             MInstPtr &atFront = use->getParent();
    //             if (record.find(atFront) == record.end())
    //             { // 无记录
    //                 MOperaPtr src1 = MachineOperand::copy(instUses[0]);
    //                 MOperaPtr offset = MachineOperand::copy(instUses[1]);
    //                 MLoadInstPtr ldr = MLoadInst::get(useblk, MachineInst::LDR, dst, src1, offset);
    //                 useblk->insertInstBefore(atFront, ldr); // 插入在使用前
    //                 std::cout << "插入溢出已有代码ldr: " << ldr->toStr() << std::endl;
    //                 if (defInst->isNeedToAdjust())
    //                 { // 由于是拷贝 如果 defInst需要矫正 这条拷贝的也需要矫正
    //                     curFun->addAdjustInst(ldr);
    //                 }
    //                 record.insert(atFront);
    //             }
    //         }
    //         else
    //         {
    //             assert(instUses.size() == 1);
    //             MInstPtr &atFront = use->getParent();
    //             if (record.find(atFront) == record.end())
    //             {
    //                 MOperaPtr src1 = MachineOperand::copy(instUses[0]);
    //                 MLoadInstPtr ldr = MLoadInst::get(useblk, MachineInst::LDR, dst, src1);
    //                 useblk->insertInstBefore(atFront, ldr);
    //                 std::cout << "插入溢出已有代码ldr: " << ldr->toStr() << std::endl;
    //                 if (defInst->isNeedToAdjust())
    //                 {
    //                     curFun->addAdjustInst(ldr);
    //                 }
    //                 record.insert(atFront);
    //             }
    //         }
    //     }
    // }
    // else
    // {
    // 其他类型 则开辟空间
    MOperaPtr offsetImm = nullptr;
    auto findIter = vregSpillOffset.find(def->getRegNo());
    if (findIter == vregSpillOffset.end())
    {
        // 没找到相关记录 则开辟溢出空间
        int offset = -(curFun->AllocaStack(4)); // 相对于fp的 偏移
        offsetImm = MachineOperand::get(MachineOperand::IMM, offset);
        offsetImm = MachineOperand::AutoDealWithImm(offsetImm, machineModule, true);
        vregSpillOffset.emplace(def->getRegNo(), offsetImm); // 插入记录
    }
    else
    {
        // 找到相关记录 复用空间
        offsetImm = MachineOperand::copy(findIter->second);
    }
    // 在def 后插入 store指令
    MBlockPtr &defBlock = defInst->getParent(); // def语句对应的块
    MStorePtr str = MStore::get(defBlock, MachineInst::STR, MachineOperand::copy(def), MachineOperand::createReg(11), offsetImm);
    defBlock->insertInstAfter(defInst, str);
    // 在每个 uses前插入 ldr
    for (auto &use : uses)
    {
        MInstPtr &atFront = use->getParent();
        if (record.find(atFront) == record.end())
        {
            MBlockPtr &useBlk = atFront->getParent();
            MOperaPtr dst = MachineOperand::copy(def);
            MLoadInstPtr ldr = MLoadInst::get(useBlk, MachineInst::LDR, dst, MachineOperand::createReg(11), MachineOperand::copy(offsetImm));
            useBlk->insertInstBefore(atFront, ldr);
            std::cout << "插入溢出代码ldr: " << ldr->toStr() << std::endl;
            record.insert(ldr);
        }
    }
    // }
}

/// @brief 线性扫描 进行寄存器 分配 一个 epoch 返回 true 则表示 fun分配完毕
/// @param fun
/// @return 是否所有 interval 都分配完毕 没有溢出
bool LinearScan::LinearScanPassEpoch(MFuncPtr fun)
{
    intervals.clear();
    active.clear();
    defUseChains.clear(); // 清空这些 因为插入溢出后 迭代结果不一样
    successAllocaRegs = true;
    oldTime.clear();
    initAvailableRegsPool(); // 初始化可用寄存器池
    // 计算def-use chain
    computeDefUseChain(fun);
    std::cout << "计算完毕def-use chian" << std::endl;
    // 计算活跃间隔
    computeIntervals(fun);

    // 自动更新  active表
    for (auto &inter : intervals)
    {
        // std::cout << "def: ";
        // std::cout << inter->def->toStr() << std::endl;
        // std::cout << "uses size: " << inter->uses.size() << std::endl;
        AutoUpdateActive(inter);
    }
    return successAllocaRegs;
}

/// @brief 将活跃间隔中的def use 虚拟寄存器操作数 映射为对应的物理寄存器
/// @param inter
void LinearScan::MapIntervalToReg(IntervalPtr inter)
{

    std::cout << inter->def->toStr() << std::endl;
    std::cout << "start: " << inter->start << " end: " << inter->end << std::endl;

    assert(inter->reg != -1);

    inter->def->setReg(inter->reg);
    for (auto &use : inter->uses)
    {
        use->setReg(inter->reg);
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
