#include <iostream>
using namespace std;
#include <vector>

// 0-1背包问题：每个物品只能取1次
// s[j]储存容量为j时最大价值
// 先遍历物品，再 “倒序” 遍历背包
void knapsack(int T, vector<int> &t, vector<int> &v, vector<long long> &s)
{
    int n = t.size() - 1;
    for (int i = 1; i <= n; i++)
    {
        // j<t[i]时dp[j]无变化，直接从j=t[i]开始遍历背包
        // 背包倒序遍历，物品可重复放入，j每隔t[i]便增加一个v[i]

        // 对于0-1背包，背包必须倒序遍历
        // 因为dp[j]的值是由上方的值和左侧的值推导出来，但左侧不能先出现值(即必须是上一轮i-1时的旧值）
        // 不然会导致物品重复拿取
        //故先从右侧开始更新
        for (int j = T; j >= t[i]; j--)
            // 优化前：0-1背包二维dp
            //  dp[i][j] = max(dp[i - 1][j], dp[i-1][j - t[i]] + v[i]);
            // 如果把dp[i - 1]那一层拷贝到dp[i]上，
            // 表达式完全可以是：dp[i][j] = max(dp[i][j], dp[i][j - t[i]] + v[i]);
            // 与其把dp[i - 1]这一层拷贝到dp[i]上，不如只用一个一维数组了，只用dp[j]（一维数组，也可以理解是一个滚动数组）。
            // 这就是滚动数组的由来，需要满足的条件是上一层可以重复利用，直接拷贝到当前层。

            s[j] = max(s[j], s[j - t[i]] + v[i]);

        // s[j]更新前表示只在前i-1个物品选择装取时最大价值，因为其数据来源于上一轮i-1时的循环
        // S[j]更新后表示在前i个物品选择装取时最大价值
    }
}

int main()
{
    int T; // 限制总时间
    int n; // 物品数目
    cin >> T >> n;
    vector<int> t(n + 1); // 花费时间
    vector<int> v(n + 1); // 物品价值
    for (int i = 1; i <= n; i++)
    {
        cin >> t[i] >> v[i];
    }
    vector<long long> s(T + 1, 0);
    knapsack(T, t, v, s);
    cout << s[T] << endl;
    return 0;
}