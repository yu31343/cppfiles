#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

// 题目描述
// 已知 n 个整数 x[1],x[2],...,x[n]
// ​以及 1 个整数 k（k<n）。从 n 个整数中任选 k 个整数相加，可分别得到一系列的和。例如当 n=4，k=3，4 个整数分别为 3,7,12,19 时，可得全部的组合与它们的和为：
// 3+7+12=22
// 3+7+19=29
// 7+12+19=38
// 3+12+19=34

// 现在，要求你计算出和为素数共有多少种。
// 例如上例，只有一种的和为素数：3+7+19=29。

// 输入格式
// 第一行两个空格隔开的整数 n,k（1≤n≤20，k<n）。
// 第二行 n 个整数，分别为 x[1],x[2],..,x[n]  (1≤x[i]<5x10^6)

// 输出格式
// 输出一个整数，表示种类数

int n, k, sum;
vector<int> x;
vector<int> path;
// vector<bool> is_prime;

// vector<bool> &prime(int n)
// {
//     static vector<bool> is_prime(n + 1, 1);
//     is_prime[0] = is_prime[1] = 0;

//     for (int i = 2; i * i <= n; i++)
//     {
//         if (is_prime[i])
//         {
//             for (int j = i * i; j <= n; j += i)
//                 is_prime[j] = 0;
//         }
//     }
//     return is_prime;
// }

bool is_prime(int num)
{
    if (num < 2)
        return false;
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

void backtrack(int t, int start)
{
    if (t > k)
    {
        int s = 0;
        for (int i = 1; i <= k; i++)
            s += path[i];
        if (is_prime(s))
            sum++;
        return;
    }

    for (int i = start; i <= n; i++)
    {
        path[t] = x[i];
        backtrack(t + 1, i + 1);
    }
}

int main()
{
    sum = 0;
    cin >> n >> k;
    x.resize(n + 1, 0);
    path.resize(k + 1, 0);
    for (int i = 1; i <= n; i++)
        cin >> x[i];
    //sort(x.begin(), x.end());
    int maxsum = 0;
    // for (int i = 1; i <= k; i++)
    //     maxsum += x[n - i + 1];
    // is_prime = prime(maxsum);

    backtrack(1, 1);

    cout << sum << endl;

    return 0;
}