#include <iostream>

// 本实现中，队头指针指向第一个元素，队尾指针指向最后一个元素的下一个位置。

// 关于队列判满的三种方法
// 1、本文件中注释掉的，if ((Q.rear + 1) % MaxSize == Q.front)。
//    这种方法会导致浪费一个存储单元。
// 2、本文件中使用的，return (Q.size == MaxSize)。
// 3、本文件中没有出现的，定义一个Q.tag，初始化tag=0。
//    每次删除成功都令tag=0，每次插入成功都令tag=1。
//    只有删除才可能队空，只有插入才可能队满。
//    队满条件为：front == rear && tag == 1
//    队空条件为：front == rear && tag == 0

#define MaxSize 10

typedef struct
{
    // 静态数组存放队列元素
    int data[MaxSize];
    // 队头指针和队尾指针
    int front, rear;
    // 队列当前长度
    int size;
} SqQueue;

// 初始化队列
void InitQueue(SqQueue &Q)
{
    // 初始化时 队头、队尾指针指向0
    Q.rear = Q.front = 0;
    // 初始化队列长度为0
    Q.size = 0;
}

// 判断队列是否为空
bool QueueEmpty(SqQueue Q)
{
    // return (Q.rear == Q.front);
    return (Q.size == 0);
}

// 判断队列是否已满
bool QueueFull(SqQueue Q)
{
    return (Q.size == MaxSize);
}

// 入队
bool EnQueue(SqQueue &Q, int x)
{
    // // 队满则报错
    // // 此处这样判断，牺牲了一个存储单元
    // if ((Q.rear + 1) % MaxSize == Q.front)
    //     return false;
    // 加入size之后，可以不浪费一个存储单元
    if (QueueFull(Q))
        return false;
    // 将x插入队尾
    Q.data[Q.rear] = x;
    // 队尾指针加1取余数
    // (9+1) % 10 = 0
    // 循环队列 逻辑上变成了环状的队列
    Q.rear = (Q.rear + 1) % MaxSize;
    // 队列长度加1
    Q.size++;
    return true;
}

// 出队
bool DeQueue(SqQueue &Q, int &x)
{
    // 队空则报错
    if (QueueEmpty(Q))
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    // 队列长度减1
    Q.size--;
    return true;
}

// 获得队头元素的值 用x返回
bool GetHead(SqQueue Q, int &x)
{
    // 队空则报错
    if (QueueEmpty(Q))
        return false;
    x = Q.data[Q.front];
    return true;
}

// 遍历队列
void Traversal(SqQueue Q)
{
    for (int i = 0; i < Q.size; i++)
    {
        std::cout << Q.data[Q.front + i] << std::endl;
    }
}

// 队列元素个数：(rear + MaxSize - front) % MaxSize

int main()
{
    SqQueue Q;
    InitQueue(Q);

    EnQueue(Q, 1);
    EnQueue(Q, 2);
    EnQueue(Q, 3);
    EnQueue(Q, 4);
    EnQueue(Q, 5);

    std::cout << "入队后：" << std::endl;
    Traversal(Q);

    int x = 0;
    std::cout << "出队：" << std::endl;
    DeQueue(Q, x);
    std::cout << x << std::endl;
    DeQueue(Q, x);
    std::cout << x << std::endl;
    DeQueue(Q, x);
    std::cout << x << std::endl;

    std::cout << "出队后：" << std::endl;
    Traversal(Q);

    std::cout << "队空：" << QueueEmpty(Q) << std::endl;
    return 0;
}