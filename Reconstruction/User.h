/**
 * @file User.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include "Value.h"
#include <cassert>

class User : public Value, public std::enable_shared_from_this<User>
{
protected:
    std::vector<ValPtr> operands; // 操作数列表 （这里与ValPtr形成了环，无法自动销毁，需要手动调用clear()）

public:
    /// @brief 析构函数
    ~User()
    {
        operands.clear();
        operands.shrink_to_fit();
    }

    /// @brief 形成了环，需要调用打破环
    void clear() override
    {
        operands.clear();
        operands.shrink_to_fit();
    }

    /// @brief 构造函数
    /// @param _ty Type指针
    User(TypePtr _ty) : Value(_ty) {}

    /// @brief 构造函数
    /// @param _ty
    /// @param _operands
    User(TypePtr _ty, std::vector<ValPtr> &_operands) : Value(_ty)
    {
        for (ValPtr &op : _operands)
        {
            operands.push_back(op);
        }
        _operands.clear();
        operands.shrink_to_fit();
    }

    /// @brief 更新被使用用户的UserList,插入使用者
    void updateUserList()
    {
        for (auto &v : operands)
        {
            v->insertUser(shared_from_this());
        }
    }

    /// @brief 构造函数
    /// @param _ty
    /// @param _ops 支持使用1 {,,,,}列表初始化
    User(TypePtr _ty, std::initializer_list<ValPtr> _ops) : Value(_ty)
    {
        for (auto &op : _ops)
        {
            operands.push_back(op);
        }
    }

    /// @brief 静态构造
    /// @param _ty
    /// @return
    static UserPtr CreateUser(TypePtr _ty)
    {
        UserPtr ptr = std::make_shared<User>(_ty);
        return ptr;
    }

    /// @brief 静态构造
    /// @param _ty
    /// @param _operands
    /// @return
    static UserPtr CreateUser(TypePtr _ty, std::vector<ValPtr> &_operands)
    {
        UserPtr ptr = std::make_shared<User>(_ty, _operands);
        for (auto &op : _operands)
        {
            op->insertUser(ptr); // 被使用者插入使用者，记录
        }
        return ptr;
    }

    /// @brief 静态构造
    /// @param _ty
    /// @param _ops
    /// @return
    static UserPtr CreateUser(TypePtr _ty, std::initializer_list<ValPtr> _ops)
    {
        UserPtr ptr = std::make_shared<User>(_ty, _ops);
        for (auto &op : _ops)
        {
            op->insertUser(ptr);
        }
        return ptr;
    }

    /// @brief 获取操作数列表
    /// @return
    std::vector<ValPtr> &getOperandsList()
    {
        return operands;
    }

    /// @brief 返回操作数
    /// @param i
    /// @return
    ValPtr getOperand(unsigned i)
    {
        assert(i < operands.size() && "i is out the range of operands!");
        return operands[i];
    }

    /// @brief 得到操作数的个数
    /// @return
    unsigned getOperandNum() { return operands.size(); }

    /// @brief 将操作数替换为指定的Value
    /// @param from 旧值
    /// @param to 替换值
    /// @return
    bool replaceUseWith(ValPtr from, ValPtr to);
};