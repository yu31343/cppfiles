#include <iostream>
using namespace std;

// 棋盘上 A 点有一个过河卒，需要走到目标 B 点。卒行走的规则：可以向下、或者向右。同时在棋盘上 C 点有一个对方的马，该马所在的点和所有跳跃一步可达的点称为对方马的控制点。因此称之为“马拦过河卒”。
//  棋盘用坐标表示，A 点(0, 0)、B 点(n, m)，同样马的位置坐标是需要给出的。
//  现在要求你计算出卒从 A 点能够到达 B 点的路径的条数，假设马的位置是固定不动的，并不是卒走一步马走一步。
//  输入格式
//  一行四个正整数，分别表示 B 点坐标和马的坐标。
//  输出格式
//  一个整数，表示所有的路径条数。

long long a, b, n, m, x[23][23], ma[23][23];   //x[][]记录方法数，ma[][]记录马能走到的位置


void work(long long x, long long y)
{
    ma[x][y] = 1;
    ma[x - 1][y - 2] = 1;
    ma[x - 2][y - 1] = 1;
    ma[x - 2][y + 1] = 1;
    ma[x - 1][y + 2] = 1;
    ma[x + 1][y - 2] = 1;
    ma[x + 2][y - 1] = 1;
    ma[x + 2][y + 1] = 1;
    ma[x + 1][y + 2] = 1;
}
int main()
{
    cin >> n >> m >> a >> b;
    a++;
    b++;
    n++;
    m++;
    work(a, b);
    x[1][1] = 1;
    
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (i == 1 && j == 1)
                continue;
            if (ma[i][j] == 0)
                x[i][j] = x[i - 1][j] + x[i][j - 1];
        }
    }

    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < m + 1; j++)
        {
            cout << x[i][j] << "\t";
        }
        cout << endl;
    }

    cout << x[n][m];
    return 0;
}