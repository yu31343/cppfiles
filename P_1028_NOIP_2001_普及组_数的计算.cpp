#include <iostream>
using namespace std;
#include <vector>



// 给出正整数 n，要求按如下方式构造数列：
// 只有一个数 n 的数列是一个合法的数列。
// 在一个合法的数列的末尾加入一个正整数，但是这个正整数不能超过该数列最后一项的一半，可以得到一个新的合法数列。
// 请你求出，一共有多少个合法的数列。

// 输入格式
// 输入只有一行一个整数，表示 n。

// 输出格式
// 输出一行一个整数，表示合法的数列个数。


//直接深搜，n太大会超时
//int sum = 1;
//vector<int> s(1000,0);
// void dfs(int t)
// {
//     if(s[t]>=1)
//     {
//         int half = s[t] / 2;
//         for (int i = 1; i <= half;i++)
//         {
//             s[t+1] = i;
//             sum++;
//             dfs(t + 1);
//         }
//     }
// }

// int main()
// {
//     int n;
//     cin >> n;
//     s[0] = n;
//     dfs(0);
//     cout << sum << endl;
//     return 0;
// }


//动态规划

int main()
{
    int n;
    cin >> n;

    vector<long long> sum(n + 1, 0);


    sum[0] = 1;             //

    for (int i = 1; i <= n;i++)
    {
        int half = i / 2;
        for (int j = 0; j <= half;j++)
        {
            sum[i] += sum[j];
        }
    }

    cout << sum[n] << endl;

}