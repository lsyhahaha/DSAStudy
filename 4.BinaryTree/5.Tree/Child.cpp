// 顺序 + 链式存储

#include <iostream>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// 树中最多的结点数
#define MAX_TREE_SIZE 100

struct CTNode
{
    // 子结点在数组中的位置
    int child;
    // 下一个子结点
    struct CTNode *next;
};
typedef struct
{
    int data;
    // 第一个子结点
    struct CTNode *firstChild;
} CTBox;
typedef struct
{
    CTBox nodes[MAX_TREE_SIZE];
    // 结点数和根的位置
    int n, r;
} CTree;

bool InitTree(CTree CT)
{
    CT.n = 0;
    CT.r = -1;
    for (int i = 0; i < MAX_TREE_SIZE; i++)
    {
        CT.nodes[i].data = 0;
        CT.nodes[i].firstChild = NULL;
    }
    return true;
}

int main()
{
    CTree CT;
    InitTree(CT);
    return 0;
}