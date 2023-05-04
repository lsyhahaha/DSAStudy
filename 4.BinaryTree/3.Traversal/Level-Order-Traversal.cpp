#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
// #include "LiBinTree.h" 包含在 #include "LinkQueue.h"
#include "LinkQueue.h"

// 算法思想：
// 1、初始化一个辅助队列
// 2、根结点入队
// 3、若队列非空，则队头结点出队，访问该结点，并将其左右子结点插入队尾（如果有的话）
// 4、重复3到队空

// 层序遍历
void LevelOrder(BiTree T)
{
    // 声明并初始化辅助队列
    LinkQueue Q;
    InitQueue(Q);

    BiTree p;

    // 根节点入队
    EnQueue(Q, T);
    // 队列不空则循环
    while (!IsEmpty(Q))
    {
        // 队头结点出队
        DeQueue(Q, p);
        // 访问该结点
        visit(p);
        // 如果左子结点非空，则左子节点入队
        if (p->lchild != NULL)
            EnQueue(Q, p->lchild);
        // 如果右子节点非空，则右子节点入队
        if (p->rchild != NULL)
            EnQueue(Q, p->rchild);
    }
}

int main()
{
    // 定义一颗空树
    BiTree root = NULL;
    InitTree(root, 1);

    InsertNode(root, 2, 0);
    InsertNode(root, 3, 1);
    InsertNode(root->lchild, 4, 0);
    InsertNode(root->lchild, 5, 1);

    LevelOrder(root);

    return 0;
}