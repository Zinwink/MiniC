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
#include "Argument.h"
#include "Function.h"
#include "Constant.h"
#include <iostream>

// *********************************** AllocaInst ***********************************************
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

/// @brief 获取alloca 申请的内存大小
/// @return
uint32_t AllocaInst::getAllocaSize()
{
    // 根据 alloca 的 Type *AllocatedType; 并结合是否是函数形参的alloca进行判断
    if (AllocatedType->isIntegerType())
    {
        // alloca 申请的内存是 int类型 4字节
        return 4;
    }
    else if (AllocatedType->isArrayType())
    {
        // alloca 申请的内存是数组类型 根据数组的大小判断
        ArrayType *arr = static_cast<ArrayType *>(AllocatedType); // 转型

        // 目前实现的内容来看 数组类型装的元素 的字节数一定为4字节 故在此简单判断编写
        std::vector<int> eachDimsV = arr->getDimValues();
        int numElems = 1;
        for (auto &dim : eachDimsV)
        {
            // 累乘获取元素数目
            numElems *= dim;
        }
        // 暂且是这样 目前数组单个值元素 是4字节
        return numElems * 4;
    }
    else if (AllocatedType->isPointerType())
    {
        // alloca 的是pointerTy  目前的实现内容来看只能是对形参为数组地址的alloca
        return 4;
    }
    // 其他情况（实现的内容里不包含 先默认为-1）
    return -1;
}

//************************************ StoreInst  **************************************************************
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
    if (val == Ptr)
    {
        // 对于 a=a 这样的不做操作
        return nullptr;
    }
    if (val->getType()->isPointerType())
    {
        LoadInstPtr load = LoadInst::get(val);
        atBack->AddInstBack(load);
        load->setBBlockParent(atBack);
        src = load;
    }
    StoreInstPtr store = StoreInst::get(src, Ptr);
    store->setBBlockParent(atBack);
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
        leftLoad->setBBlockParent(atBack);
        left = leftLoad;
    }
    if (val2->getType()->isPointerType())
    {
        LoadInstPtr rightLoad = LoadInst::get(val2);
        atBack->AddInstBack(rightLoad);
        rightLoad->setBBlockParent(atBack);
        right = rightLoad;
    }
    BinaryOperatorPtr binaryOp = BinaryOperator::get(_op, left, right);
    atBack->AddInstBack(binaryOp);
    binaryOp->setBBlockParent(atBack);
    return binaryOp;
}

//************  RetInst  ***************

/// @brief 创建 ret void
/// @return
RetInstPtr RetInst::get()
{
    RetInstPtr ret = std::make_shared<RetInst>();
    return ret;
}

RetInstPtr RetInst::get(ValPtr val)
{
    RetInstPtr ret = std::make_shared<RetInst>(val);
    ret->updateUserList();
    return ret;
}

/// @brief 在atBack后创建RetInst  一个函数只有一个retInst
/// @param atBack
/// @return
RetInstPtr RetInst::create(BasicBlockPtr atBack)
{
    RetInstPtr ret = RetInst::get();
    atBack->AddInstBack(ret);
    ret->setBBlockParent(atBack);
    return ret;
}

/// @brief
/// @param val
/// @param atBack
/// @return
RetInstPtr RetInst::create(ValPtr val, BasicBlockPtr atBack)
{
    RetInstPtr ret = RetInst::get(val);
    atBack->AddInstBack(ret);
    ret->setBBlockParent(atBack);
    return ret;
}

//**************** CallInst *****************

/// @brief 构造函数
/// @param fun
/// @param relArgs
CallInst::CallInst(ValPtr fun, std::vector<ValPtr> &relArgs)
{
    setOpcode(Opcode::Call);
    operands.push_back(fun);
    for (auto &arg : relArgs)
    {
        operands.push_back(arg);
    }
    // 设置 CallInst的类型
    FuncPtr func = std::static_pointer_cast<Function>(fun);
    setType(Type::copy(func->getReturnTy()));
}

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

