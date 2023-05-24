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
    // 顶点是否存在
    bool VexExist[MaxVertexNum];
    // 图的当前顶点数和边数/弧数
    int vexnum, arcnum;
} MGraph;

void InitGraph(MGraph &G)
{
    for (int i = 0; i < MaxVertexNum; i++)
    {
        G.Vex[i] = 0;
        G.VexExist[i] = false;
        for (int j = 0; j < MaxVertexNum; j++)
        {
            G.Edge[i][j] = false;
        }
    }
    G.vexnum = 0;
    G.arcnum = 0;
}

void Traversal(MGraph G)
{
    for (int i = 0; i < MaxVertexNum; i++)
    {
        if (G.VexExist[i])
            std::cout << G.Vex[i] << " ";
    }
    std::cout << std::endl;
}

void TraversalEdge(MGraph G)
{
    std::cout << "  ";
    Traversal(G);
    for (int i = 0; i < MaxVertexNum; i++)
    {
        if (G.VexExist[i])
        {
            std::cout << G.Vex[i] << " ";
            for (int j = 0; j < MaxVertexNum; j++)
            {
                if (G.VexExist[j])
                    std::cout << G.Edge[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
}

// 找到顶点x的下标
bool FindVex(MGraph G, VexType x, int &i)
{
    for (i = 0; i < MaxVertexNum; i++)
    {
        if (G.VexExist[i])
            if (G.Vex[i] == x)
                return true;
    }
    return false;
}

// 在图G中插入顶点x
bool InsertVertex(MGraph &G, VexType x)
{
    for (int i = 0; i < MaxVertexNum; i++)
    {
        if (!G.VexExist[i])
        {
            G.Vex[i] = x;
            G.VexExist[i] = true;
            G.vexnum++;
            return true;
        }
    }
    return false;
}

// 在图G中删除顶点
bool DeleteVertex(MGraph &G, VexType x)
{
    int xd;
    if (FindVex(G, x, xd))
    {
        G.VexExist[xd] = false;
        for (int i = 0; i < MaxVertexNum; i++)
        {
            G.Edge[xd][i] = false;
            G.Edge[i][xd] = false;
        }
        G.vexnum--;
        return true;
    }
    return false;
}

// 若(x, y)不存在，则向图G中添加该边
bool AddEdge(MGraph &G, VexType x, VexType y)
{
    int xd, yd;
    if (FindVex(G, x, xd) && FindVex(G, y, yd))
    {
        G.Edge[xd][yd] = true;
        G.Edge[yd][xd] = true;
        G.arcnum++;
        return true;
    }
    return false;
}

// 若(x, y)存在，则向图G中删除该边
// 从代码逻辑上来说，不需要做判断，直接设为false即可
bool RemoveEdge(MGraph &G, VexType x, VexType y)
{
    int xd, yd;
    if (FindVex(G, x, xd) && FindVex(G, y, yd))
    {
        G.Edge[xd][yd] = false;
        G.Edge[yd][xd] = false;
        G.arcnum--;
        return true;
    }
    return false;
}

// 判断图G是否存在边(x, y)
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
        for (int i = 0; i < MaxVertexNum; i++)
        {
            std::cout << G.Edge[xd][i];
        }
        std::cout << std::endl;
        return true;
    }
    return false;
}

// 求图G中顶点x的第一个邻接点，若有则返回顶点号。
// 若x没有邻接点或图中不存在x，则返回-1
int FirstNeighbor(MGraph G, VexType x)
{
    int xd;
    if (FindVex(G, x, xd))
    {
        for (int i = 0; i < MaxVertexNum; i++)
        {
            if (G.Edge[xd][i])
            {
                return i;
            }
        }
    }
    return -1;
}

// 假设图G中顶点y是顶点x的第一个邻接点，返回除y之外顶点x的下一个邻接点的顶点号。
// 若y是x的最后一个邻接点，则返回-1
int NextNeighbor(MGraph G, VexType x, VexType y)
{
    int xd, yd;
    if (FindVex(G, x, xd) && FindVex(G, y, yd))
    {
        if (FirstNeighbor(G, x) == yd)
        {
            for (int i = yd; i < MaxVertexNum; i++)
            {
                if (G.Edge[xd][i])
                {
                    return i;
                }
            }
        }
    }
    return -1;
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
    TraversalEdge(G);

    // 删除结点E
    DeleteVertex(G, 'E');
    std::cout << "删除结点E后，表内数据：" << std::endl;
    Traversal(G);
    TraversalEdge(G);

    // 继续插入结点H和I
    InsertVertex(G, 'H');
    InsertVertex(G, 'I');
    std::cout << "继续插入结点H和I后，表内数据：" << std::endl;
    Traversal(G);
    TraversalEdge(G);

    // 添加一些边
    AddEdge(G, 'A', 'B');
    AddEdge(G, 'A', 'C');
    AddEdge(G, 'A', 'D');
    AddEdge(G, 'B', 'H');
    std::cout << "添加一些边后，表内数据：" << std::endl;
    Traversal(G);
    TraversalEdge(G);

    // 判断边是否存在
    VexType X = 'A';
    VexType Y = 'B';
    VexType Z = 'C';
    std::cout << X << "和" << Y << "之间是否有边：" << Adjacent(G, X, Y) << std::endl;
    std::cout << Y << "和" << Z << "之间是否有边：" << Adjacent(G, Y, Z) << std::endl;
    std::cout << X << "和" << Z << "之间是否有边：" << Adjacent(G, X, Z) << std::endl;

    return 0;
}