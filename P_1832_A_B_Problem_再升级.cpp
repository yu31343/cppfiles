#include <iostream>
using namespace std;
#include <vector>
// 给定一个正整数 n，求将其分解成若干个素数之和的方案总数。

// 输入格式
// 一行一个正整数 n。

// 输出格式
// 一行一个整数表示方案总数。

// 也可以先打表，列出2-n之间所有素数，减少循环调用
//bool is_prime1(int i)
/*{
    if (i == 2)
        return true;
    if (i == 0 || i == 1)
        return false;
    for (int j = 2; j * j <= i; j++)
    {
        if (i % j == 0)
            return false;
    }
    return true;
}*/

/*
vector<bool>& prime(int n)
{
     static vector<bool> is_prime(n + 1, 1);
    // 找出所有合数并修改其bool值为0
    for (int i = 2; i <= n / 2; i++)
    {
        if (is_prime[i]) // 合数只需考虑一次
        {
            for (int j = 2; i * j <= n; j++)
            {
                is_prime[i * j] = 0;
            }
        }
    }
    return is_prime;
}
*/

//埃拉托色尼筛法生成素数表 复杂度O(n long(long n))

// 埃拉托色尼筛法的核心思想是：

// 1.将所有整数从 2 到 n 标记为“可能是素数”。
// 2.从最小的素数 2 开始，标记所有 2 的倍数为“非素数”。
// 3.找到下一个未被标记为“非素数”的数i（即下一个素数），然后标记它的所有倍数(从i*i,i*(i+1),...,到n,为什么从 i * i 开始？因为比 i * i 小的倍数（如 i * 2, i * 3...）已经在之前的步骤i=2,i=3中被标记过了。)
//为“非素数”。
// 4.重复步骤 3，直到处理到 sqrt(n) 为止。
// 5.剩下未被标记为“非素数”的数就是素数。
vector<bool>& prime(int n)
{
    static vector<bool> is_prime(n + 1, 1);
    is_prime[0] = is_prime[1] = 0;

    for (int i = 2; i * i <= n;i++)
    {
        if(is_prime[i]) //从2开始，遍历未被标记为合数的数
        {
            //标记i的所有i*i <= a <= n倍数为合数
            for (int j = i * i; j <= n;j+=i)
                is_prime[j] = 0;
        }
    
    }
    return is_prime;
}



long long count_prime(int n)
{
    vector<long long> dp(n + 1, 0);
    vector<bool> is_prime = prime(n);
    dp[0] = 1; // 为了保证dp[2]=1   否则递推下去全是0
    for (int i = 2; i <= n; i++)
    {
        if (!is_prime[i])
            continue;
        for (int j = i; j <= n; j++)
        {
            dp[j] += dp[j - i];
        }
    }
    return dp[n];
}

int main()
{
    int n;
    cin >> n;

    cout << count_prime(n) << endl;

    return 0;
}