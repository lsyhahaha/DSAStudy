#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "LiBinTree.h"

// 先序遍历操作过程
// 1、若二叉树为空，则什么也不做
// 2、若二叉树非空
//   1) 访问根节点
//   2) 先序遍历左子树
//   3) 先序遍历右子树
void PerOrder(BiTree T)
{
    if (T != NULL)
    {
        // 访问根节点
        visit(T);
        // 递归遍历左子树
        PerOrder(T->lchild);
        // 递归遍历右子树
        PerOrder(T->rchild);
    }
}

// 中序遍历操作过程
// 1、若二叉树为空，则什么也不做
// 2、若二叉树非空
//   1) 中序遍历左子树
//   2) 访问根节点
//   3) 中序遍历右子树
void InOrder(BiTree T)
{
    if (T != NULL)
    {
        InOrder(T->lchild);
        visit(T);
        InOrder(T->rchild);
    }
}

// 后序遍历操作过程
// 1、若二叉树为空，则什么也不做
// 2、若二叉树非空
//   1) 后序遍历左子树
//   2) 后序遍历右子树
//   3) 访问根节点
void PostOrder(BiTree T)
{
    if (T != NULL)
    {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        visit(T);
    }
}

// 求树的深度
int treeDepth(BiTree T)
{
    if (T == NULL)
    {
        return 0;
    }
    else
    {
        int l = treeDepth(T->lchild);
        int r = treeDepth(T->rchild);
        // 树的深度 = Max(左子树深度 右子树深度) + 1
        return l > r ? l + 1 : r + 1;
    }
}

int main()
{
    // 定义一颗空树
    BiTree root = NULL;
    InitTree(root, 1);

    InsertNode(root, 2, 0);
    InsertNode(root, 3, 1);
    InsertNode(root->lchild, 4, 0);
    InsertNode(root->lchild, 5, 1);

    std::cout << "根节点：" << root->data << std::endl
              << "根节点的左节点：" << root->lchild->data << std::endl
              << "根节点的右节点：" << root->rchild->data << std::endl
              << "根节点的左节点的左节点：" << root->lchild->lchild->data << std::endl
              << "根节点的左节点的右节点：" << root->lchild->rchild->data << std::endl;

    std::cout << "开始先序遍历！" << std::endl;
    PerOrder(root);
    std::cout << "开始中序遍历！" << std::endl;
    InOrder(root);
    std::cout << "开始后序遍历！" << std::endl;
    PostOrder(root);

    std::cout << "树的深度：" << treeDepth(root) << std::endl;

    return 0;
}