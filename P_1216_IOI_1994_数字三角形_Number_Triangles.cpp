#include <iostream>
using namespace std;
#include <vector>

// 输入格式
// 第一个行一个正整数 r ,表示行的数目。

// 后面每行为这个数字金字塔特定行包含的整数。

// 输出格式
// 单独的一行,包含那个可能得到的最大的和。

//a[i][j]+=max(a[i-1][j-1],a[i-1][j]);//本题最重要的步骤 

int solution(int n, vector<vector<int>> &a, vector<vector<int>> &s)
{
    s[0][0] = a[0][0];
    int maxsum = s[0][0];
    for (int i = 1; i < n; i++)
        s[i][0] = s[i - 1][0] + a[i][0];
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            s[i][j] = max(s[i - 1][j], s[i - 1][j - 1]) + a[i][j];
            if (i == n - 1)
            {
                if (s[i][j] > maxsum)
                    maxsum = s[i][j];
            }
        }
    }
    return maxsum;
}

int main()
{
    int r;
    cin >> r;
    vector<vector<int>> a(r, vector<int>(r, 0));
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            cin >> a[i][j];
        }
    }

    vector<vector<int>> s(r, vector<int>(r, 0));
    int res = solution(r, a, s);
    cout << res;
    return 0;
}