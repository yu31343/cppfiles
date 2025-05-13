#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
typedef vector<vector<int>> vector2;
// 给定1个1000行×20列的0-1矩阵，对于该矩阵的任意1列，其中值为1的元素的数量不超过10%。设有两个非空集合A和B，每个集合由矩阵的若干列组成。集合A和B互斥是指对于矩阵的任意一行，同时满足下列2个条件：1）若A中有一个或多个元素在这一行上的值是1，则B中的元素在这一行全部是0；2）若B中有一个或多个元素在这一行上的值是1，则A中的元素在这一行全部是0。请你设计一个算法，找出一对互斥集合A和B，使得A和B包含的列的总数最大。

// 请你设计一个算法，找出一对互斥集合 A 和 B，使得 A和 B 包含的列的总数最大

// 输入格式：
// 一个 1000 行 20 列的矩阵 matrix 作为测试用例，每行输入 20 列的元素，对矩阵找出满足题意的互斥集合。

// 输出格式：
// 输出两行，使得 A 的元素+B 的元素个数最大
// 第一行输出 A 集合中的所有元素（下标从 0 开始），以空格分开
// 第二行输出 B 集合中的所有元素，格式同上
// 如果，没有找到非空集合 A 和 B，则输出两行空行

// 实验请提交完整代码，代码需要包含主函数，相应的输出输出通过cin和cout完成
// 本实验一共20个测试用例，你的代码只针对一个测试用例矩阵，不需要使用for循环20个测试用例一起输出结果。
// 为保证输出唯一, 每个集合的输出按照升序排列, 如果存在并列的情况, 则采用以下策略：

// A和B元素列数差的绝对值最小;
// A的首元素最小
// A的列数要大于B的列数;

int n = 20;                             // 列数
vector2 a(1001, vector<int>(n + 1, 0)); // 0-1矩阵

vector<int> x, y;   // 存储A，B中列的下标(从1开始)
vector<int> bestx, besty;      // 当前最优A、B集合

int s;                     // A、B当前元素个数和
int bests;                 // A、B当前最大元素个数和

vector2 rows_with_ones(n + 1);     // 每列中值为1的行号
vector2 judge(n + 1, vector<int>(n + 1, 1)); // judge[i][j]=0表第i、j列互斥

// 判断两列是否互斥
bool is_c_fit(int i, int j)
{
    for (int row : rows_with_ones[i])
    {
        if (find(rows_with_ones[j].begin(), rows_with_ones[j].end(), row) != rows_with_ones[j].end())
            return false;
    }
    return true;
}

// 判断新加入列t是否产生互斥  toA表示新加入列是否在A集合中
bool isfit(int t, bool toA)
{
    if (toA)
    {
        for (int j : y)
        {
            if (!judge[t][j])
                return false;
        }
        return true;
    }
    // 第t列在B中
    else
    {
        for (int j : x)
        {
            if (!judge[t][j])
                return false;
        }
        return true;
    }
}

void backtrack(int t)
{
    if (t > n)
    {
        //A、B不能为空且 A的列数要大于B的列数;
        if (x.empty() || y.empty() || x.size() < y.size())
            return;
        s = (int)x.size() + (int)y.size();
        bool update = 0;




        if (s > bests)
            update = 1;
        else if (s == bests)
        {
            int diffc = (int)x.size() - (int)y.size() - ((int)bestx.size() - (int)besty.size());
            // A和B元素列数差的绝对值最小
            if (diffc < 0)
                update = 1;
            else if (diffc == 0)
            {
                // A的首元素最小
                if (x.front() < bestx.front())
                    update = 1;
            }
        }

        // 如果需要更新最优解
        if (update)
        {
            bests = s;
            bestx = x;
            besty = y;
        }

        return;
    }

    // 第t列给集合A
    x.push_back(t);
    if (isfit(t, 1))
    {
        backtrack(t + 1);
    }
    x.pop_back();

    // 第t列给集合B
    y.push_back(t);
    if (isfit(t, 0))
    {
        backtrack(t + 1);
    }
    y.pop_back();

    // 不选择第t列
    if ((int)x.size() + (int)y.size() + n - t >= bests)
        backtrack(t + 1);
}

int main()
{
    bests = 0;
    for (int i = 1; i <= 1000; i++)
    {
        for (int j = 1; j <= 20; j++)
            cin >> a[i][j];
    }

    // 预处理
    for (int j = 1; j <= 20; j++)
    {
        int count = 0;
        for (int i = 1; i <= 1000; i++)
        {
            if (count > 1000 * 0.1) // 1不超过10%
                break;
            if (a[i][j])
            {
                rows_with_ones[j].push_back(i);
                count++;
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            judge[i][j] = judge[j][i] = (int)is_c_fit(i, j);
        }
    }

    backtrack(1);

    for (int i : bestx)
        cout << i - 1 << " ";
    cout << endl;

    for (int i : besty)
        cout << i - 1 << " ";
    cout << endl;

    return 0;
}
