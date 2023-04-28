#include <stdlib.h>
#include <iostream>

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

// 双链表的结点删除
// （仿照单链表写法，修改next为prior后还可以删除p的前一个结点）
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

// 双链表的结点删除
// （借助双链表特性，可以直接删除指定结点P）
bool DeleteNextDNode2(DNode *p)
{
    // 相当于找到了p的前继，然后执行删除（后继）
    p = p->prior;
    return DeleteNextDNode(p);
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
        std::cout << p->data << std::endl;
        p = p->next;
    }
}

// 双链表的后向遍历（跳过头结点）
void BackwardTraversal2(DNode *p)
{
    // 跳过头结点
    p = p->next;
    while (p != NULL)
    {
        // 对结点p的操作，如打印，查找
        std::cout << p->data << std::endl;
        p = p->next;
    }
}

// 双链表的前向遍历
void ForwardTraversal(DNode *p)
{
    while (p != NULL)
    {
        // 对结点p的操作，如打印，查找
        std::cout << p->data << std::endl;
        p = p->prior;
    }
}

// 双链表的前向遍历（跳过头结点）
void ForwardTraversal2(DNode *p)
{
    while (p->prior != NULL)
    {
        // 对结点p的操作，如打印，查找
        std::cout << p->data << std::endl;
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
    return (p->next == NULL);
}

// 判断结点p是否为循环双链表的表尾结点
bool isTail2(DLinkList L, DNode *p)
{
    return (p->next == L);
}

// 按位查找，返回第i个元素
DNode *GetElem(DLinkList L, int i)
{
    if (i < 0)
        return NULL;
    // 指针p指向当前扫描到的结点
    DNode *p;
    // 当前p指向的是第几个结点（第0个结点 头节点）
    int j = 0;
    // p指向头结点（第0个结点，不存数据）
    p = L;
    // 循环找到第i个结点
    while (p != NULL && j < i)
    {
        p = p->next;
        j++;
    }
    return p;
}

// 按值查找，找到数据域==e的结点
DNode *LocateElem(DLinkList L, int e)
{
    DNode *p = L->next;
    // 从第1个结点开始查找数据域为e的结点
    while (p != NULL && p->data != e)
        p = p->next;
    return p;
}

// 按位序插入
bool ListInsert(DLinkList &L, int i, int e)
{
    if (i < 1)
        return false;
    // 找到第i-1个结点
    DNode *p = GetElem(L, i - 1);
    DNode *s = (DNode *)malloc(sizeof(DNode));
    s->data = e;
    return InsertNextDNode(p, s);
}

// 按位序删除
bool ListDelete(DLinkList &L, int i, int &e)
{
    // 找到第i个结点
    DNode *p = GetElem(L, i);
    // i值不合法
    if (p == NULL)
        return false;
    // 删除该结点
    return DeleteNextDNode2(p);
}

// 用于方便展示四种遍历结果的函数
void TraversalSet(DLinkList L)
{
    // 后向遍历
    printf("后向遍历（带头结点脏数据）：\n");
    BackwardTraversal(L);
    printf("————————\n");
    printf("后向遍历（不带头结点脏数据）：\n");
    BackwardTraversal2(L);
    printf("————————\n");

    // 前向遍历（注意头指针L位置问题）
    DNode *L2 = L;
    while (L2->next != NULL)
    {
        L2 = L2->next;
    }
    printf("前向遍历（带头结点脏数据）：\n");
    ForwardTraversal(L2);
    printf("————————\n");
    printf("前向遍历（不带头结点脏数据）：\n");
    ForwardTraversal2(L2);
    printf("————————\n");
}

int main()
{
    DLinkList L;
    InitDLinkList(L);

    ListInsert(L, 1, 11);
    ListInsert(L, 2, 22);
    ListInsert(L, 3, 33);

    printf("插入之前：\n");
    TraversalSet(L);

    ListInsert(L, 2, 3);

    printf("插入之后：\n");
    TraversalSet(L);

    int e = -1;
    ListDelete(L, 2, e);

    printf("删除之后：\n");
    TraversalSet(L);

    // 查询第一个位置的元素
    printf("第一个位置的元素是: %d\n", GetElem(L, 1)->data);
    // 查询22所在位置
    // 这里的函数并不能返回位置，而是结点本身，这里查询一下prior和next的数据域。
    printf("22所在位置的上一个结点数据是: %d\n", LocateElem(L, 22)->prior->data);
    printf("22所在位置的下一个结点数据是: %d\n", LocateElem(L, 22)->next->data);

    return 0;
}