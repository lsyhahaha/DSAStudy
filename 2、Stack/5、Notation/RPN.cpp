#include <stdio.h>
#include <string>
#include <iostream>

#define MaxSize 20

typedef struct
{
    // 静态数组中存放栈元素
    int data[MaxSize];
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
    return (S.top == -1);
}

// 新元素入栈
bool Push(SqStack &S, int x)
{
    // 栈满 报错
    if (S.top == MaxSize - 1)
        return false;
    // 先++ 先自加 后引用 注意顺序！
    S.data[++S.top] = x;
    return true;
}

// 出栈操作
bool Pop(SqStack &S, int &x)
{
    // 栈空 报错
    if (S.top == -1)
        return false;
    // 注意--位置！
    x = S.data[S.top--];
    return true;
}

// 读取栈顶元素
int GetTop(SqStack S)
{
    int x = -9999;
    // 栈空 报错
    if (S.top == -1)
        return false;
    // x记录栈顶元素
    x = S.data[S.top];
    return x;
}

// 后缀表达式计算
bool RPNCalc(SqStack S, std::string str[], int length)
{
    // 循环遍历字符串
    for (int i = 0; i < length; i++)
    {
        // 如果遇到运算符
        if (str[i] == "+" || str[i] == "-" || str[i] == "*" || str[i] == "/")
        {
            // 运算符
            std::string Operator = str[i];
            // 左右操作数
            int LeftElem = -9999;
            int RightElem = -9999;
            // 出栈 先出来的是右操作数
            Pop(S, RightElem);
            Pop(S, LeftElem);
            std::cout << "左操作数：" << LeftElem
                      << "，右操作数：" << RightElem
                      << "，运算符：" << Operator << std::endl;
            // 根据运算符计算 并入栈
            if (Operator == "+")
            {
                Push(S, LeftElem + RightElem);
                std::cout << "运算结果：" << LeftElem + RightElem << std::endl;
            }
            else if (Operator == "-")
            {
                Push(S, LeftElem - RightElem);
                std::cout << "运算结果：" << LeftElem - RightElem << std::endl;
            }
            else if (Operator == "*")
            {
                Push(S, LeftElem * RightElem);
                std::cout << "运算结果：" << LeftElem * RightElem << std::endl;
            }
            else if (Operator == "/")
            {
                Push(S, LeftElem / RightElem);
                std::cout << "运算结果：" << LeftElem / RightElem << std::endl;
            }
            else
            {
                // 运算符错误
                std::cout << "运算符错误" << std::endl;
                return false;
            }
        }
        // 如果不是运算符
        else
        {
            // 入栈 注意类型转换
            std::cout << "入栈元素：" << std::stoi(str[i]) << std::endl;
            Push(S, std::stoi(str[i]));
        }
    }
    return true;
}

int main()
{
    // 声明一个顺序栈（分配空间）
    SqStack S;
    InitStack(S);

    std::string Notation[] = {"3", "15", "7", "1", "1", "+", "-", "/", "*", "2", "1", "1", "+", "+", "-"};
    RPNCalc(S, Notation, 15);

    return 0;
}