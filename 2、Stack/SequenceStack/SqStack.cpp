#define MaxSize 10

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
    if (S.top == -1)
        return true;
    else
        return false;
}

// 新元素入栈
bool Push(SqStack &S, int x)
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
bool Pop(SqStack &S, int &x)
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
}

// 销毁栈：函数运行结束后自动回收内存

int main()
{
    // 声明一个顺序栈（分配空间）
    SqStack S;
    InitStack(S);
    return 0;
}