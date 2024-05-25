/**
 * @file MachineInst.h
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
#include <vector>
#include "MachineOperand.h"

class MachineBlock;
class MachineInst;
class MBinaryInst;
class MLoadInst;
class MStore;
class MMovInst;
class MCmpInst;
class MStackInst;
class MBranchInst;
using MInstPtr = std::shared_ptr<MachineInst>;
using MBlockPtr = std::shared_ptr<MachineBlock>;
using MBinaryInstPtr = std::shared_ptr<MBinaryInst>;
using MLoadInstPtr = std::shared_ptr<MLoadInst>;
using MStorePtr = std::shared_ptr<MStore>;
using MMovInstPtr = std::shared_ptr<MMovInst>;
using MCmpInstPtr = std::shared_ptr<MCmpInst>;
using MStackInstPtr = std::shared_ptr<MStackInst>;
using MBranchInstPtr = std::shared_ptr<MBranchInst>;

/// @brief 机器指令
class MachineInst : public std::enable_shared_from_this<MachineInst>
{
public:
    /// @brief 机器指令类型
    enum MinstTy
    {
        LDR, // ldr
        STR, // str
        MOV, // mov指令
        CMP, // 比较指令

        /// @brief 栈操作
        PUSH, // push
        POP,  // pop

        /// @brief 二元运算
        ADD,  // add
        SUB,  // sub
        MUL,  // 乘
        SDIV, // 有符号
        AND,  //
        OR,
        LSL, // 逻辑左移
        LSR, // 逻辑右移
        ASR, // 算数右移

        /// @brief 分支指令
        B,  // 跳转 可带条件 如 bne
        BX, // bx
        BL, // bl
    };

    // 条件后缀
    enum condSuffix
    {
        EQ,
        NE,
        LT,
        LE,
        GT,
        GE,
        NONE
    };

protected:
    MBlockPtr parent = nullptr;         // 指令属于的块
    uint64_t no;                        // 指令编号 用于活跃区间
    condSuffix cond = condSuffix::NONE; // 条件后缀
    MinstTy type;                       // 指令类型
    std::vector<MOperaPtr> defs;        // def 目的操作数
    std::vector<MOperaPtr> uses;        // use 源操作数
    void addDef(MOperaPtr dst) { defs.push_back(dst); }
    void addUse(MOperaPtr src) { uses.push_back(src); }

public:
    virtual void clear(); // 手动清理 打破引用环 使智能指针自动释放
    std::vector<MOperaPtr> &getDef() { return defs; }
    std::vector<MOperaPtr> &getUse() { return uses; }
    MBlockPtr getParent();                                 // 返回MachineBlock
    void setParent(MBlockPtr _parent);                     // 设置parent
    void setCondSuffix(condSuffix _cond) { cond = _cond; } // 设置指令条件后缀
    condSuffix getCondSuffix() { return cond; }            // 获取条件后缀
    uint64_t getNo() { return no; }                        // 获取行号
    void setNo(uint64_t _no) { no = _no; }                 // 设置编号
    virtual std::string toStr() = 0;                       // 输出字符表示
    std::string MinstTyStr();                              // 输出指令操作对应的字符串
    std::string condSuffixStr();                           // 输出条件字符串
};

/// @brief  二元指令
class MBinaryInst : public MachineInst
{
public:
    /// @brief 析构函数
    ~MBinaryInst();

    /// @brief 构造函数
    /// @param parent
    /// @param instTy
    /// @param dst
    /// @param src1
    /// @param src2
    /// @param cond
    MBinaryInst(MBlockPtr p, MinstTy instTy, MOperaPtr dst, MOperaPtr src1, MOperaPtr src2, condSuffix _cond = condSuffix::NONE);

    /// @brief 创建智能指针对象
    /// @param parent
    /// @param instTy
    /// @param dst
    /// @param src1
    /// @param src2
    /// @param cond
    /// @return
    static MBinaryInstPtr get(MBlockPtr p, MinstTy instTy, MOperaPtr dst, MOperaPtr src1, MOperaPtr src2, condSuffix _cond = condSuffix::NONE);

    /// @brief 输出字符串
    /// @return
    std::string toStr() override;
};

class MLoadInst : public MachineInst
{
public:
    /// @brief 析构函数
    ~MLoadInst() { clear(); }

    /// @brief ldr r1,#10  ldr r1, .addr_(标签地址) ldr r1, =1000000  ldr r1,[r2];
    /// @param p
    /// @param instTy
    /// @param dst
    /// @param src1
    MLoadInst(MBlockPtr p, MinstTy instTy, MOperaPtr dst, MOperaPtr src1);

    /// @brief ldr r1, [r1,#2] ldr r1, [fp,r2]   带有偏移的指令或偏移为0
    /// @param p
    /// @param instTy
    /// @param dst
    /// @param src1
    /// @param offset
    MLoadInst(MBlockPtr p, MinstTy instTy, MOperaPtr dst, MOperaPtr src1, MOperaPtr offset);

    /// @brief 创建智能指针对象
    /// @param p
    /// @param instTy
    /// @param dst
    /// @param src1
    /// @param offset
    /// @return
    static MLoadInstPtr get(MBlockPtr p, MinstTy instTy, MOperaPtr dst, MOperaPtr src1, MOperaPtr offset = nullptr);

    /// @brief 输出字符串
    /// @return
    std::string toStr() override;
};

class MStore : public MachineInst
{
public:
    /// @brief str r1,[r1,#1] str r1,[r2], str r2,[r3,r1]
    /// @param p
    /// @param instTy
    /// @param src1
    /// @param src2
    /// @param offset
    MStore(MBlockPtr p, MinstTy instTy, MOperaPtr src1, MOperaPtr src2, MOperaPtr offset = nullptr);

    /// @brief 创建智能指针
    /// @param p
    /// @param instTy
    /// @param src1
    /// @param src2
    /// @param offset
    /// @return
    static MStorePtr get(MBlockPtr p, MinstTy instTy, MOperaPtr src1, MOperaPtr src2, MOperaPtr offset = nullptr);

    /// @brief 输出字符串
    /// @return
    std::string toStr() override;
};

class MMovInst : public MachineInst
{
public:
    /// @brief 构造函数 mov r1,r2  mov r1,#2 形式  condsuffix 可加mov 条件 如 movne
    /// @param p
    /// @param instTy
    /// @param dst
    /// @param src1
    /// @param _cond
    MMovInst(MBlockPtr p, MinstTy instTy, MOperaPtr dst, MOperaPtr src1, condSuffix _cond = condSuffix::NONE);

    /// @brief 创建智能指针对象
    /// @param p
    /// @param instTy
    /// @param dst
    /// @param src1
    /// @param _cond
    /// @return
    static MMovInstPtr get(MBlockPtr p, MinstTy instTy, MOperaPtr dst, MOperaPtr src1, condSuffix _cond = condSuffix::NONE);

    /// @brief 输出字符串
    /// @return
    std::string toStr() override;
};

class MCmpInst : public MachineInst
{
public:
    /// @brief 构造函数
    /// @param p
    /// @param instTy
    /// @param src1
    /// @param src2
    MCmpInst(MBlockPtr p, MinstTy instTy, MOperaPtr src1, MOperaPtr src2);

    /// @brief 创建智能指针类型
    /// @param p
    /// @param instTy
    /// @param src1
    /// @param src2
    /// @return
    static MCmpInstPtr get(MBlockPtr p, MinstTy instTy, MOperaPtr src1, MOperaPtr src2);

    /// @brief 输出字符串
    /// @return
    std::string toStr() override;
};

class MStackInst : public MachineInst
{
public:
    /// @brief 构造函数 push,pop 栈相关的指令
    /// @param p
    /// @param instTy
    /// @param srcs
    MStackInst(MBlockPtr p, MinstTy instTy, std::vector<MOperaPtr> srcs);

    /// @brief 创建智能指针对象
    /// @param p
    /// @param instTy
    /// @param srcs
    /// @return
    static MStackInstPtr get(MBlockPtr p, MinstTy instTy, std::vector<MOperaPtr> srcs);

    /// @brief 输出字符串
    /// @return
    std::string toStr() override;
};

/// @brief 分支指令
class MBranchInst : public MachineInst
{
public:
    /// @brief 构造 b  bne bl bx 等
    /// @param p
    /// @param instTy
    /// @param src
    /// @param _cond
    MBranchInst(MBlockPtr p, MinstTy instTy, MOperaPtr src, condSuffix _cond = condSuffix::NONE);

    /// @brief 创建智能指针对象 branch
    /// @param p 
    /// @param instTy 
    /// @param src 
    /// @param _cond 
    /// @return 
    static MBranchInstPtr get(MBlockPtr p, MinstTy instTy, MOperaPtr src, condSuffix _cond = condSuffix::NONE);

    /// @brief 输出字符串
    /// @return
    std::string toStr() override;
};
