#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <bitset>
using namespace std;

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

typedef vector<vector<int>> vector2;
typedef bitset<1001> BitMask; // 使用位集合优化

class Node
{
public:
    int us; // 优先级
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
        if (a->us < b->us)
            return 1;
        else if (a->us > b->us)
            return 0;
        else
        {
            int diffA = abs((int)a->x.size() - (int)a->y.size());
            int diffB = abs((int)b->x.size() - (int)b->y.size());

            if (diffA != diffB)
                return diffA > diffB; // 优先选择列数差绝对值小的
            if (!a->x.empty() && !b->x.empty() && a->x[0] != b->x[0])
                return a->x[0] > b->x[0];     // 其次选择 A 的首元素小的
            return a->x.size() < b->x.size(); // 最后选择 A 的列数大的
        }
    }
};

vector2 a(1001, vector<int>(21, 0));
int n = 20; // 列数
vector<int> bestx, besty;
int bests;// A、B当前最大元素个数和
vector<BitMask> column_masks(21);     // 每列的位掩码表示
vector<vector<bool>> conflict_matrix(21, vector<bool>(21, false)); // 列冲突预计算矩阵
priority_queue<Node *, vector<Node *>, Compare> heap;

// 预计算列之间的冲突关系
void precompute_conflicts()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            // 检查列i和列j是否有冲突(有共同的1)
            if ((column_masks[i] & column_masks[j]).any())
            {
                conflict_matrix[i][j] = true;
                conflict_matrix[j][i] = true;
            }
        }
    }
}

// 互斥检查
bool is_conflict(int col1, int col2)
{
    return conflict_matrix[col1][col2];
}

// 入队函数
void addNode(int us, int cs, int i, vector<int> x, vector<int> y)
{
    Node *node = new Node(us, cs, i, x, y);
    heap.push(node);
}

// 优化的互斥性检查
bool isfit(int t, bool toA, vector<int> &x, vector<int> &y)
{
    if (toA)
    {
        for (int j : y)
        {
            if (is_conflict(t, j))
                return false;
        }
    }
    else
    {
        for (int j : x)
        {
            if (is_conflict(t, j))
                return false;
        }
    }
    return true;
}

// 计算上界
int bound(int current_cs, int current_i, vector<int> &x, vector<int> &y)
{
    int r = n - current_i + 1;

    // 简单上界：当前选择数 + 剩余列数
    int b = current_cs + r;

    return b;
}

void solution()
{
    int i = 1;
    bests = 0;
    int cs = 0;
    vector<int> x, y;


    while (i == 1 || !heap.empty())
    {
        if (i != n + 1)
        {
            // 将第i列给A
            if (y.empty() || isfit(i, true, x, y))
            {
                vector<int> xx = x;
                xx.push_back(i);
                int new_us = bound(cs + 1, i + 1, xx, y);
                if (new_us > bests)
                {
                    // 只有上界大于当前最优解才加入队列
                    addNode(new_us, cs + 1, i + 1, xx, y);
                }
            }

            // 将第i列给B
            if (x.empty() || isfit(i, false, x, y))
            {
                vector<int> yy = y;
                yy.push_back(i);
                int new_us = bound(cs + 1, i + 1, x, yy);
                if (new_us > bests)
                {
                    addNode(new_us, cs + 1, i + 1, x, yy);
                }
            }

            // 不选第i列
            int new_us = bound(cs, i + 1, x, y);
            if (new_us > bests)
            {
                addNode(new_us, cs, i + 1, x, y);
            }
        }
        else
        {
            // 找到完整解，检查是否更新最优解
            if (cs > bests && !x.empty() && !y.empty())
            {
                bests = cs;
                bestx = x;
                besty = y;
            }
        }

        // 取下一扩展结点
        if (!heap.empty())
        {
            Node *node = heap.top();
            heap.pop();
            i = node->i;
            cs = node->cs;
            x = node->x;
            y = node->y;
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

    // 预处理 - 构建位掩码表示
    for (int j = 1; j <= 20; j++)
    {
        column_masks[j].reset(); // 初始化全为0
        int count = 0;
        for (int i = 1; i <= 1000; i++)
        {
            if (count > 1000 * 0.1) // 1不超过10%
                break;
            if (a[i][j])
            {
                column_masks[j].set(i); // 设置对应位为1
                count++;
            }
        }
    }

    // 预计算冲突矩阵
    precompute_conflicts();

    solution();

    for (int i : bestx)
        cout << i - 1 << " ";
    cout << endl;

    for (int i : besty)
        cout << i - 1 << " ";
    cout << endl;

    return 0;
}