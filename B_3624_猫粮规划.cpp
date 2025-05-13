#include <iostream>
using namespace std;
#include <vector>

int s = 0;
int cw = 0;
int rest = 0;

void dfs(int t,int n,int l,int r,vector<int>& w)
{
    if(t>n)
    {
        if(cw>=l&&cw<=r)
            s++;
        return;
    }
    rest -= w[t];
    if(cw+w[t]<=r)
    {
        cw += w[t];
        dfs(t + 1, n, l, r, w);
        cw -= w[t];
    }
    if(cw+rest>=l)
        dfs(t + 1, n, l, r, w);
    rest += w[t];
}



int main()
{
    int n, l, r;
    cin >> n >> l >> r;
    vector<int> w(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> w[i];
        rest += w[i];
    }

    dfs(1, n, l, r, w);

    cout << s << endl;

    return 0;
}