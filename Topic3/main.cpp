/*
 *
 *  DataStructure-Topic3
 *
 *  Date: 2022/5/1
 *  Charset: UTF-8
 *  Language: cpp
 *
 *  Tested on gcc (GCC) 11.2.0, GNU ld (GNU Binutils) 2.38 (Linux version 5.15.32-1-MANJARO) and 
 * 
 *  Description: 从中序及后序遍历建立二叉树（createTreeFromInAndPostOrderTraverse函数），然后后序查找指定元素，并输出根结点到指定结点的路径。
 * 
 *  Usage:  输入二叉树的中序及后序遍历及查找元素，输出根结点到指定结点的路径。
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <stack>

using namespace std;
typedef char elem;   // 元素类型char
typedef bool status; // 状态类型bool
typedef struct bNode
{
    char data;           // 数据
    struct bNode *left;  // 左儿子指针
    struct bNode *right; // 右儿子指针
} bNode;                 //结点结构体

/**
 * @brief 创建一个二叉树结点
 *
 * @param data 结点数据
 * @return bNode* 结点指针
 */
bNode *createTreeNode(int data)
{
    bNode *node = (bNode *)malloc(sizeof(bNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * @brief 从中序和后序遍历序列构造二叉树
 *
 * @param InOrder 中序遍历
 * @param PostOrder 后序遍历
 * @return bNode* 根结点的指针
 */
bNode *createTreeFromInAndPostOrderTraverse(string InOrder, string PostOrder)
{
    if (!InOrder.size())
        return NULL; // 中序为空即结束

    int root = InOrder.find(PostOrder[PostOrder.size() - 1]);                                                                            // 获得根结点在中序遍历中的位置
    bNode *rootNode = createTreeNode(InOrder[root]);                                                                                     // 创建根结点
    rootNode->left = createTreeFromInAndPostOrderTraverse(InOrder.substr(0, root), PostOrder.substr(0, root));                           //递归建立左子树，左子树的前序遍历从0到root-1，后序遍历从0到root-1，获得的子字符串长度为root
    rootNode->right = createTreeFromInAndPostOrderTraverse(InOrder.substr(root + 1), PostOrder.substr(root, InOrder.size() - root - 1)); //递归建立右子树，左子树的前序遍历从root+1到size-1，后序遍历从root到size-1，获得的子字符串长度为size-root-1

    return rootNode; // 返回根结点
}

/**
 * @brief 倒序输出栈中内容作为路径
 *
 * @param nodeStack 访问栈
 */
void dumpStack(stack<bNode *> nodeStack)
{
    char dump[nodeStack.size()]; // 存储路径
    int cntdump = 0;             // 记录路径深度

    // 输出栈中内容
    while (!nodeStack.empty())
    {
        dump[cntdump++] = nodeStack.top()->data;
        nodeStack.pop();
    }
    reverse(dump, dump + cntdump); // 将数组内容反转

    // 输出路径
    printf("路径：");
    for (int i = 0; i < cntdump - 1; i++)
    {
        printf("%c->", dump[i]);
    }
    printf("%c\n", dump[cntdump - 1]);
    printf("路径长度：%d\n", cntdump);
}

/**
 * @brief 后序遍历
 *
 * @param root 根结点
 * @param target 查找目标
 */
void postOrderIterative(bNode *root, char target)
{
    if (root == NULL)
        return; // 空树 直接返回

    stack<bNode *> s;          // 新建栈存储结点指针
    bNode *currentNode = root; // 当前访问结点
    bNode *visitedNode = root; // 上次访问的结点

    // 当前结点非空，或栈非空时可以继续遍历
    while (currentNode || !s.empty())
    {
        // 沿左子树走到叶子结点, 并将叶子结点压入栈
        while (currentNode)
        {
            s.push(currentNode);
            currentNode = currentNode->left;
        }
        currentNode = s.top(); // 取栈顶元素即叶子结点的父结点
        // 如果栈顶元素有右子树，且未被访问
        if (currentNode->right && currentNode->right != visitedNode)
        {
            currentNode = currentNode->right; //存在右子树且未访问过，则访问右子树
        }
        else // 子树为空或被访问过
        {
            if (currentNode->data == target)
            { //若找到目标，则输出后退出
                dumpStack(s);
                return;
            }
            visitedNode = currentNode; // 记录当前访问的结点
            currentNode = NULL;        // 当前结点置为NULL，防止重复访问左子树
            s.pop();                   // 弹出访问过的结点
        }
    }
}

int main()
{
    string in, post;
    char target;
    cout << "请输入二叉树的中序及后序遍历和要查找的字符。" << endl;
    cin >> in >> post >> target;
    bNode *root = createTreeFromInAndPostOrderTraverse(in, post); //从中序和后序遍历建立二叉树
    postOrderIterative(root, target);
    return 0;
}