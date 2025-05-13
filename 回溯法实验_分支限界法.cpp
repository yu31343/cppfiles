#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <queue>
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
class Node
{
public:
    int us; //  优先级
    int cs; // 当前结点A+B
    int i;
    vector<int> x, y;

    Node(int us, int cs, int i, vector<int> x, vector<int> y)
    {
        this->us = us;
        this->cs = cs;
        this->i = i;
        this->x = x;
        this->y = y;
    }
};

class Compare
{
public:
    bool operator()(Node *a, Node *b)
    {

        vector<int> &xa = a->x;
        vector<int> &ya = a->y;
        vector<int> &xb = b->x;
        vector<int> &yb = b->y;
        if (a->us < b->us)
            return 1;
        if (a->us == b->us)
        {
            int diffc = ((int)xa.size() - (int)ya.size()) - ((int)xb.size() - (int)yb.size());
            if (diffc > 0)
                return 1;
            else if (diffc == 0)
            {
                if (!xa.empty() && !xb.empty())
                    if (xa.front() > xb.front())
                        return 1;
            }
        }
        return 0;
    }
};

int n = 20; // 列数
vector2 a(1001, vector<int>(n + 1, 0));

// vector<int> x, y; // 存储A，B中列的下标(从1开始)
vector<int> bestx, besty;
int bests;                                   // A、B当前最大元素个数和
vector2 rows_with_ones(n + 1);               // 每列中值为1的行号
vector2 judge(n + 1, vector<int>(n + 1, 1)); // judge[i][j]=0表第i、j列互斥
priority_queue<Node *, vector<Node *>, Compare> heap;

void addNode(int us, int cs, int i, vector<int> x, vector<int> y)
{
    Node *node = new Node(us, cs, i, x, y);
    heap.push(node);
}

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

// 判断新加入列是否产生互斥  toA表示新加入列是否在A集合中
bool isfit(int t, bool toA, vector<int> &x, vector<int> &y)
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

void solution()
{
    int i = 1;
    int us = 20;
    bests = 0;
    int cs = 0;
    vector<int> x, y;

    while (1)
    {

        // 第i列给A
        if (isfit(i, 1, x, y))
        {
            vector<int> xx = x;
            xx.push_back(i);
            if (cs + 1 > bests)
                bests = cs + 1;
            addNode(us, cs + 1, i + 1, xx, y);
        }

        // 第i列给B
        if (isfit(i, 0, x, y))
        {
            vector<int> yy = y;
            yy.push_back(i);
            if (cs + 1 > bests)
                bests = cs + 1;
            addNode(us, cs + 1, i + 1, x, yy);
        }

        // 不选第i列
        if (us - 1 >= bests)
        {
            addNode(us - 1, cs, i + 1, x, y);
        }

        // 取下一扩展结点

        Node *node = heap.top();
        heap.pop();
        i = node->i;
        us = node->us;
        cs = node->cs;
        x = node->x;
        y = node->y;

        if (i == n + 1)
        {
            if(!x.empty()&&!y.empty()&&x.size()>y.size())
            {
                bestx = x;
                besty = y;
                break;
            }
            i--;
        }
    }
}

int main()
{
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

    solution();

    for (int i : bestx)
        cout << i - 1 << " ";
    cout << endl;

    for (int i : besty)
        cout << i - 1 << " ";
    cout << endl;

    return 0;
}