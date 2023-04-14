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
    LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
    // 内存分配失败
    if (p == NULL)
        return false;
    // 将x给到p结点的data
    p->data = x;
    // p->next指向S指向的位置
    p->next = S;
    // p设为S结点
    S = p;
}

bool Pop(LiStack &S, int x)
{
    // 栈空 报错
    if (Empty(S))
        return false;

    // 将S设为p结点
    LinkNode *p;
    p = S;

    // 将栈顶元素给x
    x = S->data;
    // 将栈顶元素改为下一个（指针指向后一位）
    S = S->next;

    // 释放原来的栈顶元素
    free(p);

    return true;
}

// 读取栈顶元素
int GetTop(LiStack S)
{
    return S->data;
}

// 链栈的后向遍历
void BackwardTraversal(LiStack S)
{
    while (S != NULL)
    {
        // 对结点S的操作，如打印，查找
        printf("%d\n", S->data);
        S = S->next;
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