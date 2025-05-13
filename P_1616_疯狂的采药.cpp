#include <iostream>
using namespace std;
#include <vector>
typedef vector<vector<int>> vector2;  //时间T过大导致int溢出时得使用long long

// 完全背包问题：每个物品可取无限次
void knapsack(int T, vector<int> &t, vector<int> &v, vector2 &s)
{
    int n = t.size() - 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= T; j++)
        {
            if (t[i] > j)
                s[i][j] = s[i - 1][j];
            else
            {
                // 0-1背包
                // s[i][j] = max(s[i - 1][j], s[i - 1][j - t[i]] + v[i]);
                //区别：放入物品i后依然在前i个物品中选取，即i不减一，仅s容量减少
                s[i][j] = max(s[i - 1][j], s[i][j - t[i]] + v[i]);
            }
        }
    }
}

int main()
{
    int T; // 限制总时间
    int n;  //物品数目
    cin >> T >> n;
    vector<int> t(n + 1); // 花费时间
    vector<int> v(n + 1); // 物品价值
    for (int i = 1; i <= n; i++)
    {
        cin >> t[i] >> v[i];
    }
    vector2 s(n + 1, vector<int>(T + 1, 0));
    knapsack(T, t, v, s);
    cout << s[n][T] << endl;
    return 0;
}