/// @brief 在atBack basicblock后创建指令(具有判断功能，主要判断 relArgs类型是否与函数的参数类型相符，进行处理 如实参是 alloca,对应形参为 int  则需要load)
/// @param fun
/// @param relArgs
/// @param atBack
/// @return
CallInstPtr CallInst::create(ValPtr fun, std::vector<ValPtr> &relArgs, BasicBlockPtr atBack)
{
    // 目前函数的形参列表只有 数组*, int 这些类型，因此只对此基本简单判断，后继可扩充(添加类型转换指令等，或者支持其他指针类型参数)
    assert(fun->getSubclassID() == Value::FunctionVal && "not a function!");
    FuncPtr function = std::static_pointer_cast<Function>(fun);
    for (size_t i = 0; i < relArgs.size(); i++)
    {
        Type *argty = relArgs[i]->getType();
        if (argty->isPointerType())
        {
            // 简单判断 因为目前函数形参 只有 int (i32),类似于[3 x i32]* 或者int* 这样的数组指针
            // 在翻译astnode的过程中 relArgs 可能存在 int* (i32*) (是AllocaInst 或者数组索引的偏移指针), 或者 [3 x [3 x i32]]* （是AllocaInst,getelementptr）  数组类型
            // 对于 i32* 需要 loadInst  对于[3 x [3 x i32]]* 需要使用getelementptr 计算获取偏移 得到[3 x i32]* 类型偏移指针
            if (function->getArgsTy(i)->isIntegerType())
            {
                LoadInstPtr load = LoadInst::get(relArgs[i]);
                atBack->AddInstBack(load); // 加入loadInst
                load->setBBlockParent(atBack);
                relArgs[i] = load; // 替换修正为LoadInst
            }
            else
            {
                // 形参也为指针
                // 当前情形下，形参为指针只能是数组类型 i32*, [4 x i32]* 等
                // 为了判断方便 假设调用时实参的维度符合条件 则只需取实参的
                ConstantIntPtr offset = ConstantInt::get(32);
                offset->setValue(0);
                PointerType *argtyPtr = static_cast<PointerType *>(argty);
                if (argtyPtr->getElemntTy()->isPointerType() && relArgs[i]->isAllocaInst())
                {
                    // 创建 load指令
                    LoadInstPtr load = LoadInst::get(relArgs[i]);
                    atBack->AddInstBack(load);
                    load->setBBlockParent(atBack);
                    relArgs[i] = load;
                }
                getelemInstPtr getele = getelementptrInst::get(relArgs[i], 1, offset);
                relArgs[i] = getele;
                atBack->AddInstBack(getele);
                getele->setBBlockParent(atBack);
            }
        }
    }
    CallInstPtr call = CallInst::get(fun, relArgs); // relArgs修正完毕
    atBack->AddInstBack(call);                      // 加入call指令
    call->setBBlockParent(atBack);
    return call;
}

//******************** ICmpInst  **********************
/// @brief 创建ICmp
/// @param _op
/// @param val1
/// @param val2
/// @return
ICmpInstPtr ICmpInst::get(Opcode _op, ValPtr val1, ValPtr val2)
{
    ICmpInstPtr cmp = std::make_shared<ICmpInst>(_op, val1, val2);
    cmp->updateUserList();
    return cmp;
}

/// @brief 带有判断条件的 比较语句 主要判断 val1,val2 是不是allocaInst(allocaInst是地址，需要load)
/// @param _op
/// @param val1
/// @param val2
/// @param atBack
/// @return
ICmpInstPtr ICmpInst::create(Opcode _op, ValPtr val1, ValPtr val2, BasicBlockPtr atBack)
{
    ValPtr left = val1;
    ValPtr right = val2;
    if (val1->getType()->isPointerType()) // 是指针类型(allocaInst)
    {
        LoadInstPtr leftLoad = LoadInst::get(val1);
        atBack->AddInstBack(leftLoad);
        leftLoad->setBBlockParent(atBack);
        left = leftLoad;
    }
    if (val2->getType()->isPointerType())
    {
        LoadInstPtr rightLoad = LoadInst::get(val2);
        atBack->AddInstBack(rightLoad);
        rightLoad->setBBlockParent(atBack);
        right = rightLoad;
    }
    ICmpInstPtr icmp = ICmpInst::get(_op, left, right);
    atBack->AddInstBack(icmp);
    icmp->setBBlockParent(atBack);
    return icmp;
}

//******************** BranchInst ***********************

/// @brief 获取BrachInst goto
/// @param ifTrue
/// @return
BranchInstPtr BranchInst::get(ValPtr ifTrue)
{
    BranchInstPtr br = std::make_shared<BranchInst>(ifTrue);
    br->updateUserList();
    return br;
}

