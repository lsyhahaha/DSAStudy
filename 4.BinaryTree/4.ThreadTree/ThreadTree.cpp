#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

typedef struct ThreadNode
{
    int data;
    struct ThreadNode *lchild, *rchild;
    // tag == 0：表示指针指向子结点
    // tag == 1：表示指针指向“线索”
    int ltag, rtag;
} ThreadNode, *ThreadTree;

// 全局变量pre，指向当前访问结点的前驱
ThreadNode *pre = NULL;

// ThreadVisit函数完成线索化
void ThreadVisit(ThreadNode *q)
{
    if (q->lchild == NULL)
    {
        // 左子树为空，建立前驱线索
        q->lchild = pre;
        q->ltag = 1;
    }
    if (pre != NULL && pre->rchild == NULL)
    {
        // 建立前驱节点的后继线索
        pre->rchild = q;
        pre->rtag = 1;
    }
    // 让pre指向当前q，为下次访问做准备
    pre = q;
}

// 先序遍历二叉树，一边遍历一边线索化
void PreThread(ThreadTree T)
{
    if (T != NULL)
    {
        ThreadVisit(T);
        // 先序线索化之后，左子结点可能是上一个结点
        if (T->ltag == 0)
            PreThread(T->lchild);
        PreThread(T->rchild);
    }
}

// 中序遍历二叉树，一边遍历一边线索化
void InThread(ThreadTree T)
{
    if (T != NULL)
    {
        InThread(T->lchild);
        ThreadVisit(T);
        InThread(T->rchild);
    }
}

// 后序遍历二叉树，一边遍历一边线索化
void PostThread(ThreadTree T)
{
    if (T != NULL)
    {
        InThread(T->lchild);
        InThread(T->rchild);
        ThreadVisit(T);
    }
}

// 先序线索化二叉树
void CreatePreThread(ThreadTree T)
{
    // 全局变量pre初始化为NULL
    pre = NULL;
    // 非空
    if (T != NULL)
    {
        // 中序线索化
        PreThread(T);
        // 处理最后一个结点
        if (pre->rchild == NULL)
            pre->rtag = 1;
    }
}

// 中序线索化二叉树
void CreateInThread(ThreadTree T)
{
    // 全局变量pre初始化为NULL
    pre = NULL;
    // 非空
    if (T != NULL)
    {
        // 中序线索化
        InThread(T);
        // 处理最后一个结点
        if (pre->rchild == NULL)
            pre->rtag = 1;
    }
}

// 根节点插入数据并初始化
bool InitTree(ThreadTree &root, int x)
{
    root = (ThreadTree)malloc(sizeof(ThreadNode));
    root->data = x;
    root->lchild = NULL;
    root->rchild = NULL;
    return true;
}

// h表示插入左还是右
bool InsertNode(ThreadNode *f, int x, int h)
{
    ThreadNode *c;
    // 申请内存空间
    c = (ThreadNode *)malloc(sizeof(ThreadNode));
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
    ThreadTree root = NULL;
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