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
        inter->start = _def->getParent()->getNo();
        inter->end = inter->start;
        if (inter->uses.size() > 0)
        {
            auto riter = inter->uses.rbegin();
            inter->end = std::max(inter->end, (int)(*riter)->getParent()->getNo());
        }
    }
    return inter;
}

//************************************ LinearScan ********************************************************

// /// @brief 处理虚拟寄存器 和物理寄存器(对于虚拟寄存器产生def-use(简单，一个虚拟寄存器只会def一次))
// /// @brief 对于物理寄存器根据活跃变量分析获取对应的活跃区间间隔 供后继使用你
// /// @param fun
// void LinearScan::dealWithVregsAndRealRegs(MFuncPtr fun)
// {
//     defUseChains.clear();
//     // 先计算这个函数的liveIn  liveOut
//     ActiveVariAnalysis LiveAnalysis;
//     LiveAnalysis.computeLiveVariInfun(fun);
//     /*
//     根据 IR相关的设计 以指针地址作为一个value的唯一标识 对于一个MachineOperand
//     (同一虚拟寄存器编号 他只会def一次 之后是使用 因此获取函数fun的 AllUses 进行查找相应的def 即可获取 def-use chain)
//     遍历fun 获取 def-use chain 同时对指令进行编号
//     */
//     // fun 中 AllUsesInFun 列表记录
//     auto &allUsesOfFun = LiveAnalysis.AllUsesInfun;
//     std::list<MBlockPtr> &blockList = fun->getBlockList();

//     // 用于记录物理寄存器 在每个block的出口活跃记录(按照名字分类)
//     std::map<MachineOperand, std::set<MOperaPtr>> liveRealReg;

//     // 记录物理寄存器的 容器 该容器记录了 物理寄存器def-use chain(可以没有def 有些时候没有显式def指令 如函数中直接使用r0-r3形参)
//     std::multiset<MOperaPtr, cmpUsePosLt> RealRegsusefiled;

//     // 记录 RealRegsusefild 的列表
//     std::vector<std::multiset<MOperaPtr, cmpUsePosLt>> RelRegsRecord;

//     // 编写一个Lamda 函数 实现 liveRealReg 插入到 RealRegsusfile
//     auto insertFiled = [&](MOperaPtr def = nullptr)
//     {
//         if (def != nullptr)
//         {
//             RealRegsusefiled.insert(def);
//             for (auto &elem : liveRealReg[*def])
//             {
//                 RealRegsusefiled.insert(elem);
//             }
//             // 插入完毕   放入 RelRegsRecord列表中
//             RelRegsRecord.push_back(RealRegsusefiled);
//             RealRegsusefiled.clear(); // 清空供下次使用
//         }
//         else
//         {
//             // def 为空 可能是没有显式def  如函数中直接使用形参的 r0-r3 没有显式def指令
//             for (auto &elem : liveRealReg)
//             {
//                 for (auto &reg : elem.second)
//                 {
//                     RealRegsusefiled.insert(reg);
//                 }
//                 if (RealRegsusefiled.size() > 0)
//                 {
//                     // 有元素
//                     RelRegsRecord.push_back(RealRegsusefiled);
//                     RealRegsusefiled.clear();
//                 }
//             }
//         }
//     };

//     int instNo = 0; // 设置编号
//     int i = 0;      // 每个块末尾的编号
//     for (auto &blk : blockList)
//     {
//         // liveRealReg.clear(); // 更换block时清空
//         // for (auto &live : blk->getLiveOut())
//         // {
//         //     if (live->isReg())
//         //     {
//         //         // 记录出口活跃的物理寄存器对象 只记录 r0,r1,r2,r3
//         //         if (live->getRegNo() >= 0 && live->getRegNo() <= 3)
//         //             liveRealReg[*live].insert(live);
//         //     }
//         // }

//         std::list<MInstPtr> &instList = blk->getInstList();
//         i = instList.size() + i; // 当前块 末尾的编号
//         instNo = i;              // 当前指令编号

