// 压缩存储：只存储带状部分

#include <iostream>
#include<cmath>

#define n 5
#define c 0

int main()
{
    int data[n][n] = {{1, 2, c, c, c},
                      {2, 2, 3, c, c},
                      {c, 3, 3, 4, c},
                      {c, c, 4, 4, 5},
                      {c, c, c, 5, 5}};

    // 输出data
    std::cout << "输入的矩阵为：" << std::endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // 判断矩阵是否为三对角矩阵
    // 除了第i行的i-1和i+1列，其余都为c
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ((j != i && j != (i - 1) && j != (i + 1)) && data[i][j] != c)
            {
                std::cout << "不是三对角矩阵" << std::endl;
                return 1;
            }
        }
    }
    std::cout << "是三对角矩阵" << std::endl;

    // 转换存储方式
    // 创建一个大小为 ((n - 2) * 3) + 4 的数组
    int compreM[((n - 2) * 3) + 4] = {0};
    // 将data存入compreM，只存储带状区
    int x = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == i || j == (i - 1) || j == (i + 1))
            {
                compreM[x] = data[i][j];
                x++;
            }
        }
    }

    // 输出compreM
    std::cout << "压缩存储结果为：";
    for (int i = 0; i < (((n - 2) * 3) + 4); i++)
        // std::cout << "下标" << i << "的数据是：" << compreM[i] << std::endl;
        std::cout << compreM[i] << " ";
    std::cout << std::endl;

    // 逆向输出矩阵形式
    std::cout << "压缩输出为：" << std::endl;
    int data2[n][n] = {0};
    for (int k = 0; k <= (((n - 2) * 3) + 4); k++)
    {
        // i=⌈(k+2)/3⌉
        int i = ceil(((float)k + 2) / 3);
        // j=k-2i+3
        int j = k - (2 * i) + 3;
        if (i <= n && j <= n)
        {
            std::cout << "第" << i << "行 第" << j << "列 的元素是：" << compreM[k] << std::endl;
            data2[i - 1][j - 1] = compreM[k];
        }
    }
    // 输出data2
    std::cout << "输出的矩阵为：" << std::endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << data2[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // 对比存储消耗
    std::cout << "二维数组存储消耗：" << sizeof(data) << " Byte" << std::endl;
    std::cout << "压缩存储消耗：" << sizeof(compreM) << " Byte" << std::endl;

    return 0;
}