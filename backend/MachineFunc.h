/**
 * @file MachineFunc.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <memory>
#include "MachineBlock.h"
#include "Function.h"
#include "Value.h"
#include "BasicBlock.h"

class MachineFunc;
class MachineModule;
using MModulePtr = std::shared_ptr<MachineModule>;
using MFuncPtr = std::shared_ptr<MachineFunc>;

class MachineFunc
{
private:
    /// @brief 所属于的Module
    MModulePtr parent = nullptr;

    /// @brief 基本块列表
    std::list<MBlockPtr> blockList;

    /// @brief 函数编号
    uint32_t funcNo;

    /// @brief 函数名
    string funcName;

    /// @brief 函数参数个数
    uint32_t funcArgsNum = 0;

    /// @brief MachineFunc中调用函数的最大参数数目
    int32_t maxCallFunParmas = 0;

    /// @brief 所需申请的栈空间
    uint64_t stackSize = 0;

    /// @brief 记录函数使用的 全局变脸 常量标签地址
    std::unordered_map<ValPtr, string> addrPool;

    /// @brief 函数需要保存记录的寄存器 例如push {r1,r3,fp,lr} 然后在函数末尾 pop恢复
    std::set<int> regsSave;

    /// 对于变量 alloca 数组alloca 其初始偏移为 fp -num, 由于会push 除lr,fp外的寄存器
    /// 会影响偏移 因此需要矫正.  如push {r4,r5,fp,lr}  fp向下低8字节存放r5,r4的旧值， 引入新的矫正偏移8
    /// 对于push pop操作，由于saveRegs需要在寄存器分配之后确定，因此在分配完成后也需要对push,pop进行修正
    /// @brief 可能需要校正的一些指令 (主要受regsSave保存寄存器的影响: 会影响偏移或者是还未进行寄存器分配前时不确定的push pop操作)
    std::vector<MInstPtr> InstToAdjust;

public:
    /// @brief 获取函数的入口块
    /// @return
    inline MBlockPtr &getEntry() { return blockList.front(); }

    /// @brief 加入需要保存原值寄存器
    /// @param reg
    inline void addSaveReg(int reg) { regsSave.insert(reg); }

    /// @brief 将块放入到列表尾部
    /// @param block
    inline void addBlockBack(MBlockPtr block) { blockList.push_back(block); }

    /// @brief 设置函数名
    /// @param name
    inline void setFuncName(string name) { funcName = name; }

    /// @brief 获取函数名
    /// @return
    inline std::string &getFuncName() { return funcName; }

    /// @brief 设置函数编号
    /// @param no
    inline void setFuncNo(uint32_t no) { funcNo = no; }

    /// @brief 设置函数参数数目
    /// @param n
    inline void setFuncArgsNum(uint32_t n) { funcArgsNum = n; }

    /// @brief 获取函数参数数目
    /// @return
    inline uint32_t getFuncArgsNum() { return funcArgsNum; }

    /// @brief 设置最大调用参数数目
    /// @param no
    inline void setmaxCallFunParmas(int32_t no) { maxCallFunParmas = no; }

    /// @brief 获取寄存器操作数
    /// @return
    std::vector<MOperaPtr> getSavedRegs();

    /// @brief 获取函数编号
    /// @return
    inline uint32_t getFuncNo()
    {
        return funcNo;
    }

    /// @brief 增加该函数使用的标签地址
    /// @param val
    /// @param str
    inline void insertAddrPool(ValPtr val, string &str)
    {
        addrPool.emplace(val, str);
    }

    /// @brief 获取常量 全局变量标签池
    /// @return
    inline std::unordered_map<ValPtr, string> &getAddrPool() { return addrPool; }

    /// @brief 获取需要保存的寄存器集合
    /// @return
    inline std::set<int> &getSavedRegSet() { return regsSave; }

    /// @brief 申请栈空间(最后判断并进行8字节对齐)
    /// @return
    inline uint64_t AllocaStack(uint64_t size)
    {
        stackSize += size;
        return stackSize;
    }

    inline void addAdjustInst(MInstPtr inst) { InstToAdjust.push_back(inst); }

    /// @brief 构造函数
    /// @param p 属于的module
    /// @param _funcNo 函数编号
    MachineFunc(MModulePtr p);

    /// @brief 析构函数
    ~MachineFunc();

    /// @brief 手动打破环 使智能指针自动释放
    void clear();

    /// @brief 修正InstToAdjust中的指令
    void AdjustInsts();

    /// @brief 输出函数使用的标签地址池
    /// @return
    string printAddrPool();

    /// @brief 输出函数对应的汇编
    /// @return
    string output();

    /// @brief 创建智能指针类型
    /// @param p
    /// @return
    static MFuncPtr get(MModulePtr p);
};
