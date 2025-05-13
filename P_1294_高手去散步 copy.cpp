#include <iostream>
using namespace std;
#include <vector>
#include <climits>

// 鳌头山上有 n 个观景点，观景点两两之间有游步道共 m 条。那些没有路的观景点高手是不会选择去的。另外，也不喜欢去同一个观景点一次以上。而高手想让走的路程最长，已知高手的穿梭机可以让他们在任意一个观景点出发，也在任意一个观景点结束。

// 输入格式
// 第一行，两个用空格隔开的整数 n 、 m. 之后 m 行，为每条游步道的信息：两端观景点编号、长度。

// 输出格式
// 一个整数，表示他走的最长路程。

int n, m;
int bests = 0, s = 0;

vector<int> x;
vector<vector<int>> a;

void backtrack(int t)
{
    if (t > n)
    {
        if (s > bests)
            bests = s;
    }
    else
    {
        for (int i = t; i <= n; i++)
        {
            swap(x[t], x[i]);
            int road = a[x[t - 1]][x[t]];
            if (road == INT_MAX)
            {
                if (s > bests)
                    bests = s;
            }
            else
            {
                s += road;
                backtrack(t + 1);
                s -= road;
            }
            swap(x[t], x[i]);
        }
    }
}

int main()
{
    cin >> n >> m;
    a.resize(n + 1, vector<int>(n + 1, INT_MAX));
    x.resize(n + 1);
    for (int i = 0; i <= n; i++)
    {
        x[i] = i;
        a[0][i] = 0;
        a[i][0] = 0;
    }
    for (int i = 0; i < m; i++)
    {
        int p, q, len;
        cin >> p >> q >> len;
        a[p][q] = a[q][p] = len;
    }

    backtrack(1);

    cout << bests;

    return 0;
}