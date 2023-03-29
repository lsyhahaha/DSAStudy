// 本实现中，队头指针指向第一个元素，队尾指针指向最后一个元素。

#define MaxSize 10

typedef struct
{
    // 静态数组存放队列元素
    int data[MaxSize];
    // 队头指针和队尾指针
    int front, rear;
} SqQueue;

void InitQueue(SqQueue &Q)
{
    // 队头指向0
    Q.front = 0;
    // 队尾指向n-1
    Q.rear = MaxSize - 1;
}

// 判空
bool QueueEmpty(SqQueue Q)
{
    return ((Q.rear + 1) % MaxSize == Q.front);
}

// 判满
// 解决办法同SqQueue.cpp中提到的三种办法

int main()
{
    SqQueue Q;
    InitQueue(Q);
    return 0;
}