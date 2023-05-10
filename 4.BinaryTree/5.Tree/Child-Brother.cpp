// 链式存储

typedef struct CSNode
{
    int data;
    struct CSNode *firstchild, *nextsibling;
} CSNode, *CSTree;