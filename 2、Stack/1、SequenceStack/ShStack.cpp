#define MaxSize 10

typedef struct
{
    // 静态数组中存放栈元素
    int data[MaxSize];
    // 1号栈顶指针
    int top0;
    // 2号栈顶指针
    int top1;
} ShStack;

// 初始化栈
void InitStack(ShStack &S)
{
    // 从下向上
    S.top0 = -1;
    // 从上向下
    S.top1 = MaxSize;
}

// 栈满条件：top0 + 1 == top1