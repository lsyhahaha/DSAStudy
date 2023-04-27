#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

typedef struct LNode
{
    // 节点内存储的数据
    int data;
    // 指向下一个节点
    struct LNode *next;
} LNode, *LinkList;

// 两个别名让代码可读性更强（它们实际上就是完全一样的一个东西LNode，即声明一个指向单链表第一个节点的指针）
// LNode *L 一个结点
// LinkList L 一个单链表

// 初始化链表（带头结点）
bool InitList(LinkList &L)
{
    L = (LNode *)malloc(sizeof(LNode));
    if (L == NULL)
        return false;
    L->next = NULL;
    return true;
}

// 初始化循环单链表
bool InitList2(LinkList &L)
{
    L = (LNode *)malloc(sizeof(LNode));
    if (L == NULL)
        return false;
    // 头结点next指向头结点
    L->next = L;
    return true;
}

// 判断链表是否为空
bool Empty(LinkList L)
{
    if (L->next == NULL)
        return true;
    else
        return false;
}

// 判断循环单链表是否为空
bool Empty2(LinkList L)
{
    // 检查头结点next是否指向自己
    if (L->next == L)
        return true;
    else
        return false;
}

// 按位查找，返回第i个元素
LNode *GetElem(LinkList L, int i)
{
    if (i < 0)
        return NULL;
    // 指针p指向当前扫描到的结点
    LNode *p;
    // 当前p指向的是第几个结点（第0个结点 头节点）
    int j = 0;
    // p指向头结点（第0个结点，不存数据）
    p = L;
    // 循环找到第i个结点
    while (p != NULL && j < i)
    {
        p = p->next;
        j++;
    }
    return p;
}

// 按值查找，找到数据域==e的结点
LNode *LocateElem(LinkList L, int e)
{
    LNode *p = L->next;
    // 从第1个结点开始查找数据域为e的结点
    while (p != NULL && p->data != e)
        p = p->next;
    return p;
}

// 指定结点后插
bool InsertNextNode(LNode *p, int e)
{
    if (p == NULL)
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    // 内存分配失败
    if (s == NULL)
        return false;
    // 用结点s保存数据元素e
    s->data = e;
    s->next = p->next;
    // 将结点s连接到p后
    p->next = s;
    return true;
}

// 指定结点前插
bool InsertPriorNode(LNode *p, int e)
{
    if (p == NULL)
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    // 内存分配失败
    if (s == NULL)
        return false;
    s->next = p->next;
    // 新节点s连接到p后
    p->next = s;
    // 将p中元素复制到s中
    s->data = p->data;
    // p中元素覆盖为e
    p->data = e;
    return true;
}

// 按位序插入
bool ListInsert(LinkList &L, int i, int e)
{
    if (i < 1)
        return false;
    // 找到第i-1个结点
    LNode *p = GetElem(L, i - 1);
    return InsertNextNode(p, e);
}

// 按位序删除
bool ListDelete(LinkList &L, int i, int &e)
{
    // 找到第i-1个结点
    LNode *p = GetElem(L, i - 1);
    // i值不合法
    if (p == NULL)
        return false;
    // 第i-1个结点之后已无其他结点
    if (p->next == NULL)
        return false;
    // 令q指向被删除结点
    LNode *q = p->next;
    // 用e返回元素的值
    e = q->data;
    // 将*q结点从链中“断开”
    p->next = q->next;
    // 释放结点的存储空间
    free(q);
    // 删除成功
    return true;
}

// 尾插法建立单链表
LinkList List_TailInsert(LinkList &L)
{
    int x;
    // 建立头结点
    L = (LinkList)malloc(sizeof(LNode));
    // r为表尾指针
    LNode *s, *r = L;
    // 输入结点的值
    scanf("%d", &x);
    // 输入9999代表结束
    while (x != 9999)
    {
        // 在r结点之后插入元素x
        s = (LNode *)malloc(sizeof(LNode));
        s->data = x;
        r->next = s;
        // 永远保持r指向最后一个结点
        r = s;
        scanf("%d", &x);
    }
    // 表尾指针置空
    r->next = NULL;
    return L;
}

// 头插法建立单链表
LinkList List_HeadInsert(LinkList &L)
{
    LNode *s;
    int x;
    // 创建头结点
    L = (LinkList)malloc(sizeof(LNode));
    // 初始为空链表
    L->next = NULL;
    // 输出结点的值
    scanf("%d", &x);
    // 输入9999表示结束
    while (x != 9999)
    {
        // 创建新结点
        s = (LNode *)malloc(sizeof(LNode));
        s->data = x;
        s->next = L->next;
        // 将新结点插入表中，L为头指针
        L->next = s;
        scanf("%d", &x);
    }
    return L;
}

// 求表的长度
int Length(LinkList L)
{
    // 统计表长
    int len = 0;
    LNode *p = L;
    while (p->next != NULL)
    {
        p = p->next;
        len++;
    }
    return len;
}

// 判断结点p是否为单链表的表尾结点
bool isTail(LinkList L, LNode *p)
{
    if (p->next == NULL)
        return true;
    else
        return false;
}

// 判断结点p是否为循环单链表的表尾结点
bool isTail2(LinkList L, LNode *p)
{
    // 判断其next是否指向头结点
    if (p->next == L)
        return true;
    else
        return false;
}

// 遍历单链表
void Traversal(LinkList L)
{
    // 声明一个p指针，指向L->next所指对象
    LNode *p = L->next;
    // 只要p不等于NULL，就继续
    while (p != NULL)
    {
        std::cout << p->data << std::endl;
        p = p->next;
    }
}

int main()
{
    LinkList L;
    InitList(L);

    ListInsert(L, 1, 11);
    ListInsert(L, 2, 22);
    ListInsert(L, 3, 33);

    printf("插入操作前:\n");
    // 遍历顺序表
    Traversal(L);
    printf("————————\n");

    // 在第二个位置插入数据
    ListInsert(L, 2, 3);

    printf("插入操作后:\n");
    // 遍历顺序表
    Traversal(L);
    printf("————————\n");

    // 用变量e把删除的元素“带回来”
    int e = -1;
    ListDelete(L, 2, e);

    printf("删除操作后:\n");
    printf("删除了元素%d\n", e);
    // 遍历顺序表
    Traversal(L);
    printf("————————\n");

    // 查询第一个位置的元素
    printf("第一个位置的元素是: %d\n", GetElem(L, 1)->data);
    // 查询22所在位置
    // 这里的函数并不能返回位置，而是结点本身，这里查询一下next的数据域。
    printf("22所在位置的下一个结点数据是: %d\n", LocateElem(L, 22)->next->data);

    return 0;
}