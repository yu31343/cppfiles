#include <iostream>
using namespace std;
#include <vector>

// 输入格式
//  第一行有 2 个整数 T（1≤T≤1000）和 M（1≤M≤100），用一个空格隔开，T 代表总共能够用来采药的时间，M 代表山洞里的草药的数目。
//  接下来的 M 行每行包括两个在 1 到 100 之间（包括 1 和 100）的整数，分别表示采摘某株草药的时间和这株草药的价值。

// 输出格式
// 输出在规定的时间内可以采到的草药的最大总价值。

// 0-1背包问题
/*
    采前i个草药，限制时间为j时，所能获得的最大价值：v[i][j]
    j=0 v[i][j]=v[i][0]=0;
    i=0 v[i][j]=v[0][j]=0;
    i>=1,j>=1
        t[i]>j  第i个草药超过限制时间无法采集 v[i][j]=v[i-1][j]
        t[i]<=j 第i个草药能采集，在采与不采之间取最大价值
        v[i][j]=max(v[i-1][j],v[i-1][j-t[i]]+m[i])
*/
void knapsack(const vector<int> &t, const vector<int> &m, int time, vector<vector<int>> &v)
{
    int mount = m.size() - 1; // 种类数
    for (int i = 1; i <= mount; i++)
    {
        for (int j = 1; j <= time; j++)
        {
            if (t[i] > j)
                v[i][j] = v[i - 1][j];
            else
                v[i][j] = max(v[i - 1][j], v[i - 1][j - t[i]] + m[i]);
        }
    }
}

int main()
{
    int time, mount; // time总时间 mount 草药种数
    cin >> time >> mount;
    vector<int> t(mount + 1, 0); // t[i]:第i个草药采集时间
    vector<int> m(mount + 1, 0); // m[i]:第i个草药价值
    for (int i = 1; i <= mount; i++)
    {
        cin >> t[i] >> m[i];
    }

    vector<vector<int>> v(mount + 1, vector<int>(time + 1, 0));
    knapsack(t, m, time, v);

    // for (int i = 0; i <= mount; i++)
    // {
    //     for (int j = 0; j <= time; j++)
    //         cout << v[i][j] << " ";
    //     cout << endl;
    // }
    cout << v[mount][time] << endl;
    return 0;
}