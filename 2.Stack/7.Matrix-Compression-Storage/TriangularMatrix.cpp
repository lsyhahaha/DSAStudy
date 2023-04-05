// 压缩存储：只存储 主对角线 和 下三角区/上三角区，其他元素为0，按行或列优先存入一维数组。

// 数组大小：1+2+3+……+n = ((1+n)*n)/2

#include <iostream>

#define n 5
#define c 0

int main()
{
    int data[n][n] = {{1, 1, 1, 1, 1},
                      {c, 2, 2, 2, 2},
                      {c, c, 3, 3, 3},
                      {c, c, c, 4, 4},
                      {c, c, c, c, 5}};
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         std::cout << "请输入第" << i + 1 << "行，第" << j + 1 << "列的数据：";
    //         std::cin >> data[i][j];
    //     }
    // }

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

    // 判断是否为三角矩阵
    // 矩阵是否经过翻转 0为没有 1为有
    int flag = 0;
    int flagUp = 0;
    int flagDown = 0;
    int flagCount = (((n * n) - n) / 2);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i > j && data[i][j] == c)
            {
                // 下三角区的元素是0
                flagDown++;
            }
            else if (i < j && data[i][j] == c)
            {
                // 上三角区的元素是0
                flagUp++;
            }
        }
    }
    if (flagDown == flagCount)
    {
        std::cout << "下三角区全为c，上三角矩阵" << std::endl;
        // 将上三角矩阵转换为下三角矩阵，方便后续处理
        flag = 1;
        std::cout << "为方便后续处理，矩阵将被翻转" << std::endl;
        for (int i = 0; i < n; i++)
        {
            // 注意：只需处理对角线下面的元素
            for (int j = 0; j < i; j++)
            {
                int temp = data[i][j];
                data[i][j] = data[j][i];
                data[j][i] = temp;
            }
        }
    }
    if (flagUp == flagCount)
    {
        std::cout << "上三角区全为c，下三角矩阵" << std::endl;
    }
    if (flagDown < flagCount && flagUp < flagCount)
    {
        std::cout << "不是三角矩阵" << std::endl;
        return 1;
    }

    // 以下三角矩阵模式输出
    std::cout << "以下三角矩阵模式输出：" << std::endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // 转换存储方式
    // 创建一个大小为 (((1 + n) * n) / 2) 的数组
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
    std::cout << "压缩输出为：" << std::endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i >= j)
            {
                std::cout << compreM[((i * (i - 1)) / 2) + j - 1] << " ";
            }
            else
            {
                std::cout << c << " ";
            }
        }
        std::cout << std::endl;
    }

    // 对比存储消耗
    std::cout << "二维数组存储消耗：" << sizeof(data) << " Byte" << std::endl;
    std::cout << "压缩存储消耗：" << sizeof(compreM) << " Byte" << std::endl;

    return 0;
}