// 考研较多考

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// 二叉链表
typedef struct BiTNode
{
    // 数据域
    int data;
    // 左右子结点指针以及父节点指针
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 根节点插入数据并初始化
bool InitTree(BiTree &root, int x)
{
    root = (BiTree)malloc(sizeof(BiTNode));
    root->data = x;
    root->lchild = NULL;
    root->rchild = NULL;
    return true;
}

// h表示插入左还是右
bool InsertNode(BiTNode *f, int x, int h)
{
    BiTNode *c;
    // 申请内存空间
    c = (BiTNode *)malloc(sizeof(BiTNode));
    // 插入数据
    c->data = x;
    // 左右子结点指针
    c->lchild = NULL;
    c->rchild = NULL;
    if (f != c)
    {
        if (h == 0)
        {
            f->lchild = c;
        }
        else if (h == 1)
        {
            f->rchild = c;
        }
        else
        {
            std::cout << "变量 int h 填写有误，应为 0（代表左）或 1（代表右）" << std::endl;
            return false;
        }
    }
    return true;
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

    return 0;
}