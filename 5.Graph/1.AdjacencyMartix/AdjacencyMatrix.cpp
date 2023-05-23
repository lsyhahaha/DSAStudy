#include <iostream>

#define MaxVertexNum 100

// 顶点数据类型
typedef char VexType;

typedef struct
{
    // 顶点表
    VexType Vex[MaxVertexNum];
    // 邻接矩阵 边表
    bool Edge[MaxVertexNum][MaxVertexNum];
    // 图的当前顶点数和边数/弧数
    int vexnum, arcnum;
} MGraph;

void InitGraph(MGraph &G)
{
    for (int i = 0; i < MaxVertexNum; i++)
    {
        G.Vex[i] = 0;
        for (int j = 0; j < MaxVertexNum; j++)
        {
            G.Edge[i][j] = false;
        }
    }
    G.vexnum = 0;
}

void Traversal(MGraph G)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        std::cout << G.Vex[i] << " ";
    }
    std::cout << std::endl;
}

// 找到顶点x的下标
bool FindVex(MGraph G, VexType x, int &i)
{
    for (i = 0; i < G.vexnum; i++)
    {
        if (G.Vex[i] == x)
            return true;
    }
    return false;
}

// 在图G中插入顶点x
bool InsertVertex(MGraph &G, VexType x)
{
    G.Vex[G.vexnum] = x;
    G.vexnum++;
    return true;
}

// 在图G中删除顶点

// 若(x, y)或<x, y>不存在，则向图G中添加该边
bool AddEdge(MGraph &G, VexType x, VexType y)
{
    int xd, yd;
    if (FindVex(G, x, xd) && FindVex(G, y, yd))
    {
        G.Edge[xd][yd] = true;
        return true;
    }
    return false;
}

// 若(x, y)或<x, y>存在，则向图G中删除该边
// 从代码逻辑上来说，不需要做判断，直接设为false即可
bool RemoveEdge(MGraph &G, VexType x, VexType y)
{
    int xd, yd;
    if (FindVex(G, x, xd) && FindVex(G, y, yd))
    {
        G.Edge[xd][yd] = false;
        return true;
    }
    return false;
}

// 判断图G是否存在边<x, y>或(x, y)
bool Adjacent(MGraph G, VexType x, VexType y)
{
    int xd, yd;
    if (FindVex(G, x, xd) && FindVex(G, y, yd))
    {
        // 返回代表二者关系的Bool值
        return G.Edge[xd][yd];
    }
    return false;
}

// 列出图G中与结点x邻接的边
bool Neighbors(MGraph G, VexType x)
{
    int xd;
    if (FindVex(G, x, xd))
    {
        for (int i = 0; i < G.vexnum; i++)
        {
            std::cout << G.Edge[xd][i];
        }
        std::cout << std::endl;
        return true;
    }
    return false;
}

int main()
{
    // 声明和初始化
    MGraph G;
    InitGraph(G);

    // 插入一些顶点
    InsertVertex(G, 'A');
    InsertVertex(G, 'B');
    InsertVertex(G, 'C');
    InsertVertex(G, 'D');
    InsertVertex(G, 'E');
    InsertVertex(G, 'F');
    InsertVertex(G, 'G');

    // 遍历表
    std::cout << "当前表内数据：" << std::endl;
    Traversal(G);

    return 0;
}