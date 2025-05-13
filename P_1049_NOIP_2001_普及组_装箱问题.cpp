#include <bits/stdc++.h>
using namespace std;

// 有一个箱子容量为 V，同时有 n 个物品，每个物品有一个体积。

//  现在从 n 个物品中，任取若干个装入箱内（也可以不取），使箱子的剩余空间最小。输出这个最小值。

//  输入格式
// 第一行共一个整数 V，表示箱子容量。
//  第二行共一个整数 n，表示物品总数。
//  接下来 n 行，每行有一个正整数，表示第 i 个物品的体积。

//  输出格式
// 共一行一个整数，表示箱子最小剩余空间。

//0-1背包问题：物品重量和价值相等v=m

void knapsack(vector<int> &v, int C, vector<vector<int>> &m)
{
    int n = v.size() - 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            if (v[i] > j)
                m[i][j] = m[i - 1][j];
            else
            {
                m[i][j] = max(m[i - 1][j], m[i - 1][j - v[i]] + v[i]);
            }
        }
    }
}

int main()
{
    int C; // 容量
    int n; // 物品个数
    cin >> C >> n;
    vector<int> v(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        cin >> v[i];
    }
    vector<vector<int>> m(n + 1, vector<int>(C + 1, 0));

    knapsack(v, C, m);

    // for (int i = 0; i <= n; i++)
    // {
    //     for (int j = 0; j <=C; j++)
    //         cout << m[i][j] << " ";
    //     cout << endl;
    // }

    cout << C-m[n][C] << endl;

    return 0;
}