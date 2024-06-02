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

/// @brief 处理虚拟寄存器 和物理寄存器(对于虚拟寄存器产生def-use(简单，一个虚拟寄存器只会def一次))
/// @brief 对于物理寄存器根据活跃变量分析获取对应的活跃区间间隔 供后继使用你
/// @param fun
void LinearScan::dealWithVregsAndRealRegs(MFuncPtr fun)
{
    defUseChains.clear();
    // 先计算这个函数的liveIn  liveOut
    ActiveVariAnalysis LiveAnalysis;
    LiveAnalysis.computeLiveVariInfun(fun);
    /*
    根据 IR相关的设计 以指针地址作为一个value的唯一标识 对于一个MachineOperand
    (同一虚拟寄存器编号 他只会def一次 之后是使用 因此获取函数fun的 AllUses 进行查找相应的def 即可获取 def-use chain)
    遍历fun 获取 def-use chain 同时对指令进行编号
    */
    // fun 中 AllUsesInFun 列表记录
    auto &allUsesOfFun = LiveAnalysis.AllUsesInfun;
    std::list<MBlockPtr> &blockList = fun->getBlockList();

    // 用于记录物理寄存器 在每个block的出口活跃记录(按照名字分类)
    std::map<MachineOperand, std::set<MOperaPtr>> liveRealReg;

    // 记录物理寄存器的 容器 该容器记录了 物理寄存器def-use chain(可以没有def 有些时候没有显式def指令 如函数中直接使用r0-r3形参)
    std::multiset<MOperaPtr, cmpUsePosLt> RealRegsusefiled;

    // 记录 RealRegsusefild 的列表
    std::vector<std::multiset<MOperaPtr, cmpUsePosLt>> RelRegsRecord;

    // 编写一个Lamda 函数 实现 liveRealReg 插入到 RealRegsusfile
    auto insertFiled = [&](MOperaPtr def = nullptr)
    {
        if (def != nullptr)
        {
            RealRegsusefiled.insert(def);
            for (auto &elem : liveRealReg[*def])
            {
                RealRegsusefiled.insert(elem);
            }
            // 插入完毕   放入 RelRegsRecord列表中
            RelRegsRecord.push_back(RealRegsusefiled);
            RealRegsusefiled.clear(); // 清空供下次使用
        }
        else
        {
            // def 为空 可能是没有显式def  如函数中直接使用形参的 r0-r3 没有显式def指令
            for (auto &elem : liveRealReg)
            {
                for (auto &reg : elem.second)
                {
                    RealRegsusefiled.insert(reg);
                }
                if (RealRegsusefiled.size() > 0)
                {
                    // 有元素
                    RelRegsRecord.push_back(RealRegsusefiled);
                    RealRegsusefiled.clear();
                }
            }
        }
    };

    int instNo = 0; // 设置编号
    int i = 0;      // 每个块末尾的编号
    for (auto &blk : blockList)
    {
        liveRealReg.clear(); // 更换block时清空
        for (auto &live : blk->getLiveOut())
        {
            if (live->isReg())
            {
                // 记录出口活跃的物理寄存器对象 只记录 r0,r1,r2,r3
                if (live->getRegNo() >= 0 && live->getRegNo() <= 3)
                    liveRealReg[*live].insert(live);
            }
        }

        std::list<MInstPtr> &instList = blk->getInstList();
        i = instList.size() + i; // 当前块 末尾的编号
        instNo = i;              // 当前指令编号

        // 由于 物理寄存器会有多次def 因此逆序遍历指令列表
        for (auto riter = instList.rbegin(); riter != instList.rend(); riter++)
        {
            auto &inst = *riter;
            inst->setNo(instNo--);
            auto &defs = inst->getDef();
            for (auto &def : defs)
            {
                // 对于虚拟寄存器直接加入即可 因为只def一次
                if (def->isVReg())
                { // vreg 只被def 一次后继可以use 也可以没有  所以可以这样简单写
                    defUseChains[def].insert(allUsesOfFun[*def].begin(), allUsesOfFun[*def].end());
                }
                if (def->isReg() && def->getRegNo() >= 0 && def->getRegNo() <= 3)
                { // 只记录 r0-r3
                    // 处理物理寄存器 并获取其活跃间隔 加入到Active已分配表中
                    // 物理寄存器不太方便获取 def-use chain 因为有时没有显式的def语句
                    auto &uses = liveRealReg[*def];
                    auto &allusesReg = LiveAnalysis.getAllUsesInfun()[*def];
                    // 有 def 有 uses 构成def use chain
                    insertFiled(def); // 定义的 Lamda函数 在前面定义了
                    // 有def 有 uses 当前 def-use chain已结束 清理 供下次使用
                    RealRegsusefiled.clear();
                    // 更新 liveRealReg[*def]为空  (当前use已经和def相联系了 前面指令def的物理寄存器在之后的use不可见)
                    liveRealReg.erase(*def); // 删除该键值对
                }
            }
            for (auto &use : inst->getUse())
            {
                // 遍历use  只记录 r0-r3
                if (use->isReg() && use->getRegNo() >= 0 && use->getRegNo() <= 3)
                {
                    // 插入使用变量 (可能和上逆序上前的指令的def 形成 def-use chain)
                    liveRealReg[*use].insert(use);
                }
            }
        }
        // 该基本块逆序遍历完毕后 看liveRealReg是否为空(如果某些物理寄存器的use 找不到显式的def 则会出现这种情况)
        insertFiled(nullptr); // 使用前面定义的Lamda函数
    }
    // 函数所有块都遍历完毕后 将RelRegsRecord 遍历产生 物理寄存器的Interval 并加其加入Active表中
    for (auto &elem : RelRegsRecord)
    {
        assert(elem.size() > 0);
        auto iterBegin = elem.begin();
        auto iterEnd = elem.rbegin();
        // 直接使用最后一个和最前一个是因为 multiset已经根据使用位置从小到大排序了
        int start = (*iterBegin)->getParent()->getNo();
        int end = (*iterEnd)->getParent()->getNo();
        // 创建interval
        IntervalPtr relRegInterval = Interval::get(start, end, true);
        relRegInterval->reg = (*iterBegin)->getRegNo(); // 设置物理寄存器编号
        regs.erase(relRegInterval->reg);                // 从寄存器池中删除该寄存器 变为使用状态
        // 插入active表中
        active.insert(relRegInterval);
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
        if (defUse.first->isVReg())
        {
            // 获取 InterVal的 start end
            uint32_t start = defUse.first->getParent()->getNo();
            uint32_t end = start;
            if (defUse.second.size() > 0)
            {
                end = (*defUse.second.rbegin())->getParent()->getNo();
            }
            IntervalPtr interval = Interval::get(start, end, defUse.first, defUse.second);
            // 加入到 Intervals中
            intervals.insert(interval);
        }
    }
}

