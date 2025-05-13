#include <iostream>
using namespace std;
#include <vector>

vector<int> x;

//三叉树

void dfs(int t, int n, int k)
{
    if (t > n)
    {
        for (int i = 1; i <= n;i++)
            cout << x[i] << " ";
        cout << endl;
    }
    else
    {
        for (int i = 1; i <= k;i++)
        {
            x[t] = i;
            dfs(t + 1, n, k);
        }
    }
}

int main()
{
    int n, k;
    cin >> n >> k;
    x.resize(n + 1, 0);

    dfs(1, n, k);

    return 0;
}