// 另一种链栈的实现，看了更好的实现后我一度以为自己“写反了”。
// 其实只是S结点的定义问题，按照书上的说法，S结点永远是栈顶结点，
// 但在这个实现里，S结点是栈底结点，每次循环到栈顶（够累的）

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct LinkNode
{
    // 数据域
    int data;
    // 指针域
    struct LinkNode *next;
} *LiStack;

// 初始化链栈
bool InitStack(LiStack &S)
{
    S = NULL;
    return true;
}

// 判断链栈是否为空
bool Empty(LiStack S)
{
    return (S == NULL);
}

// 进栈
bool Push(LiStack &S, int x)
{
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    // 内存分配失败
    if (s == NULL)
        return false;
    // 第一个结点的情况
    if (Empty(S))
    {
        s->data = x;
        s->next = S;
        S = s;
        return true;
    }
    // 第二个结点之后的情况
    // 指针p指向扫描到的结点
    LinkNode *p;
    // p指向第一个结点（注意：不是头节点）
    p = S;
    // 循环到最后一个结点
    while (p->next != NULL)
    {
        p = p->next;
    }
    // 将x给到s结点的data
    s->data = x;
    // s指向p指向的位置（NULL）
    s->next = p->next;
    // p指向s
    p->next = s;
    return true;
}

// 出栈
bool Pop(LiStack &S, int &x)
{
    // 栈空 报错
    if (Empty(S))
        return false;
    // 如果第一个结点的next为空，单独处理
    if (S->next == NULL)
    {
        printf("栈内最后一个元素Pop\n");
        x = S->data;
        free(S);
        S = NULL;
        return true;
    }
    // 指针p指向扫描到的结点
    LinkNode *p;
    LinkNode *e;
    // p指向第一个结点（注意：不是头节点）
    p = S;
    // 循环到倒数第二个结点
    while (p->next->next != NULL)
    {
        p = p->next;
    }
    // e指向最后一个结点
    e = p->next;
    // 最后一个结点的值给x
    x = e->data;
    // 倒数第二个结点指向NULL
    p->next = NULL;
    // 释放最后一个结点
    free(e);
    return true;
}

// 读取栈顶元素
int GetTop(LiStack S)
{
    // 指针p指向扫描到的结点
    LinkNode *p;
    // p指向第一个结点（注意：不是头节点）
    p = S;
    int x = -9999;
    if (p == NULL)
        return x;
    // 循环到最后一个结点
    while (p->next != NULL)
    {
        p = p->next;
    }
    // 将最后一个结点的值给x
    x = p->data;
    return x;
}

// 链栈的后向遍历
void BackwardTraversal(LinkNode *p)
{
    while (p != NULL)
    {
        // 对结点p的操作，如打印，查找
        printf("%d\n", p->data);
        p = p->next;
    }
}

int main()
{
    LiStack S;
    InitStack(S);

    Push(S, 1);
    Push(S, 9);
    Push(S, 1);
    Push(S, 5);
    Push(S, 4);
    Push(S, 0);
    Push(S, 3);
    Push(S, 0);
    Push(S, 1);
    Push(S, 0);
    Push(S, 7);

    printf("现在的栈状态：\n");
    BackwardTraversal(S);
    printf("栈顶元素是：%d\n", GetTop(S));
    printf("——————————\n");

    int x = 0;

    while (Pop(S, x))
    {
        printf("Pop掉：%d\n", x);
        printf("现在的栈状态：\n");
        BackwardTraversal(S);
        printf("栈顶元素是：%d\n", GetTop(S));
        printf("——————————\n");
    }

    return 0;
}