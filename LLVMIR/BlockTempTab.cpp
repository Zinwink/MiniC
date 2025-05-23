/**
 * @file BlockTempTab.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-04-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "BlockTempTab.h"
#include <cassert>

/// @brief 析构函数
BlockTempTab::~BlockTempTab()
{
    DeclVars.clear();
}

/// @brief 查找声明变量引用 (只用于确定使用的变量是哪一个作用域声明的，搜索域包含本符号表以及所有上层父符号表)
/// @param 查找变量名
/// @return 声明变量指针
ValPtr BlockTempTab::findDeclVar(string &name)
{
    BaseSymTab *cur = this;
    while (cur != nullptr)
    {                                                // 从当前表查起，向上查父符号表
        ValPtr val = cur->findDeclVarOfCurTab(name); // 调用cur进行cur指向表的查找
        if (val == nullptr)
        {
            // cur指向的当前符号表未找到  指向父表迭代
            cur = cur->getParent().get();
        }
        else
        { // 找到
            return val;
        }
    }
    cur = nullptr;
    // 循环结束 所有上层父表都为找到
    return nullptr;
}

/// @brief 为当前表新增声明变量
/// @param  变量
/// @return 变量
ValPtr BlockTempTab::newDeclVar(ValPtr var)
{
    assert(var != nullptr); // 参数一定不能为nullptr
    string name = var->getName();
    if (findDeclVarOfCurTab(name) == nullptr)
    {
        // 当前表中不存在该变量
        DeclVars.emplace(name, var); // 加入至查询哈希表
        return var;
    }
    else
    { // 存在该变量
        return nullptr;
    }
}

/// @brief 创建BlockTempTab表
/// @param _parent
/// @return
BaseSymTabPtr BlockTempTab::get(BaseSymTabPtr _parent )
{
    BaseSymTabPtr tab = std::make_shared<BlockTempTab>(_parent);
    return tab;
}
