// 压缩存储：只存储 主对角线 和 下三角区/上三角区，按行或列优先存入一维数组。

// 数组大小：1+2+3+……+n = ((1+n)*n)/2

// ╭ 1 2 3 4 5 ╮
// │ 2 2 3 4 5 │
// │ 3 3 3 4 5 │
// │ 4 4 4 4 5 │
// ╰ 5 5 5 5 5 ╯

#define n 5

#include <iostream>

int main()
{
    int data[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << "请输入第" << i + 1 << "行，第" << j + 1 << "列的数据：";
            std::cin >> data[i][j];
        }
    }

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

    // 判断是否对称
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (data[i][j] != data[j][i])
                return 1;
        }
    }
    std::cout << "矩阵对称" << std::endl;

    // 转换存储方式
    // 创建一个大小为 ((1 + n) * n) / 2 的数组
    int compreM[((1 + n) * n) / 2] = {0};
    // 将data存入compreM，只存储下三角区和对角线
    // ！此处的ij不是下标的ij，而是数学描述上的ij。
    // 行优先还是列优先取决于这里的i和j嵌套位置，这里是行优先。
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i >= j)
            {
                // 下标 k = ((i * (i - 1)) / 2) + j - 1
                // std::cout << "将" << i << "行，" << j << "列的数据" << data[i - 1][j - 1] << "存放在下标：" << ((i * (i - 1)) / 2) + j << std::endl;
                compreM[((i * (i - 1)) / 2) + j - 1] = data[i - 1][j - 1];
            }
        }
    }

    // 输出compreM
    std::cout << "压缩存储结果为：";
    for (int i = 0; i < (((1 + n) * n) / 2); i++)
        // std::cout << "下标" << i << "的数据是：" << compreM[i] << std::endl;
        std::cout << compreM[i] << " ";
    std::cout << std::endl;

    // 输出矩阵形式
    std::cout << "压缩输出为："<<std::endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i >= j)
            {
                std::cout << compreM[((i * (i - 1)) / 2) + j - 1]<<" ";
            }
            else
            {
                std::cout << compreM[((j * (j - 1)) / 2) + i - 1]<<" ";
            }
        }
        std::cout << std::endl;
    }
}