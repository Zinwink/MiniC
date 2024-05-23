
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

#include <iostream>

int main()
{
    GenerateAST *excutor = new GenerateAST("/home/mole/Program/compile_principle/MiniC/tests/test2.c");
    excutor->run();
    // VisualizeAST(ast_root, "../tests/test2.png");

    ModulePtr module = Module::get();
    IRGenPtr codeGen = IRGen::get(ast_root, module);
    codeGen->run();
    ElimUseLessBBlock(module);

    eraseModuleDeadInst(module); // 删除死指令

    module->printIR("../tests/test1__13.ll");
    free_ast(ast_root);
    // 测试遍历ast得到llvm ir  仅测试简单用例
    // ScopeMg *scope = new ScopeMg();
    // IRGenerate *irgen = new IRGenerate(scope, ast_root);
    // irgen->run();
    // irgen->IR2Str("../tests/test2__self.ll");
    // TypePtr ty = Type::getIntNType(32);

    // ValPtr v1 = std::make_shared<Value>(Type::getLabelType());
    // ValPtr v2 = std::make_shared<Value>(Type::getLabelType());
    // new User(Type::getIntNType(32), {v1, v2});
    // UserPtr ptr(new User(Type::getIntNType(32), {v1, v2}));
    // ptr->updateUserList();
    // UserPtr ptr=std::make_shared<User>(Type::getIntNType(32), {v1, v2}));
    // UserPtr ptr = User::CreateUser(Type::getIntNType(32), {v1, v2});
    // std::cout << v1->getUseList().size() << std::endl;
    // std::cout << ptr->getOperandNum() << std::endl;
    // for (auto &p : v1->getUseList())
    // {
    //     std::cout << p << std::endl;
    // }
    // std::cout << ptr << std::endl;
    // ValPtr val = ptr;
    // std::cout << std::static_pointer_cast<User>(val) << std::endl;
    // val->clear();
    // ptr->clear();
    return 0;
}