/// @brief 获取条件跳转
/// @param cond 条件
/// @param ifTrue 真 basicblock
/// @param ifFalse 假 basicBlock
/// @return
BranchInstPtr BranchInst::get(ValPtr cond, ValPtr ifTrue, ValPtr ifFalse)
{
    BranchInstPtr br = std::make_shared<BranchInst>(cond, ifTrue, ifFalse);
    br->updateUserList();
    return br;
}

//******************** getelementptrInst ************************

/// @brief 获取gainDim对应的Bytes 字节数 如果gainDim 指向的是数组的最后一个维度元素 则为4字节
/// @return
int getelementptrInst::getgainDimBytes()
{
    // 计算字节数 没有考虑其他元素类型 目前数组只有 int

    int res = -1;
    ValPtr baseAddr = getOperand(0); // 获取基址
    Type *addrTy = baseAddr->getType();
    // addrTy肯定是指针类型
    PointerType *addrTyP = static_cast<PointerType *>(addrTy);
    Type *containedTy = addrTyP->getElemntTy();
    if (containedTy->isIntegerType())
    {
        // 基地址是 int *一般这是数组形参引入的 如果是声明数组 肯定会有元素个数[3 x i32] *
        res = 4;
    }
    else
    {
        assert(containedTy->isArrayType() && "not a array type!");
        ArrayType *containdArrTy = static_cast<ArrayType *>(containedTy);
        std::vector<int> dimsV = containdArrTy->getDimValues(); // 获取各个维度的数值
        // 基地址是 [3 x i32]* 等类型
        // 如果 gainDIm 为0 则1字节数 为 4* (dimsV中所有各个维度的乘积)
        res = 1;
        for (size_t i = gainDim; i < dimsV.size(); i++)
        {
            res *= dimsV[i];
        }
        res *= 4;
    }
    assert(res != -1 && "gainDim may out of the array dims range!");
    return res;
}

/// @brief 构造函数
/// @param arrayBaseAdress
/// @param gainDim
/// @param offset
getelementptrInst::getelementptrInst(ValPtr arrayBaseAdress, int _gainDim, ValPtr offset)
{
    assert(arrayBaseAdress->getType()->isPointerType() && ">>>Error! file: DerivedInst.cpp");

    setgainDim(_gainDim);
    setOpcode(Opcode::GetelementPtr);
    operands.push_back(arrayBaseAdress);
    operands.push_back(offset);

    PointerType *ptrTy = static_cast<PointerType *>(arrayBaseAdress->getType());

    assert((ptrTy->getElemntTy()->isArrayType() || ptrTy->getElemntTy()->isIntegerType()) && "Error!");
    if (ptrTy->getElemntTy()->isIntegerType())
    {
        // 设置为 Int 因为只支持int
        setType(PointerType::get(Type::getIntNType(32)));
        gainDim = 0; // 一定为0
    }
    else
    {
        // 根据gainDim 判定类型 0 则为arrayBaseAdress
        // 1 则为 arrayBaseAdress 的element 元素* 指针
        ArrayType *arrTy = static_cast<ArrayType *>(ptrTy->getElemntTy());
        assert(_gainDim <= arrTy->getDims() && ">>>Error!: ");
        Type *curElemTy = arrTy;
        for (int i = 0; i < _gainDim; i++)
        {
            if (curElemTy->isArrayType())
            {
                ArrayType *tmp = static_cast<ArrayType *>(curElemTy);
                curElemTy = tmp->getContainedTy();
            }
        }
        setType(PointerType::get(Type::copy(curElemTy))); // 设置类型
    }
}

/// @brief 创建指令
/// @param arrayBaseAdress
/// @param offset
/// @return
getelemInstPtr getelementptrInst::get(ValPtr arrayBaseAdress, int _gainDim, ValPtr offset)
{
    // 目前情况下 offset一定非指针  是 i32 等类型
    assert(!offset->getType()->isPointerType() && ">>>>Error! file: DerivedInst.cpp");
    getelemInstPtr getelemPtr = std::make_shared<getelementptrInst>(arrayBaseAdress, _gainDim, offset);

    getelemPtr->updateUserList();
    return getelemPtr;
}

