#include <iostream>

#define SIZE 13
// 集合元素数据
// int UFSets[SIZE] = {-1, 0, -1, -1, 1, 1, 2, 3, 3, 3, 4, 4, 7};
int UFSets[SIZE] = {-6, 0, -2, -5, 1, 1, 2, 3, 3, 3, 4, 4, 7};

// 初始化并查集
void Inital(int S[])
{
    for (int i = 0; i < SIZE; i++)
        S[i] = -1;
}

// 查操作（时间复杂度O(n)），找x所属集合（返回x所属根节点）
// 复杂度中的n，实际上就是树的高度h，优化策略就是让树不要长太高，
// 也就是并操作时，尽量让小树并到大树里
int Find(int S[], int x)
{
    // 循环寻找x的根
    while (S[x] >= 0)
        x = S[x];
    // 根的S[]小于0
    return x;
}

// 并操作（时间复杂度O(1)），将两个集合合并为一个
bool Union(int S[], int Root1, int Root2)
{
    // 要求Root1与Root2是不同的集合
    if (Root1 == Root2)
        return false;
    S[Root2] = Root1;
    return true;
}

// 优化后的并操作（用负的绝对值表示结点数）
// 整棵树的高度不会超过⌊log₂n⌋+1
// 即此时，查的操作时间复杂度为O(log₂n)
// 而以下的并操作仍然是O(1)的复杂度
bool Union2(int S[], int Root1, int Root2)
{
    // 要求Root1与Root2是不同的集合
    if (Root1 == Root2)
        return false;
    // Root2结点数更少
    if (S[Root2] > S[Root1])
    {
        // 累加结点总数
        S[Root1] += S[Root2];
        // 小树合并到大树
        S[Root2] = Root1;
    }
    // Root1结点数更少
    else
    {
        // 累加结点总数
        S[Root2] += S[Root1];
        // 小树合并到大树
        S[Root1] = Root2;
    }
    return true;
}

int main()
{
    std::cout << "查找第六个位置的根：" << Find(UFSets, 6) << std::endl;
    Union2(UFSets, 0, 2);
    std::cout << "并操作后，查找第六个位置的根：" << Find(UFSets, 6) << std::endl;

    return 0;
}