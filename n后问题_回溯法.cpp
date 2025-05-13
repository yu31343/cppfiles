#include <iostream>
using namespace std;
#include <vector>

int n;         // 皇后个数
vector<int> x; // 当前解
int sum;       // 当前已找到的可行方案数

bool place(int i)
{
    //判断是否与之前放过的皇后位于 同一列 或 同一斜线上
    for (int j = 1; j < i;j++)
    {
        if(x[j]==x[i]||abs(i-j)==abs(x[i]-x[j]))
            return false;
    }
    return true;
}

bool place1(int i)
{
    //判断是否与之前放过的皇后位于 同一斜线上
    for (int j = 1; j < i;j++)
    {
        if(abs(i-j)==abs(x[i]-x[j]))
            return false;
    }
    return true;
}

//n叉树 穷举
void backtrack(int t)
{
    if (t > n)
    {
        sum++;
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            x[t] = i;
            // 判断[t][i]能不能放皇后
            if (place(t))   //传的是t！
                backtrack(t + 1);
        }
    }
}

//排列树 保证不同列，只需检查是否同一斜线
void backtrack1(int t)
{
    if(t>n)
    {
        sum++;
    }
    else
    {
        for (int i = t; i <= n;i++)
        {
            swap(x[t], x[i]);
            if(place1(t))
                backtrack1(t + 1);
            swap(x[t], x[i]);
        }
    }
}

int main()
{
    cin >> n;
    x.resize(n + 1, 0);
    sum = 0;

    //n叉树
    backtrack(1);
    cout << sum << endl;

    //排列树
    sum = 0;
    for (int i = 1; i <= n;i++)
        x[i] = i;
    backtrack1(1);

    cout << sum << endl;
    return 0;
}