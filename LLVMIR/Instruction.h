/**
 * @file Instruction.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "User.h"
class Counter;
class BasicBlock;
class Instruction;
using InstPtr = std::shared_ptr<Instruction>;
using BasicBlockPtr = std::shared_ptr<BasicBlock>;

/// @brief 指令操作码
enum class Opcode
{
    Alloca, // AllocaInst
    Store,  // StoreInst
    Ret,    // RetInst
    Load,   // LoadInst
    Call,   // CallInst 函数调用

    /// @brief branchInst
    Goto,        // 无条件跳转  BranchInst  br label ..
    ConditionBr, // 有条件跳转 br condition,label t, label f

    /// @brief getelementptr
    GetelementPtr, // 获取数组偏移指针的指令

    /// @brief BinaryInst 目前 8-14
    AddInteger, // 整数加法
    SubInteger, // 整数减法
    DivInteger, // 整数除法
    MulInteger, // 整数乘法
    ModInteger, // 整数取余
    SHl,        // 逻辑左移
    ASHR,       // 算数右移

    /// @brief icmp 比较指令

    GtInteger,    // 大于 icmp sgt/ugt
    LtIntegr,     // 小于  icmp slt/ult
    EqInTeger,    // ==  icmp eq
    GeInTeger,    // >=
    LeInteger,    // <=
    NotEqInteger, // !=

    ICMP, // 标识ICMP指令

    // Zext 指令
    Zext,

    // PhiNode
    PhiNode,

    Unknown // 未知
};

class Instruction : public User
{
protected:
    BasicBlockPtr parent = nullptr; // 指令所属的基本块
    Opcode op;                      // 指令操作码

public:
    /// @brief 析构函数
    ~Instruction() { parent.reset(); };

    virtual void clear() override
    {
        User::clear();
        parent.reset();
    }

    /// @brief 无参构造
    Instruction()
    {
        setSubClassID(Value::InstructionVal);
        op = Opcode::Unknown;
    }

    /// @brief 构造函数
    /// @param _ty
    Instruction(Type *_ty) : User(_ty)
    {
        setSubClassID(Value::InstructionVal);
        op = Opcode::Unknown;
    }

    /// @brief 设置parent
    /// @param _p
    void setBBlockParent(BasicBlockPtr _p)
    {
        parent = _p;
    }

    /// @brief 获取 parent
    /// @return
    BasicBlockPtr &getBBlockParent()
    {
        return parent;
    }

    /// @brief 获取指令操作码
    /// @return
    Opcode &getOpcode() { return op; }

    /// @brief 设置Opcode
    /// @param _op
    void setOpcode(Opcode _op) { op = _op; }

    /// @brief 获取指令操作码对应的名字
    /// @return
    string getOpcodeName();

    /// @brief 是否时PhiNode
    /// @return 
    bool isPhiNode();

    /// @brief 判断是否是分支指令
    /// @return
    bool isBranchInst();

    /// @brief 是否是Alloca
    /// @return
    bool isAllocaInst();

    /// @brief 是否是storeinst
    /// @return
    bool isStoreInst();

    /// @brief 是否是LoadInst
    /// @return
    bool isLoadInst();

    /// @brief 是否是二元指令
    /// @return
    bool isBinaryInst();

    /// @brief 是否是 getelementptr 指令
    /// @return
    bool isGetelemPtrInst();

    /// @brief 是否是整数比较指令
    /// @return
    bool isICmpInst();

    /// @brief 是否是Zext 指令
    /// @return
    bool isZextInst();

    /// @brief 是否是ret Inst
    /// @return
    bool isRetInst();

    /// @brief 是否是 CallInst
    /// @return
    bool isCallInst();

    /// @brief 判断指令是否是死指令
    /// @return
    virtual bool isDeadInst() { return false; }

    /// @brief 为指令设置 dead标记  对于 StoreInst 这类无直接User的指令具有作用
    virtual void setDeadSign() {};

    /// @brief 如果指令结果是常数 则自动传播(对于二元运算 比较 跳转等)
    virtual void AutoTransmitWhenIsConst() {};

    /// @brief 指令是否是常数或者是肯定的 如: br i1 true,block1,block2 这是恒定的 可以处理
    /// @return
    virtual bool isConst() { return false; }

    /// @brief 获取指令的字符串翻译
    /// @param inst
    /// @param cnt
    /// @return
    static string toIRstr(InstPtr inst, Counter *cnt);
};

// 下面是一些指令翻译为文本函数

/// @brief AllocaInst文本
/// @param alloca
/// @return
string AllocaInstStr(InstPtr alloca, Counter *cnt);

/// @brief StoreInst文本
/// @param store
/// @return
string StoreInstStr(InstPtr store, Counter *cnt);

/// @brief 二元运算文本
/// @param binaryop
/// @return
string BinaryInstStr(InstPtr binaryop, Counter *cnt);

/// @brief LoadInst文本
/// @param load
/// @param cnt
/// @return
string LoadInstStr(InstPtr load, Counter *cnt);

/// @brief RetInst文本
/// @param ret
/// @param cnt
/// @return
string RetInstStr(InstPtr ret, Counter *cnt);

/// @brief CallInst文本
/// @param call
/// @param cnt
/// @return
string CallInstStr(InstPtr call, Counter *cnt);

/// @brief branchInst输出文本
/// @param br
/// @param cnt
/// @return
string BranchInstStr(InstPtr br, Counter *cnt);

/// @brief 比较语句文本
/// @param icmp
/// @param cnt
/// @return
string ICmpInstStr(InstPtr icmp, Counter *cnt);

/// @brief getelementptr指令翻译
/// @param getelem
/// @param cnt
/// @return
string GetelementInstStr(InstPtr getelem, Counter *cnt);

/// @brief 获取ZextInst的字符表示
/// @param zext
/// @param cnt
/// @return
string ZextInstStr(InstPtr zext, Counter *cnt);

/// @brief 获取phi节点的字符表示
/// @param phi 
/// @param cnt 
/// @return 
string PhiNodeStr(InstPtr phi, Counter *cnt);