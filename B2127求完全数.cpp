#include <iostream>
using namespace std;
#include <cmath>

// 完全数：对于一个自然数，所有比它小的所有因数之和，等于它本身，它就是个完全数。如 6 = 1 + 2 + 3。
bool is_perfect_num(int n)
{
    int sq_n = sqrt(n);
    int sum = 1;
    for (int i = 2; i <= sq_n; i++)
    {
        if (n % i == 0)
        {
            if (i != n / i)
                sum += i + n / i;   //注意n为平方数的情况！否则sqrt(n)被重复计算！
            else
                sum += i;
        }
    }
    if (sum == n)
        return true;
    return false;
}

int main()
{
    int n = 0;
    cin >> n;
    for (int i = 2; i < n; i++)
    {
        if (is_perfect_num(i))
        {
            cout << i << endl;
        }
    }

    return 0;
}