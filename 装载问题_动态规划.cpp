#include <iostream>
using namespace std;
#include <vector>

typedef vector<vector<int>> vector2;

void knapsack(int n, int c1, vector<int> &w, vector2 &s)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= c1; j++)
        {
            if (w[i] > j)
                s[i][j] = s[i - 1][j];
            else
                s[i][j] = max(s[i - 1][j], s[i - 1][j - w[i]] + w[i]);
        }
    }
}

void traceback(int n, int c1, vector<int> &w, vector2 &s, vector<int> &x)
{
    for (int i = n ; i > 1; i--)
    {
        if (s[i][c1] == s[i - 1][c1])
        {
            // cout << "第" << i << "号货物装第二艘船" << endl;
            x[i] = 0;
        }
        else
        {
            x[i] = 1;
            cout << "第" << i << "号货物装第一艘船" << endl;
            c1 -= w[i];
        }
    }
    if (s[1][c1] != 0)
    {
        cout << "第1号货物装第一艘船" << endl;
        x[1] = 1;
    }
    else
    {
        cout << "第1号货物装第二艘船" << endl;
        x[1] = 0;
    }
}

int main()
{
    int n; // 集装箱个数
    cin >> n;
    int c1, c2; // 两艘船载重量
    cin >> c1 >> c2;
    vector<int> w(n + 1); // 货物重量
    for (int i = 1; i <= n; i++)
    {
        cin >> w[i];
    }
    vector2 s(n + 1, vector<int>(c1 + 1, 0));
    knapsack(n, c1, w, s);
    cout << s[n][c1] << endl;

    vector<int> x(n + 1);
    traceback(n, c1, w,s, x);

    return 0;
}