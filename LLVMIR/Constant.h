/**
 * @file Constant.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 常量类
 * @version 1.0
 * @date 2024-05-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "Value.h"
#include "Type.h"
#include "DerivedTypes.h"
#include <map>
#include <cassert>

class ConstantInt;
class Constant;
class globInitilizer;
using ConstantIntPtr = std::shared_ptr<ConstantInt>;
using ConstantPtr = std::shared_ptr<Constant>;
using globInitilizerPtr = std::shared_ptr<globInitilizer>;

/// @brief Constant类
class Constant : public Value
{
protected:
    unsigned SubclassData : 27;
    enum class ConstantTy
    {
        ConstantInt,
        GlobInitilizer,
        Unknown
    };

    ConstantTy cstantClass = ConstantTy::Unknown;

public:
    /// @brief 析构
    ~Constant() = default;
    /// @brief 默认无参构造
    Constant() { setSubClassID(Value::ConstantV); }

    /// @brief 构造
    /// @param _ty
    Constant(Type *_ty) : Value(_ty, Value::ConstantV) {}

    inline bool isConstantInt() { return cstantClass == ConstantTy::ConstantInt; }

    inline bool isGlobInitList() { return cstantClass == ConstantTy::GlobInitilizer; }
};

/// @brief ConstantInt类型
class ConstantInt : public Constant
{
private:
    string Cname;
    uint32_t data; // 存放int 的值

public:
    /// @brief 析构
    ~ConstantInt() = default;

    /// @brief 构造函数
    /// @param bits
    /// @param isSign
    ConstantInt(unsigned bits, bool isSign = true)
    {
        cstantClass = ConstantTy::ConstantInt;
        if (isSign)
        {
            setType(Type::getIntNType(bits)); // 设置类型  有符号整数
        }
        else
        {
            setType(Type::getUintNType(bits)); // 无符号整数
        }
    }

    /// @brief 获取Value名
    /// @return
    string getName() override { return Cname; }

    /// @brief 设置Value名
    /// @param name
    void setName(string &name) override
    {
        Cname = name;
        HasName = 1; // 有名字
    }

    /// @brief 设置值
    /// @param a
    void setValue(unsigned a) { data = a; }

    /// @brief 获取值(只存二进制码),，如果为有符号 使用 int 接受转型
    /// @return 默认为有符号
    int32_t getValue() { return data; }

    /// @brief 获取ConstantInt
    /// @param bits
    /// @param isSign
    /// @return
    static ConstantIntPtr get(unsigned bits, bool isSign = true)
    {
        ConstantIntPtr ptr = std::make_shared<ConstantInt>(bits, isSign);
        return ptr;
    }
};

/// @brief 全局变量数组使用的初始化列表
class globInitilizer : public Constant
{
private:
    std::vector<ValPtr> elems;

public:
    /// @brief 构造 函数
    /// @param ty
    globInitilizer(Type *ty)
    {
        setType(ty);
        cstantClass = ConstantTy::GlobInitilizer;
    }

    /// @brief 获取存储的列表
    /// @return
    std::vector<ValPtr> &getElems() { return elems; }

    /// @brief 加入元素
    /// @param val
    void addElem(ValPtr val)
    {
        elems.push_back(val);
    }

    /// @brief 创建智能指针对象
    /// @param ty
    /// @return
    static globInitilizerPtr get(Type *ty)
    {
        globInitilizerPtr init = std::make_shared<globInitilizer>(ty);
        return init;
    }

    /// @brief 根据数组维度信息对dst初始化，采用递归的形式
    /// @param dst 要初始化的对象
    /// @param dims 数组维度
    /// @param initVal 初始值
    static void initElem(globInitilizerPtr dst, std::vector<int> &dims, ValPtr initVal)
    {
        if (dims.size() == 0)
            return; // 为空的话结束
        if (dims.size() == 1)
        {
            // 只有1维的话 直接根据信息将元素加入
            for (int i = 0; i < dims[0]; i++)
            {
                dst->addElem(initVal);
            }
        }
        else
        {
            // 获取子块的维度信息(多维数组)
            std::vector<int> newDim(dims.begin() + 1, dims.end());
            for (int i = 0; i < dims[0]; i++)
            {
                ArrayType *arrty = ArrayType::get(newDim, Type::getIntNType(32)); // 默认元素类型维int 只写了int
                globInitilizerPtr elem = globInitilizer::get(arrty);
                initElem(elem, newDim, initVal); // 递归初始化elem
                // elem初始化完毕后 加入到dst中
                dst->addElem(elem);
            }
        }
    }

    /// @brief 根据record记录进行列表相应元素的替换
    /// @param dst 操作的全局变量初始化列表
    /// @param dims 维度信息
    /// @param record
    static void replaceValueInPos(globInitilizerPtr dst, std::vector<int> &dims, std::map<int, ValPtr> &record)
    {
        assert(dims.size() != 0);
        if (dims.size() == 1)
        {
            // 一维数组 直接根据record展平结果替换即可
            for (auto &pair : record)
            {
                int pos = pair.first;
                auto &val = pair.second;
                assert(val != nullptr);
                dst->getElems()[pos] = val;
            }
        }
        else
        {
            // 不止一维

            // 获取展开pos对应的每一维的下标
            auto getPosVec = [&](int _pos)
            {
                std::vector<int> res;
                int resDim = 1;
                for (int i = 0; i < dims.size(); i++)
                {
                    resDim *= dims[i];
                }
                int i = 0;
                do
                {
                    resDim = resDim / dims[i];
                    int merch = _pos / resDim; // 商
                    _pos = _pos % resDim;      // 余数
                    res.push_back(merch);
                    i++;
                } while (i < dims.size());
                return res;
            };
            for (auto &pair : record)
            {
                int pos = pair.first;
                auto &val = pair.second;
                auto dimVec = getPosVec(pos); // 获取下标表示
                auto initLizer = dst;
                for (int i = 0; i < dimVec.size() - 1; i++)
                {
                    initLizer = std::static_pointer_cast<globInitilizer>(initLizer->getElems()[dimVec[i]]);
                }
                assert(val != nullptr);
                initLizer->getElems()[dimVec[dimVec.size() - 1]] = val;
            }
        }
    }

    /// @brief 获取展平为一维的数据表示
    /// @param res
    /// @param init
    static void getFlattenDigit(std::vector<int> &res, globInitilizerPtr init)
    {
        auto &elems = init->getElems();
        for (auto &elem : elems)
        {
            if (elem->isGlobInitilizerList())
            {
                // 需要递归
                globInitilizerPtr elemInit = std::static_pointer_cast<globInitilizer>(elem);
                getFlattenDigit(res, elemInit);
            }
            else
            {
                // 得到数据
                assert(elem->isConstantInt()); // 目前支持int类型
                ConstantIntPtr intC = std::static_pointer_cast<ConstantInt>(elem);
                res.push_back(intC->getValue());
            }
        }
    }

    /// @brief 获取字符串表示
    /// @param init
    /// @return
    static string toStr(globInitilizerPtr init)
    {
        string str = init->getType()->TypeStr() + " ";
        str += "[";
        auto &elems = init->getElems();
        for (int i = 0; i < elems.size(); i++)
        {
            auto &elem = elems[i];
            assert(elem != nullptr);
            assert(elem->isConstant());
            if (elem->isGlobInitilizerList())
            {
                globInitilizerPtr cast = std::static_pointer_cast<globInitilizer>(elem);
                str += toStr(cast);
                if (i != (elems.size() - 1))
                {
                    str += ", ";
                }
            }
            else
            {
                assert(elem != nullptr);
                assert(elem->isConstantInt());
                ConstantIntPtr intv = std::static_pointer_cast<ConstantInt>(elem);
                string intStr = std::to_string(intv->getValue());
                str += (elem->getType()->TypeStr() + " " + intStr);
                if (i != (elems.size() - 1))
                {
                    str += ", ";
                }
            }
        }
        str += "]";
        return str;
    }
};