/**
 * @file MachineModule.h
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
#include <deque>
#include "MachineFunc.h"
#include "GlobalVariable.h"
#include <unordered_map>
#include "Value.h"

class MCount;
class MachineModule;
using MModulePtr = std::shared_ptr<MachineModule>;
using MCntPtr = std::shared_ptr<MCount>;

class MachineModule
{
private:
    /// @brief 函数列表
    std::vector<MFuncPtr> funcList;

    /// @brief 全局变量列表
    std::vector<GlobalVariPtr> globalVaris;

    /// @brief data段  目前只存 globalvariable
    std::vector<string> dataSection;

    /// @brief bss段 目前只存 globalvariable相关
    std::vector<string> bssSection;

    /// @brief 编号记录
    MCntPtr counter = nullptr;

    /// @brief 当前函数编号
    uint64_t curFuncNo = 0;

    /// @brief 当前函数
    MFuncPtr curFun = nullptr;

    /// @brief 当前块
    MBlockPtr curBlock = nullptr;

public:
    /// @brief 获取函数列表
    /// @return
    inline std::vector<MFuncPtr> &getFuncList() { return funcList; }

    /// @brief 添加函数
    /// @param fun
    inline void addFunc(MFuncPtr fun) { funcList.push_back(fun); }

    /// @brief 获取全局变量列表
    /// @return
    inline std::vector<GlobalVariPtr> &getGlobalVars() { return globalVaris; }

    /// @brief 添加全局变量
    /// @param g
    inline void addGlobalVaris(GlobalVariPtr &g) { globalVaris.push_back(g); }

    /// @brief 获取当前函数编号
    /// @return
    inline uint64_t getCurFuncNo() { return curFun->getFuncNo(); }

    /// @brief 当前函数编号自增
    inline void curFuncNoAdd() { curFuncNo++; }

    /// @brief 获取当前函数
    /// @return
    inline MFuncPtr &getCurFun() { return curFun; }

    /// @brief 设置当前函数
    /// @param fun
    inline void setCurFun(MFuncPtr fun)
    {
        curFun = fun;
        curFun->setFuncNo(curFuncNo); // 设置编号
        curFuncNo++;
    }

    /// @brief 获取当前块
    /// @return
    inline MBlockPtr &getCurBlock() { return curBlock; }

    /// @brief 设置当前块
    /// @param b
    inline void setCurBlock(MBlockPtr b) { curBlock = b; }

    /// @brief 重置计数器
    void CnterReset();

    /// @brief 获取编号 全局变脸 常量标签地址  临时变量的虚拟寄存器编号
    /// @param val
    /// @return
    uint32_t getNo(ValPtr val);

    /// @brief 判断是否有编号记录
    /// @param val
    /// @return
    bool hasNumRecord(ValPtr val);

    /// @brief 不插入记录 生成并获取相应的编号
    /// @return
    uint32_t getRegNo();

    /// @brief 构造函数
    MachineModule();

    /// @brief  析构函数
    ~MachineModule();

    /// @brief 获取指针智能对象
    /// @return
    static MModulePtr get();

    /// @brief 产生全局变量声明 (.data 段和 .bss)
    /// @return
    void genGlobalVariDecl();

    /// @brief 将Arm指令打印至文件中
    /// @param filePath
    void printArm(string filePath);

    /// @brief 手动清理
    void clear();
};

/// @brief 为MachineBlock  全局变量 常量池等地址标签编号(当当前函数结束时清空重置)
class MCount
{
private:
    uint32_t MachineBlockNo = 0; // block编号
    uint32_t RegNo = 0;          // 虚拟寄存器 编号(物理寄存器编号由创建时指定)
    uint32_t LabelAddr = 0;      // 标签地址编号

    /// @brief 记录表
    std::unordered_map<ValPtr, uint32_t> record;

public:
    /// @brief 获取记录表
    /// @return
    inline std::unordered_map<ValPtr, uint32_t> &getRecordMap() { return record; }

    /// @brief 获取当前使用的寄存器编号
    /// @return
    inline int32_t getCurUsedMaxRegNo()
    {
        return (int32_t)(RegNo)-1;
    }

    /// @brief 获取编号 当记录中存在时 取出 不存在时放入 并增加计数
    /// @param val
    /// @return
    uint32_t getNo(ValPtr val);

    /// @brief 不插入value记录 直接获取编号
    /// @return
    uint32_t getRegNo() { return RegNo++; }

    /// @brief 判断val是否已经有记录 给函数的后4 Argument使用,防止反复Load
    /// @param val 主要用于IR优化后 load消减时(类似于Mem2Reg)
    /// @return
    bool hasRecord(ValPtr val);

    /// @brief 记录重置
    inline void reset()
    {
        record.clear();
        MachineBlockNo = 0;
        RegNo = 0;
        LabelAddr = 0;
    }
};


/// @brief 简单删除一些无用指令
/// @param machine 
void EasyElimInst(MModulePtr machine);