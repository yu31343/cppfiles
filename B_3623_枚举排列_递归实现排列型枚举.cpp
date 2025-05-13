#include <iostream>
using namespace std;
#include <vector>

//生成P(n,k)所有排列，按字典序排序

void dfs(int t, int n, int k, vector<int> &x, vector<bool> &visited)
{
    if (t > k)
    {
        for (int i = 1; i <= k; i++)
            cout << x[i] << " ";
        cout << endl;
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            if (!visited[i])
            {
                x[t] = i;
                visited[i] = true;
                dfs(t + 1, n, k, x, visited);
                visited[i] = false;
            }
        }
    }
}

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> x(k + 1);
    vector<bool> visited(n + 1,false);

    dfs(1, n, k, x, visited);
    
    return 0;
}