// 静态链表最大长度
#define MaxSize 10

// 静态链表结构类型定义
typedef struct Node
{
    // 存储数据元素
    int data;
    // 下一个元素的数组下标
    int next;
} SLinkList[MaxSize];
// 在之后可以用SLinkList定义一个长度为MaxSize的Node型数组

int main()
{
    // 等价于 struct Node a[MaxSize];
    SLinkList a;
}