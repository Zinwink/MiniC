/**
 * @file StdFunc.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief  std库函数支持
 * @version 1.0
 * @date 2024-06-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <vector>
#include "Function.h"
#include "DerivedTypes.h"
#include "Type.h"

void initStdFunc(std::vector<FuncPtr> &stdFuns)
{
    if (stdFuns.size() > 0)
    {
        return;
    }
    std::vector<Type *> argTys;
    {
        // int getint()
        FunctionType *getintTy = FunctionType::get(Type::getIntNType(32));
        FuncPtr getint = Function::get(getintTy, "getint");
        getint->setBuildInTag();
        stdFuns.push_back(getint);
    }

    {
        // int getch()
        FunctionType *getchTy = FunctionType::get(Type::getIntNType(32));
        FuncPtr getch = Function::get(getchTy, "getch");
        getch->setBuildInTag();
        stdFuns.push_back(getch);
    }

    {
        // int getarray(int a[])
        argTys.clear();
        argTys.push_back(PointerType::get(Type::getIntNType(32)));
        FunctionType *getarrayTy = FunctionType::get(Type::getIntNType(32), argTys);
        FuncPtr getarray = Function::get(getarrayTy, "getarray");
        getarray->setBuildInTag();
        stdFuns.push_back(getarray);
    }

    {
        // void putint(int k)
        argTys.clear();
        argTys.push_back(Type::getIntNType(32));
        FunctionType *putintTy = FunctionType::get(Type::getVoidType(), argTys);
        FuncPtr putint = Function::get(putintTy, "putint");
        putint->setBuildInTag();
        stdFuns.push_back(putint);
    }

    {
        // void putch(int a);
        argTys.clear();
        argTys.push_back(Type::getIntNType(32));
        FunctionType *putchTy = FunctionType::get(Type::getVoidType(), argTys);
        FuncPtr putch = Function::get(putchTy, "putch");
        putch->setBuildInTag();
        stdFuns.push_back(putch);
    }

    {
        // void putarray(int n,int a[]);
        argTys.clear();
        argTys.push_back(Type::getIntNType(32));
        argTys.push_back(PointerType::get(Type::getIntNType(32)));
        FunctionType *putarrayTy = FunctionType::get(Type::getVoidType(), argTys);
        FuncPtr putarray = Function::get(putarrayTy, "putarray");
        putarray->setBuildInTag();
        stdFuns.push_back(putarray);
    }

    {
        // llvm.memset.p0i8.i64(i8*,i8,i64,i1)
        argTys.clear();
        argTys.push_back(PointerType::get(Type::getIntNType(8)));
        argTys.push_back(Type::getIntNType(8));
        argTys.push_back(Type::getIntNType(64));
        argTys.push_back(Type::getIntNType(1));
        FunctionType *llvm_memset = FunctionType::get(Type::getVoidType(), argTys);
        FuncPtr memset = Function::get(llvm_memset, "llvm.memset.p0i8.i64");
        memset->setBuildInTag();
        stdFuns.push_back(memset);
    }
    // 获取库函数列表
    argTys.clear();
}
