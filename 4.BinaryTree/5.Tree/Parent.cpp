#include <iostream>

// 树中最多的结点数
#define MAX_TREE_SIZE 100

// 树结点定义
typedef struct
{
    // 数据元素
    int data;
    // 双亲位置
    int parent;
} PTNode;

// 树的类型定义
typedef struct
{
    // 双亲表示
    PTNode nodes[MAX_TREE_SIZE];
    // 结点数
    int n;
} PTree;

// 初始化树
bool InitTree(PTree &PT)
{
    for (int i = 0; i < MAX_TREE_SIZE; i++)
    {
        PT.nodes[i].data = 0;
        PT.nodes[i].parent = -1;
        PT.n = 0;
    }
    return true;
}

// 插入结点 x是数据，y是父结点下标
bool InsertNode(PTree &PT, int x, int y)
{
    PT.nodes[PT.n].data = x;
    if (PT.n != 0)
        PT.nodes[PT.n].parent = y;
    else
        PT.nodes[PT.n].parent = -1;
    PT.n++;
    return true;
}

// 逆向遍历，从某一结点开始一直找到根节点
void RevTraversal(PTree PT, PTNode s)
{
    while (s.parent != -1)
    {
        std::cout << s.data << std::endl;
        s = PT.nodes[s.parent];
    }
    std::cout << s.data << std::endl;
}

int main()
{
    PTree PT;
    InitTree(PT);

    InsertNode(PT, 1, -1);
    InsertNode(PT, 2, 0);
    InsertNode(PT, 3, 0);
    InsertNode(PT, 4, 1);
    InsertNode(PT, 5, 3);
    InsertNode(PT, 6, 4);

    PTNode s = PT.nodes[5];

    RevTraversal(PT, s);

    return 0;
}