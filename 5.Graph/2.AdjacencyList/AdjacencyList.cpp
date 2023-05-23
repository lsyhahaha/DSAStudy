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
} VNode, AdjList[MaxVertexNum];

// 用邻接表存储的图
typedef struct
{
    AdjList vertices;
    int vexnum, arcnum;
} ALGraph;