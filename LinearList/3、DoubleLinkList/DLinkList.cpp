#include <stdlib.h>

typedef struct DNode
{
    int data;
    struct DNode *prior, *next;
} DNode, *DLinkList;

// 初始化双链表
bool InitDLinkList(DLinkList &L)
{
    // 分配一个头结点
    L = (DNode *)malloc(sizeof(DNode));
    // 内存不足 分配失败
    if (L == NULL)
        return false;
    // 头结点的prior永远指向NULL
    L->prior = NULL;
    // 头结点之后暂时还没有结点
    L->next = NULL;
    return true;
}

// 初始化循环双链表
bool InitDLinkList2(DLinkList &L)
{
    // 分配一个头结点
    L = (DNode *)malloc(sizeof(DNode));
    // 内存不足 分配失败
    if (L == NULL)
        return false;
    // 头结点的prior指向头结点
    L->prior = L;
    // 头结点的next指向头结点
    L->next = L;
    return true;
}

// 双链表的插入 在p节点后插入s结点
bool InsertNextDNode(DNode *p, DNode *s)
{
    // 非法参数
    if (p == NULL || s == NULL)
        return false;
    s->next = p->next;
    // 如果p结点有后继结点
    // 对于循环双链表，可以没有这个判断条件
    if (p->next != NULL)
        p->next->prior = s;
    s->prior = p;
    p->next = s;
    return true;
}

// 双链表的删除
bool DeleteNextDNode(DNode *p)
{
    if (p == NULL)
        return false;
    DNode *q = p->next;
    if (q == NULL)
        return false;
    p->next = q->next;
    // 对于循环双链表，可以没有这个判断条件
    if (q->next != NULL)
        q->next->prior = p;
    free(q);
    return true;
}

// 销毁双链表
void DestoryList(DLinkList &L)
{
    // 循环释放各个数据节点
    while (L->next != NULL)
        DeleteNextDNode(L);
    // 释放头结点
    free(L);
    // 头指针指向NULL
    L = NULL;
}

// 双链表的后向遍历
void BackwardTraversal(DNode *p)
{
    while (p != NULL)
    {
        // 对结点p的操作，如打印，查找
        p = p->next;
    }
}

// 双链表的前向遍历
void ForwardTraversal(DNode *p)
{
    while (p != NULL)
    {
        // 对结点p的操作，如打印，查找
        p = p->prior;
    }
}

// 双链表的前向遍历（跳过头结点）
void ForwardTraversal2(DNode *p)
{
    while (p->prior != NULL)
    {
        // 对结点p的操作，如打印，查找
        p = p->prior;
    }
}

// 判断双链表是否为空
bool Empty(DLinkList L)
{
    if (L->next == NULL)
        return true;
    else
        return false;
}

// 判断循环双链表是否为空
bool Empty2(DLinkList L)
{
    if (L->next == L)
        return true;
    else
        return false;
}

// 判断结点p是否为双链表的表尾结点
bool isTail(DLinkList L, DNode *p)
{
    if (p->next == NULL)
        return true;
    else
        return false;
}

// 判断结点p是否为循环双链表的表尾结点
bool isTail(DLinkList L, DNode *p)
{
    if (p->next == L)
        return true;
    else
        return false;
}

int main()
{
    DLinkList L;
    InitDLinkList(L);
}