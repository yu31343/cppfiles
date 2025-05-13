#include <iostream>
using namespace std;
#include <vector>
#include <map>
int n;         // 物品个数
int c;         // 背包容量
vector<int> w; // 物品重量
vector<int> v; // 物品价值
int cw;        // 当前已装重量
int cp;        // 当前已装价值
int bestp;     // 当前最优价值
int r=0;         // 当前剩余物品价值总和

void sort_by_pp()
{
    multimap<float, int, greater<>> q;
    // 单位重量价值数组
    for (int i = 1; i <= n; i++)
    {
        q.insert(make_pair(v[i] * 1.00 / w[i], i));
    }
    vector<int> ww(w);
    vector<int> vv(v);
    multimap<float, int, greater<>>::iterator it = q.begin();
    for (int i = 1; i <= n; i++)
    {

        w[i] = ww[(it)->second];
        v[i] = vv[(it)->second];
        it++;
    }
}

// 利用贪心算法求装入第i个物品到最后一个物品所能取得价值的上界
float bound(int i)
{
    int bound = cp;
    int cleft = c - cw;
    while (i <= n && w[i] <= cleft)
    {
        bound += v[i];
        cleft -= w[i];
        i++;
    }

    // 背包未满，部分装入物品
    if (i <= n)
    {
        bound += v[i] * 1.0 / w[i] * cleft;
    }
    return bound;
}

//照搬装载问题剪枝思路
void backtrack1(int i)
{
    if (i > n)
    {
        bestp = cp;
        return;
    }

    r -= w[i];
    if(cw+w[i]<=c)
    {
        cw += w[i];
        cp += v[i];
        backtrack1(i + 1);
        cw -= w[i];
        cp -= v[i];
    }
    //利用装载问题剪枝条件判断
    //假设剩余物品全装是否更优，若否裁去右子树
    if(cw+r>bestp)
    {
        backtrack1(i + 1);
    }
    r += w[i];
}

void backtrack(int i)
{
    // 到达叶节点
    if (i > n)
    {
        bestp = cp;
        return;
    }

    // 搜索子树

    // 能否进入左子树
    if (cw + w[i] <= c)
    {
        cw += w[i];

        //cout << 1 << " ";

        cp += v[i];
        backtrack(i + 1);

        cw -= w[i];
        cp -= v[i];
    }
    // 能否进入右子树
    // 利用贪心算法求出剩余物品可取得价值的上界bound
    if (bound(i + 1) > bestp)
    {
        backtrack(i + 1);
        //cout << 2 << " ";
    }
}

void knapsack()
{
    // 将物品按单位重量价值排序
    sort_by_pp();
    backtrack(1);
}

int main()
{
    cin >> n >> c;
    cw = 0;
    cp = 0;
    bestp = 0;
    w.resize(n + 1, 0);
    v.resize(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        cin >> w[i] >> v[i];
        r += w[i];
    }
    sort_by_pp();

    knapsack();
    cout << bestp << endl;
}