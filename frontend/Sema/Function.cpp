#include "Function.h"

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
