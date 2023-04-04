#include <iostream>

// 计算正整数n!
int factorial(int n)
{
    if (n == 0 || n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int main()
{
    std::cout << factorial(10) << std::endl;
}