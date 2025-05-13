#include <iostream>
using namespace std;
#include <vector>

int n, c1, c2; // 货物数，两艘船载重量
vector<int> w; // 每个货物重量
int cw = 0;    // 当前第一艘船载重量
int bestw = 0; // 当前第一艘船最优载重量

// 为剪枝增加变量
int r = 0; // 剩余货物重量

// 构造最优解
vector<int> x;     // 当前解，x[i]=1表示装货物i
vector<int> bestx; // 当前最优解，即满足bestw的x

//------------------------------------------------------------

// 不剪枝
//  void backtrack(int i)
//  {
//      if(i>n)
//      {
//          //到达叶节点
//          if(cw>bestw)
//              bestw = cw;
//          return;
//      }
//      //内部结点，逐层搜索
//      //搜索左子树
//      if(cw+w[i]<=c1)
//      {
//          cw += w[i];
//          backtrack(i + 1);
//          cw -= w[i]; //搜索完左子树返回上层根节点
//      }

//     //直接搜索右子树
//     backtrack(i + 1);
// }

//-------------------------------------------------------------------

// 增加上界函数剪枝
// void backtrack(int i)
// {
//     if (i > n)
//     {
//         // 到达叶节点
//         if (cw > bestw)
//             bestw = cw;
//         return;
//     }
//     // 内部结点，逐层搜索

//     // 不管是否选货物i，进入子树货物i的去向已经确定，剩余货物不再考虑i
//     r -= w[i];

//     // 搜索左子树
//     if (cw + w[i] <= c1)
//     {
//         cw += w[i];
//         backtrack(i + 1);
//         cw -= w[i]; // 搜索完左子树返回上层根节点
//     }

//     // 搜索右子树

//     // cw+r<=bestw时，即使剩余全装，也无法超过bestw
//     // 只需cw+r>bestw时，进入右子树

//     if (cw + r > bestw)
//     {
//         backtrack(i + 1);
//     }

//     r += w[i]; // 返回上层的父节点
// }

//---------------------------------------------------------------

// 增加构造最优解方法
void backtrack(int i)
{
    if (i > n)
    {
        // 到达叶节点
        if (cw > bestw)
        {
            bestw = cw;

            for (int i = 0; i <= n; i++)
                bestx[i] = x[i];
            //可直接bestx=x
        }
        return; //立即返回，防止有后续操作
    }
    // 内部结点，逐层搜索

    // 不管是否选货物i，进入子树货物i的去向已经确定，剩余货物不再考虑i
    r -= w[i];

    // 搜索左子树
    if (cw + w[i] <= c1)
    {
        x[i] = 1; // 选取
        cw += w[i];
        backtrack(i + 1);
        cw -= w[i]; // 搜索完左子树返回上层根节点
    }

    // 搜索右子树

    // cw+r<=bestw时，即使剩余全装，也无法超过bestw
    // 只需cw+r>bestw时，进入右子树

    if (cw + r > bestw)
    {
        x[i] = 0; // 不选

        backtrack(i + 1);
    }

    r += w[i]; // 返回上层的父节点
}

int main()
{
    cin >> n >> c1 >> c2;
    w.resize(n + 1);
    x.resize(n + 1);
    bestx.resize(n + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> w[i];
        r += w[i];
    }

    backtrack(1);

    cout << bestw << endl;

    for (int i = 1; i <= n; i++)
        cout << bestx[i] << " ";

    return 0;
}