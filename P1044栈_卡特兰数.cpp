#include <bits/stdc++.h>
using namespace std;


// 你的程序将对给定的 n，计算并输出由操作数序列 1, 2,…, n 经过栈的出栈入栈操作可能得到的输出序列的总数。

//输入格式 输入文件只含一个整数 n（1≤n≤18）。

//输出格式 输出文件只有一行，即可能输出序列的总数目。

//等价问题：
// 在平面直角坐标系中，从(0,0)
// 出发，每次只能向上走或者向右走，且不能越过y=x这条直线（可以碰到），求走到(n,n)的不同路径的数量
//向右走：入栈 | 向左走：出栈 | 不能越过y=x：栈内元素个数>=0

//直接利用卡特兰数递推公式其一: C(n)=C(n-1)*(4n-2)/(n+1)
int catalan(int n)
{
    int res=1;
    for(int i=1;i<=n;i++)
        res *= ((4 * i - 2)*1.0 / (i + 1));
    return res;
}

//动态规划：递推公式
/*
    记f(i,j)为push i次,pop j次情况总数(等价于原点到(x,y)路径总数)
    (j>i | j<0 时，f(i,j)=0)
    j=0 f(i,j)=1
    f(i,j)=f(i-1,j)+f(i,j-1)    j>0;
    求f(n,n)
*/

int solution(int n)
{
    vector<vector<int>> f(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i <= n;i++)
        f[i][0] = 1;
    for(int i=1;i<=n;i++)
    {
        for (int j = 1; j <= i;j++)
        {
            f[i][j] = f[i - 1][j] + f[i][j - 1];
        }
    }
    return f[n][n];
}



int main()
{
    int n;
    cin>>n;

    cout << solution(n) << endl;

    //cout << catalan(n) << endl;
    return 0;
}