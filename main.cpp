
#include <cstdio>
#include "AST_Graph.h"
#include "GenerateAST.h"
#include "AST.h"
#include "IRGenerate.h"

int main()
{
    GenerateAST *excutor = new GenerateAST("/home/mole/Program/compile_principle/MiniC/tests/test2.c");
    excutor->run();
    VisualizeAST(ast_root, "../tests/test2.png");

    // 测试遍历ast得到llvm ir  仅测试简单用例
    ScopeMg *scope = new ScopeMg();
    IRGenerate *irgen = new IRGenerate(scope, ast_root);
    irgen->run();
    irgen->IR2Str("../tests/test2__self.ll");

    return 0;
}
