#define MaxVertexNum 100
// #define INFINITY 最大int值
typedef char VertexType;
// 可以表示权值
typedef int EdgeType;
typedef struct
{
    VertexType Vex[MaxVertexNum];
    EdgeType Edge[MaxVertexNum][MaxVertexNum];
    int vexnum, arcnum;
} MGraph;