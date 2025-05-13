#include <iostream>
using namespace std;
#include <vector>
// 题目描述
// 楼梯有 N 阶，上楼可以一步上一阶，也可以一步上二阶。
// 编一个程序，计算共有多少种不同的走法。

// 输入格式
// 一个数字，楼梯数。

// 输出格式 输出走的方式总数。
vector<long long> v;

long long  count_floor(int n)
{
    if (n == 1)
    {
        return 1;
    }
    if (n == 2)
    {
        return 2;
    }
    if (v[n] == 0)
        v[n] = count_floor(n - 1) + count_floor(n - 2);
    return v[n];
}

int main()
{
    int n;
    cin >> n;
    v.resize(n + 1, 0);
    cout << count_floor(n) << endl;
    return 0;
}