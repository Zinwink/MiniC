
#include <cstdio>
#include "AST_Graph.h"
#include "FrontEndExcutor.h"
#include "AST.h"

int main()
{
    printf("hello world");
    FrontEndExcutor *excutor = new FrontEndExcutor("/home/mole/Program/compile_principle/MiniC/tests/test1.c");
    excutor->run();
    VisualizeAST(ast_root, "../test1.png");
    return 0;
}
