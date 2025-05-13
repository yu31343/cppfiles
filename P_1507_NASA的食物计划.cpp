#include <iostream>
using namespace std;
#include <vector>
typedef vector<vector<vector<int>>> vector3;
// 题目描述
// 航天飞机的体积有限，当然如果载过重的物品，燃料会浪费很多钱，每件食品都有各自的体积、质量以及所含卡路里。在告诉你体积和质量的最大值的情况下，请输出能达到的食品方案//所含卡路里的最大值，当然每个食品只能使用一次。

// 输入格式
// 第一行 2 个整数，分别代表体积最大值 h 和质量最大值 t。

// 第二行 1 个整数代表食品总数 n。

// 接下来 n 行每行 3 个数 体积 h[i]，质量 t[i]，所含卡路里 k[i]

// 输出格式
// 一个数，表示所能达到的最大卡路里（int 范围内)


//双限制 0-1背包
void knapsack(int H, int T, vector<int> &h, vector<int> &t, vector<int> &ka, vector3 &v)
{
    int n = h.size() - 1;
    for (int i = 1; i <= n; i++)
    {
        //体积
        for (int j = 1; j <= H; j++)
        {
            //质量
            for (int k = 1; k <= T;k++)
            {
                //放不了
                if(t[i]>k||h[i]>j)
                    v[i][j][k] = v[i - 1][j][k];
                //能放，选放与不放之中价值最大者
                else
                {
                    v[i][j][k] = max(v[i - 1][j][k], v[i - 1][j - h[i]][k - t[i]]+ka[i]);
                }
            }
        }
    }
}

int main()
{
    int H, T; // 体积最大值，质量最大值
    cin >> H >> T;
    int n; // 物品总数
    cin >> n;
    vector<int> h, t, k;
    h.resize(n + 1);
    t.resize(n + 1);
    k.resize(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> h[i] >> t[i] >> k[i];
    }

    vector3 v(n + 1, vector<vector<int>>(H + 1, vector<int>(T + 1, 0)));
    knapsack(H, T, h, t, k, v);
    cout << v[n][H][T] << endl;
    return 0;
}