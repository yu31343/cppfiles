#include <iostream>
using namespace std;
#include <vector>

// 每件物品规定了一个重要度，分为 5 等：用整数 1−5 表示，第 5 等最重要。已知每件物品的价格（都是整数元）。在不超过 N 元（可以等于 N 元）的前提下，使每件物品的价格与重要度的乘积的总和最大。

// 请你设计一个满足要求的购物单。

// 输入格式
// 第一行，为 2 个正整数，用一个空格隔开：n,m（n<30000,m<25）其中 n 表示总钱数，m 为希望购买物品的个数。

// 从第 2 行到第 m+1 行，第 j 行给出了编号为 j−1 的物品的基本数据，每行有 2 个非负整数 v,p（其中 v 表示该物品的价格 (v≤10000)，p 表示该物品的重要度（1≤p≤5）。

// 输出格式
// 1 个正整数，为不超过总钱数的物品的价格与重要度乘积的总和的最大值（<100000000）。

//0-1背包问题

void knapsack(vector<int> &v, vector<int> &p, int n, vector<vector<int>> &s)
{
    int m = v.size() - 1; // 物品个数
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (v[i] > j)
                s[i][j] = s[i - 1][j];
            else
            {
                s[i][j] = max(s[i - 1][j], s[i - 1][j - v[i]] + v[i] * p[i]);
            }
        }
    }
}

int main()
{
    int n, m; // n总钱数 m物品个数
    cin >> n >> m;
    vector<int> v(m + 1, 0); // 物品价格
    vector<int> p(m + 1, 0); // 物品重要度
    for (int i = 1; i <= m; i++)
    {
        cin >> v[i] >> p[i];
    }

    vector<vector<int>> s(m + 1, vector<int>(n + 1, 0));
    knapsack(v, p, n, s);
    cout << s[m][n] << endl;
    return 0;
}