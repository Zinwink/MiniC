
#include <cstdio>
#include "AST_Graph.h"
#include "GenerateAST.h"
#include "AST.h"

int main()
{
    printf("hello world");
    GenerateAST *excutor = new GenerateAST("/home/mole/Program/compile_principle/MiniC/tests/test2.c");
    excutor->run();
    VisualizeAST(ast_root, "../tests/test2.png");

    // 测试遍历ast得到llvm ir  仅测试简单用例
        


    return 0;
}
