#include <iostream>
using namespace std;
#include <vector>

void dfs(int t, int n, vector<char> &c)
{
    if (t > n)
    {
        for (int i = 1; i <= n; i++)
            cout << c[i];
        cout << endl;
    }
    else
    {

        c[t] = 'N';
        dfs(t + 1, n, c);

        c[t] = 'Y';
        dfs(t + 1, n, c);
    }
}

int main()
{
    int n;
    cin >> n;
    vector<char> c(n + 1);
    dfs(1, n, c);

    return 0;
}