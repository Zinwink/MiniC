/**
 * @file GlobalVariable.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "GlobalVariable.h"
#include "Module.h"

/// @brief 全局变量翻译为文本
/// @param g
/// @param cnt
/// @return
string GlobalVariable::toIRstr(GlobalVariPtr g, Counter *cnt)
{
    // 目前只有int 只获取int
    string initiStr;
    ConstantPtr initi = g->getInitilizer();
    if (initi == nullptr)
    {
        initiStr = (g->getElemTy()->isArrayType() ? string("zeroinitializer") : string("0"));
    }
    else
    {
        // 数组初始化列表类型
        if (initi->isGlobInitilizerList())
        {
            globInitilizerPtr initCast = std::static_pointer_cast<globInitilizer>(initi);
            initiStr = globInitilizer::toStr(initCast);
        }
        else
        {
            ConstantIntPtr conInt = std::static_pointer_cast<ConstantInt>(g->getInitilizer());
            initiStr = std::to_string(conInt->getValue());
        }
    }
    string str = string("@") + g->getName() + string(" = global ");
    if (initi != nullptr && !initi->isGlobInitList())
    { // 由于获取globInitilizer 时多编写了一个类型字符串 因此在这里判断一下 防止重复
        str += g->getElemTy()->TypeStr();
    }
    str += (string(" ") + initiStr);
    return str;
}

/// @brief 字节大小
/// @return
uint32_t GlobalVariable::byteSizes()
{
    int res = 0;
    if (getElemTy()->isIntegerType())
    {
        IntegerType *intTy = static_cast<IntegerType *>(getElemTy());
        res = (intTy->getBitsWidth()) / 8; // 字节数
    }
    else if (getElemTy()->isArrayType())
    {
        ArrayType *arrTy = static_cast<ArrayType *>(getElemTy());
        std::vector<int> arrDims = arrTy->getDimValues();
        // 累乘  目前只有 int 累乘后 乘4 就是了
        res = 1;
        for (auto &dim : arrDims)
        {
            res *= dim;
        }
        res *= 4;
    }
    return res;
}