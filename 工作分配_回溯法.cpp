#include <iostream>
using namespace std;
#include <vector>
#include <climits>
typedef vector<vector<int>> vector2;

// 问题描述：设有n件工作分配给n个人。将工作i分配给第j个人所需的费用为c[i][j]。试
// 设计一个算法，为每个人都分配1件不同的工作，并使总费用达到最小。
// 算法设计：设计一个算法，对于给定的工作费用，计算最佳工作分配方案，使总费用达
// 到最小。

int n;         // 人数
vector2 c;     // 工作费用
vector<int> x; //x[i]:给第i个人分配的工作
vector<int> bestx;  //当前最优分配
int bestc=INT_MAX;  //当前最小总费用
int cc;     //当前总费用


void backtrack(int t)
{
    if (t > n)
    {
        if(cc<bestc)
        {
            bestc=cc;
            bestx = x;
        }
    }
    else
    {
        for (int i = t; i <= n;i++)
        {
            swap(x[t], x[i]);
            cc += c[x[t]][t];
            if (cc < bestc)
                backtrack(t + 1);
            cc -= c[x[t]][t];
            swap(x[t], x[i]);
        }
    }
}

int main()
{
    cin >> n;
    c.resize(n + 1, vector<int>(n + 1));

    x.push_back(0);
    for (int i = 1; i <= n; i++)
        x.push_back(i);
    bestx = x;
    cc = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cin >> c[i][j];
    }

    backtrack(1);
    for (int i = 1; i <= n;i++)
    {
        cout << "工人" << i << "分配工作" << bestx[i] << endl;
    }
        cout << "最小费用：";
    cout << bestc << endl;

    return 0;
}