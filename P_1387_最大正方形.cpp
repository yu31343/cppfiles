#include <iostream>
using namespace std;
#include <vector>

// 题目描述
// 在一个 n×m 的只包含 0 和 1 的矩阵里找出一个不包含 0 的最大正方形，输出边长。

// 输入格式
// 输入文件第一行为两个整数 n,m(1≤n,m≤100)，接下来 n 行，每行 m 个数字，用空格隔开，0 或 1。

// 输出格式
// 一个整数，最大正方形的边长。

// 记f[i][j]表示以元素a[i][j]为右下角的正方形的最大边长
// 则f[i][j]满足：
// a[i][j]==0时，f[i][j]=0
// a[i][j]==1时
// f[i][j] = min(f[i - 1][j - 1],f[i - 1][j], f[i][j - 1]) + 1;
// 即取左上角方格最大正方形和左边、上边方格最大正方形的公共部分

typedef vector<vector<int>> vector2;

int solution(int n, int m, vector2 &a, vector2 &f)
{
    int maxlen = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i][0] == 1)
        {
            f[i][0] = 1;
            maxlen = 1;
        }
    }
    for (int j = 0; j < m; j++)
    {
        if (a[0][j] == 1)
        {
            f[0][j] = 1;
            maxlen = 1;
        }
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            if (a[i][j] == 1)
            {
                f[i][j] = min(f[i - 1][j - 1], min(f[i - 1][j], f[i][j - 1])) + 1;
                maxlen = max(maxlen, f[i][j]);
            }
            else
                f[i][j] = 0;
        }
    }
    return maxlen;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector2 a(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> a[i][j];
        }
    }

    vector2 f(n, vector<int>(m, 0));

    cout << solution(n, m, a, f) << endl;
    return 0;
}