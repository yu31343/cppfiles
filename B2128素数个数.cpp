#include <iostream>
using namespace std;
// #include <cmath>
//  编程求 2 ～ n(n 为大于 2 的正整数）中有多少个素数。

bool is_prime(int n)
{
    // if (n == 2)
    //     return true;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main()
{
    int n = 0;
    cin >> n;
    int count = 0;
    for (int i = 2; i <= n; i++)
    {
        if (is_prime(i))
            count++;
    }
    cout << count << endl;
    return 0;
}