#include <stddef.h>

typedef struct LNode
{
    int data;
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

int main()
{
    LinkList L;
    InitList(L);
}