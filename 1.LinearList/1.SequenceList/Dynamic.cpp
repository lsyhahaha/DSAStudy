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

// 基本操作——插入
bool ListInsert(SeqList &L, int i, int e)
{
    // 判断参数合法性
    if (i < 1 || i > L.length + 1)
        return false;
    // 从最后一位开始，i之后的都想后移动一位
    for (int j = L.length; j >= i; j--)
        L.data[j] = L.data[j - 1];
    L.data[i - 1] = e;
    L.length++;
    return true;
}

// 基本操作——删除
bool ListDelete(SeqList &L, int i, int &e)
{
    // 判断参数合法性
    if (i < 1 || i > L.length)
        return false;
    // 将被删除的元素赋值给e
    e = L.data[i - 1];
    // 从i之后一位开始，i之后的都想前移动一位
    for (int j = i; j < L.length; j++)
        L.data[j - 1] = L.data[j];
    L.length--;
    return true;
}

// 基本操作——按位查找
int GetElem(SeqList L, int i)
{
    // 位序从1开始，下标从0开始
    // 指针访问的方法和普通数组一样
    return L.data[i - 1];
}

// 基本操作——按值查找
int LocateElem(SeqList L, int e)
{
    for (int i = 0; i < L.length; i++)
        if (L.data[i] == e)
            return i + 1;
    return 0;
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
    // 在前三个位置写入数据
    ListInsert(L, 1, 11);
    ListInsert(L, 2, 22);
    ListInsert(L, 3, 33);

    printf("插入操作前:\n");

    // 违规打印整个顺序表
    for (int i = 0; i < InitSize; i++)
        printf("data[%d]=%d\n", i, L.data[i]);
    printf("————————\n");

    // 在第二个位置插入数据
    ListInsert(L, 2, 3);

    printf("插入操作后:\n");

    // 违规打印整个顺序表
    for (int i = 0; i < InitSize; i++)
        printf("data[%d]=%d\n", i, L.data[i]);
    printf("————————\n");

    // 用变量e把删除的元素“带回来”
    int e = -1;
    ListDelete(L, 2, e);

    printf("删除操作后:\n");
    printf("删除了元素%d\n", e);

    // 违规打印整个顺序表
    for (int i = 0; i < InitSize; i++)
        printf("data[%d]=%d\n", i, L.data[i]);
    printf("————————\n");

    // 增加长度
    int increaseSize = 5;
    IncreaseSize(L, increaseSize);

    printf("长度增加%d后:\n", increaseSize);

    // 违规打印整个顺序表
    for (int i = 0; i < InitSize + increaseSize; i++)
        printf("data[%d]=%d\n", i, L.data[i]);
    printf("————————\n");

    // 查询第一个位置的元素
    printf("第一个位置的元素是: %d\n", GetElem(L, 1));
    // 查询22所在位置
    printf("22所在位置是: %d\n", LocateElem(L, 22));

    return 0;
}