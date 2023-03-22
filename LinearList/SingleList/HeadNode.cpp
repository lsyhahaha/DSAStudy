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

int main()
{
    LinkList L;
    InitList(L);
}