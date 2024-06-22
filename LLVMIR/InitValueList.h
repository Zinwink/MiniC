/**
 * @file InitValueList.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 用于表示数组初始化列表
 * @version 1.0
 * @date 2024-06-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include "Value.h"
#include <map>

class InitValueList;
/// @brief 数组初始化列表
using InitListPtr = std::shared_ptr<InitValueList>;

/// @brief 初始值列表 作为容器使用 本身不设置类型
class InitValueList : public Value
{
private:
    /// @brief 列表元素  由于是value 因此元素也能存放InitValueList进行嵌套
    std::vector<ValPtr> elemList;

    bool hasConstQualifier = false; // 是否是const修饰 即是否是常量列表

public:
    /// @brief 构造函数数
    InitValueList()
    {
        setSubClassID(Value::InitValueList);
    }

public:
    /// @brief 获取数组的初始化列表中存放的元素
    /// @return
    std::vector<ValPtr> &getElems() { return elemList; }

    /// @brief 向数组初始化列表中添加元素
    /// @param val
    void addElem(ValPtr val) { elemList.push_back(val); }

    /// @brief 设置const修饰
    void setConstQualify() override { hasConstQualifier = true; }

    /// @brief 是否由const修饰
    /// @return
    bool isConstQualify() override
    {
        return hasConstQualifier;
    }

    /// @brief 创建InitListPtr指针
    /// @return
    static InitListPtr get()
    {
        InitListPtr res = std::make_shared<InitValueList>();
        return res;
    }
};

/// @brief 根据提供的维度新型得到数组初始化列表的分割映射结果(采用递归的方法分割 得到的映射结果为展开为1维索引的结果)
/// @param dims 使用的数组维度信息
/// @param initList 要处理的初始化列表
/// @param preInd 前一个索引
/// @param record  存放分割映射结果
void splitMapInitList(std::vector<int>& dims, InitListPtr initList, int preInd, std::map<int, ValPtr> &record)
{
    // 递归终止条件
    if (dims.size() == 0)
        return; // 传入的数组维度信息不存在时递归结束
    auto &elems = initList->getElems();
    int resDim = 1; // 记录Dims除第一位外后面维度的乘积长度(如int A[2][3][4] 的resDim=3*4 对于 int A[2]  resDim=1;)
    if (dims.size() > 1)
    {
        for (int i = 1; i < dims.size(); i++)
        {
            resDim *= dims[i];
        }
    }
    int curBraces = -1; // 当前属于的块
    for (int i = 0; i < elems.size(); i++)
    {
        auto &elem = elems[i];
        if (elem->isInitValueList())
        {
            // 元素还是一个符合的列表 {} 则递归分割
            // 先修正上一个块的隐含元素导致的元素不对齐
            // 对齐predInd
            preInd = (curBraces + 1) * resDim - 1;
            curBraces++;
            // 获取后面的维度信息 进行递归
            InitListPtr init = std::static_pointer_cast<InitValueList>(elem);
            std::vector<int> newDim(dims.begin() + 1, dims.end());
            splitMapInitList(newDim, init, preInd, record);
            // 递归结束后 对齐predInd 因为花括号中会隐含省略元素
            preInd = (curBraces + 1) * resDim - 1;
        }
        else
        {
            // 普通元素 遍历即可
            record.emplace(++preInd, elem);
            curBraces = preInd / resDim;
        }
    }
}