//         // 由于 物理寄存器会有多次def 因此逆序遍历指令列表
//         for (auto riter = instList.rbegin(); riter != instList.rend(); riter++)
//         {
//             auto &inst = *riter;
//             inst->setNo(instNo--);
//             auto &defs = inst->getDef();
//             for (auto &def : defs)
//             {
//                 // 对于虚拟寄存器直接加入即可 因为只def一次
//                 if (def->isVReg())
//                 { // vreg 只被def 一次后继可以use 也可以没有  所以可以这样简单写
//                     defUseChains[def].insert(allUsesOfFun[*def].begin(), allUsesOfFun[*def].end());
//                 }
//                 // if (def->isReg() && def->getRegNo() >= 0 && def->getRegNo() <= 3)
//                 // { // 只记录 r0-r3
//                 //     // 处理物理寄存器 并获取其活跃间隔 加入到Active已分配表中
//                 //     // 物理寄存器不太方便获取 def-use chain 因为有时没有显式的def语句
//                 //     auto &uses = liveRealReg[*def];
//                 //     auto &allusesReg = LiveAnalysis.getAllUsesInfun()[*def];
//                 //     // 有 def 有 uses 构成def use chain
//                 //     insertFiled(def); // 定义的 Lamda函数 在前面定义了
//                 //     // 有def 有 uses 当前 def-use chain已结束 清理 供下次使用
//                 //     RealRegsusefiled.clear();
//                 //     // 更新 liveRealReg[*def]为空  (当前use已经和def相联系了 前面指令def的物理寄存器在之后的use不可见)
//                 //     liveRealReg.erase(*def); // 删除该键值对
//                 // }
//             }
//             // for (auto &use : inst->getUse())
//             // {
//             //     // 遍历use  只记录 r0-r3
//             //     if (use->isReg() && use->getRegNo() >= 0 && use->getRegNo() <= 3)
//             //     {
//             //         // 插入使用变量 (可能和上逆序上前的指令的def 形成 def-use chain)
//             //         liveRealReg[*use].insert(use);
//             //     }
//             // }
//         }
//         // 该基本块逆序遍历完毕后 看liveRealReg是否为空(如果某些物理寄存器的use 找不到显式的def 则会出现这种情况)
//         // insertFiled(nullptr); // 使用前面定义的Lamda函数
//     }
//     // 函数所有块都遍历完毕后 将RelRegsRecord 遍历产生 物理寄存器的Interval 并加其加入Active表中
//     // for (auto &elem : RelRegsRecord)
//     // {
//     //     assert(elem.size() > 0);
//     //     auto iterBegin = elem.begin();
//     //     auto iterEnd = elem.rbegin();
//     //     // 直接使用最后一个和最前一个是因为 multiset已经根据使用位置从小到大排序了
//     //     int start = (*iterBegin)->getParent()->getNo();
//     //     int end = (*iterEnd)->getParent()->getNo();
//     //     // 创建interval
//     //     IntervalPtr relRegInterval = Interval::get(start, end, true);
//     //     relRegInterval->reg = (*iterBegin)->getRegNo(); // 设置物理寄存器编号
//     //     regs.erase(relRegInterval->reg);                // 从寄存器池中删除该寄存器 变为使用状态
//     //     // 插入active表中
//     //     active.insert(relRegInterval);
//     // }

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
// }

