#include <iostream>
using namespace std;
#include <vector>
#include <cstdio>
#include <algorithm>

class Permutation
{
    int n;
    vector<int> x;

public:
    Permutation(int nn)
    {
        this->n = nn;
        x.resize(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            x[i] = i;
        }
        backtrack(1);
    }

    Permutation(int nn, vector<bool> &visited)
    {
        this->n = nn;
        x.resize(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            x[i] = i;
        }
        backtrack(1, visited);
    }

    Permutation() {}
    void backtrack(int t);
    void backtrack(int t, vector<bool> &visited);
};

void Permutation::backtrack(int t)
{
    if (t > n)
    {
        for (int i = 1; i <= n; i++)
            printf("%5d", x[i]);
        cout << endl;
    }
    else
    {
        for (int i = t; i <= n; i++)
        {
            swap(x[t], x[i]);

            backtrack(t + 1);

            swap(x[t], x[i]);
        }
    }
}

// 引入visited数组，正向遍历同时排除已使用元素，保证输出按照字典序排列
void Permutation::backtrack(int t, vector<bool> &visited)
{
    if (t > n)
    {
        if (x[1] <= x[n])
        {
            for (int i = 1; i <= n; i++)
                printf("%5d", x[i]);
            cout << endl;
        }
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            if (!visited[i])
            {
                visited[i] = 1;
                x[t] = i;
                backtrack(t + 1, visited);
                visited[i] = 0;
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    vector<bool> visited(n + 1, false);
    Permutation{n,visited};
    return 0;
}