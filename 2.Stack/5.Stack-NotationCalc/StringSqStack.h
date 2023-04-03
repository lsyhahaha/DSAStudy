// 字符型顺序栈基本操作

#include <stdio.h>
#include <string>

#define MaxSize 20

namespace StringStack
{
    typedef struct
    {
        // 静态数组中存放栈元素
        std::string StringData[MaxSize];
        // 栈顶指针
        int top;
    } StringSqStack;

    // 初始化栈
    void InitStack(StringSqStack &S)
    {
        // 初始化栈顶指针
        S.top = -1;
    }

    // 判断栈空
    bool StackEmpty(StringSqStack S)
    {
        if (S.top == -1)
            return true;
        else
            return false;
    }

    // 新元素入栈
    bool Push(StringSqStack &S, std::string x)
    {
        // 栈满 报错
        if (S.top == MaxSize - 1)
            return false;
        // // 指针先加一
        // S.top = S.top + 1;
        // // 新元素入栈
        // S.StringData[S.top] = x;
        // 以上两行代码等价于
        // 先++ 先自加 后引用 注意顺序！
        S.StringData[++S.top] = x;
        return true;
    }

    // 出栈操作
    bool Pop(StringSqStack &S, std::string &x)
    {
        // 栈空 报错
        if (S.top == -1)
            return false;
        // // 栈顶元素先出栈
        // x = S.StringData[S.top];
        // // 指针再减一
        // S.top = S.top - 1;
        // 以上两行代码等价于
        // 注意--位置！
        x = S.StringData[S.top--];
        return true;
    }

    // 读取栈顶元素
    std::string GetTop(StringSqStack S)
    {
        // 栈空 报错
        if (S.top == -1)
            return "栈空";
        return S.StringData[S.top];
    }
}