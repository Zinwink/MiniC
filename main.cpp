
#include <cstdio>
#include "AST_Graph.h"
#include "GenerateAST.h"
#include "AST.h"
#include "User.h"
#include "DerivedTypes.h"
#include "Type.h"
#include "Module.h"
#include "IRGen.h"
#include "ElimBasicBlock.h"
#include "DeadInstElim.h"
#include "MachineModule.h"
#include "ArmInstGen.h"
#include "LinearScan.h"
#include "getopt-port.h"
#include <iostream>

// /// @brief 是否显示帮助信息
// bool gShowHelp = false;

// /// @brief 显示抽象语法树，非线性IR
// int gShowAST = 0;

// /// @brief 产生线性IR，线性IR，默认输出
// int gShowLineIR = 0;

// /// @brief 显示汇编
// int gShowASM = 0;

// /// @brief 直接运行，默认运行
// int gDirectRun = 0;

// /// @brief 输出中间IR，含汇编或者自定义IR等，默认输出线性IR
// int gShowSymbol = 0;

// /// @brief 输入源文件
// std::string gInputFile;

// /// @brief 输出文件，不同的选项输出的内容不同
// std::string gOutputFile;

// /// @brief 显示帮助
// /// @param exeName
// void showHelp(const std::string &exeName)
// {
//     std::cout << exeName + " -S [-A | -D] [-a | -I] [-o output] source\n";
//     std::cout << exeName + " -R [-A | -D] source\n";
// }

// /// @brief 参数解析与有效性检查
// /// @param argc
// /// @param argv
// /// @return
// int ArgsAnalysis(int argc, char *argv[])
// {
//     int ch;

//     // 指定参数解析的选项，可识别-h、-o、-S、-a、-I、-R、-A、-D选项，并且-o要求必须要有附加参数
//     const char options[] = "ho:SaIRAD";

//     opterr = 1;

// lb_check:
//     while ((ch = getopt(argc, argv, options)) != -1)
//     {
//         switch (ch)
//         {
//         case 'h':
//             gShowHelp = true;
//             break;
//         case 'o':
//             gOutputFile = optarg;
//             break;
//         case 'S':
//             gShowSymbol = 1;
//             break;
//         case 'a':
//             gShowAST = 1;
//             break;
//         case 'I':
//             // 产生中间IR
//             gShowLineIR = 1;
//             break;
//         case 'R':
//             // 直接运行，默认运行
//             gDirectRun = 1;
//             break;
//         default:
//             return -1;
//             break; /* no break */
//         }
//     }

//     argc -= optind;
//     argv += optind;

//     if (argc >= 1)
//     {

//         // 第一次设置
//         if (gInputFile.empty())
//         {

//             gInputFile = argv[0];
//         }
//         else
//         {
//             // 重复设置则出错
//             return -1;
//         }

//         if (argc > 1)
//         {
//             // 多余一个参数，则说明输入的源文件后仍然有参数要解析
//             optind = 0;
//             goto lb_check;
//         }
//     }

//     // 必须指定输入文件和输出文件
//     if (gInputFile.length() == 0)
//     {
//         return -1;
//     }

//     // 这三者只能指定一个
//     int flag = gShowSymbol + gDirectRun;
//     if (flag != 1)
//     {
//         // 运行与中间IR只能同时选择一个
//         return -1;
//     }

//     flag = gShowLineIR + gShowAST;

//     if (gShowSymbol)
//     {

//         if (flag == 0)
//         {
//             // 没有指定，则输出汇编指令
//             gShowASM = 1;
//         }
//         else if (flag != 1)
//         {
//             // 线性中间IR、抽象语法树只能同时选择一个
//             return -1;
//         }
//     }
//     else
//     {
//         // 如果-S没有指定，但指定了-a等选项时，则失败
//         if (flag != 0)
//         {
//             return -1;
//         }
//     }

//     if (gOutputFile.empty())
//     {

//         // 默认文件名
//         if (gShowAST)
//         {
//             gOutputFile = "ast.png";
//         }
//         else if (gShowLineIR)
//         {
//             gOutputFile = "ir.ll";
//         }
//         else
//         {
//             gOutputFile = "asm.s";
//         }
//     }
//     else
//     {

//         // 直接运行时，文件不能指定
//         if (gDirectRun)
//         {
//             return -1;
//         }
//     }

//     return 0;
// }

// int main(int argc, char *argv[])
// {
//     // 默认返回值-1
//     int result = -1;
//     do
//     {
//         int subResult = ArgsAnalysis(argc, argv);
//         if (subResult < 0)
//         {
//             // 在终端显示程序帮助信息
//             showHelp(argv[0]);
//             // 错误不用设置，因此result默认值为-1
//             break;
//         }
//         // 显示帮助
//         if (gShowHelp)
//         {
//             // 在终端显示程序帮助信息
//             showHelp(argv[0]);
//             // 这里必须设置返回值，因默认值为-1
//             result = 0;
//             break;
//         }
//         // 产生抽象语法树
//         GenerateAST *excutor = new GenerateAST(gInputFile);
//         excutor->run();
//         // 输出AST
//         if (gShowAST)
//         {
//             VisualizeAST(ast_root, gOutputFile);
//             free_ast(ast_root); // 释放资源
//             result = 0;         // 返回结果正常
//             break;
//         }

//         ModulePtr module = Module::get();
//         IRGenPtr codeGen = IRGen::get(ast_root, module);
//         codeGen->run();
//         ElimUseLessBBlock(module);
//         ElimUseLessBBlock(module);
//         eraseModuleDeadInst(module); // 删除死指令

//         // 输出 线性IR
//         if (gShowLineIR)
//         {
//             module->printIR(gOutputFile);
//             result = 0;
//             break;
//         }

//         MModulePtr Mmodule = MachineModule::get();
//         ArmInstGenPtr ArmGen = ArmInstGen::get(module, Mmodule);
//         ArmGen->run();
//         LinearScanPtr linearscan = LinearScan::get(Mmodule);
//         linearscan->allocateReg(); // 分配寄存器

//         // 产生汇编
//         if (gShowASM)
//         {
//             Mmodule->printArm(gOutputFile);
//             Mmodule->clear();
//             result = 0;
//             break;
//         }

//     } while (false);
//     return result;
// }

int main()
{
    GenerateAST *excutor = new GenerateAST("../tests/test2.c");
    excutor->run();

    ModulePtr module = Module::get();
    IRGenPtr codeGen = IRGen::get(ast_root, module);
    codeGen->run();
    ElimUseLessBBlock(module);
    ElimUseLessBBlock(module);
    eraseModuleDeadInst(module); // 删除死指令

    MModulePtr Mmodule = MachineModule::get();
    ArmInstGenPtr ArmGen = ArmInstGen::get(module, Mmodule);
    ArmGen->run();
    LinearScanPtr linearscan = LinearScan::get(Mmodule);
    linearscan->allocateReg(); // 分配寄存器

    Mmodule->printArm("../tests/test2.s");
    Mmodule->clear();

    return 0;
}