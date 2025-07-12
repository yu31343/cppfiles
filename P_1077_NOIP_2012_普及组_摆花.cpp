#include <iostream>
using namespace std;
#include <vector>

// 小明的花店新开张，为了吸引顾客，他想在花店的门口摆上一排花，共 m 盆。通过调查顾客的喜好，小明列出了顾客最喜欢的 n 种花，从 1 到 n 标号。为了在门口展出更多种花，规定第 i 种花不能超过 a[i]
// 盆，摆花时同一种花放在一起，且不同种类的花需按标号的从小到大的顺序依次摆列。

// 试编程计算，一共有多少种不同的摆花方案。

// 输入格式
// 第一行包含两个正整数 n 和 m，中间用一个空格隔开。

// 第二行有 n 个整数，每两个整数之间用一个空格隔开，依次表示 a[n]
// ​

// 输出格式
// 一个整数，表示有多少种方案。注意：因为方案数可能很多，请输出方案数对 10^6+7 取模的结果。

// 问题等价于
// 有n个数c1,c2,c3,...,cn
// c[i]<=a[i]
// 且c1+c2+...+cn=m的方案数


//深搜 超时
// int n, m;
// vector<int> a;
// int sum = 0, count = 0, leftm = 0;

// void dfs(int t)
// {
//     if (t > n||sum==m)
//     {
//         if (sum == m)
//             count++;
//         return;
//     }
//     for (int i = 0; i <= a[t]; i++)
//     {
//         leftm -= a[t];

//         if (sum + i + leftm >= m && sum + i <= m)
//         {
//             sum += i;

//             dfs(t + 1);
            
//             sum -= i;
//         }
//         leftm += a[t];
//     }
// }

// int main()
// {

//     cin >> n >> m;
//     a.resize(n + 1, 0);
//     for (int i = 1; i <= n; i++)
//     {
//         cin >> a[i];
//         leftm += a[i];
//     }
//     dfs(1);
//     cout << count % (1000000 + 7) << endl;

//     return 0;
// }


//动态规划
//s(n,m)表示只使用前n个数使得加和为m的方案数
//s(n,m)=sum(s(n-1,m-i))  i=0,1,...,a[n],...,m
int n, m;
vector<int> a;
vector<vector<int>> s;

void solution()
{
    s[0][0] = 1;    //n=0：前0个数相加为0只有1种，其他无方案
    for (int i = 1; i <= n;i++)
    {
        for (int j = 0; j <= m;j++)     //j取0：前n个数相加为0只有一种
        {
            for (int k = 0; k <= min(j, a[i]);k++)
            {
                s[i][j] += s[i - 1][j - k]%(1000000+7);
            }
        }
    }
}


int main()
{

    cin >> n >> m;
    a.resize(n + 1, 0);
    s.resize(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    solution();

    cout << s[n][m] % (1000000 + 7) << endl;

    return 0;
}