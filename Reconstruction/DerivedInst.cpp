/**
 * @file DerivedInst.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "DerivedInst.h"
#include "BasicBlock.h"

/// @brief 静态函数  获取指令对象指针
/// @param name
/// @param _allocatedTy
/// @return
AllocaInstPtr AllocaInst::get(string name, Type *_allocatedTy)
{
    AllocaInstPtr alloca = std::make_shared<AllocaInst>(_allocatedTy);
    alloca->setName(name);    // 设置名字
    alloca->updateUserList(); // 更新使用者的UserList
    return alloca;
}

/// @brief 创建指令StoreInst
/// @param val
/// @param Ptr
/// @return
StoreInstPtr StoreInst::get(ValPtr val, ValPtr Ptr)
{
    StoreInstPtr store = std::make_shared<StoreInst>(val, Ptr);
    store->updateUserList();
    return store;
}

/// @brief 在atBack基本快后创建指令(有条件判断)
/// @param val
/// @param Ptr
/// @return
StoreInstPtr StoreInst::create(ValPtr val, ValPtr Ptr, BasicBlockPtr atBack)
{
    ValPtr src = val;
    if (val->getType()->isPointerType())
    {
        LoadInstPtr load = LoadInst::get(val);
        atBack->AddInstBack(load);
        src = load;
    }
    StoreInstPtr store = StoreInst::get(src, Ptr);
    atBack->AddInstBack(store);
    return store;
}

/// @brief 创建获取LoadInst
/// @param Ptr
/// @return
LoadInstPtr LoadInst::get(ValPtr Ptr)
{
    LoadInstPtr load = std::make_shared<LoadInst>(Ptr);
    load->updateUserList();
    return load;
}

/// @brief 创建BInaryOperator指令
/// @param _op
/// @param val1
/// @param val2
/// @return
BinaryOperatorPtr BinaryOperator::get(Opcode _op, ValPtr val1, ValPtr val2)
{
    BinaryOperatorPtr binaryOp = std::make_shared<BinaryOperator>(_op, val1, val2);
    binaryOp->updateUserList();
    return binaryOp;
}

/// @brief 在Block末尾创建BinaryOperator指令(该创建方法具有自动识别类型的功能)
/// @param _op
/// @param val1
/// @param val2
/// @param atBack
/// @return
BinaryOperatorPtr BinaryOperator::create(Opcode _op, ValPtr val1, ValPtr val2, BasicBlockPtr atBack)
{
    ValPtr left = val1;
    ValPtr right = val2;
    if (val1->getType()->isPointerType()) // 是指针类型(allocaInst)
    {
        LoadInstPtr leftLoad = LoadInst::get(val1);
        atBack->AddInstBack(leftLoad);
        left = leftLoad;
    }
    if (val2->getType()->isPointerType())
    {
        LoadInstPtr rightLoad = LoadInst::get(val2);
        atBack->AddInstBack(rightLoad);
        right = rightLoad;
    }
    BinaryOperatorPtr binaryOp = BinaryOperator::get(_op, left, right);
    atBack->AddInstBack(binaryOp);
    return binaryOp;
}

//************  RetInst  ***************
RetInstPtr RetInst::get(ValPtr val)
{
    RetInstPtr ret = std::make_shared<RetInst>(val);
    ret->updateUserList();
    return ret;
}

//**************** CallInst *****************
/// @brief 创建CallInst
/// @param fun
/// @param relArgs
/// @return
CallInstPtr CallInst::get(ValPtr fun, std::vector<ValPtr> &relArgs)
{
    CallInstPtr call = std::make_shared<CallInst>(fun, relArgs);
    call->updateUserList();
    return call;
}