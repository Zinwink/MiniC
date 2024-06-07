/**
 * @file Value.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief Value基类(是包括  Instruct,Constant,Function,Argument的父类)
 * @version 1.0
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include "Type.h"
#include <list>
#include <algorithm>
// #include <iostream>

class User;
class Value;
class Counter;
using ValPtr = std::shared_ptr<Value>;
using UserPtr = std::shared_ptr<User>;

/// @brief Value类，是所有包括Instruction,等的基类
class Value
{
public:
    enum SubClassID
    {
        InstructionVal, // 指令类型
        BasicBlockVal,  // 基本快
        ArgumentVal,    // 函数参数
        FunctionVal,    // 函数子类
        GlobalVari,     // 全局变量
        Constant,       // 常量基类(Int,  Expr等)
        Unknown         // 未知
    };

    using User_iterator = std::list<UserPtr>::iterator;

private:
    Type *ty = nullptr;          // 类型
    std::list<UserPtr> UserList; // 该Value被其他Value使用的记录列表
    SubClassID ValID;            // 标识

protected:
    unsigned HasName = 0;

public:
    /// @brief 析构
    ~Value()
    {
        // std::cout << "销毁" << std::endl;
        delete ty;
        ty = nullptr;
        UserList.clear();
    }

    /// @brief User,Value中的属性形成了环，释放时需要先调用释放内部引用计数
    virtual void clear();

    /// @brief 默认无参构造
    Value() : ValID(Value::Unknown){};

    /// @brief 构造函数
    /// @param _ty 类型
    Value(Type *_ty) : ty(_ty)
    {
    }

    /// @brief 构造函数
    /// @param _ty
    /// @param _id
    Value(Type *_ty, SubClassID _id) : ty(_ty), ValID(_id) {}

public:
    /// @brief 获取Value类型
    /// @return
    Type *getType() { return ty; }

    /// @brief 设置Type
    /// @param _ty
    void setType(Type *_ty) { ty = _ty; }

    /// @brief 获取子类类型
    /// @return
    SubClassID &getSubclassID() { return ValID; }

    /// @brief 设置SubClassID
    /// @param _id
    void setSubClassID(SubClassID _id) { ValID = _id; }

    bool hasName() { return HasName; }

    /// @brief 获取Value名
    /// @return
    virtual string getName() { return string("Null"); }

    /// @brief 设置Value名
    /// @param name
    virtual void setName(string &name) {}

    /// @brief 将所有使用本对象的User的本对象指针替换(可能用于优化时)
    /// @param _self 本对象
    /// @param newVal 替换值
    static void replaceAllUsesWith(ValPtr _self, ValPtr newVal);

    /// @brief 获取User列表
    /// @return
    std::list<UserPtr> &getUseList() { return UserList; }

    /// @brief 插入 USer
    /// @param user
    void insertUser(UserPtr user)
    {
        auto iter = std::find(UserList.begin(), UserList.end(), user);
        if (iter == UserList.end())
        { // 未找到  防止插入重复对象
            UserList.push_back(user);
        }
    }

    void deleteUser(UserPtr user)
    {
        // 删除USer  当User不在UserList中时不操作
        auto iter = std::find(UserList.begin(), UserList.end(), user);
        if (iter != UserList.end())
        {
            // 找到了
            UserList.erase(iter);
            // 删除该User
        }
    }

    /// @brief 判断是否是常数数值类型
    /// @return
    inline bool isConstant()
    {
        return getSubclassID() == Value::Constant;
    }

    /// @brief 是否是全局变量
    /// @return
    inline bool isGlobalVariable()
    {
        return getSubclassID() == Value::GlobalVari;
    }

    /// @brief 是否是指令类型
    /// @return
    inline bool isInstruct()
    {
        return getSubclassID() == Value::InstructionVal;
    }

    /// @brief 是否是Alloca
    /// @return
    bool isAllocaInst();

    /// @brief 是否是 getelementptr 指令
    /// @return
    bool isGetelemPtrInst();

    /// @brief 是否是整数比较指令
    /// @return
    bool isICmpInst();

    /// @brief 判断是 callInst
    /// @return
    bool isCallInst();

    /// @brief 是否是STore
    /// @return
    bool isStoreInst();

    /// @brief 是否是load
    /// @return 
    bool isLoadInst();

    /// @brief 是不是 zextinst
    /// @return
    bool isZextInst();

    /// @brief 是否是函数形参
    /// @return
    inline bool isArgument()
    {
        return getSubclassID() == Value::ArgumentVal;
    }

    /// @brief 是否是基本块类型
    /// @return
    inline bool isBasicBlockVal() { return getSubclassID() == Value::BasicBlockVal; }

    /// @brief 是否是指令产生的临时变量 如 call,BinaryInst,load,Icmp等指令产生的结果(为值类型 不包括getelementptr 产生的指针类型偏移地址)
    /// @return
    bool isTemporary();
};

/// @brief 获取 Val的 llvm 标识  可以是函数 全局变量 常量 %编号形式
/// @param val
/// @param cnt
/// @return
string getllvmID(ValPtr val, Counter *cnt);