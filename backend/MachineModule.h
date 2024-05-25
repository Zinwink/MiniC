/**
 * @file MachineModule.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <memory>

class MachineModule;
using MModulePtr = std::shared_ptr<MachineModule>;

class MachineModule
{
private:
    /* data */
public:
    MachineModule(/* args */);
    ~MachineModule();
};