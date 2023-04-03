// 整型顺序栈基本操作

#include <stdio.h>
#include <string>
#include <iostream>

#define MaxSize 20

namespace IntStack
{
    typedef struct
    {
        // 静态数组中存放栈元素
        int intData[MaxSize];
        // 栈顶指针
        int top;
    } IntSqStack;

    // 初始化栈
    void InitStack(IntSqStack &S)
    {
        // 初始化栈顶指针
        S.top = -1;
    }

    // 判断栈空
    bool StackEmpty(IntSqStack S)
    {
        return (S.top == -1);
    }

    // 新元素入栈
    bool Push(IntSqStack &S, int x)
    {
        // 栈满 报错
        if (S.top == MaxSize - 1)
            return false;
        // 先++ 先自加 后引用 注意顺序！
        S.intData[++S.top] = x;
        return true;
    }

    // 出栈操作
    bool Pop(IntSqStack &S, int &x)
    {
        // 栈空 报错
        if (S.top == -1)
            return false;
        // 注意--位置！
        x = S.intData[S.top--];
        return true;
    }

    // 读取栈顶元素
    int GetTop(IntSqStack S)
    {
        // 栈空 报错
        if (S.top == -1)
            return false;
        // x记录栈顶元素
        return S.intData[S.top];
    }
}