/// @brief 具有判断功能的指令创建(如判断arrayBaseAdress是数组基地址还是基地址的位置 )
/// @param arrayBaseAdress 数组基址
/// @param dims 数组各个维度的索引值 包含表达式 变量
/// @param atBack 插入指令到尾部
/// @return
getelemInstPtr getelementptrInst::create(ValPtr arrayBaseAdress, std::vector<ValPtr> dims, BasicBlockPtr atBack)
{
    assert(arrayBaseAdress->getType()->isPointerType() && "arrayBaseAdress is not a pointerType");
    PointerType *arrptr = static_cast<PointerType *>(arrayBaseAdress->getType());

    if (arrptr->getElemntTy()->isPointerType())
    { //  **
        PointerType *elemTy = static_cast<PointerType *>(arrptr->getElemntTy());
        // 目前的情况看 说明这是对形参的 Alloca  因此是指针的指针
        LoadInstPtr load = LoadInst::get(arrayBaseAdress);
        atBack->AddInstBack(load); // 加入load指令
        load->setBBlockParent(atBack);
        if (elemTy->getElemntTy()->isArrayType())
        {
            ArrayType *arrty = static_cast<ArrayType *>(elemTy->getElemntTy());

            std::vector<int> dimsOrd = arrty->getDimValues(); // 获取维度数据
            assert((dimsOrd.size() + 1) >= dims.size() && " logic error! large than the array dim! ");
            // 下面使用乘加指令
            ValPtr mulAdd = dims[0];
            if (mulAdd->getType()->isPointerType())
            {
                //  在单维数组中可能出现的情况 单位数组的索引可能使用一个 allocaInst 变量 那是i32*
                LoadInstPtr mulAddLoad = LoadInst::get(mulAdd);
                atBack->AddInstBack(mulAddLoad);
                mulAddLoad->setBBlockParent(atBack);
                mulAdd = mulAddLoad;
            }
            for (size_t i = 0; i < dimsOrd.size(); i++)
            {
                ConstantIntPtr cont = ConstantInt::get(32);
                cont->setValue(dimsOrd[i]);
                BinaryOperatorPtr mul = BinaryOperator::create(Opcode::MulInteger, mulAdd, cont, atBack);

                BinaryOperatorPtr add = BinaryOperator::create(Opcode::AddInteger, mul, dims[i + 1], atBack);
                mulAdd = add; // 迭代
            }
            getelemInstPtr getelem = getelementptrInst::get(load, dims.size() - 1, mulAdd);
            atBack->AddInstBack(getelem);
            getelem->setBBlockParent(atBack);
            return getelem;
        }
        else
        {
            // 一维形参数组 Alloca  i32**  只有1维
            ValPtr offset = dims[0];
            if (offset->getType()->isPointerType())
            {
                LoadInstPtr loadoff = LoadInst::get(offset);
                atBack->AddInstBack(loadoff);
                loadoff->setBBlockParent(atBack);
                offset = loadoff;
            }
            getelemInstPtr getelem = getelementptrInst::get(load, 0, offset);
            atBack->AddInstBack(getelem);
            getelem->setBBlockParent(atBack);
            return getelem;
        }
    }
    else
    {
        // elemet 维数组类型  [8 x i32]*  等  非函数形参数组地址拷贝
        // 下面使用乘加指令
        ArrayType *arrty = static_cast<ArrayType *>(arrptr->getElemntTy());
        ValPtr mulAdd = dims[0];
        if (mulAdd->getType()->isPointerType())
        {
            // 索引不是 i32 而是指针  这种情况出现在  索引是变量(AllocaInst)地址  如 A   A代表地址
            LoadInstPtr load = LoadInst::get(mulAdd);
            atBack->AddInstBack(load);
            load->setBBlockParent(atBack);
            mulAdd = load;
        }
        std::vector<int> dimsOrd = arrty->getDimValues(); // 获取维度数据

        for (size_t i = 1; i < dims.size(); i++)
        { //  非函数形参拷贝 可获得声明数组的完整大小 因此从第二位开始
            ConstantIntPtr cont = ConstantInt::get(32);
            cont->setValue(dimsOrd[i]);
            BinaryOperatorPtr mul = BinaryOperator::create(Opcode::MulInteger, mulAdd, cont, atBack);
            BinaryOperatorPtr add = BinaryOperator::create(Opcode::AddInteger, mul, dims[i], atBack);
            mulAdd = add; // 迭代
        }
        getelemInstPtr getelem = getelementptrInst::get(arrayBaseAdress, dims.size(), mulAdd);
        atBack->AddInstBack(getelem);
        getelem->setBBlockParent(atBack);
        return getelem;
    }
}