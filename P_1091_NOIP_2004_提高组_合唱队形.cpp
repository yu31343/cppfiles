#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 求给定序列的一个最长的子序列，满足这个序列先升序再降序。

int n;
vector<int> a;

vector<int> f; // f[i]: 以a[i]结尾的最长升序"子序列"长度 (非连续子序列，可跳跃)
vector<int> g; // g[i]: 以a[n+1-i]开头的最长降序子序列长度
               // 结果res=max(f[i]+g[n+1-i]-1)  i=1,2,..,n

void maxupstr(vector<int> &f)
{
    // f[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j < i; j++)
        {
            if (a[i] > a[j])
                f[i] = max(f[i], f[j] + 1);
            // else
            //     f[i] = f[i];
        }
    }
}

int main()
{
    cin >> n;
    a.resize(n + 1, 0);
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    f.resize(n + 1, 1); // 单个元素至少为1
    g.resize(n + 1, 1);

    maxupstr(f);

    reverse(a.begin() + 1, a.end()); // 翻转数列 降序->升序

    maxupstr(g);

    int maxlen = 0;

    for (int i = 1; i <= n; i++)
    {
        maxlen = max(maxlen, f[i] + g[n + 1 - i] - 1);
    }

    cout << n - maxlen << endl;

    return 0;
}