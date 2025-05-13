#include <iostream>
using namespace std;
#include <vector>
#include <queue>

int n;          // 物品个数
int c;          // 第一艘船载重量
vector<int> w;  // 物品重量
int bestw;      // 当前最优载重量
queue<int> que; // 活结点队列

// 入队函数-未剪枝版本使用
// void enQueue(int wt, int i)
// {
//     // 检查当前结点是否为叶子结点
//     // 叶子结点wt就是一个解，无需入队
//     if (i == n)
//     {
//         if (wt > bestw)
//             bestw = wt;
//     }
//     // 非叶子结点直接入队
//     else
//         que.push(wt);
// }

// 未剪枝版本
//  void maxLoading()
//  {
//      // 初始化
//      bestw = 0;
//      que.push(-1); // 同层结点尾部标志

//     int i = 1;  // 当前扩展结点所在层
//     int ew = 0; // 当前扩展结点相应载重量

//     // 搜索
//     while (1)
//     {
//         // 检查左儿子结点
//         if (ew + w[i] <= c)
//             enQueue(ew + w[i], i); // 入队

//         // 右儿子结点一定可行
//         enQueue(ew, i); // 直接入队

//         // 取下一扩展结点
//         ew = que.front();
//         que.pop();
//         // 读取到分层标志,将进入下一层处理
//         if (ew == -1)
//         {
//             // 队列已空，所有结点已处理完毕
//             if (que.empty())
//                 return;     //bestw已是最优值
//             // 尾部放置结点尾部标志
//             que.push(-1);
//             // 取下一扩展结点
//             ew = que.front();
//             que.pop();
//             i++; // 进入下一层
//         }
//     }
// }

// 剪枝版本
int r; // 剩余物品重量

void maxLoading()
{
    // 初始化
    bestw = 0;
    r = 0;
    for (int i = 2; i <= n; i++) // 注意：从2开始，第一个物品已无需考虑
        r += w[i];
    que.push(-1); // 同层结点尾部标志

    int i = 1;  // 当前扩展结点所在层
    int ew = 0; // 当前扩展结点相应载重量

    // 搜索
    while (1)
    {
        // 检查左儿子结点
        int wt = ew + w[i];
        if (wt <= c)
        {
            // 提前更新bestw，方便右子树剪枝
            if (wt > bestw)
                bestw = wt;
            // 非叶子结点入队
            if (i < n)
                que.push(wt); // 入队
        }

        // 检查右儿子结点
        //剪枝  非叶子结点才考虑入队
        if(ew+r>bestw&&i<n)
        {
            que.push(ew);   //入队；
        }

        // 取下一扩展结点
        ew = que.front();
        que.pop();

        // 读取到分层标志,将进入下一层处理
        if (ew == -1)
        {
            // 队列已空，所有结点已处理完毕
            if (que.empty())
                return; // bestw已是最优值
            // 尾部放置结点尾部标志
            que.push(-1);
            // 取下一扩展结点
            ew = que.front();
            que.pop();
            i++; // 进入下一层
            r -= w[i];  //减掉物品i
        }
    }
}

int main()
{
    cin >> n >> c;
    w.resize(n + 1, 0);
    for (int i = 1; i <= n; i++)
        cin >> w[i];

    maxLoading();

    cout << bestw << endl;

    return 0;
}