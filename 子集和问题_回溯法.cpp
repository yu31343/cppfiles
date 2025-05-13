#include <iostream>
#include <vector>
using namespace std;

// 算法设计：对于给定的正整数的集合S={x1,x2,...,xn}和正整数c，计算S的一个子集S1，使得S1中所有元素的和=c。

vector<int> s;
int n; // S的大小
int c;
int cw=0;    // 当前和
int bestw=0; // 当前最大和(不超过c)
int r = 0; // 剩余元素和

vector<bool> x;     // 当前解
vector<bool> bestx; // 当前最优解

bool backtrack(int t)
{
    if (t > n)
    {
        bestx = x;
        bestw = cw;
        if (bestw == c)
            return true;
        else
            return false;
    }
    r -= s[t];

    if (cw + s[t] <= c)
    {
        x[t] = 1;
        cw += s[t];
        if (backtrack(t + 1))
            return true;
        cw -= s[t];
    }

    if (cw + r > bestw)
    {
        x[t] = 0;
        if (backtrack(t + 1))
            return true;
    }

    r += s[t];
    return false;
}

int main()
{
    cin >> n >> c;
    s.resize(n + 1, 0);
    x.resize(n + 1);
    bestx.resize(n + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        r += s[i];
    }

    if (backtrack(1))
    {
        for (int i = 1; i <= n; i++)
        {
            if (x[i])
                cout << s[i] << " ";
        }
        cout << endl;
    }
    else
        cout << "不存在" << endl;
    return 0;
}