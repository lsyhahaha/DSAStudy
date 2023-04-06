// 注意：此方法无法随机存取；

#include <iostream>
#include "LiStack.h"

#define n 5
#define m 10

int main()
{
    LiStack S;
    InitStack(S);

    int data[n][n] = {{0, 1, 0, 0, 0},
                      {3, 0, 0, 2, 0},
                      {0, 0, 0, 4, 0},
                      {0, 0, 0, 0, 6},
                      {0, 1, 0, 0, 0}};

    // 循环入栈
    int x = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (data[i][j] != 0)
            {
                Push(S, i, j, data[i][j]);
                x++;
            }
        }
    }

    // 遍历栈
    BackwardTraversal(S);
}