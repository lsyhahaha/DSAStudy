#include <stdio.h>

// 定义最大长度
#define MaxSize 10

// 定义结构体，并赋予别名
typedef struct
{
    // 用静态的“数组”存放数据元素
    int data[MaxSize];
    // 顺序表当前长度
    int length;
} SqList;

// 基本操作——初始化顺序表
void InitList(SqList &L)
{
    // 初始化操作可以省略（因为长度初始为0）
    // for (int i = 0; i < MaxSize; i++)
    //     // 将所有数据元素设置为默认初始值
    //     L.data[i] = 0;
    // 顺序表初始长度为0
    L.length = 0;
}

int main()
{
    // 声明一个顺序表
    SqList L;
    // 初始化顺序表
    InitList(L);
    // 后续操作

    // 尝试“违规”打印整个数组
    // i < L.length 更加合法，但仍不是一个好的选择
    // 最好的选择是使用基本操作来访问各个数据元素
    for (int i = 0; i < MaxSize; i++)
        printf("data[%d]=%d\n", i, L.data[i]);

    return 0;
}