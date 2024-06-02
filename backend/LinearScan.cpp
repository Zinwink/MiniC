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

/// @brief 计算def-use Chain
/// @param fun
void LinearScan::genDefUseChains(MFuncPtr fun)
{
    defUseChains.clear();
    // 先计算这个函数的liveIn  liveOut
    ActiveVariAnalysis LiveAnalysis;
    LiveAnalysis.computeAllUsesInfun(fun); // 根据 IR相关的设计 以指针地址作为一个value的唯一标识 对于一个MachineOperand(同一虚拟寄存器编号 他只会def一次 之后是使用 因此获取函数fun的 AllUses 进行查找相应的def 即可获取 def-use chain)
    // 遍历fun 获取 def-use chain 同时对指令进行编号
    auto &allUsesOfFun = LiveAnalysis.AllUsesInfun; // fun 中 AllUsesInFun 列表记录

    for (auto &elem : allUsesOfFun)
    {
        std::cout << "key:" << (elem.first).toStr() << std::endl;
        for (auto &op : elem.second)
        {
            std::cout << "value:" << op->toStr() << std::endl;
        }
    }

    std::list<MBlockPtr> &blockList = fun->getBlockList();
    int instNo = 0; // 设置编号
    for (auto &blk : blockList)
    {
        std::list<MInstPtr> &instList = blk->getInstList();
        for (auto &inst : instList)
        {
            inst->setNo(instNo++);
            auto &defs = inst->getDef();
            for (auto &def : defs)
            {
                defUseChains[def].insert(allUsesOfFun[*def].begin(), allUsesOfFun[*def].end());
            }
        }
    }
}

/// @brief 计算活跃间隔
/// @param fun
void LinearScan::computeIntervals(MFuncPtr fun)
{
    intervals.clear();
    // 根据def-Use chain 获取 interval;

    std::cout << "def use chain------" << std::endl;
    for (auto &defUse : defUseChains)
    {
        std::cout << "def:" << defUse.first->toStr();
        std::cout << " is vreg: " << defUse.first->isVReg();
        std::cout << "line: " << defUse.first->getParent()->getNo() << std::endl;
        for (auto &use : defUse.second)
        {
            std::cout << "use:" << use->toStr() << std::endl;
            std::cout << " line: " << use->getParent()->getNo() << std::endl;
            std::cout << "def==Use: " << (use == defUse.first) << std::endl;
        }
    }

    for (auto &defUse : defUseChains)
    {
        if (defUse.first->isVReg())
        {
            // 获取 InterVal的 start end
            uint32_t start = defUse.first->getParent()->getNo();
            uint32_t end = 0;
            end = (*defUse.second.rbegin())->getParent()->getNo();
            IntervalPtr interval = Interval::get(start, end, defUse.first, defUse.second);
            // 加入到 Intervals中
            intervals.insert(interval);
        }
    }

    std::cout << "intervals:------" << std::endl;
    for (auto &interval : intervals)
    {
        std::cout << "def: " << interval->def->toStr() << std::endl;
        for (auto &use : interval->uses)
        {
            std::cout << "uses:" << use->toStr() << std::endl;
        }
        std::cout << "start: " << interval->start << std::endl;
        std::cout << "end: " << interval->end << std::endl;
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
    res.first = nullptr;
    res.second = nullptr;
    if (end1 > start2)
    {
        // 会有冲突 下面计算获取 inter1InActive中的冲突点 供后继 产生溢出代码时使用
        // 查找 uses中 使用位置 >= start2的操作数对应指令的 编号位置
        for (auto &use : inter1InActive->uses)
        {
            int pos = use->getParent()->getNo();
            res.first = use->getParent(); // str 的位置是溢出use对应指令的前一条指令
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
            break; // 之后的无需遍历
        }
    }
    // 在处理完上面的基础上 对 curInster尝试寄存器分配
    // 如果 当前 寄存器池中有可用的寄存器则进行分配即可 分配后 将curInter插入active 表中
    // 自动处理冲突  则选择 终点 end最后的地方的interval进行溢出 并产生溢出处理代码
    if (regs.size() > 0)
    {
        // 还有寄存器 分配寄存器 将 curInter插入Active中
        auto last = regs.rbegin(); // 取最后一个寄存器使用
        curInter->reg = *(regs.rbegin());
        active.insert(curInter);
        regs.erase(std::prev(last.base())); // 从寄存器池中删除
    }
    else
    {
        // 没有寄存器可用 则有冲突 选择 end最后 生命周期最长的interval删除溢出
        auto first = active.begin();
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
    genDefUseChains(fun);
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
            fun->addSaveReg(inter->reg);
        }
    }
}