/**
 * @file BisonParser.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 语法分析共同头文件
 * @version 1.0
 * @date 2024-04-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "Literal_Val.h"

/// @brief yyparse的类型声明
#ifndef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse(void *YYPARSE_PARAM);
#else
int yyparse();
#endif
#else
#if defined __STDC__ || defined __cplusplus
int yyparse(void);
#else
int yyparse();
#endif();
#endif

#include "MiniCBison.h"