#include <iostream>
using namespace std;
#include <vector>
typedef vector<vector<int>> vector2;
// 自 01 背包问世之后，小 A 对此深感兴趣。一天，小 A 去远游，却发现他的背包不同于 01 背包，他的物品大致可分为 k 组，每组中的物品相互冲突，现在，他想知道最大的利用价值是多少。  k<=100

// 输入格式
// 两个数 m,n，表示一共有 n 件物品，总重量为 m。

// 接下来 n 行，每行 3 个数 a[i] b[i] c[i]
// ，表示物品的重量，利用价值，所属组数。

// 输出格式
// 一个数，最大的利用价值。

// 分组背包问题
// 与0-1背包类似，但每组物品只能选一个
// v[i][k],w[i][k]分别表示第i组第k个物品的价值和重量
// 可用dp[i][j]表示只考虑前i组物品且背包容量为j的情况下所能取得的最大价值
// 则有：
//   dp[i][j]=dp[i-1][j]     //初值，即第i组物品全都装不了时
//   dp[i][j]=max(dp[i][j],dp[i-1][j-w[i][k]]+v[i][k]) 其中1<=k<=第i组物品数量
int knapsack(vector2 &w, vector2 &v, int n, int C)
{
    vector2 s(n + 1, vector<int>(C + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        int groupsize = w[i].size() - 1; // 第k组物品个数，提前定义防止在for循环反复调用size函数

        for (int j = 1; j <= C; j++)
        {
            // 先假设不放第i组物品
            // s[i][j] = s[i - 1][j];    //写这句则后面k从1开始取即可，k从0取可删去

            /// 从第i组k个物品中选
            for (int k = 0; k <= groupsize; k++)
            {
                if (w[i][k] <= j)
                    s[i][j] = max(s[i][j], s[i - 1][j - w[i][k]] + v[i][k]);
            }
        }
    }
    return s[n][C];
}

// 分组背包：一维dp版
int knapsack2(vector2 &w, vector2 &v, int n, int C)
{
    vector<int> dp(C + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        int groupsize = w[i].size() - 1; // 防止在for循环反复调用

        // 倒序遍历背包，但是先不做范围限制

        // 必须先遍历背包容量（j），如果先遍历k，则同组中有多个物品时
        // dp[j]会在从选第二个物品起采用已更新的值(w[i][k]<=j<=C的dp[j]均被更新)，而不是上一轮i-1时未更新的值
        // 无法达到防止重复的效果

        for (int j = C; j >= 1; j--)
        {
            //遍历k时j未发生变化，从而达到防止重复的效果
            for (int k = 1; k <= groupsize; k++)
            {
                // 此处对j做范围限制
                if (j >= w[i][k])
                    dp[j] = max(dp[j], dp[j - w[i][k]] + v[i][k]);
            }
        }
    }
    return dp[C];
}

int main()
{
    int n, C;   // 物品数量，背包容量
    int nn = 0; // 组数
    cin >> C >> n;
    vector2 w(101, vector<int>(1, 0)); // w[i][k]   第i组第k个物品重量
    vector2 v(101, vector<int>(1, 0)); // v[i][k]   第i组第k个物品价值
    for (int i = 1; i <= n; i++)
    {
        int w1, v1, n1;
        cin >> w1 >> v1 >> n1;
        w[n1].push_back(w1);
        v[n1].push_back(v1);
        nn = max(nn, n1);
    }
    cout << knapsack2(w, v, nn, C);
    return 0;
}