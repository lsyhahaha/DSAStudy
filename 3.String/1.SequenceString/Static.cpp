#include <iostream>
#include <cstring>

#define MAXLEN 255
#define LEN 5

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
int index2(SString S, SString T)
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
            // 与KMP相比，i指针回溯。
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

// 求next数组
// next[0]弃用，这样可以不过度思考下标问题
// 第一个字符不匹配时，任何模式串都一样，j=0，next[1]都无脑写0。
// 第二个字符不匹配时，任何模式串都一样，尝试匹配第一个字符，next[2]都无脑写1。
// 从第三个字符开始：
// 在不匹配的位置前面，划一条分界线。模式串一步一步向后退，直到分界线前“能对上”，或者模式串完全跨过分界线为止。
// 此时分界线后对于模式串是哪，next数组值就是多少
// ababaa的next数组：
// 序号     1 2 3 4 5 6
// 模式串   a b a b a a
// next[j] 0 1 1 2 3 4
// 下面的代码是我自己根据以上逻辑写的
bool fineNext(SString T, int next[])
{
    // 前两个位置直接给0和1
    next[1] = 0;
    next[2] = 1;
    // 从模式串第3个位置不匹配开始依次处理，至串长结束。
    for (int i = 3; i <= T.length; i++)
    {
        // 为了方便，重新定义一个模式串的子串
        // 这个子串表示已知主串且匹配上的部分
        SString TS;
        // 从模式串中掏出这个子串
        SubString(TS, T, 1, i - 1);
        // 输出看一下
        // std::cout << "当前模式串的子串：";
        // prints(TS);
        // std::cout << std::endl;
        // 错位对比子串和模式串，是否相同
        // 从1开始，循环到i-1，也就是已知并匹配的部分
        int x = 1, y = 1, z = 1;
        while ((y + z) <= (i - 1))
        {
            // 如果相同，则判断下一个位置
            if (T.ch[x] == TS.ch[y + z])
            {
                x++;
                y++;
                // std::cout << "匹配" << std::endl;
            }
            // 如果不同，错一位重新对比
            else
            {
                x = 1;
                y = 1;
                z++;
                // std::cout << "不匹配" << std::endl;
            }
        }
        // 如果(y+z)超出子串范围(i-1)，则匹配成功
        if ((y + z) > (i - 1))
        {
            next[i] = i - z;
        }
    }

    return true;
}

// 求nextval数组
// 首先需要先求出next数组
bool fineNextval(SString T, int next[], int nextval[])
{
    // nextval[1]无脑写0
    nextval[1] = 0;
    // 从第二个位置开始，依次求nextval
    for (int j = 2; j <= T.length; j++)
    {
        // 如果当前的next[j]所指的字符，和目前j所指的j相等
        if (T.ch[next[j]] == T.ch[j])
            // 则直接给到最终next[j]的位置，这样就避免了一次无效匹配
            nextval[j] = nextval[next[j]];
        // 不相等
        else
            // 则和next数组保持一致
            nextval[j] = next[j];
    }

    return true;
}

// KMP算法
// 传入主串和模式串以及next数组
int index_KMP(SString S, SString T, int next[])
{
    int i = 1, j = 1;
    while (i <= S.length && j <= T.length)
    {
        // 主串与模式串中元素依次对比，相同则继续对比下一个元素。
        if (j == 0 || S.ch[i] == T.ch[j])
        {
            i++;
            j++;
        }
        // 否则 模式串根据next数组向右移动
        else
        {
            // 与朴素模式匹配相比，i指针不回溯
            j = next[j];
        }
    }
    if (j > T.length)
        return i - T.length;
    else
        return -9999;
}
// 最坏时间复杂度 = O(m+n)
// 其中，求next数组复杂度 = O(m)

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

    char *char5 = "aaacaaaabdaaaab";
    char *char6 = "aaaab";

    StrAssign(Y1, char5);
    StrAssign(Y2, char6);

    std::cout << "朴素模式匹配1：" << index(Y1, Y2) << std::endl;
    std::cout << "朴素模式匹配2：" << index2(Y1, Y2) << std::endl;

    int next[LEN];
    int nextval[LEN];
    fineNext(Y2, next);
    fineNextval(Y2, next, nextval);

    // 输出next数组
    std::cout << "next数组：";
    for (int i = 1; i < LEN + 1; i++)
    {
        std::cout << next[i] << " ";
    }
    std::cout << std::endl;

    // 输出nextval数组
    std::cout << "nextval数组：";
    for (int i = 1; i < LEN + 1; i++)
    {
        std::cout << nextval[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "KMP：" << index_KMP(Y1, Y2, nextval) << std::endl;

    return 0;
}