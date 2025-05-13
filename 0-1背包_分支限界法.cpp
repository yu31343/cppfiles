//剪枝效果不如回溯法  ？？？时间复杂度比较高  为什么？

#include <iostream>
using namespace std;
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <functional>

class Node
{
public:
    double uprofit; // 优先级（最大价值上界）
    double weight;  // 结点相应重量
    double profit;  // 结点相应价值
    int i;          // 所在层序号
    Node *parent;   // 父节点指针
    bool leftchild; // 是否为左孩子结点

    Node(double uprofit, double profit, double weight, int i, Node *parent, bool leftchild)
    {
        this->uprofit = uprofit;
        this->profit = profit;
        this->weight = weight;
        this->i = i;
        this->parent = parent;
        this->leftchild = leftchild;
    }
};

// priority_queue 的 比较函数 的作用是 判断元素的优先级顺序：
// 当比较函数 Compare(a, b) 返回 true 时，表示 a 的优先级低于 b，b 应该排在 a 前面。
// 当返回 false 时，表示 a 的优先级不低于 b，a 可以保持在当前位置。
class Compare
{ 
public:
    bool operator()(Node *a, Node *b)
    {
        return a->uprofit < b->uprofit; // 注意大顶堆是<号！！！
    }
};

int n;                              // 物品总数
double c;                           // 背包容量
double cw;                          // 当前已装物品重量
double cp;                          // 当前已装物品价值
vector<double> w;                   // 物品重量
vector<double> p;                   // 物品价值
multimap<double, int, greater<>> q; // 单位重量价值数组

priority_queue<Node *, vector<Node *>, Compare> heap; // 优先队列
vector<int> bestx;                                    // 最优解数组

// 按单位重量价值大小排序
void sort_by_pp()
{

    for (int i = 1; i <= n; i++)
        q.insert(make_pair(p[i] / w[i], i));
    vector<double> ww(w);
    vector<double> pp(p);
    multimap<double, int, greater<>>::iterator it = q.begin();
    for (int i = 1; i <= n; i++)
    {
        w[i] = ww[it->second];
        p[i] = pp[it->second];
        it++;
    }
}

// 上界函数（即计算优先级函数）
// 计算从剩下i-n个物品从所能获得最大价值的上界
double bound(int i)
{
    double cleft = c - cw; // 背包剩余容量
    double b = cp;         // 价值上界

    while (i <= n && w[i] <= cleft)
    {
        cleft -= w[i];
        b += p[i];
        i++;
    }

    if (i <= n)
        b += p[i] / w[i] * cleft;
    return b;
}

// 入队函数
void addNode(double uprofit, double profit, double weight, int i, Node *parent, bool leftchild)
{
    Node *node = new Node(uprofit, profit, weight, i, parent, leftchild);
    heap.push(node);
}

double knapsack()
{
    sort_by_pp();
    cw = 0;
    cp = 0;
    Node *e = nullptr; // 父节点
    int i = 1;
    double bestp = 0.0;        // 当前最优价值
    double uprofit = bound(1); // 当前价值上界

    while (i != n + 1) // 非叶子结点
    {
        // 检查左孩子
        double wt = cw + w[i];
        if (wt <= c)
        {
            double pt = cp + p[i];
            if (pt > bestp)
                bestp = pt;
            addNode(uprofit, pt, wt, i + 1, e, 1);
            //cout << 1 << " ";
            // 左孩子的优先级继承其父节点
        }

        // 检查右孩子
        // 优先级重新计算
        uprofit = bound(i + 1); // bound函数会带来非常高的时间复杂度 ？？？
        if (uprofit >= bestp)
        {
            addNode(uprofit, cp, cw, i + 1, e, 0);
            //cout << 2 << " ";
        }
        // 取下一扩展结点
        Node *node = heap.top();
        heap.pop();
        // 更新结点相关量
        e = node;
        cw = node->weight;
        cp = node->profit;
        uprofit = node->uprofit;
        i = node->i;
    }

    // 构造最优解
    // 注意w[],p[]顺序已被打乱，需要q[]来还原
    multimap<double, int, greater<>>::iterator it = --q.end();
    for (int j = n; j >= 1; j--)
    {
        bestx[(it--)->second] = e->leftchild;
        e = e->parent;
    }

    return bestp;
}

int main()
{
    cin >> n >> c;
    w.resize(n + 1, 0);
    p.resize(n + 1, 0);
    bestx.resize(n + 1, 0);
    for (int i = 1; i <= n; i++)
        cin >> w[i] >> p[i];

    double res = knapsack();

    // for (int i = 1; i <= n; i++)
    //     cout << bestx[i] << " ";
    // cout << endl;

    cout << res << endl;

    return 0;
}