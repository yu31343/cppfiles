#include <iostream>
using namespace std;
#include <queue>
#include <vector>

// 活结点类
class QNode
{
public:
    QNode *parent;  // 父节点指针
    bool leftchild; // 左孩子标志
    int weight;     // 结点相应载重量

    QNode(QNode *parent, bool leftchild, int weight)
    {
        this->parent = parent;
        this->leftchild = leftchild;
        this->weight = weight;
    }
};

int n, c, r;
vector<int> w;
int bestw;          // 当前最优载重量
vector<int> bestx;  // 当前最优解（0-1序列）
queue<QNode *> que; // 活结点队列
QNode *beste;       // 当前最优扩展结点

// 入队算法
void enQueue(int wt, int i, QNode *parent, bool leftchild)
{
    // 叶子结点
    if (i == n)
    {
        // 最优解结点
        if (wt == bestw)
        {
            beste = parent;
            bestx[n] = leftchild;
        }
        return;
    }

    // 非叶子结点
    QNode *b = new QNode(parent, leftchild, wt);    //注意要加new将结点开辟在堆区，否则会被释放造成非法访问
    que.push(b);
}

void maxLoading()
{
    // 初始化
    bestw = 0;
    r = 0;
    for (int i = 2; i <= n; i++)
        r += w[i];

    que.push(nullptr); // 同层结点尾部标志

    QNode *e = nullptr; // 父节点
    beste = nullptr;

    int i = 1;
    int ew = 0;

    while (1)
    {
        // 检查左儿子结点
        int wt = ew + w[i];
        if (wt <= c)
        {
            if (wt > bestw)
                bestw = wt;
            enQueue(wt, i, e, 1);
        }

        // 检查右儿子结点
        // 剪枝
        if (wt + r > bestw)
        {
            enQueue(ew, i, e, 0);
        }

        // 取下一扩展结点
        e = que.front();
        que.pop();

        // 读取到分层标志
        if (e == nullptr)
        {
            // 队列已空，所有结点已处理完毕
            if (que.empty())
                break; // 先别return 后面还要构造最优解

            // 尾部放置结点尾部标志
            que.push(nullptr);

            // 取下一扩展结点
            e = que.front();
            que.pop();

            // 进入下一层
            i++;

            r -= w[i]; // 减掉物品i
        }

        // 新结点载重量
        ew = e->weight;
    }

    // 构造最优解
    // bestx[n]已赋值为正确值，且beste为叶子结点上一层结点
    // 故j从n-1开始
    for (int j = n - 1; j >= 1; j--)
    {
        bestx[j] = beste->leftchild;
        // 是父节点左孩子表选取物品j，右孩子则为不选

        beste = beste->parent; // 继续往上
    }
}

int main()
{
    cin >> n >> c;
    w.resize(n + 1, 0);
    for (int i = 1; i <= n; i++)
        cin >> w[i];

    bestx.resize(n + 1, 0);

    maxLoading();

    // 输出最优解，bestx[i]为0表不选物品i，1表示选择物品i
    for (int i = 1; i <= n; i++)
        cout << bestx[i] << " ";
    cout << endl;

    // 最大载重量
    cout << bestw << endl;
    return 0;
}