/// @brief 获取溢出位置 如果无溢出 返回nullptr
/// @param inter1 注意是在active表中的
/// @param inter2
/// @return 返回 没溢出的最后一条use 以及溢出的第一条use
std::pair<MInstPtr, MInstPtr> LinearScan::computeSpillPos(IntervalPtr inter1InActive, IntervalPtr inter2)
{
    int end1 = inter1InActive->end;
    int start2 = inter2->start;
    std::pair<MInstPtr, MInstPtr> res;
    res.first = inter1InActive->def->getParent();
    res.second = nullptr;
    if (end1 > start2)
    {
        // 会有冲突 下面计算获取 inter1InActive中的冲突点 供后继 产生溢出代码时使用
        // 查找 uses中 使用位置 >= start2的操作数对应指令的 编号位置
        MInstPtr pre = nullptr;
        for (auto &use : inter1InActive->uses)
        {
            int pos = use->getParent()->getNo();
            if (pos > start2)
            {
                res.second = use->getParent();
                break;
            }
        }
    }
    return res;
}

/// @brief 自动处理冲突(和active表中已经分配寄存器的活跃间隔比较)  如果有的话 自动更新active表
/// @param curInter 当前扫描的活跃间隔
void LinearScan::AutoUpdateActive(IntervalPtr curInter)
{
    int start = curInter->start;
    // 删除 生命周期在当前start前结束的活跃间隔 并返回寄存器为可用状态
    for (auto riter = active.rbegin(); riter != active.rend();)
    {
        // 逆序遍历  因为active按照end的大小 从大到小排列
        if ((*riter)->end <= start)
        {
            auto iter = std::prev(riter.base()); // 获取正序迭代器
            // 恢复 该 internal 占用的寄存器
            regs.insert((*riter)->reg);
            active.erase(iter);
        }
        else
        {
            break; // 之后的无需遍历 因为multiset已经排序
        }
    }
    // 在处理完上面的基础上 对 curInster尝试寄存器分配
    // 如果 当前 寄存器池中有可用的寄存器则进行分配即可 分配后 将curInter插入active 表中
    // 自动处理冲突  则选择 终点 end最后的地方的interval进行溢出 并产生溢出处理代码
    if (regs.size() > 0)
    {
        // 还有寄存器 分配寄存器 将 curInter插入Active中
        // auto last = regs.rbegin(); // 取最后一个寄存器使用
        // curInter->reg = *(regs.rbegin());
        // active.insert(curInter);
        // regs.erase(curInter->reg); // 从寄存器池中删除

        // 2. 从最小的 开始取
        auto first = regs.begin();
        curInter->reg = *(first);
        active.insert(curInter);
        regs.erase(curInter->reg);
    }
    else
    {
        // 没有寄存器可用 则有冲突 选择 end最后 生命周期最长的interval删除溢出
        auto first = active.begin();
        if ((*first)->isPreAlloca)
        {
            // 预分配的不能溢出
            // 迭代得到下一个 虚拟寄存器的 活跃间隔（multiset已经排序）
            auto next = std::next(first);
            while (next != active.end())
            {
                if ((*next)->isPreAlloca)
                {
                    next = std::next(next);
                }
            }
            first = next;
        }
        IntervalPtr spillInterval = (*first);
        spillInterval->spill = true;
        int regNo = spillInterval->reg;
        curInter->reg = regNo;
        active.erase(first);       // 删除溢出的intervcal
        active.insert(curInter);   // 插入分配寄存器的interval
        successAllocaRegs = false; // 有冲突 会有溢出
        // 计算 溢出位置 并插入溢出处理代码
        std::pair<MInstPtr, MInstPtr> spillInstPos = computeSpillPos(spillInterval, curInter);
        genSpillCode(spillInterval, spillInstPos);
    }
}

