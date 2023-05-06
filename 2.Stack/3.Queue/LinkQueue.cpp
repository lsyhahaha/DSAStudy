#include <stdlib.h>
#include <iostream>

// 链式队列结点
typedef struct LinkNode
{
    int data;
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
void EnQueue(LinkQueue &Q, int x)
{
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    s->data = x;
    s->next = NULL;
    Q.rear->next = s;
    Q.rear = s;
}

// 入队（不带头结点）
void EnQueue2(LinkQueue &Q, int x)
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
bool DeQueue(LinkQueue &Q, int &x)
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
bool DeQueue2(LinkQueue &Q, int &x)
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

// 遍历队列（带头结点）
void Traversal(LinkQueue Q)
{
    LinkNode *p = Q.front;
    while (p->next != NULL)
    {
        std::cout << p->next->data << std::endl;
        p = p->next;
    }
}

// 遍历队列（不带头结点）
void Traversal2(LinkQueue Q)
{
    LinkNode *p = Q.front;
    while (p != NULL)
    {
        std::cout << p->data << std::endl;
        p = p->next;
    }
}

// 链队列除非内存不足，否则一般不会队满

int main()
{
    LinkQueue Q;

    // 带头结点方式
    std::cout << "带头结点：" << std::endl;
    InitQueue(Q);

    EnQueue(Q, 1);
    EnQueue(Q, 2);
    EnQueue(Q, 3);
    EnQueue(Q, 4);
    EnQueue(Q, 5);

    std::cout << "入队后：" << std::endl;
    Traversal(Q);

    int x = 0;
    std::cout << "出队：" << std::endl;
    DeQueue(Q, x);
    std::cout << x << std::endl;
    DeQueue(Q, x);
    std::cout << x << std::endl;
    DeQueue(Q, x);
    std::cout << x << std::endl;

    std::cout << "出队后：" << std::endl;
    Traversal(Q);

    std::cout << "队空：" << IsEmpty(Q) << std::endl;

    // 不带头结点方式
    std::cout << "不带头结点：" << std::endl;
    InitQueue2(Q);

    EnQueue2(Q, 1);
    EnQueue2(Q, 2);
    EnQueue2(Q, 3);
    EnQueue2(Q, 4);
    EnQueue2(Q, 5);

    std::cout << "入队后：" << std::endl;
    Traversal2(Q);

    x = 0;
    std::cout << "出队：" << std::endl;
    DeQueue2(Q, x);
    std::cout << x << std::endl;
    DeQueue2(Q, x);
    std::cout << x << std::endl;
    DeQueue2(Q, x);
    std::cout << x << std::endl;

    std::cout << "出队后：" << std::endl;
    Traversal2(Q);

    std::cout << "队空：" << IsEmpty(Q) << std::endl;

    return 0;
}