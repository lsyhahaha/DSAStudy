#include <stdlib.h>

#define MaxVertexNum 100

typedef int VertexType;

// “边/弧”
typedef struct ArcNode
{
    // 边/弧指向哪个结点
    int adjvex;
    // 指向下一条弧的指针
    struct ArcNode *next;
    // 边权值
    // InfoType info;
} ArcNode;
// “顶点”
typedef struct VNode
{
    // 顶点信息
    VertexType data;
    // 第一条边/弧
    ArcNode *first;
    // 顶点是否存在
    bool VexExist;
} VNode, AdjList[MaxVertexNum];

// 用邻接表存储的图
typedef struct
{
    AdjList vertices;
    int vexnum, arcnum;
} ALGraph;

void InitGraph(ALGraph &G)
{
    for (int i = 0; i < MaxVertexNum; i++)
    {
        G.vertices[i].data = 0;
        G.vertices[i].first = NULL;
        G.vertices[i].VexExist = true;
    }
    G.vexnum = 0;
    G.arcnum = 0;
}

// 找到顶点x的下标
bool FindVex(ALGraph G, VNode x, int &i)
{
    for (i = 0; i < MaxVertexNum; i++)
    {
        if (G.vertices[i].data == x.data)
            return true;
    }
    return false;
}

// 在图G中插入顶点x
bool InsertVertex(ALGraph &G, VNode x)
{
    for (int i = 0; i < MaxVertexNum; i++)
    {
        if (!G.vertices[i].VexExist)
        {
            G.vertices[i] = x;
            G.vexnum++;
            return true;
        }
    }
    return false;
}

// 在图G中删除顶点
bool DeleteVertex(ALGraph &G, VNode x)
{
    int xd;
    if (FindVex(G, x, xd))
    {
        G.vertices[xd].VexExist = false;
        G.vertices[xd].first = NULL;
        return true;
    }
    return false;
}

// 若(x, y)不存在，则向图G中添加该边
bool AddEdge(ALGraph &G, VNode x, VNode y)
{
    int xd, yd;
    if (FindVex(G, x, xd) && FindVex(G, y, yd))
    {
        G.vertices[xd].first->next = G.vertices[xd].first;
        G.vertices[xd].first->adjvex = yd;
        G.vertices[yd].first->next = G.vertices[yd].first;
        G.vertices[yd].first->adjvex = xd;
        return true;
    }
    return false;
}

// 若(x, y)存在，则向图G中删除该边
// 从代码逻辑上来说，不需要做判断，直接设为false即可
bool RemoveEdge(ALGraph &G, VNode x, VNode y)
{
    int xd, yd;
    if (FindVex(G, x, xd) && FindVex(G, y, yd))
    {
        G.vertices[xd].first = G.vertices[xd].first->next;
        G.vertices[yd].first = G.vertices[yd].first->next;
        return true;
    }
    return false;
}

// 判断图G是否存在边(x, y)
bool Adjacent(ALGraph G, VNode x, VNode y)
{
    int xd, yd;
    if (FindVex(G, x, xd) && FindVex(G, y, yd))
    {
        ArcNode *p = G.vertices[xd].first;
        for (int i = 0; i < MaxVertexNum; i++)
        {
            if (p->adjvex == yd)
            {
                return true;
            }
            p = p->next;
        }
    }
    return false;
}

int main()
{
    ALGraph G;
    InitGraph(G);

    return 0;
}