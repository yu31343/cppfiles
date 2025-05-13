#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

// 设有一个长度为L的钢条，在钢条上标有n个位置点（p1, p2,…, pn）。现在需要按钢条上标注的位置将钢条切割为n + 1段，假定每次切割所需要的代价与所切割的钢条长度成正比。请编写一个算法，能够确定一个切割方案，使切割的总代价最小。

// 算法要求：请编写一个算法，能够确定一个切割方案，使切割的总代价最小。

//动态规划： 矩阵连乘类问题

// 函数原型：
void MinCost(int L, int n, int *p, vector<vector<int>> &s)
{
    sort(p + 1, p + n + 1);

    for (int i = 0; i <= n + 1; i++)
        cout << p[i] << " ";
    cout << endl;

    vector<vector<int>> cost(n + 1, vector<int>(n + 2, 0));

    // for (int i = 0; i < n + 1; i++)
    // {
    //     cost[i][i + 1] = 0;
    // }

    for (int r = 2; r <= n + 1; r++)
    {
        for (int i = 0; i + r <= n + 1; i++)
        {
            int j = i + r;
            cost[i][j] = cost[i][i + 1] + cost[i + 1][j] + p[j] - p[i]; // cost[i][i + 1] =0,舍去
            s[i][j] = i + 1;
            for (int k = i + 2; k < j; k++)
            {
                int temp = cost[i][k] + cost[k][j] + p[j] - p[i];
                if (temp < cost[i][j])
                {
                    cost[i][j] = temp;
                    s[i][j] = k;
                }
            }
        }
    }

    // for (int i = 0; i < n + 1; i++)
    // {
    //     for (int j = 0; j < n + 1; j++)
    //     {
    //         cout << cost[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    cout << cost[0][n + 1] << endl;
}

// 你的代码只需要补全上方函数来实现算法,可根据自己需要建立别的函数
// 其中L是钢条长度，n是位置点个数，p包含n 个切割点的位置（乱序）
// 只需要提交这几行代码，其他的都是后台系统自动完成的。类似于 LeetCode

// 回溯切割位置
void traceback(int i, int j, int *p, vector<vector<int>> &s)
{
    if (j==i+1)
        return;
    cout << p[s[i][j]] << " ";

    traceback(i, s[i][j], p, s);

    traceback(s[i][j], j, p, s);
}

int main()
{
    // 后台自动给出测试代码放在这里，无需同学编写
    int L, n;
    cin >> L >> n;
    int *p;
    vector<vector<int>> s(n + 1, vector<int>(n + 2, 0)); // 回溯矩阵，记录切割位置
    p = new int[n + 2];
    p[0] = 0;
    p[n + 1] = L;
    for (int i = 1; i < n + 1; i++)
    {
        cin >> p[i];
    }
    // 调用函数输出一个切割最小的代价和，结果通过cout输出，均为int类型
    MinCost(L, n, p, s);
    traceback(0, n + 1, p, s);
    return 0;
}