#include <iostream>
using namespace std;
#include <vector>
#include <climits>
// 将一个整数 m 分解为 n 个四次方数的和的形式，要求 n 最小。例如，当 m=706 时，因为 706=5^4+3^4

// 所以有 n=2。可以证明此时 n 最小。

// 输入格式
// 一行，一个整数 m。

// 输出格式
// 一行，一个整数 n。

// 这题是个完全背包

// 首先建模：每次选取一个数，以这个数的四次方为体积，以m为总容量，以1为价值，求背包的最小价值，其中每个数字可以使用无限多次（完全背包的标志）。因此我们可以打表，打出1到m四次方根的数字的四次方，然后进行背包

int solution(int m)
{
    vector<int> dp(m + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i <= m; i++)
    {
        //列举0-i之间所有的四次方数
        for (int j = 1; j * j * j * j <= i; j++)
        {
            dp[i] = min(dp[i], dp[i - j * j * j * j] + 1);
        }
    }
    return dp[m];
}

int main()
{
    int m;
    cin >> m;
    cout << solution(m) << endl;
    return 0;
}