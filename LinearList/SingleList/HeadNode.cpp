#include <stddef.h>
#include <stdlib.h>

typedef struct LNode
{
    // 节点内存储的数据
    int data;
    // 指向下一个节点
    struct LNode *next;
} LNode, *LinkList;

// LNode *L 声明一个指向单链表第一个节点的指针
// LinkList L 声明一个指向单链表第一个节点的指针，代码可读性更强

// 初始化链表（带头结点）
bool InitList(LinkList &L)
{
    L = (LNode *)malloc(sizeof(LNode));
    if (L == NULL)
        return false;
    L->next = NULL;
    return true;
}

// 判断链表是否为空
bool Empty(LinkList L)
{
    if (L->next == NULL)
        return true;
    else
        return false;
}

// 按位序插入
bool ListInsert(LinkList &L, int i, int e)
{
    // 找到第i-1个结点
    LNode *p = GetElem(L, i - 1);
    return InsertNextNode(p, e);
}

// 指定结点后插
bool InsertNextNode(LNode *p, int e)
{
    if (p == NULL)
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    // 内存分配失败
    if (s == NULL)
        return false;
    // 用结点s保存数据元素e
    s->data = e;
    s->next = p->next;
    // 将结点s连接到p后
    p->next = s;
    return true;
}

// 指定结点前插
bool InsertPriorNode(LNode *p, int e)
{
    if (p == NULL)
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    // 内存分配失败
    if (s == NULL)
        return false;
    s->next = p->next;
    // 新节点s连接到p后
    p->next = s;
    // 将p中元素复制到s中
    s->data = p->data;
    // p中元素覆盖为e
    p->data = e;
    return true;
}

// 按位序删除
bool ListDelete(LinkList &L, int i, int &e)
{
    // 找到第i-1个结点
    LNode *p = GetElem(L, i - 1);
    // i值不合法
    if (p == NULL)
        return false;
    // 第i-1个结点之后已无其他结点
    if (p->next == NULL)
        return false;
    // 令q指向被删除结点
    LNode *q = p->next;
    // 用e返回元素的值
    e = q->data;
    // 将*q结点从链中“断开”
    p->next = q->next;
    // 释放结点的存储空间
    free(q);
    // 删除成功
    return true;
}

// 删除指定节点p
bool DeleteNode(LNode *p)
{
    if (p == NULL)
        return false;
    // 令q指向*p的后继结点
    LNode *q = p->next;
    // 和后继结点交换数据域
    p->data = p->next->data;
    // 将*q结点从链中“断开”
    p->next = q->next;
    // 释放后继结点的存储空间
    free(q);
    return true;
}

// 按位查找，返回第i个元素
LNode *GetElem(LinkList L, int i)
{
    if (i < 0)
        return NULL;
    // 指针p指向当前扫描到的结点
    LNode *p;
    // 当前p指向的是第几个结点（第0个结点 头节点）
    int j = 0;
    // p指向第一个结点（注意：不是头节点）
    p = L;
    // 循环摘到第i个结点
    while (p != NULL && j < i)
    {
        p = p->next;
        j++;
    }
    return p;
}

int main()
{
    LinkList L;
    InitList(L);
}