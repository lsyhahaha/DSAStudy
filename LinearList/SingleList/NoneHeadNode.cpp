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
    LNode *p;
    int j = 1;
    p = L;
    while (p != NULL && j < i - 1)
    {
        p = p->next;
        j++;
    }
    if (p == NULL)
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

int main()
{
    LinkList L;
    InitList(L);
}