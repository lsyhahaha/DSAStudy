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

// 初始化链表
bool InitList(LinkList &L)
{
    L = NULL;
    return true;
}

// 判断链表是否为空
bool Empty(LinkList L)
{
    return (L == NULL);
}

// 按位序插入
bool ListInsert(LinkList &L, int i, int e)
{
    if (i < 1)
        return false;
    // 处理第一个结点的操作与其他结点不同
    if (i == 1)
    {
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data = e;
        s->next = L;
        L = s;
        return true;
    }
    // 指针p指向当前扫描到的结点
    LNode *p;
    // 当前p指向的是第几个结点
    int j = 1;
    // p指向第一个结点（注意：不是头节点）
    p = L;
    // 循环摘到第i-1个结点
    while (p != NULL && j < i - 1)
    {
        p = p->next;
        j++;
    }
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

int main()
{
    LinkList L;
    InitList(L);
}