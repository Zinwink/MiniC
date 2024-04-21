#include "Function.h"

/// @brief 获取对应的IR字符串表示
/// @return
string FunFormalParam::toString(Counter *cnt)
{
    string str = type.toString() + string(" noundef %") + std::to_string(cnt->getCount());
    return str;
}

/// @brief 析构函数
Function::~Function()
{

    for (auto param : FormalParamList)
    {
        delete param;
        param = nullptr;
    }
    FormalParamList.clear();
}

/// @brief 符号表
// SymTab *sym;
/// @brief 无参构造函数
Function::Function() : retType(BasicValueType::TYPE_MAX)
{
    funTab = new FuncTab();
    cnter = new Counter();
    IRCodes = new IRBlock();
}

/// @brief 根据名字以及返回类型进行构造
/// @param _name
/// @param retTy
Function::Function(std::string &_name, const ValueType &retTy)
{
    name = _name;
    retType = retTy;
    funTab = new FuncTab();
    cnter = new Counter();
    IRCodes = new IRBlock();
}

/// @brief 将函数转化为IR string表示
/// @param str 用于存储字符串
/// @return 字符串
string &Function::toString(string &str)
{
    str = string("\ndefine dso_local ") + retType.toString() + string(" @") + name + string("(");
    for (uint32_t i = 0; i < FormalParamList.size(); i++)
    {
        string paramStr = FormalParamList[i]->toString(cnter);
        str += paramStr;
        if (i != (FormalParamList.size() - 1))
        { // 不是最后一个形参
            str += string(", ");
        }
    }
    str += string(") {\n");
    // 先翻译加上函数中的alloca指令字符串
    for (auto &frontir : IRCodes->irfront())
    {
        string frontstr;
        frontstr = frontir->toString(frontstr, cnter);
        str += string(" "); // 缩进一格
        str += frontstr;
        str += string("\n"); // 换行
    }
    // 再依次翻译剩余的指令
    for (auto &backir : IRCodes->irback())
    {
        string backstr;
        backstr = backir->toString(backstr, cnter);
        str += string(" "); // 缩进一格
        str += backstr;
        str += string("\n"); // 换行
    }
    // 翻译完成 加上 }
    str += string("}\n");
    return str;
}