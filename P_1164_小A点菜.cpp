#include <iostream>
using namespace std;
#include <vector>

// uim口袋里只剩 M 元 (M≤10000)。

// 餐馆虽低端，但是菜品种类不少，有 N 种 (N≤100)，第 i 种卖 a_i元 (a_i≤1000)。
// 由于是很低端的餐馆，所以每种菜只有一份。
// 小 A 奉行“不把钱吃光不罢休”的原则，所以他点单一定刚好把 uim 身上所有钱花完。他想知道有多少种点菜方法。

// 输入格式
// 第一行是两个正整数，表示 N 和 M。

// 第二行起 N 个正数 a_i
//  （可以有相同的数字，每个数字均在 1000 以内）。

// 输出格式
// 一个正整数，表示点菜方案数，保证答案的范围在 int 之内。

//类背包问题
/*
    用s[i][j]表示从前i道菜中吃光j元钱的方法总数
    j=0 || i=0 s[i][j]=0
    j=s[i] s[i][j]=s[i-1][j]+1  //第i道菜价格=j，可以只吃第i道菜，方法数+1
    j<s[i] s[i][j]=s[i-1][j]    //单独吃i的钱都不够，方法数不变
    j<s[i] s[i][j]=s[i-1][j]+s[i-1][j-a[i]]
    //钱足够，方法数=不吃第i道菜方法数+吃第i道菜方法数（需要在前i-1道菜中吃光j-a[i]元）
*/


void knapsack(int n,int m,vector<int>& a,vector<vector<int>>& s)
{
    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j <= m;j++)
        {
            if(j==a[i])
                s[i][j] = s[i - 1][j] + 1;
            else if(j<a[i])
                s[i][j] = s[i - 1][j];
            else
                s[i][j] = s[i - 1][j] + s[i - 1][j - a[i]];
        }
    }
}

int main()
{
    int n,m;
    cin >> n >> m;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    vector<vector<int>> s(n + 1, vector<int>(m + 1, 0));
    knapsack(n, m, a, s);
    cout << s[n][m] << endl;
    return 0;
}