/// @brief 计算 fun的虚拟寄存器 物理寄存器的 def-use chain
/// @param fun
void LinearScan::computeDefUseChain(MFuncPtr fun)
{
    // 先清空
    defUseChains.clear();
    isUncertainDefSets.clear();
    isArgInitDefSets.clear();
    // 先计算这个函数的liveIn  liveOut
    ActiveVariAnalysis LiveAnalysis;
    LiveAnalysis.computeLiveVariInfun(fun);
    std::cout << "计算完毕def-use chian" << std::endl;

    /*
    根据 IR相关的设计 以指针地址作为一个value的唯一标识 对于一个MachineOperand
    (同一虚拟寄存器编号 他只会def一次 之后是使用 因此获取函数fun的 AllUses 进行查找相应的def 即可获取 def-use chain)
    对于r0-r3物理寄存器 它可def 多次 需要使用LiveIn LiveOut 获取def-use 关系
    同时根据 分支影响 某些use 可能对应多个def 是不确定的状态需要把这些使用交集运算取出(对此我的策略是创建一个def标记 同时标志他是不确定的)
    */
    // fun 中 AllUsesInFun 列表记录
    auto &allUsesOfFun = LiveAnalysis.AllUsesInfun;
    std::list<MBlockPtr> &blockList = fun->getBlockList();
    // 用于存放 有待处理的物理寄存器 r0-r3的def-use chain(初步获取的)
    std::unordered_map<MOperaPtr, std::unordered_set<MOperaPtr>> relRegsDefUse;
    // 创建一个带有 isArgDef 的 r0-r3形参初始值记录
    std::vector<MOperaPtr> ArgInits = {MachineOperand::createReg(0),
                                       MachineOperand::createReg(1),
                                       MachineOperand::createReg(2),
                                       MachineOperand::createReg(3)};

    int instNo = 0; // 设置编号
    int i = 0;      // 每个块末尾的编号
    for (auto &blk : blockList)
    {
        // 用于记录物理寄存器 在每个block的出口活跃记录(按照名字分类)
        std::map<MachineOperand, std::set<MOperaPtr>> liveRealReg;
        for (auto &live : blk->getLiveOut())
        { // 获取 基本块 中 r0-r3 的出口活跃记录
            if (live->isReg())
            {
                // 记录出口活跃的物理寄存器对象 只记录 r0,r1,r2,r3
                if (live->getRegNo() >= 0)
                    liveRealReg[*live].insert(live);
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
                    // 对于虚拟寄存器类型 它只def 一次
                    defUseChains[def].insert(allUsesOfFun[*def].begin(), allUsesOfFun[*def].end());
                }
                else if (def->isReg() && def->getRegNo() >= 0 && def->getRegNo() <= 3)
                {
                    // 物理寄存器 r0-r3
                    auto &uses = liveRealReg[*def];
                    relRegsDefUse[def].insert(uses.begin(), uses.end());
                    liveRealReg[*def].clear(); // 清空该def的活跃部分
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
        // 剩下的这段liveRealReg中关于 r0-r3带有 isArgDef标记的物理寄存器 没有对应的def指令(他们的值来自于函数初始状态下r0-r3的值)
        for (auto &arg : ArgInits)
        {
            auto iter = liveRealReg.find(*arg); // 查找带有arg键的uses
            if (iter != liveRealReg.end())
            {
                // 找到了
                if ((*iter).second.size() != 0)
                {
                    std::cout << "argDef" << std::endl;
                    // 存在记录  则加入到defUseChains 并加入到isArgInitDefSets记录
                    isArgInitDefSets.insert(arg);
                    defUseChains[arg].insert(liveRealReg[*arg].begin(), liveRealReg[*arg].end());
                    liveRealReg[*arg].clear();
                }
            }
        }
    }

    // 遍历完 所有的block后对relRegsDefUse进行处理
    // 因为物理寄存器可以def多次 在交汇节点可能出现use 对应多个def的情况
    // std::deque<std::pair<MOperaPtr, std::unordered_set<MOperaPtr>>> workList;
    // for (auto &elem : relRegsDefUse)
    // {
    //     workList.push_back(elem); // 加入队列中
    // }
    // while (!workList.empty())
    // {
    //     auto pair = workList.front();
    //     MOperaPtr &Defreg = pair.first; // 弹出元素的def对应的操作数
    //     auto &uses = pair.second;       // 弹出元素的uses
    //     workList.pop_front();           // 弹出首元素
    //     for (auto &elem : workList)
    //     {
    //         if (uses.size() == 0)
    //             break; // 没有元素 交集为空 退出循环
    //         // 遍历剩余元素 求交集
    //         MOperaPtr &Defelem = elem.first; // def
    //         auto &Useselem = elem.second;    // uses
    //         if (*Defreg == *Defelem)
    //         {
    //             // 查看交集
    //             std::unordered_set<MOperaPtr> temp;
    //             std::set_intersection(uses.begin(), uses.end(), Useselem.begin(),
    //                                   Useselem.end(), std::inserter(temp, temp.end()));
    //             if (!temp.empty())
    //             {
    //                 // 有交集 创建一个新的 def-uses 链加入到队列 以及加入到relRegsDefUse表中
    //                 // 有交集 说明一个 use 有多个def 是不定状态 加入到isUncertainDefSets表中
    //                 MOperaPtr defCopy = MachineOperand::copy(Defreg);
    //                 isUncertainDefSets.insert(defCopy); // 加入到 不定状态记录中
    //                 std::pair<MOperaPtr, std::unordered_set<MOperaPtr>> newDefUss = {defCopy, temp};
    //                 workList.push_back(newDefUss);   // 加入队列中 下次迭代使用
    //                 relRegsDefUse.insert(newDefUss); // 加入到relRegsDefUse
    //                 // 使用差集对 relRegsDefUse 对应的元素进行运算更新
    //                 for (auto &tp : temp)
    //                 { // 减去交集（将交集取出）
    //                     relRegsDefUse[Defreg].erase(tp);
    //                     relRegsDefUse[Defelem].erase(tp);
    //                     Useselem.erase(tp); // 当前队列的头部元素更新(放止和新放入的newDefUss再取交集)
    //                     uses.erase(tp);
    //                 }
    //             }
    //         }
    //     }
    // }
    // 对relRegsDefUse处理完毕后 将其加入到 defUsesChains
    for (auto &elem : relRegsDefUse)
    {
        MOperaPtr def = elem.first;
        auto &uses = elem.second;
        auto iter = isUncertainDefSets.find(def);
        if (iter != isUncertainDefSets.end())
        {
            // 是不定状态 看uses大小
            if (uses.size() > 0)
            {
                // 如果 uses大小为0 说明不是最终的不定状态
                defUseChains[def].insert(uses.begin(), uses.end());
            }
        }
        else
        {
            // 不是不定状态直接加入
            defUseChains[def].insert(uses.begin(), uses.end());
        }
    }
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
        // if (uses.size() == 0)
        // {
        //     std::cout << "uses数值为0" << std::endl;
        //     std::cout << "寄存器编号:" << def->toStr() << std::endl;
        // }
        if (def->isVReg())
        {
            // 虚拟寄存器只def 一次直接创建
            IntervalPtr inter = Interval::get(def, uses);
            intervals.insert(inter);
        }
        else
        {
            // 物理寄存器 r0-r3
            assert(def->getRegNo() >= 0 && def->getRegNo() <= 3);
            bool isUncertain = false;
            bool isArgDef = false;
            auto iter = isUncertainDefSets.find(def);
            if (iter != isUncertainDefSets.end())
            {
                // 找到了 是不定状态 def 只是一个标记
                isUncertain = true;
            }
            auto isArgInitIter = isArgInitDefSets.find(def);
            if (isArgInitIter != isArgInitDefSets.end())
            {
                // 找到了 是函数形参r0-r3初始值
                isArgDef = true;
            }
            IntervalPtr inter = Interval::get(def, uses, true);

            intervals.insert(inter);
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
        // file << "is Uncertain: " << interval->isUncertainDef << "\n";
        file << "-----------------\n";
    }
}

/// @brief 获取溢出位置 如果无溢出 返回nullptr
/// @param inter1Tospill 准备溢出的间隔
/// @param inter2
/// @return 返回 str ldr 指令的插入位置
std::pair<MOperaPtr, MOperaPtr> LinearScan::computeSpillPos(IntervalPtr inter1Tospill, IntervalPtr inter2)
{
    // res.first为nullptr 表示需要在 函数入口块处插入 str
    // res.second为nullptr 表示无需插入 ldr指令
    std::pair<MOperaPtr, MOperaPtr> res = {nullptr, nullptr};
    int start = inter2->start;
    // store位置
    if (!inter1Tospill->isPreAlloca)
    {
        res.first = inter1Tospill->def;
    }
    else
    {
        // if (inter1Tospill->isUncertainDef)
        // {
        //     auto iter = inter1Tospill->uses.begin();
        //     res.first = (*iter);
        // }
        // else if (inter1Tospill->isArgDef)
        // {
        //     // 无操作
        // }
        // else
        // {
        //     // 有确定def 的 PreAlloca 间隔(确定了物理寄存器)
        //     res.first = inter1Tospill->def;
        // }
    }
    // ldr 位置
    for (auto iter = inter1Tospill->uses.begin(); iter != inter1Tospill->uses.end();)
    {
        int lineno = (*iter)->getParent()->getNo();
        if (lineno >= start)
        {
            res.second = (*iter);
            break;
        }
        else
        {
            ++iter;
        }
    }
    if (res.first == nullptr)
    {
        // if (inter1Tospill->isArgDef)
        // {
        //     // std::cout << "this is argDef-----------" << std::endl;
        // }
        // if (inter1Tospill->isUncertainDef)
        // {
        //     std::cout << "this is uncertaindef" << std::endl;
        // }
        // if (!inter1Tospill->isPreAlloca)
        // {
        //     std::cout << "this is not PreAlloca" << std::endl;
        // }
        // if (inter1Tospill->isPreAlloca)
        // {
        //     std::cout << "this is PreAlloca but not argDEf or uncerntain def" << std::endl;
        // }
    }

    return res;
}

/// @brief 从 Active表中查找冲突的活跃间隔 并将其从active表中移除
/// @param curInter 当前需要分配的活跃间隔
/// @return
IntervalPtr LinearScan::FindConflictInter(IntervalPtr curInter)
{
    // 该函数使用再 AutoUpdateActive(IntervalPtr curInter) 中
    // 不会检查错误 以及异常情况
    // 该函数只 查找 并顺带删除冲突需要溢出的间隔 不做其他任何操作
    IntervalPtr res = nullptr;
    if (curInter->isPreAlloca)
    {
        int needRegNo = curInter->def->getRegNo();
        // 需要指定的寄存器 从头开始查找
        for (auto iter = active.begin(); iter != active.end();)
        {
            int regNo = (*iter)->reg;
            if (needRegNo == regNo)
            {
                // 找到了 冲突间隔
                res = (*iter);
                if (regs.size() > 0 && !res->isPreAlloca)
                {
                    // 如果还有寄存器可以使用 并且本间隔不是预分配的间隔
                    auto curfirstReg = regs.begin();
                    res->reg = *curfirstReg;
                    regs.erase(curfirstReg);
                    res = nullptr;
                }
                else
                {
                    // 有冲突
                    iter = active.erase(iter);
                    regs.insert(regNo); // 返回寄存器可用状态
                }
                break;
            }
            else
            {
                iter++;
            }
        }
    }
    else
    {
        // 是虚拟寄存器间隔 溢出第一个即可
        auto iter = active.begin();
        res = (*iter);
        regs.insert(res->reg);
        active.erase(iter);
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

        // std::cout << "弹出区间" << std::endl;
        // 逆序遍历  因为active按照end的大小 从大到小排列
        if ((*riter)->end < start)
        {
            auto iter = std::prev(riter.base()); // 获取正序迭代器
            // 恢复 该 internal 占用的寄存器
            regs.insert((*riter)->reg);
            active.erase(iter);
        }
        else if ((*riter)->end == start)
        {
            // 边界条件 如果是一个 def 一个 use 那么没有冲突
            // if (!curInter->isUncertainDef)
            // {
            //     // UncertainDef的第一条是 use
            //     auto iter = std::prev(riter.base()); // 获取正序迭代器
            //     // 恢复 该 internal 占用的寄存器
            //     regs.insert((*riter)->reg);
            //     active.erase(iter);
            // }
            // else
            // {
            //     ++riter;
            // }
        }
        else
        {
            break; // 之后的无需遍历 因为multiset已经排序
        }
    }

    // std::cout << "AutoUpdateActive " << std::endl;

    // 在处理完上面的基础上 对 curInster尝试寄存器分配
    // 如果 当前 寄存器池中有可用的寄存器则进行分配即可 分配后 将curInter插入active 表中
    // 自动处理冲突  则选择 终点 end最后的地方的interval进行溢出 并产生溢出处理代码
    if (regs.size() > 0)
    {
        // 是虚拟寄存器的活跃间隔 对寄存器的指定没要求
        if (!curInter->isPreAlloca)
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
            // std::cout << "分配寄存器" << std::endl;
        }
        else
        {
            // 是 r0-r3物理寄存器的活跃间隔 需要指定r0-r3
            int needRegNo = curInter->def->getRegNo(); // 指定的寄存器编号
            auto iter = regs.find(needRegNo);
            if (iter != regs.end())
            {
                // 可用 则分配
                curInter->reg = needRegNo;
                active.insert(curInter);
                regs.erase(needRegNo);
            }
            else
            {
                // 不可用 找到 冲突的活跃间隔 将其溢出
                IntervalPtr spillInter = FindConflictInter(curInter);
                // 如果溢出的间隔也是预分配只能使用该寄存器的间隔 只能将其溢出
                if (spillInter != nullptr)
                {
                    // 分配
                    curInter->reg = needRegNo;
                    active.insert(curInter);
                    regs.erase(needRegNo);

                    spillInter->reg = -1;
                    // 产生溢出代码：
                    successAllocaRegs = false;                        // 有溢出
                    auto pos = computeSpillPos(spillInter, curInter); // 计算溢出位置信息
                    genSpillCode(spillInter, pos);                    // 产生溢出代码
                }
                else
                {
                    // 没有冲突
                    // 分配
                    curInter->reg = needRegNo;
                    active.insert(curInter);
                    regs.erase(needRegNo);
                }
            }
        }
    }
    else
    {
        // 没有寄存器可用 则有冲突 选择 end最后 生命周期最长的interval删除溢出
        // std::cout << "查找冲突" << std::endl;
        IntervalPtr spillInter = FindConflictInter(curInter);
        // std::cout << "找到冲突" << std::endl;
        assert(spillInter != nullptr);
        int regNo = spillInter->reg;
        curInter->reg = regNo;
        regs.erase(regNo);
        spillInter->reg = -1;
        active.insert(curInter);
        // 产生溢出代码：
        successAllocaRegs = false; // 有溢出

        auto pos = computeSpillPos(spillInter, curInter); // 计算溢出位置信息
        genSpillCode(spillInter, pos);                    // 产生溢出代码
        std::cout << "产生溢出" << std::endl;

        // auto first = active.begin();
        // assert(active.size() > 0);
        // if ((*first)->isPreAlloca)
        // {
        //     // 预分配的不能溢出
        //     // 迭代得到下一个 虚拟寄存器的 活跃间隔（multiset已经排序）
        //     auto next = std::next(first);
        //     while (next != active.end())
        //     {
        //         std::cout << "next alloca" << std::endl;
        //         if ((*next)->isPreAlloca)
        //         {
        //             next = std::next(next);
        //         }
        //         else
        //         {
        //             first = next;
        //             break;
        //         }
        //     }
        // }
        // IntervalPtr spillInterval = (*first);

        // std::cout << "the spillInterval start, end" << spillInterval->start << "," << spillInterval->end << std::endl;
        // spillInterval->spill = true;
        // int regNo = spillInterval->reg;
        // curInter->reg = regNo;

        // std::cout << "the curInter start, end" << curInter->start << "," << curInter->end << std::endl;

        // active.erase(first);       // 删除溢出的intervcal
        // active.insert(curInter);   // 插入分配寄存器的interval
        // successAllocaRegs = false; // 有冲突 会有溢出
        // // 计算 溢出位置 并插入溢出处理代码
        // std::pair<MInstPtr, MInstPtr> spillInstPos = computeSpillPos(spillInterval, curInter);
        // genSpillCode(spillInterval, spillInstPos);
        // std::cout << "genSpillInterval" << std::endl;
    }
}

/// @brief 插入溢出时的代码 def后使用 str, 在firstUsePos前插入ldr
/// @param inter 活跃间隔
/// @param pos pos的第一 第二个元素对应  插入 str  ldr指令的位置
void LinearScan::genSpillCode(IntervalPtr interSpilled, std::pair<MOperaPtr, MOperaPtr> &pos)
{
    auto &firstPos = pos.first;
    auto &secondPos = pos.second;
    assert(!(firstPos == nullptr && secondPos == nullptr));
    MFuncPtr fun = nullptr;
    MBlockPtr blk1 = nullptr; // pos1指令属于的块
    MInstPtr pos1 = nullptr;
    MBlockPtr blk2 = nullptr; // pos2指令属于的块
    MInstPtr pos2 = nullptr;
    if (firstPos != nullptr)
    {
        pos1 = firstPos->getParent();
        blk1 = pos1->getParent();
        fun = blk1->getParent();
    }
    if (secondPos != nullptr)
    {
        pos2 = secondPos->getParent();
        blk2 = pos2->getParent();
        fun = blk2->getParent();
    }
    // str 指令肯定要插入
    int offset = -(fun->AllocaStack(4)); // 相对于fp的 偏移
    MOperaPtr offsetImm = MachineOperand::get(MachineOperand::IMM, offset);
    offsetImm = MachineOperand::AutoDealWithImm(offsetImm, machineModule, true);
    if (pos1 == nullptr)
    {
        // assert(interSpilled->isArgDef);
        // 在函数的入口块差入 str
        MBlockPtr &entry = fun->getEntry();
        // 创建 str
        auto &def = interSpilled->def;
        MStorePtr str = MStore::get(entry, MachineInst::STR, MachineOperand::copy(def), MachineOperand::createReg(11), offsetImm);
        entry->getInstList().push_front(str);

        std::cout << "产生entry str指令: " << str->toStr() << std::endl;
    }
    else
    {
        // 不为nullPtr 在指定指令后插入 str
        auto &def = interSpilled->def;
        MStorePtr str = MStore::get(blk1, MachineInst::STR, MachineOperand::copy(def), MachineOperand::createReg(11), offsetImm);
        blk1->insertInstAfter(pos1, str);

        std::cout << "产生def后的 str指令: line: " << def->getParent()->getNo() << " " << str->toStr() << std::endl;
    }

    // 差入ldr指令
    if (pos2 != nullptr)
    {
        if (!interSpilled->isPreAlloca) // 虚拟寄存器活跃间隔
        {
            // 创建 ldr 指令
            MOperaPtr vreg = MachineOperand::get(MachineOperand::VREG, fun->genSpillLoadVregNo()); // 从栈内存中加载位置虚拟寄存器
            MLoadInstPtr ldr = MLoadInst::get(blk2, MachineInst::LDR, vreg, MachineOperand::createReg(11), MachineOperand::copy(offsetImm));
            // 插入指定位置之前
            blk2->insertInstBefore(pos2, ldr);
            // 需要将 secondPos以及之后的操作数都替换为 vreg类型
            auto iter = interSpilled->uses.find(secondPos);
            while (iter != interSpilled->uses.end())
            {
                // 设置为新的编号
                (*iter)->setRegNo(vreg->getRegNo());
                ++iter;
            }
            std::cout << "产生 load指令: line:" << pos2->getNo() << " " << ldr->toStr() << std::endl;
        }
        else
        {
            // 物理寄存器 不用替换
            auto &def = interSpilled->def;
            MLoadInstPtr ldr = MLoadInst::get(blk2, MachineInst::LDR, MachineOperand::copy(def), MachineOperand::createReg(11), MachineOperand::copy(offsetImm));
            blk2->insertInstBefore(pos2, ldr);
            std::cout << "物理寄存器产生 load指令: " << ldr->toStr() << std::endl;
        }
    }

    // int offset = -(fun->AllocaStack(4)); // 相对于fp的 偏移
    // MOperaPtr offsetImm = MachineOperand::get(MachineOperand::IMM, offset);
    // offsetImm = MachineOperand::AutoDealWithImm(offsetImm, machineModule, true);
    // MStorePtr str = MStore::get(blk, MachineInst::STR, MachineOperand::copy(def), MachineOperand::createReg(11), offsetImm);

    // 在 指定指令后插入str指令保存寄存器旧值
    // blk->insertInstAfter(pos.first, str);

    // 将 interSpilled 后面的指令 的虚拟寄存器替换为新def(由ldr指令新def的虚拟寄存器)的编号

    // auto iter = std::find(blk->getInstList().begin(), blk->getInstList().end(), pos.second);
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
    computeDefUseChain(fun);
    std::cout << "计算完毕def-use chian" << std::endl;
    // 计算活跃间隔
    computeIntervals(fun);

    // 自动更新  active表
    for (auto &inter : intervals)
    {
        std::cout << "def: ";
        std::cout << inter->def->toStr() << std::endl;
        std::cout << "uses size: " << inter->uses.size() << std::endl;
        AutoUpdateActive(inter);
    }
    return successAllocaRegs;
}

/// @brief 将活跃间隔中的def use 虚拟寄存器操作数 映射为对应的物理寄存器
/// @param inter
void LinearScan::MapIntervalToReg(IntervalPtr inter)
{
    inter->def->setReg(inter->reg);
    assert(inter->reg != -1);
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
