// 需要两个栈
// 操作数栈：用于存放操作数 RPNCalc
// 运算符栈：用于存放运算符 INtoRPN
// 扫描到操作数，压入操作数栈
// 扫描到运算符或界限符，按照“IN to RPN”的逻辑压入运算符栈。
// （期间也会弹出运算符，每当弹出一个运算符时，就需要再弹出两个操作数栈的栈顶元素并执行相应运算，运算结果再压会操作数栈）

// 定义两类栈的基本操作
#include "StringSqStack.h"
#include "IntSqStack.h"

// PRN计算函数
void RPNCalc(std::string Operator, IntStack::IntSqStack &NS)
{
    // 弹出操作数栈的两个元素
    int LeftElem;
    int RightElem;
    // 先出栈的是右操作数
    IntStack::Pop(NS, RightElem);
    IntStack::Pop(NS, LeftElem);
    // 根据运算符计算 并入栈
    if (Operator == "+")
    {
        IntStack::Push(NS, LeftElem + RightElem);
        std::cout << "运算结果：" << LeftElem + RightElem << std::endl;
    }
    else if (Operator == "-")
    {
        IntStack::Push(NS, LeftElem - RightElem);
        std::cout << "运算结果：" << LeftElem - RightElem << std::endl;
    }
    else if (Operator == "*")
    {
        IntStack::Push(NS, LeftElem * RightElem);
        std::cout << "运算结果：" << LeftElem * RightElem << std::endl;
    }
    else if (Operator == "/")
    {
        IntStack::Push(NS, LeftElem / RightElem);
        std::cout << "运算结果：" << LeftElem / RightElem << std::endl;
    }
    else
    {
        // 运算符错误
        std::cout << "运算符错误" << std::endl;
    }
}

// 中缀转后缀
// 从左到右处理各个元素，直到末尾，可能有三种情况：
// 1.操作数：直接添加到操作数栈
// 2.界限符：遇到 ( 直接入栈；遇到 ) 则依次弹出栈内运算符并加入RPN（操作数栈），知道弹出 ( 为止。注意 ( 本身不加入操作数栈（也进不去）
// 3.运算符：依次弹出运算符栈中【优先级 高于 或 等于】当前运算符的所有运算符，并加入RPN（操作数栈），若碰到 ( 或栈空则停止。之后再把当前运算符入栈。
// 按照上面方法处理完所有字符后，栈中剩余运算符依次弹出，添加到后缀表达式（操作数栈）。
void INtoRPN(StringStack::StringSqStack &OS, IntStack::IntSqStack &NS, std::string Notation[], int length)
{
    // 循环遍历字符串
    for (int i = 0; i < length; i++)
    {
        // 如果遇到低级运算符
        if (Notation[i] == "+" || Notation[i] == "-")
        {
            // std::cout << "遇到低级运算符：" << Notation[i] << std::endl;
            // 低级运算符遇到的所有运算符全是同级或高级，且栈非空
            while ((StringStack::GetTop(OS) == "+" || StringStack::GetTop(OS) == "-" ||
                    StringStack::GetTop(OS) == "*" || StringStack::GetTop(OS) == "/") &&
                   StringStack::StackEmpty(OS) != true)
            {
                // 弹出运算符
                std::string Operator;
                StringStack::Pop(OS, Operator);
                std::cout << "弹出了运算符+-：" << Operator << std::endl;
                // PRN计算，结果压入操作数栈
                RPNCalc(Operator, NS);
            }
            // 都搞定了，再把当前运算符压入运算符栈
            StringStack::Push(OS, Notation[i]);
            std::cout << "把：" << Notation[i] << "压入" << std::endl;
        }
        // 如果遇到高级运算符
        else if (Notation[i] == "*" || Notation[i] == "/")
        {
            // std::cout << "遇到高级运算符：" << Notation[i] << std::endl;
            // 高级运算符只能遇到同级，低级不管他，且栈非空
            while ((StringStack::GetTop(OS) == "*" || StringStack::GetTop(OS) == "/") &&
                   StringStack::StackEmpty(OS) != true)
            {
                // 弹出运算符
                std::string Operator;
                StringStack::Pop(OS, Operator);
                std::cout << "弹出了运算符*/：" << Operator << std::endl;
                // PRN计算，结果压入操作数栈
                RPNCalc(Operator, NS);
            }
            // 都搞定了，再把当前运算符压入运算符栈
            StringStack::Push(OS, Notation[i]);
            std::cout << "把：" << Notation[i] << "压入" << std::endl;
        }
        // 如果遇到左括号
        else if (Notation[i] == "(" || Notation[i] == "[" || Notation[i] == "{")
        {
            // std::cout << "遇到左括号：" << Notation[i] << std::endl;
            // 直接压入运算符栈
            StringStack::Push(OS, Notation[i]);
            std::cout << "把：" << Notation[i] << "压入" << std::endl;
        }
        // 如果遇到右括号
        else if (Notation[i] == ")" || Notation[i] == "]" || Notation[i] == "}")
        {
            std::cout << "遇到右括号：" << Notation[i] << std::endl;
            // 不是左括号，且栈非空
            while ((StringStack::GetTop(OS) != "(" && StringStack::GetTop(OS) != "[" && StringStack::GetTop(OS) != "{") && StringStack::StackEmpty(OS) != true)
            {
                // 不是，弹出运算符栈的元素(+-*/)
                std::string Operator;
                StringStack::Pop(OS, Operator);
                std::cout << "弹出了运算符)：" << Operator << std::endl;
                // PRN计算，结果压入操作数栈
                RPNCalc(Operator, NS);
                // std::cout << "遇到右括号，并执行了计算。" << std::endl;
            }
            // 弹出左括号
            std::string LeftTmp;
            StringStack::Pop(OS, LeftTmp);
        }
        // 如果遇到操作数
        else
        {
            // std::cout << "遇到操作数：" << std::stoi(Notation[i]) << std::endl;
            // 直接压入操作数栈
            IntStack::Push(NS, std::stoi(Notation[i]));
            std::cout << "把：" << Notation[i] << "压入" << std::endl;
        }
    }
    // 最后 运算符栈还剩一个，操作数栈还剩两个
    // 但如果有人在最外面套了个括号，就必须判断一下运算符栈栈空
    if (StringStack::StackEmpty(OS) != true)
    {
        std::string Operator;
        StringStack::Pop(OS, Operator);
        std::cout << "弹出了运算符：" << Operator << std::endl;
        // PRN计算，结果压入操作数栈
        RPNCalc(Operator, NS);
    }
}

int main()
{
    // 声明并初始化操作数栈和运算符栈
    StringStack::StringSqStack OS;
    IntStack::IntSqStack NS;
    StringStack::InitStack(OS);
    IntStack::InitStack(NS);

    std::string Notation[] = {"(", "(", "15", "/", "(", "7", "-", "(", "1", "+", "1", ")", ")", ")", "*", "3", ")", "-", "(", "2", "+", "(", "1", "+", "1", ")", ")"};

    int length = sizeof(Notation) / sizeof(std::string);

    INtoRPN(OS, NS, Notation, length);

    // 输出结果
    std::cout << std::endl
              << "计算结果为" << IntStack::GetTop(NS) << std::endl;

    return 0;
}