/**
 * @file CFGUtils.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 控制流图的一些工具 可视化 求支配节点
 * @version 1.0
 * @date 2024-06-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "CFGUtils.h"
#include "Module.h"
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include <queue>
#include <iostream>

/// @brief 计算基本块的必经节点集
/// @param fun
/// @return
std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> CFGUtils::computeDoms(FuncPtr fun)
{
    std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> Doms; // 基本块的必经节点集
    auto &blockList = fun->getBasicBlocks();
    // 进行初始化
    BasicBlockPtr &entry = fun->getEntryBlock();
    Doms[entry].insert(entry); // 入口块加入自己

    /// 用于记录活动队列  如果前驱的dom 都不变 那么本块也不变；如果本快变了将直接后继块加入队列
    std::deque<BasicBlockPtr> workList;
    auto nextIter = std::next(blockList.begin());
    for (auto iter = nextIter; iter != blockList.end(); iter++)
    { // 除入口 其他块初始为全集
        auto &blk = *iter;
        Doms[blk].insert(blockList.begin(), blockList.end());
        workList.push_back(blk);
    }
    // 下面进行迭代数据流 获取结果
    while (!workList.empty())
    {
        BasicBlockPtr blk = workList.front();
        workList.pop_front(); // 弹出该块

        // dom[n]=n U {所有前驱 dom的交集}
        std::set<BasicBlockPtr> oldDom = Doms[blk];
        std::vector<BasicBlockPtr> preds = blk->getImmedPreds();
        std::set<BasicBlockPtr> predInsert; // 记录所有前驱的交集
        Doms[blk] = {blk};
        if (preds.size() > 0)
        {
            predInsert = Doms[preds[0]];
        }
        for (size_t i = 1; i < preds.size(); i++)
        {
            std::set<BasicBlockPtr> tmp;
            std::set_intersection(predInsert.begin(), predInsert.end(),
                                  Doms[preds[i]].begin(), Doms[preds[i]].end(), std::inserter(tmp, tmp.end()));
            predInsert = tmp; // 迭代
        }
        Doms[blk].insert(predInsert.begin(), predInsert.end());
        if (oldDom != Doms[blk])
        {
            // 如果发生了 改变 根据数据流方程会影响后继 DOms计算 因此将后继块加入队列
            auto succes = blk->getJumpList();
            for (auto &succ : succes)
            {
                workList.push_back(succ);
            }
        }
    }
    return Doms;
}

/// @brief 根据支配节点求解支配边界
/// @param fun
/// @param Doms
/// @return
std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> CFGUtils::computeDomFronter(FuncPtr fun, std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> &Doms)
{
    // 在已有支配节点的条件下计算支配边界
    std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> DomFronter;
    auto &blockList = fun->getBasicBlocks();
    // 逆序遍历基本块 根据支配边界的定义求解每个块的支配边界
    for (auto iter = blockList.rbegin(); iter != blockList.rend(); iter++)
    {
        auto &blk = *iter;
        auto preds = blk->getImmedPreds();
        for (auto &pred : preds)
        {
            for (auto &dom : Doms[pred])
            {
                // pred的支配节点
                // 如果前驱pred的支配节点 不严格支配该节点 则前驱的支配节点的支配边界中包含该节点
                // 根据定义
                auto isInDom = Doms[blk].find(dom);
                bool isSDom = (isInDom != Doms[blk].end()) && (*isInDom != blk); // 严格支配的定义 s dom a && s!=a;
                if (!isSDom)
                {
                    // 不严格支配 则说明 dom 的支配边界包含本节点
                    DomFronter[dom].insert(blk);
                }
            }
        }
    }
    return DomFronter;
}

/// @brief 根据支配节点求解 直接支配节点
/// @param fun
/// @param Doms
/// @return
std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> CFGUtils::computeIDom(FuncPtr fun, std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> &Doms)
{
    // 根据Doms 计算直接支配节点 也构成了支配树
    std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> IDoms;
    auto &blkList = fun->getBasicBlocks();
    for (auto &blk : blkList)
    {
        auto doms = Doms[blk]; // blk的支配点集
        doms.erase(blk);       // 先删除自身(没使用引用 不会更改参数)
        for (auto &dom : doms)
        {
            std::set<BasicBlockPtr> res = doms;
            res.erase(dom);
            // 看dom 是否支配剩余的节点 如果不支配 说明是blk的直接支配节点
            bool isIDom = true;
            for (auto &resElem : res)
            {
                isIDom = isIDom && (Doms[resElem].find(dom) == Doms[resElem].end());
            }
            if (isIDom)
            {
                IDoms[blk].insert(dom);
                break;
            }
        }
    }
    return IDoms;
}

/// @brief 根据Dom 获取支配树(先获取直接支配节点)
/// @param fun
/// @param Doms
/// @return
std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> CFGUtils::computeDFT(FuncPtr fun, std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> &Doms)
{
    std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> DFTree;
    // 获取直接支配节点
    std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> IDoms = CFGUtils::computeIDom(fun, Doms);
    // 遍历直接支配节点 得到支配树记录
    for (auto &elem : IDoms)
    {
        auto &blk = elem.first;
        auto &IdomSet = elem.second;
        assert(IdomSet.size() == 1);
        auto &idom = *(IdomSet.begin());
        DFTree[idom].insert(blk);
    }
    return DFTree;
}

// *******************  数据流图的可视化   ***************************
/// @brief 根据基本块得到对应的节点
/// @param g
/// @param blk
/// @param cnt
/// @return
Agnode_t *genBasicBlockNode(Agraph_t *g, BasicBlockPtr &blk, Counter *cnt, std::unordered_map<BasicBlockPtr, Agnode_t *> &record)
{
    // 第三个参数1表示创建一个新节点，0表示如果已经存在相同名称节点，则不创建
    auto iter = record.find(blk);
    if (iter == record.end())
    { // 无记录则创建
        Agnode_t *node = agnode(g, (char *)nullptr, 1);
        if (node != nullptr)
        {
            string blockName = getllvmID(blk, cnt);
            blockName.erase(0, 1); // 删除前面的百分号
            std::string label = "{" + blockName + ":\\l ";
            for (auto &inst : blk->getInstLists())
            {
                label += Instruction::toIRstr(inst, cnt);
                label += string("\\l ");
            }
            label.pop_back();
            if (blk->getJumpList().size() == 2)
            {
                label += "|{<s0>T|<s1>F}";
            }
            label += "}";
            // 设置文本颜色与字体 black Simsun  最后一个参数为默认值 属性不存在则使用它
            agsafeset(node, (char *)"fontcolor", (char *)"black", (char *)"");
            // 设置节点的名字label
            agsafeset(node, (char *)"label", (char *)label.c_str(), (char *)"");
            // 设置叶子节点形状为矩形
            agsafeset(node, (char *)"shape", (char *)"record", (char *)"");
            // 设置叶子节点填充颜色 黄色
            agsafeset(node, (char *)"style", (char *)"filled", (char *)"");
            agsafeset(node, (char *)"fillcolor", (char *)"#f59c7d70", (char *)"");
            agsafeset(node, (char *)"color", (char *)"#3d50c3ff", (char *)"");
            record.emplace(blk, node); // 加入记录中
        }
        return node;
    }
    else
    {
        // 存在记录则直接返回结果
        return iter->second;
    }
}

/// @brief 产生指定函数的控制流图
/// @param fun
/// @param filePath 路径
/// @return
void genCFG(FuncPtr fun, const std::string &filePath)
{
    // 先创建 gv上下文
    GVC_t *gv = gvContext();

    // 创建一个图形  参数依次表示 图形名称，有向图，使用默认的内存分配器
    string funcName = fun->getName();
    Agraph_t *g = agopen((char *)(funcName.c_str()), Agdirected, nullptr);
    if (!g)
    {
        gvFreeContext(gv);
        return;
    }
    string cfgName = string("CFG for ") + "\'" + fun->getName() + "\' " + "function";
    agsafeset(g, (char *)"label", (char *)cfgName.c_str(), (char *)"");
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
    // 下面遍历基本块形成控制流图
    std::unordered_map<BasicBlockPtr, Agnode_t *> record; // 记录已经产生节点的基本块
    auto &blkList = fun->getBasicBlocks();
    Counter cnt = Counter();
    // 先为每个block编号
    for (auto &blk : blkList)
    {
        getllvmID(blk, &cnt);
    }
    // 遍历blkList形成控制流图
    for (auto &blk : blkList)
    {
        Agnode_t *blkNode = genBasicBlockNode(g, blk, &cnt, record);
        auto succes = blk->getJumpList(); // 后继节点
        if (succes.size() == 1)
        {
            // 直接跳转
            Agnode_t *jump = genBasicBlockNode(g, succes[0], &cnt, record);
            Agedge_t *edge1 = agedge(g, blkNode, jump, (char *)nullptr, 1);
        }
        else if (succes.size() == 2)
        {
            Agnode_t *trueNode = genBasicBlockNode(g, succes[0], &cnt, record);
            Agnode_t *falseNode = genBasicBlockNode(g, succes[1], &cnt, record);
            Agedge_t *trueEdge = agedge(g, blkNode, trueNode, (char *)nullptr, 1);
            Agedge_t *falseEdge = agedge(g, blkNode, falseNode, (char *)nullptr, 1);
            agsafeset(trueEdge, (char *)"tailport", (char *)"s0", (char *)"");
            agsafeset(falseEdge, (char *)"tailport", (char *)"s1", (char *)"");
        }
    }
    gvLayout(gv, g, "dot");
    assert(gv != nullptr && g != nullptr && !fileType.empty() && !filePath.empty());
    // 输出图片
    gvRenderFilename(gv, g, fileType.c_str(), filePath.c_str());
    // 关闭图形上下文 清理资源
    record.clear();
    gvFreeLayout(gv, g);
    agclose(g);
    gvFreeContext(gv);
}