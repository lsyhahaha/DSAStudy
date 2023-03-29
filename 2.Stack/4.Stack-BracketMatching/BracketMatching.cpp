#include <stdio.h>

#define MaxSize 10

typedef struct
{
    // 静态数组中存放栈元素
    char data[MaxSize];
    // 栈顶指针
    int top;
} SqStack;

// 初始化栈
void InitStack(SqStack &S)
{
    // 初始化栈顶指针
    S.top = -1;
}

// 判断栈空
bool StackEmpty(SqStack S)
{
    if (S.top == -1)
        return true;
    else
        return false;
}

// 新元素入栈
bool Push(SqStack &S, char x)
{
    // 栈满 报错
    if (S.top == MaxSize - 1)
        return false;
    // // 指针先加一
    // S.top = S.top + 1;
    // // 新元素入栈
    // S.data[S.top] = x;
    // 以上两行代码等价于
    // 先++ 先自加 后引用 注意顺序！
    S.data[++S.top] = x;
    return true;
}

// 出栈操作
bool Pop(SqStack &S, char &x)
{
    // 栈空 报错
    if (S.top == -1)
        return false;
    // // 栈顶元素先出栈
    // x = S.data[S.top];
    // // 指针再减一
    // S.top = S.top - 1;
    // 以上两行代码等价于
    // 注意--位置！
    x = S.data[S.top--];
    return true;
}

// 读取栈顶元素
bool GetTop(SqStack S, int &x)
{
    // 栈空 报错
    if (S.top == -1)
        return false;
    // x记录栈顶元素
    x = S.data[S.top];
    return true;
}

// 销毁栈：函数运行结束后自动回收内存

bool bracketCheck(SqStack S, char str[], int length)
{
    for (int i = 0; i < length; i++)
    {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{')
        {
            // 扫描到左括号入栈
            Push(S, str[i]);
        }
        else
        {
            // 扫描到右括号 且当前栈空
            if (StackEmpty(S))
                // 匹配失败
                return false;

            char topElem;
            // 出栈
            Pop(S, topElem);
            if (str[i] == ')' && topElem != '(')
                return false;
            if (str[i] == ']' && topElem != '[')
                return false;
            if (str[i] == '}' && topElem != '{')
                return false;
        }
    }
    // 最后 栈空则匹配成功
    return StackEmpty(S);
}

int main()
{
    // 声明一个顺序栈（分配空间）
    SqStack S;
    InitStack(S);

    char bracketM[] = "{(([(]))}";

    printf("%d\n", bracketCheck(S, bracketM, 10));

    return 0;
}