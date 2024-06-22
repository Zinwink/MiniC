/**
 * @file DerivedInst.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief  Instruction的派生类
 * @version 1.0
 * @date 2024-05-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "Instruction.h"
#include "DerivedTypes.h"
#include "Constant.h"
#include "Type.h"
#include "Argument.h"
#include <unordered_map>

class AllocaInst;
class StoreInst;
class BinaryOperator;
class LoadInst;
class RetInst;
class CallInst;
class ICmpInst;
class BranchInst;
class getelementptrInst;
class ZextInst;
class BitCastInst; // bitcast指令
class PhiNode;
class PhiElimMove; // 伪指令  phi消减时使用

using AllocaInstPtr = std::shared_ptr<AllocaInst>;
using StoreInstPtr = std::shared_ptr<StoreInst>;
using BinaryOperatorPtr = std::shared_ptr<BinaryOperator>;
using LoadInstPtr = std::shared_ptr<LoadInst>;
using RetInstPtr = std::shared_ptr<RetInst>;
using CallInstPtr = std::shared_ptr<CallInst>;
using ICmpInstPtr = std::shared_ptr<ICmpInst>;
using BranchInstPtr = std::shared_ptr<BranchInst>;
using getelemInstPtr = std::shared_ptr<getelementptrInst>;
using ZextInstPtr = std::shared_ptr<ZextInst>;
using PhiNodePtr = std::shared_ptr<PhiNode>;
using PhiElimMovePtr = std::shared_ptr<PhiElimMove>;
using BitCastPtr = std::shared_ptr<BitCastInst>; // bitcast指令

/// @brief AllocaInst (将充当变量)(AllocaInst本身的Type是指针类型)
class AllocaInst : public Instruction
{
    friend class Instruction;

private:
    string AllocaName;    // 名字
    Type *AllocatedType;  //  Alloca指令申请的类型
    ArgPtr arg = nullptr; // 用于判断是否是为函数形参开辟的空间

    // 相对于 fp的偏移。一般而言其 地址为 [fp,#-num]
    // 特殊地 如果alloca 是为函数形参声明的空间 前4个空间仍然满足 [fp,#-num]
    // 但是 除前4个形参外的 Alloca 空间实际上 指向的为调用函数时压栈的空间 [fp,#(8+(argNo-4)*4)] argNo从0开始
    int64_t offset;

    bool hasConstQualifier = false; // 是否是const修饰
    bool _isDead = false;

public:
    /// @brief 析构函数
    ~AllocaInst()
    {
        // AllocaInst本身的Type 为PointerType 将复用AllocatedType 因此析构时只需将 AllocatedType=null
        // 防止反复释放
        delete AllocatedType;
        AllocatedType = nullptr;
        arg.reset();
    };

    /// @brief 无参构造
    AllocaInst()
    {
        setOpcode(Opcode::Alloca);
    }

    /// @brief 构造函数
    /// @param _ty
    AllocaInst(Type *_allocatedType)
    {
        AllocatedType = _allocatedType;
        setType(PointerType::get(Type::copy(_allocatedType)));
        setOpcode(Opcode::Alloca);
    }

    /// @brief 为指令设置 dead标记  对于 StoreInst 这类无直接User的指令具有作用
    void setDeadSign() override
    {
        _isDead = true;
        for (auto &user : getUseList())
        {
            if (user->isInstruct())
            {
                InstPtr inst = std::static_pointer_cast<Instruction>(user);
                inst->setDeadSign();
            }
        }
    }

    /// @brief 判断AllocaInst是否是死指令
    /// @return
    bool isDeadInst() override
    {
        if (_isDead)
        {
            return true;
        }
        if (getUseList().size() == 0)
        {
            return true;
        }
        else
        {
            // if (!AllocatedType->isArrayType())
            // {
            //     // alloca不是 作为数组首地址使用 而是作为内存容器存放 int 或者指针类型(如函数形参)
            //     bool res = true;
            //     for (auto &user : getUseList())
            //     {
            //         if (user->isLoadInst())
            //         {
            //             if (user->isLoadInst())
            //             {
            //                 res = false;
            //                 break;
            //             }
            //         }
            //     }
            //     if (res)
            //     {   //alloca是死的 则 其store也是死的
            //         for (auto &user : getUseList())
            //         {
            //             if (user->isInstruct())
            //             {
            //                 InstPtr inst = std::static_pointer_cast<Instruction>(user);
            //                 inst->setDeadSign();
            //             }
            //         }
            //     }
            // return res;
            // }
        }
        return false;
    }

    /// @brief 设置const修饰
    void setConstQualify() override { hasConstQualifier = true; }

    /// @brief 是否由const修饰
    /// @return
    bool isConstQualify() override
    {
        return hasConstQualifier;
    }

    /// @brief 判断是否是为函数形参声明的栈空间
    /// @return
    inline bool isAllocaArgument() { return arg != nullptr; }

    /// @brief 返回 Alloca 申请的空间对应的函数形参
    /// @return
    inline ArgPtr &getAllocaArg() { return arg; }

    /// @brief 设置Alloca对应的函数形参
    /// @param _arg
    inline void setAllocaArg(ArgPtr _arg) { arg = _arg; }

    /// @brief 获取Value名
    /// @return
    inline string getName() override { return AllocaName; }

    /// @brief 获取相对于当前fp的偏移
    /// @return
    inline int64_t getOffset() { return offset; }

    /// @brief 设置偏移
    /// @param off
    inline void setOffset(int64_t off) { offset = off; }

    /// @brief 设置Value名
    /// @param name
    void setName(string &name) override
    {
        AllocaName = name;
        HasName = 1;
    }

    /// @brief 获取存储类型
    /// @return
    inline Type *getAllocatedType() { return AllocatedType; }

    /// @brief 获取alloca 申请的内存大小
    /// @return
    uint32_t getAllocaSize();

    /// @brief 静态函数  获取指令对象指针
    /// @param name
    /// @param _allocatedTy
    /// @return
    static AllocaInstPtr get(string name, Type *_allocatedTy);
};

/// @brief storeInst
class StoreInst : public Instruction
{
    friend class Instruction;

private:
    bool _isDead = false; // StoreInst 没有UserList需要结合数据流分析进行判断

public:
    /// @brief 析构函数
    ~StoreInst() = default;

    /// @brief 无参构造
    StoreInst()
    {
        setOpcode(Opcode::Store);
    }

    /// @brief 构造函数
    /// @param val 存放值
    /// @param Ptr 存放位置  指针类型
    StoreInst(ValPtr val, ValPtr Ptr)
    {
        setOpcode(Opcode::Store);
        operands.push_back(val);
        operands.push_back(Ptr);
    }

    /// @brief 根据数据流分析进行标记
    void setDeadSign() override
    {
        _isDead = true;
    }

    /// @brief StoreInst 是否是不必要指令
    /// @return
    bool isDeadInst() override;

    /// @brief 创建指令StoreInst
    /// @param val
    /// @param Ptr
    /// @return
    static StoreInstPtr get(ValPtr val, ValPtr Ptr);

    /// @brief 在atBack基本快后创建指令(有条件判断)
    /// @param val
    /// @param Ptr
    /// @return
    static StoreInstPtr create(ValPtr val, ValPtr Ptr, BasicBlockPtr atBack);
};

/// @brief  LoadInst
class LoadInst : public Instruction
{
    friend class Instruction;

private:
    bool _isDead = false;

public:
    /// @brief 析构函数
    ~LoadInst()
    {
        setType(nullptr); // Value Type来自操作数地elementType
    }

    /// @brief 构造函数
    /// @param Ptr
    LoadInst(ValPtr Ptr)
    {
        assert(Ptr->getType()->isPointerType() && "ValPtr is not a PointerType!");
        setOpcode(Opcode::Load);
        operands.push_back(Ptr);
        PointerType *pointerTy = static_cast<PointerType *>(Ptr->getType());
        setType(pointerTy->getElemntTy());
    }

    /// @brief 为指令设置 dead标记  对于 StoreInst 这类无直接User的指令具有作用
    void setDeadSign() override
    {
        _isDead = true;
    }

    /// @brief 判断LoadInst是否是死指令
    /// @return
    bool isDeadInst() override
    {
        if (_isDead)
        {
            return true;
        }
        if (getUseList().size() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /// @brief 创建获取LoadInst
    /// @param Ptr
    /// @return
    static LoadInstPtr get(ValPtr Ptr);
};

/// @brief 二元运算符
class BinaryOperator : public Instruction
{
    friend class Instruction;

public:
    /// @brief 析构函数
    ~BinaryOperator() = default;

    /// @brief
    /// @param val1
    /// @param val2
    BinaryOperator(Opcode _op, ValPtr val1, ValPtr val2)
    {
        setOpcode(_op);
        ValPtr op1 = val1;
        ValPtr op2 = val2;
        if (_op == Opcode::AddInteger || _op == Opcode::MulInteger)
        {
            // 为了后继简单使用哈希函数 如果是 加法 乘法 按照地址顺序交换操作数
            // 加法 乘法满足交换律 第一个操作数的地址更小
            if (val1->isConstantInt() && val2->isConstantInt())
            {
                // 两个操作数都是常数类型 按照长度 大小排序
                ConstantIntPtr val1C = std::static_pointer_cast<ConstantInt>(val1);
                ConstantIntPtr val2C = std::static_pointer_cast<ConstantInt>(val2);
                if (val1C->getValue() >= val2C->getValue())
                { // 从小到达排
                    op1 = val2;
                    op2 = val1;
                }
            }
            else if (val1->isConstantInt() && !val2->isConstantInt())
            {
                // 统一将常数放在后面
                op1 = val2;
                op2 = val1;
            }
            else if (!val1->isConstantInt() && val2->isConstantInt())
            {
                // 无操作
            }
            else
            {
                // val1， val2 都不是常数
                if (val1 >= val2)
                { // 按地址排序
                    op1 = val2;
                    op2 = val1;
                }
            }
        }
        operands.push_back(op1);
        operands.push_back(op2);

        // 目前只设置为int结果类型 后面可以根据  val1,val2类型编写函数获取结果类型进行设置
        setType(Type::getIntNType(32));
    }

    /// @brief 判断BinaryInst是否是死指令
    /// @return
    bool isDeadInst() override
    {
        if (getUseList().size() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /// @brief 当是二元运算的结果是常数时自动替换传播
    void AutoTransmitWhenIsConst() override;

    /// @brief 创建BInaryOperator指令
    /// @param _op
    /// @param val1
    /// @param val2
    /// @return
    static BinaryOperatorPtr get(Opcode _op, ValPtr val1, ValPtr val2);

    /// @brief 在Block末尾创建BinaryOperator指令(该创建方法具有自动识别类型的功能)
    /// @param _op
    /// @param val1
    /// @param val2
    /// @param atBack
    /// @return
    static BinaryOperatorPtr create(Opcode _op, ValPtr val1, ValPtr val2, BasicBlockPtr atBack);
};

/// @brief RetInst
class RetInst : public Instruction
{
    friend class Instruction;

public:
    /// @brief 析构
    ~RetInst() = default;

    /// @brief 无返回值  ret void
    RetInst()
    {
        setOpcode(Opcode::Ret);
    }

    /// @brief 构造
    /// @param val
    RetInst(ValPtr val)
    {
        operands.push_back(val);
        setOpcode(Opcode::Ret);
    }

    /// @brief 判断RetInst是否是死指令
    /// @return
    bool isDeadInst() override
    {
        return false; // retInst一定有用
    }

    /// @brief 创建 ret void
    /// @return
    static RetInstPtr get();

    /// @brief 创建 RetInst
    /// @param val
    /// @return
    static RetInstPtr get(ValPtr val);

    /// @brief 在atBack后创建RetInst  一个函数只有一个retInst
    /// @param atBack
    /// @return
    static RetInstPtr create(BasicBlockPtr atBack);

    /// @brief
    /// @param val
    /// @param atBack
    /// @return
    static RetInstPtr create(ValPtr val, BasicBlockPtr atBack);
};

class CallInst : public Instruction
{
public:
    /// @brief 析构
    ~CallInst() = default;

    /// @brief 构造函数
    /// @param fun
    /// @param relArgs
    CallInst(ValPtr fun, std::vector<ValPtr> &relArgs);

    /// @brief 判断CallInst是否是死指令
    /// @return
    bool isDeadInst() override;

    /// @brief 当调用函数结果是常数时自动替换传播 当然 函数调用一般不会删除 因为有副作用
    void AutoTransmitWhenIsConst() override;

    /// @brief 创建CallInst
    /// @param fun
    /// @param relArgs
    /// @return
    static CallInstPtr get(ValPtr fun, std::vector<ValPtr> &relArgs);

    /// @brief 在atBack basicblock后创建指令(具有判断功能，主要判断 relArgs类型是否与函数的参数类型相符，进行处理 如实参是 alloca,对应形参为 int  则需要load)
    /// @param fun
    /// @param relArgs
    /// @param atBack
    /// @return
    static CallInstPtr create(ValPtr fun, std::vector<ValPtr> &relArgs, BasicBlockPtr atBack);
};

class ICmpInst : public Instruction
{
public:
    /// @brief 析构
    ~ICmpInst() = default;

    /// @brief 构造函数
    /// @param _op
    /// @param val1
    /// @param val2
    ICmpInst(Opcode _op, ValPtr val1, ValPtr val2)
    {
        setOpcode(_op);
        operands.push_back(val1);
        operands.push_back(val2);
        setType(Type::getIntNType(1));
    }

    /// @brief 判断IcmpInst是否是死指令
    /// @return
    bool isDeadInst() override
    {
        if (getUseList().size() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /// @brief 当比较的结果是常数时自动替换传播
    void AutoTransmitWhenIsConst() override;

    /// @brief 创建ICmp
    /// @param _op
    /// @param val1
    /// @param val2
    /// @return
    static ICmpInstPtr get(Opcode _op, ValPtr val1, ValPtr val2);

    /// @brief 带有判断条件的 比较语句 主要判断 val1,val2 是不是allocaInst(allocaInst是地址，需要load)
    /// @param _op
    /// @param val1
    /// @param val2
    /// @param atBack
    /// @return
    static ICmpInstPtr create(Opcode _op, ValPtr val1, ValPtr val2, BasicBlockPtr atBack);
};

/// @brief 无条件跳转
class BranchInst : public Instruction
{
public:
    /// @brief 析构
    ~BranchInst() = default;

    /// @brief 无条件跳转 Goto
    /// @param ifTrue BasicBlock
    BranchInst(ValPtr ifTrue)
    {
        setOpcode(Opcode::Goto);
        operands.push_back(ifTrue);
    }

    /// @brief 条件跳转
    /// @param cond  i1 条件
    /// @param ifTrue 真basicblock
    /// @param ifFalse 假 basicblock
    BranchInst(ValPtr cond, ValPtr ifTrue, ValPtr ifFalse)
    {
        setOpcode(Opcode::ConditionBr);
        operands.push_back(cond);    // 0
        operands.push_back(ifTrue);  // 1
        operands.push_back(ifFalse); // 2
    }

    /// @brief 判断BranchInst是否是死指令
    /// @return
    bool isDeadInst() override
    {
        // 分支指令没有 User
        return false;
    }

    /// @brief 当 条件跳转的条件确定或者真假出口相同时 自动替换
    void AutoTransmitWhenIsConst() override;

    /// @brief 获取BrachInst goto
    /// @param ifTrue
    /// @return
    static BranchInstPtr get(ValPtr ifTrue);

    /// @brief 获取条件跳转
    /// @param cond 条件
    /// @param ifTrue 真 basicblock
    /// @param ifFalse 假 basicBlock
    /// @return
    static BranchInstPtr get(ValPtr cond, ValPtr ifTrue, ValPtr ifFalse);
};

/// @brief 获取数组偏移指针的指令
/// 实际上 该指令具有较多功能，在这里仅仅用于数组指针偏移  因此只有两个操作数 一个为数组的基地址，一个为偏移的大小(没有乘元素的字节数)
class getelementptrInst : public Instruction
{
private:
    int gainDim = -1; // 获取所在维度的偏移指针  指定维度(从0开始)
    // 如 对于 [8 x i32]*  若gainDim为0 则得到 [8 x i32]* 指针
    // 瑞gainDim为1，则得到i32*, 上面示例中gainDim 的大小最多为 1
    // gainDim只是一个标记 不作为操作数
    // 操作数为 数组基质 和 偏移(非字节偏移)

public:
    /// @brief 析构函数
    ~getelementptrInst() = default;

    /// @brief 设置 gainDim
    /// @param dim
    void setgainDim(int dim) { gainDim = dim; };

    /// @brief 获取 gainDim
    /// @return
    int getgainDim() { return gainDim; }

    /// @brief 获取gainDim对应的Bytes 字节数 如果gainDim 指向的是数组的最后一个维度元素 则为4字节
    /// @return
    int getgainDimBytes();

    /// @brief 构造函数
    /// @param arrayBaseAdress
    /// @param gainDim
    /// @param offset
    getelementptrInst(ValPtr arrayBaseAdress, int _gainDim, ValPtr offset);

    /// @brief 判断getelementptrInst是否是死指令
    /// @return
    bool isDeadInst() override
    {
        if (getUseList().size() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /// @brief 创建指令
    /// @param arrayBaseAdress
    /// @param offset
    /// @return
    static getelemInstPtr get(ValPtr arrayBaseAdress, int _gainDim, ValPtr offset);

    /// @brief 具有判断功能的指令创建(如判断arrayBaseAdress是数组基地址还是基地址的位置 根据arrayBaseAdress类型和dim数组结合判断指令的类型)
    /// @param arrayBaseAdress 数组基址
    /// @param dims 数组各个维度的索引值 包含表达式 变量
    /// @param atBack 插入指令到尾部
    /// @return
    static getelemInstPtr create(ValPtr arrayBaseAdress, std::vector<ValPtr> dims, BasicBlockPtr atBack);
};

/// @brief 用于将 i1扩展为 i32指令 目前只有这一个功能
class ZextInst : public Instruction
{
public:
    /// @brief 析构函数
    ~ZextInst() = default;

    /// @brief 构造函数
    /// @param i1
    ZextInst(ValPtr i1, Type *i32);

    /// @brief 判断getelementptrInst是否是死指令
    /// @return
    bool isDeadInst() override
    {
        if (getUseList().size() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /// @brief 当 要转换的 i1 bool 结果为 true 或false 时自动转换传播
    void AutoTransmitWhenIsConst() override;

    /// @brief 获取智能指针对象
    /// @param i1
    /// @param i32
    /// @return
    static ZextInstPtr get(ValPtr i1, Type *i32);
};

// phi节点
class PhiNode : public Instruction
{
private:
    ValPtr addr = nullptr; // 对应的alloca地址
    std::list<std::pair<ValPtr, BasicBlockPtr>> record;

public:
    /// @brief 析构函数
    ~PhiNode() { addr.reset(); }

    /// @brief 清空 打破可能的环(好像不存在环 还是写一下)
    void clear() override
    {
        Instruction::clear();
        addr.reset();
        record.clear();
    }

    /// @brief 获取phi节点对应的内存alloca地址
    /// @return
    ValPtr &getAddr() { return addr; }

    /// @brief 设置对应的alloca地址
    /// @param _addr
    void setAddr(ValPtr _addr) { addr = _addr; }

    /// @brief 默认构造函数
    PhiNode(ValPtr _addr)
    {
        setOpcode(Opcode::PhiNode);
        setAddr(_addr);
        Type *_addrTy = _addr->getType();
        PointerType *pty = static_cast<PointerType *>(_addrTy);
        setType(Type::copy(pty->getElemntTy()));
    }

    /// @brief 添加来源 在智能指针对象建立后使用否则会出错
    /// @param val
    void addSrc(ValPtr val, BasicBlockPtr blk);

    /// @brief 获取phi节点的记录
    /// @return
    inline std::list<std::pair<ValPtr, BasicBlockPtr>> &getSrc() { return record; }

    /// @brief 获取指定block的项
    /// @param blk
    /// @return
    inline ValPtr getSrcFromBlk(BasicBlockPtr blk)
    {
        for (auto &pair : record)
        {
            if (pair.second == blk)
            {
                return pair.first;
            }
        }
        return nullptr;
    }

    /// @brief 判断是否是死指令
    /// @return
    bool isDeadInst() override
    {
        if (getUseList().size() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /// 下面需要重写一下replaceUseWith以及removeUse 因为phi节点比较特殊 它的操作数不在operands中

    /// @brief 将操作数替换为指定的Value
    /// @param from 旧值
    /// @param to 替换值
    /// @return
    virtual bool replaceUseWith(ValPtr from, ValPtr to) override;

    /// @brief 删除使用
    /// @param val
    virtual void removeUse(ValPtr val) override;

    /// @brief 创建智能指针对象 (注意要使用setBBlockParent指定所在基本块)
    /// @param _addr
    /// @return
    static PhiNodePtr get(ValPtr _addr)
    {
        PhiNodePtr phi = std::make_shared<PhiNode>(_addr);
        return phi;
    }
};

/// @brief 伪指令用于phi节点删除时使用 move
class PhiElimMove : public Instruction
{
public:
    /// @brief 析构函数
    ~PhiElimMove() = default;

    /// @brief 构造函数
    /// @param phi
    /// @param src
    PhiElimMove(ValPtr phi, ValPtr src)
    {
        operands.push_back(phi);
        operands.push_back(src);
    }

    /// @brief 获取定义的value
    /// @return
    ValPtr getDef() { return getOperand(0); }

    /// @brief 获取使用的Value
    /// @return
    ValPtr getUse() { return getOperand(1); }

    /// @brief 创建智能指针对象
    /// @param phi
    /// @param src
    /// @return
    static PhiElimMovePtr get(ValPtr phi, ValPtr src)
    {
        PhiElimMovePtr mov = std::make_shared<PhiElimMove>(phi, src);
        // 就不维护 UserList了 这是伪指令 用于方便后继转换使用
        return mov;
    }
};

/// @brief bitcast指令
class BitCastInst : public Instruction
{
public:
    /// @brief 析构
    ~BitCastInst() = default;

    /// @brief 构造函数
    /// @param src
    /// @param dstTy
    BitCastInst(ValPtr src, Type *dstTy)
    {
        setOpcode(Opcode::BitCast);
        operands.push_back(src);
        setType(dstTy);
    }

    /// @brief 创建智能指针对象
    /// @param src
    /// @param dstTy
    /// @return
    static BitCastPtr get(ValPtr src, Type *dstTy)
    {
        BitCastPtr bitcast = std::make_shared<BitCastInst>(src, dstTy);
        src->insertUser(bitcast);
        return bitcast;
    }
};