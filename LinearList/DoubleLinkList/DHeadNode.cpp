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

// 双链表的插入 在p节点后插入s结点
bool InsertNextDNode(DNode *p, DNode *s)
{
    // 非法参数
    if (p == NULL || s == NULL)
        return false;
    s->next = p->next;
    // 如果p结点有后继结点
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

int main()
{
    DLinkList L;
    InitDLinkList(L);
}