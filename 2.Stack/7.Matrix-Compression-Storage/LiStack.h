// 这是一个为了 SparseMatrixSq.cpp 所修改的链栈

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct LinkNode
{
    // 数据域
    int i;
    int j;
    int v;
    // 指针域
    struct LinkNode *next;
} *LiStack;

// 初始化链栈
bool InitStack(LiStack &S)
{
    S = NULL;
    return true;
}

// 判断链栈是否为空
bool Empty(LiStack S)
{
    return (S == NULL);
}

// 进栈
bool Push(LiStack &S, int i, int j, int v)
{
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    // 内存分配失败
    if (s == NULL)
        return false;
    // 第一个结点的情况
    if (Empty(S))
    {
        s->i = i;
        s->j = j;
        s->v = v;
        s->next = S;
        S = s;
        return true;
    }
    // 第二个结点之后的情况
    // 指针p指向扫描到的结点
    LinkNode *p;
    // p指向第一个结点（注意：不是头节点）
    p = S;
    // 循环到最后一个结点
    while (p->next != NULL)
    {
        p = p->next;
    }
    // 将x给到s结点的data
    s->i = i;
    s->j = j;
    s->v = v;
    // s指向p指向的位置（NULL）
    s->next = p->next;
    // p指向s
    p->next = s;
    return true;
}

// 出栈
bool Pop(LiStack &S, int &i, int &j, int &v)
{
    // 栈空 报错
    if (Empty(S))
        return false;
    // 如果第一个结点的next为空，单独处理
    if (S->next == NULL)
    {
        printf("栈内最后一个元素Pop\n");
        i = S->i;
        j = S->j;
        v = S->v;
        free(S);
        S = NULL;
        return true;
    }
    // 指针p指向扫描到的结点
    LinkNode *p;
    LinkNode *e;
    // p指向第一个结点（注意：不是头节点）
    p = S;
    // 循环到倒数第二个结点
    while (p->next->next != NULL)
    {
        p = p->next;
    }
    // e指向最后一个结点
    e = p->next;
    // 最后一个结点的值给x
    i = e->i;
    j = e->j;
    v = e->v;
    // 倒数第二个结点指向NULL
    p->next = NULL;
    // 释放最后一个结点
    free(e);
    return true;
}

// 读取栈顶元素
bool GetTop(LiStack S, int &i, int &j, int &v)
{
    // 指针p指向扫描到的结点
    LinkNode *p;
    // p指向第一个结点（注意：不是头节点）
    p = S;
    if (p == NULL)
        return false;
    // 循环到最后一个结点
    while (p->next != NULL)
    {
        p = p->next;
    }
    // 将最后一个结点的值给x
    i = p->i;
    j = p->j;
    v = p->v;
    return true;
}

// 链栈的后向遍历
void BackwardTraversal(LinkNode *p)
{
    while (p != NULL)
    {
        // 对结点p的操作，如打印，查找
        printf("第%d行，第%d列的数值为：%d\n", (p->i) + 1, (p->j) + 1, (p->v) + 1);
        p = p->next;
    }
}