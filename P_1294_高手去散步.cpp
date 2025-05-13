#include <iostream>
using namespace std;
#include <vector>
#include <climits>

// 鳌头山上有 n 个观景点，观景点两两之间有游步道共 m 条。那些没有路的观景点高手是不会选择去的。另外，也不喜欢去同一个观景点一次以上。而高手想让走的路程最长，已知高手的穿梭机可以让他们在任意一个观景点出发，也在任意一个观景点结束。

// 输入格式
// 第一行，两个用空格隔开的整数 n 、 m. 之后 m 行，为每条游步道的信息：两端观景点编号、长度。

// 输出格式
// 一个整数，表示他走的最长路程。

int n, m;
vector<vector<int>> a;

int bests = 0;
vector<bool> visited;   //标记顶点是否被访问过

//深搜  u:当前顶点 len:当前总路长
void dfs(int u, int len, vector<bool> &visited)
{
    bests = max(len, bests);

    //遍历可以与u连接且未被访问过的顶点v
    for (int v = 1; v <= n; v++)
    {
        if (!visited[v] && a[u][v] != INT_MAX)
        {
            visited[v] = true;
            //当前顶点变为v，路长更新
            dfs(v, len + a[u][v], visited);
            visited[v] = false;
        }
    }
}

int main()
{
    cin >> n >> m;
    a.resize(n + 1, vector<int>(n + 1, INT_MAX));


    for (int i = 0; i < m; i++)
    {
        int p, q, len;
        cin >> p >> q >> len;
        a[p][q] = a[q][p] = len;
    }

    //任意选择起点
    for (int i = 1; i <= n; i++)
    {
        visited.assign(n + 1, false);   //访问标记数组重新初始化
        visited[i] = true;              //第一个顶点标记为已访问
        dfs(i, 0, visited);             //第一层搜索
    }

    cout << bests << endl;

    return 0;
}