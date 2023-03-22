#include <stdlib.h>
#include <stdio.h>

// 默认最大长度
#define InitSize 10

// 定义结构体，并赋予别名
typedef struct
{
    // 指示动态分配数组的指针
    int *data;
    // 顺序表的最大容量
    int MaxSize;
    // 顺序表当前长度
    int length;
} SeqList;

// 基本操作——初始化
void InitList(SeqList &L)
{
    // 用malloc函数申请一片连续的存储空间
    // 注意转换为int型
    L.data = (int *)malloc(InitSize * sizeof(int));
    L.length = 0;
    L.MaxSize = InitSize;
}

// 增加动态数组的长度
void IncreaseSize(SeqList &L, int len)
{
    int *p = L.data;
    L.data = (int *)malloc((L.MaxSize + len) * sizeof(int));
    for (int i = 0; i < L.length; i++)
    {
        L.data[i] = p[i];
    }
    L.MaxSize = L.MaxSize + len;
    free(p);
}

int main()
{
    // 声明一个顺序表
    SeqList L;
    // 初始化顺序表
    InitList(L);
    // 后续操作

    // 违规打印整个顺序表
    for (int i = 0; i < InitSize; i++)
        printf("data[%d]=%d\n", i, L.data[i]);

    // 增加长度
    int increaseSize = 5;
    IncreaseSize(L, increaseSize);

    printf("长度增加%d后:\n", increaseSize);

    // 违规打印整个顺序表
    for (int i = 0; i < InitSize + increaseSize; i++)
        printf("data[%d]=%d\n", i, L.data[i]);

    return 0;
}