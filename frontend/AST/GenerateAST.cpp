/**
 * @file GenerateAST.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 执行词法语法分析得到ASt
 * @version 1.0
 * @date 2024-04-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "GenerateAST.h"
#include "BisonParser.h"
#include "FlexLexer.h"

/// @brief 执行前端分析
/// @return 执行成功 true 失败false
bool GenerateAST::run(bool showInfo)
{
    yyin = fopen(filepath.c_str(), "r");
    if (yyin == nullptr)
    {
        printf("File open failed %s\n", filepath.c_str());
        return false;
    }
    // 查看LALR移进规约过程 设置showInfo为true
    if (showInfo)
        yydebug = 1;

    bool result = yyparse();
    if (result != 0)
    {
        printf("yyparse failed\n");
        fclose(yyin); // 关闭文件
        return false;
    }

    fclose(yyin);
    return true;
}