#include <iostream>

#define MAXLEN 255

typedef struct
{
    // 定长顺序存储
    char ch[MAXLEN];
    // 默认初始化
    int length = 0;
} SString;

// 赋值操作
bool StrAssign(SString &T, char *chars)
{
    if (strlen(chars) > MAXLEN)
        return false;
    // 这是一个赋值操作，不需要拼接
    T.length = 0;
    for (int i = 0; i < strlen(chars); i++)
    {
        // 为了让下标和串的位置相匹配，这里+1，浪费了ch[0]
        T.ch[T.length + 1] = chars[i];
        T.length++;
    }
    return true;
}

// 复制操作
bool StrCopy(SString &T, SString S)
{
    // 从1开始，到S串长结束
    for (int i = 1; i <= S.length; i++)
    {
        // 数据和串长对应
        T.ch[i] = S.ch[i];
        T.length = S.length;
    }
    return true;
}

// 判空操作
bool StrEmpty(SString S)
{
    return (S.length == 0);
}

// 求串长
int StrLength(SString S)
{
    return S.length;
}

// 清空操作
bool ClearString(SString &S)
{
    S.length = 0;
    return true;
}

// 销毁串：静态实现的串会在调用完成后自动释放

// 串连接
bool Concat(SString &T, SString S1, SString S2)
{
    for (int i = 1; i <= S1.length; i++)
    {
        T.ch[i] = S1.ch[i];
    }
    T.length = S1.length;

    for (int i = (S1.length + 1); i <= (S1.length + S2.length); i++)
    {
        T.ch[i] = S2.ch[i - S1.length];
    }
    T.length += S2.length;

    return true;
}

// 输出串
bool prints(SString S)
{
    for (int i = 1; i <= S.length; i++)
    {
        std::cout << S.ch[i];
    }
    return true;
}

// 求子串
bool SubString(SString &Sub, SString S, int pos, int len)
{
    // 子串范围越界
    if (pos + len - 1 > S.length)
        return false;
    for (int i = pos; i < pos + len; i++)
        Sub.ch[i - pos + 1] = S.ch[i];
    Sub.length = len;
    return true;
}

// 比较串 若S>T，则返回>0 若S=T，则返回=0 若S<T，则返回<0
int StrCompare(SString S, SString T)
{
    for (int i = 1; (i <= S.length && i <= T.length); i++)
    {
        if (S.ch[i] != T.ch[i])
            return S.ch[i] - T.ch[i];
    }
    return S.length - T.length;
}

// 定位操作 若主串S中存在与串T值相同的子串，则返回它在主串S中第一次出现的位置，否则函数值为0
int index(SString S, SString T)
{
    // i是开始取子串的位置，n是S的长度，m是T的长度
    int i = 1, n = StrLength(S), m = StrLength(T);
    SString sub;
    while (i <= n - m + 1)
    {
        // 从主串取子串
        SubString(sub, S, i, m);
        // 主串的子串与T对比，不相等则
        if (StrCompare(sub, T) != 0)
            // 取子串的位置向后移动
            i++;
        // 相等则
        else
            // 返回的i正好是字串位置
            return i;
    }
    // 匹配失败
    return 0;
}

// 朴素 模式匹配 算法（暴力算法）
// 假设：主串长度为n，模式串长度为m
// 暴力算法：将主串中所有长度为m的子串依次与模式串进行对比，直接找到一个完全匹配的子串，或所有子串都不匹配为止。
// 最多对比 n-m+1 个子串
// 定位操作Index函数就是一种朴素模式匹配算法。
// 朴素 模式匹配 算法（暴力算法）
int Index2(SString S, SString T)
{
    int i = 1, j = 1;
    while (i <= S.length && j <= T.length)
    {
        // 主串与模式串中元素依次对比，相同则继续对比下一个元素。
        if (S.ch[i] == T.ch[j])
        {
            i++;
            j++;
        }
        // 不相同则
        else
        {
            // i-j 回到了最开始的前一个位置
            // +1 让我们回到了开始的位置
            // +2 让我们到了下一个可以匹配的子串开头
            i = i - j + 2;
            j = 1;
        }
    }
    // j 大于模式串长度，证明全部匹配成功，返回起始位置
    if (j > T.length)
        return i - T.length;
    // 否则 匹配失败
    else
        return 0;
}
// 设主串长度为n，模式串长度为m
// 最坏的情况，每个子串都要对比m个字符，共n-m+1个子串，
// 复杂度 = O((n-m+1)m) = O(nm)
// 注：一般情况下 n >> m

int main()
{
    SString S1;
    SString S2;

    char *char1 = "Hello ";
    char *char2 = "World!";

    StrAssign(S1, char1);
    StrAssign(S2, char2);

    std::cout << "S1串内容：";
    prints(S1);
    std::cout << std::endl
              << "S1串长：" << StrLength(S1) << std::endl;

    std::cout << "S2串内容：";
    prints(S2);
    std::cout << std::endl
              << "S2串长：" << StrLength(S2) << std::endl;

    SString S3;
    Concat(S3, S1, S2);

    std::cout << "S3串内容：";
    prints(S3);
    std::cout << std::endl
              << "S3串长：" << StrLength(S3) << std::endl;

    SString Sub;
    SubString(Sub, S3, 2, 4);

    std::cout << "S3的Sub串内容：";
    prints(Sub);
    std::cout << std::endl
              << "Sub串长：" << StrLength(Sub) << std::endl;

    SString Y1;
    SString Y2;

    char *char3 = "abcdef";
    char *char4 = "abcdeh";

    StrAssign(Y1, char3);
    StrAssign(Y2, char4);

    std::cout << "比较字符串大小：";
    if (StrCompare(Y1, Y2) > 0)
    {
        prints(Y1);
        std::cout << " > ";
        prints(Y2);
        std::cout << std::endl;
    }
    else if (StrCompare(Y1, Y2) < 0)
    {
        prints(Y1);
        std::cout << " < ";
        prints(Y2);
        std::cout << std::endl;
    }
    else if (StrCompare(Y1, Y2) == 0)
    {
        prints(Y1);
        std::cout << " = ";
        prints(Y2);
        std::cout << std::endl;
    }

    char *char5 = "abcdef";
    char *char6 = "cde";

    StrAssign(Y1, char5);
    StrAssign(Y2, char6);

    std::cout << index(Y1, Y2) << std::endl;

    return 0;
}