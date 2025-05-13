#include <iostream>
#include <vector>
using namespace std;

// 机器猫初始时位于 (1,1) 的位置，问能否走到 (n,m) 位置。
// 输入格式
// 第一行，两个正整数 n,m。
// 接下来 n 行，输入这个迷宫。每行输入一个长为 m 的字符串，# 表示墙，. 表示空地。

// 输出格式
// 仅一行，一个字符串。如果机器猫能走到 (n,m)，则输出 Yes；否则输出 No。

int n, m;
bool isok = 0;
vector<vector<char>> a;

void dfs(int i, int j)
{
    if(isok)
        return;
    if (i == n && j == m)
    {
        isok = 1;
        return;
    }
    a[i][j] = '#';
    if (a[i - 1][j] != '#')
        dfs(i - 1, j);
    if (a[i + 1][j] != '#')
        dfs(i + 1, j);
    if (a[i][j + 1] != '#')
        dfs(i , j+1);
    if (a[i][j - 1] != '#')
        dfs(i, j-1);
}

int main()
{
    cin >> n >> m;

    a.resize(n + 2, vector<char>(m + 2, '#'));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    }

    dfs(1, 1);

    if(isok)
        cout << "Yes";
    else
        cout << "No";

    return 0;
}