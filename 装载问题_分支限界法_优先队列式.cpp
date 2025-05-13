#include <iostream>
using namespace std;
#include <vector>
#include <queue>

// 扩展结点类
class Node
{
public:
    int uweight; // 活结点优先级（上界）
    int i;       // 结点所在层序号

    Node *parent;   // 父节点指针
    bool leftchild; // 是否为父节点的左孩子结点

    Node(int uweight, int i, Node *parent, bool leftchild)
    {
        this->uweight = uweight;
        this->i = i;
        this->parent = parent;
        this->leftchild = leftchild;
    }
};

// 结点比较仿函数
class Compare
{
public:
    bool operator()(Node *a, Node *b) const
    {
        // 优先级比较
        return a->uweight < b->uweight;
    }
};

int n, c;
vector<int> w;
vector<int> r;                  // 剩余重量 数组
priority_queue<Node *,vector<Node*>, Compare> heap; // 优先队列（堆）
vector<int> bestx;              // 最优解0-1序列

// 入队函数(叶子结点也要入队，不需要判断)
void addNode(int uweight, int i, Node *parent, bool leftchild)
{
    Node *node = new Node(uweight, i, parent, leftchild);
    heap.push(node);
}

int maxLoading()
{
    // 初始化 i、e、ew
    int i = 1;
    Node *e = nullptr; // 当前扩展节点
    int ew = 0;

    r.resize(n + 1, 0);
    for (int j = n - 1; j >= 1; j--)
        r[j] = r[j + 1] + w[j + 1];

    // 搜索
    while (i != n + 1) // 非叶子结点时循环，遇到叶子结点
    {
        // 检查左儿子结点
        if (ew + w[i] <= c)
            addNode(ew + w[i] + r[i], i + 1, e, 1);
        // 优先级、当前结点所在层，该节点的父节点指针、是否为左儿子

        // 右儿子总是可行，无需额外判断
        addNode(ew + r[i], i + 1, e, 0);

        // 取下一扩展结点 更新i、e、ew
        Node *node = heap.top();
        heap.pop();
        i = node->i;
        e = node;
        ew = node->uweight - r[i - 1]; // 当前载重量=当前优先级-r
    }

    // 构造最优解
    for (int j = n; j >= 1; j--)
    {
        bestx[j] = e->leftchild; // 此处e为最优解叶子结点
        e = e->parent;
    }

    return ew; // 叶子结点优先级/载重量即为结果（最大载重量）
}

int main()
{
    cin >> n >> c;
    w.resize(n + 1, 0);
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    bestx.resize(n + 1, 0);

    int res = maxLoading();

    for (int i = 1; i <= n; i++)
        cout << bestx[i] << " ";
    cout << endl;
    cout << res << endl;
    return 0;
}