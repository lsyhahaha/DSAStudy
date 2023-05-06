#include <stdlib.h>
#include "LiBinTree.h"

// 链式队列结点
typedef struct LinkNode
{
    // 保存指针，而不是结点本身，更加省空间。
    BiTNode *data;
    struct LinkNode *next;
} LinkNode;

// 链式队列
typedef struct
{
    // 队列的头指针和尾指针
    LinkNode *front, *rear;
} LinkQueue;

// 初始化队列（带头结点）
void InitQueue(LinkQueue &Q)
{
    // 初始化时 头指针和尾指针都指向头结点
    Q.front = Q.rear = (LinkNode *)malloc(sizeof(LinkNode));
    // front的next指向NULL
    Q.front->next = NULL;
}

// 初始化队列（不带头结点）
void InitQueue2(LinkQueue &Q)
{
    // 初始化时，头指针和尾指针都指向NULL
    Q.front = NULL;
    Q.rear = NULL;
}

// 判空（带头结点）
bool IsEmpty(LinkQueue Q)
{
    return (Q.front == Q.rear);
    // 或
    // return (Q.front->next == NULL)
}

// 判空（不带头结点）
bool IsEmpty2(LinkQueue Q)
{
    return (Q.front == NULL);
}

// 入队（带头结点）
void EnQueue(LinkQueue &Q, BiTNode *x)
{
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    s->data = x;
    s->next = NULL;
    Q.rear->next = s;
    Q.rear = s;
}

// 入队（不带头结点）
void EnQueue2(LinkQueue &Q, BiTNode *x)
{
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    s->data = x;
    s->next = NULL;
    // 在空队列中插入第一个元素
    if (Q.front == NULL)
    {
        // 修改队头队尾指针
        Q.front = s;
        Q.rear = s;
    }
    else
    {
        // 新结点插入到rear结点之后
        Q.rear->next = s;
        // 修改rear指针
        Q.rear = s;
    }
}

// 出队（带头结点）
bool DeQueue(LinkQueue &Q, BiTNode *&x)
{
    // 空队
    if (IsEmpty(Q))
        return false;
    LinkNode *p = Q.front->next;
    // 用变量x返回队头元素
    x = p->data;
    // 修改头结点的next指针
    Q.front->next = p->next;
    // 此次是最后一个结点出队
    if (Q.rear == p)
        // 修改rear指针指向头结点
        Q.rear = Q.front;
    // 释放结点空间
    free(p);
    return true;
}

// 出队（不带头结点）
bool DeQueue2(LinkQueue &Q, BiTNode *&x)
{
    // 空队
    if (IsEmpty2(Q))
        return false;
    // p指向此次出队的结点
    LinkNode *p = Q.front;
    // 用变量x返回队头元素
    x = p->data;
    // 修改front指针
    Q.front = p->next;
    // 此次是最后一个结点出队
    if (Q.rear == p)
    {
        // front和rear指针指向NULL
        Q.front = NULL;
        Q.rear = NULL;
    }
    // 释放结点空间
    free(p);
    return true;
}