/// @brief 插入溢出时的代码 def后使用 str, 在firstUsePos前插入ldr
/// @param inter 活跃间隔
/// @param pos pos的第一 第二个元素对应  插入 str  ldr指令的位置
void LinearScan::genSpillCode(IntervalPtr interSpilled, std::pair<MInstPtr, MInstPtr> &pos)
{
    // 首先需要在 def 之后插入 str指令 保存旧值
    MOperaPtr &def = interSpilled->def;
    MInstPtr &defInst = def->getParent();
    MBlockPtr &blk = defInst->getParent();
    MFuncPtr &fun = blk->getParent();
    // 创建插入指令  def 一定时vreg
    int offset = -(fun->AllocaStack(4)); // 相对于fp的 偏移
    MOperaPtr offsetImm = MachineOperand::get(MachineOperand::IMM, offset);
    offsetImm = MachineOperand::AutoDealWithImm(offsetImm, machineModule, true);
    MStorePtr str = MStore::get(blk, MachineInst::STR, MachineOperand::copy(def), MachineOperand::createReg(11), offsetImm);

    // 在 指定指令后插入str指令保存寄存器旧值
    blk->insertInstAfter(pos.first, str);

    // 创建 ldr 指令
    MOperaPtr vreg = MachineOperand::get(MachineOperand::VREG, fun->genSpillLoadVregNo()); // 从栈内存中加载位置虚拟寄存器
    MLoadInstPtr ldr = MLoadInst::get(blk, MachineInst::LDR, vreg, MachineOperand::createReg(11), MachineOperand::copy(offsetImm));
    // 插入指定位置之前
    blk->insertInstBefore(pos.second, ldr);
}

/// @brief 线性扫描 进行寄存器 分配 一个 epoch 返回 true 则表示 fun分配完毕
/// @param fun
/// @return 是否所有 interval 都分配完毕 没有溢出
bool LinearScan::LinearScanPassEpoch(MFuncPtr fun)
{
    intervals.clear();
    active.clear();
    defUseChains.clear();
    successAllocaRegs = true;
    initAvailableRegsPool(); // 初始化可用寄存器池
    // 计算def-use chain
    dealWithVregsAndRealRegs(fun);
    // 计算活跃间隔
    computeIntervals(fun);
    // 自动更新  active表
    for (auto &inter : intervals)
    {
        AutoUpdateActive(inter);
    }
    return successAllocaRegs;
}

/// @brief 将活跃间隔中的def use 虚拟寄存器操作数 映射为对应的物理寄存器
/// @param inter
void LinearScan::MapIntervalToReg(IntervalPtr inter)
{
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
        bool issucces = false;
        while (!issucces)
        {
            issucces = LinearScanPassEpoch(fun);
        }
        // 成功后 为每个interval设置好对应的物理寄存器
        for (auto &inter : intervals)
        {
            MapIntervalToReg(inter);
            // 添加 savedRegs
            if (inter->reg > 3)
            {
                fun->addSaveReg(inter->reg);
            }
        }
    }
}