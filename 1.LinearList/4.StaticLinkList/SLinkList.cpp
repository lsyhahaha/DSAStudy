#include <iostream>

// 静态链表最大长度
#define MaxSize 10

// 静态链表结构类型定义
typedef struct Node
{
    // 存储数据元素
    int data;
    // 下一个元素的数组下标
    int next;
    // 是否为开始位置
    int start;
} Node, SLinkList[MaxSize];
// 在之后可以用SLinkList定义一个长度为MaxSize的Node型数组

// 初始化链表
bool InitList(SLinkList &a)
{
    for (int i = 0; i < MaxSize; i++)
    {
        a[i].data = 0;
        // 约定：
        // -1代表不指向数组任何位置（用于最末尾的位置）
        // -2代表该结点数据废弃（用于可写入的位置）
        a[i].next = -2;
        // -1不是起点
        // 0是起点
        a[i].start = -1;
    }
    return true;
}

int GetElemSubscript(SLinkList a, int i)
{
    Node p;
    // p是第几个位置
    int j = 1;
    // 找到开始位置
    int startInt = -4;
    for (int k = 0; k < MaxSize; k++)
    {
        // 找到开始位置
        if (a[k].start == 0)
        {
            startInt = k;
            break;
        }
    }
    // p是第一个位置
    p = a[startInt];
    // 保存当前位置的下标
    int subscript = startInt;
    // 循环找到第i个位置
    while (p.next != -1 && j < i)
    {
        subscript = p.next;
        p = a[subscript];
        j++;
    }
    return subscript;
}

// 按值查找，找到数据域==e的结点
int LocateElem(SLinkList a, int e)
{
    Node p;
    // p是第几个位置
    int j = 1;
    // 找到开始位置
    int startInt = -4;
    for (int k = 0; k < MaxSize; k++)
    {
        // 找到开始位置
        if (a[k].start == 0)
        {
            startInt = k;
            break;
        }
    }
    // p是第一个位置
    p = a[startInt];
    // 循环找到e出现的位置
    while (p.next != -1 && p.data != e)
    {
        p = a[p.next];
        j++;
    }
    return j;
}

// 按位序插入
bool ListInsert(SLinkList &a, int i, int e)
{
    if (i < 1 || i >= MaxSize)
        return false;
    int x = -3;
    int y = -3;
    // 遍历所有位置，找到末尾和可写入位置
    for (int i = 0; i < MaxSize; i++)
    {
        if (a[i].next == -1)
        {
            x = i;
        }
        if (a[i].next == -2)
        {
            y = i;
        }
    }
    // 没有==-2，意思是链表满了
    if (y == -3)
    {
        return false;
    }
    // 没有==-1，只有刚初始化完会有的情况
    if (x == -3)
    {
        a[0].data = e;
        a[0].next = -1;
        a[0].start = 0;
        return true;
    }
    // 找到第i-1个位置
    int p = GetElemSubscript(a, i - 1);
    // 第i个位置写入e
    a[y].data = e;
    // 第i个位置的后继是i-1个位置的后继
    a[y].next = a[p].next;
    // 不是开始节点
    a[y].start = -1;
    // 第i-1个位置的后继是第i个位置
    a[p].next = y;
    // std::cout << a[p].data << std::endl;
    return true;
}

// 按位序删除
bool ListDelete(SLinkList &a, int i, int &e)
{
    // 找到第i-1个位置
    int p = GetElemSubscript(a, i - 1);
    // 第i个位置
    int q = a[p].next;
    // 将第i-1个位置的后继改为第i个位置的后继
    a[p].next = a[q].next;
    // 将第i个位置改为可写
    a[q].next = -2;
    // 带回数据
    e = a[q].data;
    return true;
}

void Traversal(SLinkList a)
{
    int startInt = -4;
    for (int i = 0; i < MaxSize; i++)
    {
        // 找到开始位置
        if (a[i].start == 0)
        {
            startInt = i;
            break;
        }
    }
    // 没到队尾，就一直循环
    int endInt = a[startInt].data;
    while (endInt != -1)
    {
        std::cout << a[startInt].data << std::endl;
        startInt = a[startInt].next;
        endInt = a[startInt].next;
    }
    std::cout << a[startInt].data << std::endl;
}

// 非法打印函数
// 可以直接把创建的MaxSize大小数组完全打印出来，忽略元素之间的关系
void illegalPrintf(SLinkList a)
{
    for (int i = 0; i < MaxSize; i++)
    {
        std::cout << a[i].next << std::endl;
    }
}

int main()
{
    // 等价于 struct Node a[MaxSize];
    SLinkList a;
    InitList(a);

    ListInsert(a, 1, 11);
    ListInsert(a, 2, 22);
    ListInsert(a, 3, 33);

    printf("插入操作前:\n");
    // 遍历顺序表
    Traversal(a);
    printf("————————\n");

    // 在第一个位置插入数据
    ListInsert(a, 1, 3);

    printf("插入操作后:\n");
    // 遍历顺序表
    Traversal(a);
    printf("————————\n");

    // 用变量e把删除的元素“带回来”
    int e = -1;
    ListDelete(a, 1, e);

    printf("删除操作后:\n");
    printf("删除了元素%d\n", e);
    // 遍历顺序表
    Traversal(a);
    printf("————————\n");

    // 查询第一个位置的元素
    printf("第一个位置的元素是: %d\n", a[GetElemSubscript(a, 1)].data);
    // 查询22所在位置
    printf("22所在位置是: %d\n", LocateElem(a, 22));

    return 0;
}