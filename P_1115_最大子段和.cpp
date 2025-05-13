#include <iostream>
using namespace std;
#include <vector>
#include <climits>
// 给出一个长度为 n 的序列 a，选出其中连续且非空的一段使得这段和最大。

// 输入格式
// 第一行是一个整数，表示序列的长度 n。
// 第二行有 n 个整数，第 i 个整数表示序列的第 i 个数字 a[i]

// 输出格式
// 输出一行一个整数表示答案。

// 直接枚举，n太大时超出时间限制
//  int longest_substr(vector<int> &a)
//  {
//      int n = a.size();
//      int msum = INT_MIN;
//
//      for (int i = 0; i < n; i++)
//      {
//          for (int j = i; j < n; j++)
//          {

//             int sum=0;
//             for (int k = i; k <= j; k++)
//             {
//                 sum += a[k];
//             }
//             msum = max(msum, sum);
//         }
//     }
//     return msum;
// }

// int longest_substr(vector<int> &a, vector<vector<int>> &m)
// {
//     int n = a.size();
//     int msum = INT_MIN;
//     for (int i = 0; i < n;i++)
//         m[i][i] = a[i];
//     for (int r = 1; r < n;r++)
//     {
//         for (int i = 0; i + r < n;i++)
//         {
//             int j = i + r;
//             m[i][j] = m[i][j - 1] + a[j];
//             msum = max(m[i][j], msum);
//         }
//     }
//         // for (int i = 0; i < n; i++)
//         // {
//         //     for (int j = i; j < n; j++)
//         //     {
//         //         for (int k = i; k <= j; k++)
//         //         {
//         //             m[i][j] += a[k];
//         //         }
//         //         msum = max(msum, m[i][j]);
//         //     }
//         // }
//     return msum;
// }

//有效序列：最后一个元素为a[i]的最优序列，即所有以a[i]结尾的连续子序列中和最大的那一个序列
//其对应最大和记为b[i]

// 第一个数为一个有效序列 i=0  b[i]=a[i];

// 如果一个数加上上一个有效序列得到的结果比这个数大，那么该数也属于这个有效序列。
// 如果一个数加上上一个有效序列得到的结果比这个数小，那么这个数单独成为一个新的有效序列
//        b[i]=max(a[i],b[i-1]+a[i])   i>=1

// 在执行上述处理的过程中实时更新当前有效序列的所有元素之和并取最大值。
//        result=max(b[i])  i=0,1,2...,n

int longest_substr(vector<int>& a, vector<int>& b)
{
    int n = a.size();
    int result = INT_MIN;
    b[0] = a[0];
    for (int i = 1; i < n;i++)
    {
        b[i] = max(a[i], b[i - 1] + a[i]);
        result = max(b[i], result);
    }
    return result;
}

int main()
{
    int n;
    cin >> n;
    vector<int> a(n, 0);
    vector<int> b(n, 0);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    cout << longest_substr(a, b) << endl;

    return 0;
}