#include <iostream>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ThreadNode
{
    int data;
    struct ThreadNode *lchild, *rchild;
    // tag == 0：表示指针指向子结点
    // tag == 1：表示指针指向“线索”
    int ltag, rtag;
} ThreadNode, *ThreadTree;

void visit(ThreadNode *T)
{
    std::cout << "当前结点数据：" << T->data << std::endl;
}

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
        PostThread(T->lchild);
        PostThread(T->rchild);
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

// 后序线索化二叉树
void CreatePostThread(ThreadTree T)
{
    // 全局变量pre初始化为NULL
    pre = NULL;
    // 非空
    if (T != NULL)
    {
        // 后序线索化
        PostThread(T);
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
    root->ltag = 0;
    root->rtag = 0;
    return true;
}

// 插入结点。h表示插入左还是右
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
    c->ltag = 0;
    c->rtag = 0;
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

// —————— 先序前驱后继遍历 - 开始 ——————
// 先序遍历一定是从根结点开始
// 先序遍历某一节点的后续一定是左子结点，若没有则是右子结点

ThreadNode *NextPreNode(ThreadNode *p)
{
    if (p->rtag == 0 && p->lchild != NULL)
        return p->lchild;
    else
        return p->rchild;
}

void PreOrder(ThreadNode *T)
{
    for (ThreadNode *p = T; p != NULL; p = NextPreNode(p))
        visit(p);
}

// 先序线索二叉树没办法向中序线索二叉树那样找先序前驱，除非暴力遍历的土办法，或者修改二叉树结构（想办法找到父节点）。
// 1、如果p是父结点的左子结点，则p的前驱是父节点；
// 2、如果p是父结点的右子结点，父结点没有左子结点，则p的前驱是父结点；
// 3、如果p是父结点的右子结点，父结点有左子结点，则p的前驱是父结点左子树中最后一个先序遍历的结点；
// 4、如果p是整棵树的根节点，则p没有先序前驱。

// —————— 先序前驱后继遍历 - 结束 ——————

// —————— 中序前驱后继遍历 - 开始 ——————
// 中序遍历一定是从整个树的最左下（不一定是叶子结点）开始
// 中序遍历某一结点的后继一定是右子树最左下的结点（不一定是叶子结点）

// 找到以p为根的子树中，第一个被中序遍历的结点
ThreadNode *FirstNode(ThreadNode *p)
{
    // 循环找到“最左下的”结点（不一定是叶结点）
    while (p->ltag == 0)
        p = p->lchild;
    return p;
}

// 在中序线索二叉树中找到结点p的后继结点
ThreadNode *NextNode(ThreadNode *p)
{
    // 右子树“最左下”结点
    if (p->rtag == 0)
        return FirstNode(p->rchild);
    else
        // rtag == 1 直接返回
        return p->rchild;
}

// 对中序线索二叉树进行中序遍历（利用线索实现的非递归算法，空间复杂度O(1)）
void InOrder(ThreadNode *T)
{
    for (ThreadNode *p = FirstNode(T); p != NULL; p = NextNode(p))
        visit(p);
}

// 中序遍历找前驱，只要找到p结点左子树最右下的结点，即为p的前驱

// 找到以p为根的子树中，最后一个被中序遍历的结点
ThreadNode *LastNode(ThreadNode *p)
{
    // 循环找到“最右下”结点（不一定是叶结点）
    while (p->rtag == 0)
        p = p->rchild;
    return p;
}

// 在中序线索二叉树中找到结点p的前驱结点
ThreadNode *PreNode(ThreadNode *p)
{
    // 左子树中“最右下”结点
    if (p->ltag == 0)
        return LastNode(p->lchild);
    else
        // ltag == 1 直接返回
        return p->lchild;
}

// 对中序线索二叉树进行逆向中序遍历
void RevInOrder(ThreadNode *T)
{
    for (ThreadNode *p = LastNode(T); p != NULL; p = PreNode(p))
        visit(p);
}

// —————— 中序前驱后继遍历 - 结束 ——————

// —————— 后序前驱后继遍历 - 开始 ——————

// 后续前驱，如果有右子结点则为右子结点，否则为左子结点。

ThreadNode *PrePostNode(ThreadNode *p)
{
    if (p->ltag == 0 && p->rchild != NULL)
        return p->rchild;
    else
        return p->lchild;
}

void RevPostOrder(ThreadNode *T)
{
    for (ThreadNode *p = T; p != NULL; p = PrePostNode(p))
        visit(p);
}

// 后续后继，对于一个结点p来说，没办法在p为根的子树中找到p的后继。
// 除非使用先序前驱的那些解决方法，找到p的父结点。
// 1、如果能找到p的父结点，且p为右子结点，则p的父结点是p的后续后继；
// 2、如果能找到p的父结点，且p为左子结点，其右兄弟结点为空，则p的父结点是其后续后继；
// 3、如果能找到p的父结点，且p是左子结点，其右兄弟节点非空，则p的后续后继是其右兄弟结点按后续遍历第一个访问的结点。

// —————— 后序前驱后继遍历 - 结束 ——————

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

    // 请注意，这里不能同时运行三段代码

    // // 先序线索化二叉树
    // CreatePreThread(root);
    // std::cout << "先序线索化遍历：" << std::endl;
    // PreOrder(root);

    // // 中序线索化二叉树
    // CreateInThread(root);
    // std::cout << "中序线索化遍历：" << std::endl;
    // InOrder(root);
    // std::cout << "中序线索化逆向遍历：" << std::endl;
    // RevInOrder(root);

    // 后序线索化二叉树
    CreatePostThread(root);
    std::cout << "后序线索化遍历：" << std::endl;
    RevPostOrder(root);

    return 0;
}