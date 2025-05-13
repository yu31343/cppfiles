#include <iostream>
#include <vector>
using namespace std;

// 选取和不超过 S 的若干个"不同的"正整数，使得所有数的约数（不含它本身）之和最大。

// 输入格式
// 输入一个正整数 S。

// 输出格式
// 输出最大的约数之和。

//其实这题是个背包问题(而且是0-1背包，因为i不能相同)
//S就是背包容量V，i就是重量，i的因子和a[i]就是价值。
//故dp[k] = max(dp[k], dp[k - i] + devide_count(i));   i<=k<=s
//倒序遍历背包即可
int devide_count(int n)
{
    if (n == 0 || n == 1)
        return 0;
    int sum = 1;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            int d_n = n / i;
            if (i != d_n)
                sum += i + d_n;
            else
                sum += i;
        }
    }
    return sum;
}

int maxdevide(int s)
{
    vector<int> dp(s + 1, 0);   //dp[0]=0
/*
    for (int i = 1; i <= s; i++)
    {
        for (int k =s; k >= i; k--)
        {
            dp[k] = max(dp[k], dp[k - i] + devide_count(i));
        }
        
    }

*/
    for (int i = 1; i <= s;i++)
    {
        for (int k = 1; k <= i;k++)
        {
            dp[i] = max(dp[i], dp[i - k] + devide_count(k));
        }
    }
    return dp[s];
}


int main()
{
    int s;
    cin >> s;
    cout << maxdevide(s) << endl;
    return 0;
}