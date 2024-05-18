/**
 * @file AST_Graph.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-04-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "AST_Graph.h"

/// @brief 获取节点名字
/// @param node 节点
/// @return 字符串名
std::string getNodeName(ast_node *node)
{
    std::string name;
    switch (node->node_type)
    {
    case ast_node_type::AST_LEAF_LITERAL_INT:
        name = std::to_string(node->literal_val.digit.int32_digit);
        break;
    case ast_node_type::AST_LEAF_LITERAL_FLOAT:
        name = std::to_string(node->literal_val.digit.float_digit);
        break;
    case ast_node_type::AST_LEAF_LITERAL_UINT:
        name = std::to_string(node->literal_val.digit.uint32_digit);
        break;
    case ast_node_type::AST_LEAF_VAR_ID:
        name = node->literal_val.digit.id;
        break;
    case ast_node_type::AST_LEAF_CONST_VAR_ID:
        name = node->literal_val.digit.id;
        break;
    case ast_node_type::AST_OP_VAR_DEF:
        name = "=";
        break;
    case ast_node_type::AST_OP_CONST_VAR_DEF:
        name = "=";
        break;
    case ast_node_type::AST_OP_NEG:
        name = "negative";
        break;
    case ast_node_type::AST_OP_LEFT_SELF_SUB:
        name = "left --";
        break;
    case ast_node_type::AST_OP_RIGHT_SELF_SUB:
        name = "right --";
        break;
    case ast_node_type::AST_OP_LEFT_SELF_ADD:
        name = "left ++";
        break;
    case ast_node_type::AST_OP_RIGHT_SELF_ADD:
        name = "right ++";
        break;
    case ast_node_type::AST_OP_ADD:
        name = "+";
        break;
    case ast_node_type::AST_OP_SUB:
        name = "-";
        break;
    case ast_node_type::AST_OP_MUL:
        name = "*";
        break;
    case ast_node_type::AST_OP_DIV:
        name = "/";
        break;
    case ast_node_type::AST_OP_MOD:
        name = "%";
        break;
    case ast_node_type::AST_OP_ASSIGN:
        name = "=";
        break;
    case ast_node_type::AST_OP_COND_AND:
        name = "&&";
        break;
    case ast_node_type::AST_OP_COND_OR:
        name = "||";
        break;
    case ast_node_type::AST_OP_COND_NOT:
        name = "!";
        break;
    case ast_node_type::AST_OP_COND_EQU:
        name = "==";
        break;
    case ast_node_type::AST_OP_COND_NOTEQU:
        name = "!=";
        break;
    case ast_node_type::AST_OP_COND_LESS:
        name = "<";
        break;
    case ast_node_type::AST_OP_COND_GREATER:
        name = ">";
        break;
    case ast_node_type::AST_OP_COND_LESSEQU:
        name = "<=";
        break;
    case ast_node_type::AST_OP_COND_GREATEREQU:
        name = ">=";
        break;
    case ast_node_type::AST_OP_BLOCK:
        name = "block";
        break;
    case ast_node_type::AST_OP_EXPER:
        name = "expr";
        break;
    case ast_node_type::AST_OP_RETURN_STATEMENT:
        name = "return";
        break;
    case ast_node_type::AST_OP_BREAK:
        name = "break";
        break;
    case ast_node_type::AST_OP_CONTINUE:
        name = "continue";
        break;
    case ast_node_type::AST_OP_FUNC_DEF:
        name = "funcDef:" + std::string(node->literal_val.digit.id);
        break;
    case ast_node_type::AST_OP_FUNC_DECLARE:
        name = "funcDeclare:" + std::string(node->literal_val.digit.id);
        break;
    case ast_node_type::AST_OP_FUNC_FORMAL_PARAMS:
        name = "formal-params";
        break;
    case ast_node_type::AST_LEAF_FUNC_FORMAL_PARAM:
        name = node->literal_val.digit.id;
        // name = node->attr->TypeStr() + string(": ") + string(name);
        break;
    case ast_node_type::AST_OP_COMPILE_UNIT:
        name = "CompileUnit";
        break;
    case ast_node_type::AST_OP_FUNC_REAL_PARAMS:
        name = "real-params";
        break;
    case ast_node_type::AST_OP_FUNC_CALL:
        name = "fun-call:" + std::string(node->literal_val.digit.id);
        break;
    case ast_node_type::AST_OP_DECL_ITEMS:
        name = "DeclarationItems";
        name = string(name) + string(": ") + node->attr->TypeStr();
        break;
    case ast_node_type::AST_OP_CONST_DECL_ITEMS:
        name = "Const-DeclarationItems";
        name += string(": ") + node->attr->TypeStr();
        break;
    case ast_node_type::AST_OP_IFSTMT:
        name = "If-stmt";
        break;

    case ast_node_type::AST_OP_WHILESTMT:
        name = "While-stmt";
        break;
    case ast_node_type::AST_OP_DOWHILESTMT:
        name = "Do-while";
        break;

    case ast_node_type::AST_OP_ARRAY:
        name = node->literal_val.digit.id;
        name += ": array";
        break;
    case ast_node_type::AST_OP_ARRAY_INDEX:
        name = "array-index";
        break;

    case ast_node_type::AST_NULL:
        name = "[ ]";
        break;

    default:
        name = "unknown";
        break;
    }
    return name;
}

/// @brief 生成叶子节点的图形
/// @param g Agraph_t 图形对象
/// @param astnode ast节点
/// @return Agnode_t* 节点
Agnode_t *genLeafGraphNode(Agraph_t *g, ast_node *astnode)
{
    // 第三个参数1表示创建一个新节点，0表示如果已经存在相同名称节点，则不创建
    Agnode_t *node = agnode(g, (char *)nullptr, 1);
    if (node != nullptr)
    {
        std::string name = getNodeName(astnode);
        // 设置文本颜色与字体 black Simsun  最后一个参数为默认值 属性不存在则使用它
        agsafeset(node, (char *)"fontcolor", (char *)"black", (char *)"");
        agsafeset(node, (char *)"fontname", (char *)"SimSun", (char *)"");

        // 设置节点的名字label
        agsafeset(node, (char *)"label", (char *)name.c_str(), (char *)"");
        // 设置叶子节点形状为矩形
        agsafeset(node, (char *)"shape", (char *)"record", (char *)"");
        // 设置叶子节点填充颜色 黄色
        agsafeset(node, (char *)"style", (char *)"filled", (char *)"");
        agsafeset(node, (char *)"fillcolor", (char *)"yellow", (char *)"");
    }
    return node;
}

/// @brief 生成非叶子节点图形
/// @param g 图形对象
/// @param astnode
/// @return Agnode_t*
Agnode_t *genInternalGraphNode(Agraph_t *g, ast_node *astnode)
{
    // 得到astnode子节点对应的Agnode_t图可视化节点
    std::vector<Agnode_t *> Agsons;
    // 下面遍历astnode的子节点生成子节点对应Agnode_t
    for (auto &son : astnode->sons)
    {
        Agnode_t *ag_son = Traverse_AST(g, son);
        Agsons.push_back(ag_son);
    }
    // 创建该节点对应的图形Agnode_t节点
    Agnode_t *node = agnode(g, (char *)nullptr, 1);
    if (node != nullptr)
    {
        std::string name = getNodeName(astnode);
        // 设置父节点的显示效果
        agsafeset(node, (char *)"label", (char *)name.c_str(), (char *)"");
        agsafeset(node, (char *)"shape", (char *)"ellipse", (char *)"");
        // 下面设置父节点与子节点的边
        for (Agnode_t *agson : Agsons)
        {
            // 添加一条边
            agedge(g, node, agson, (char *)nullptr, 1);
        }
    }
    return node;
}

/// @brief 遍历AST,得到图形
/// @param g 图形对象
/// @param astnode
/// @return
Agnode_t *Traverse_AST(Agraph_t *g, ast_node *astnode)
{ // 递归
    if (astnode == nullptr)
    {
        return nullptr;
    }
    Agnode_t *root;
    if (isLeafNode(astnode))
    {
        // 为叶子节点
        root = genLeafGraphNode(g, astnode);
    }
    else
    {
        // 非叶子节点
        root = genInternalGraphNode(g, astnode);
    }
    return root;
}

/// @brief 可视化AST
/// @param root AST根节点
/// @param filePath AST保存的图片路径(包含图片名)
void VisualizeAST(ast_node *root, const std::string &filePath)
{
    // 先创建 gv上下文
    GVC_t *gv = gvContext();
    // 创建一个图形  参数依次表示 图形名称，有向图，使用默认的内存分配器
    Agraph_t *g = agopen((char *)"ast", Agdirected, nullptr);

    Traverse_AST(g, root); // 遍历产生Agrph图

    gvLayout(gv, g, "dot");
    // 保存图片格式类型
    std::string fileType;
    std::string::size_type pos = filePath.find_last_of('.'); // 查找最后一个点的位置
    if (pos == std::string::npos)
    {
        // 未找到  未指定类型
        fileType = "png";
    }
    else
    {
        fileType = filePath.substr(pos + 1); // 得到后面的文件类型后缀
    }
    // 输出图片
    gvRenderFilename(gv, g, fileType.c_str(), filePath.c_str());

    // 关闭图形上下文 清理资源
    gvFreeLayout(gv, g);
    agclose(g);
    gvFreeContext(gv);
}
