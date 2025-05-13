#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
// 算法要求：设计一个算法求 T 的最小顶点集合 S，使 T/S 为一个 d 森林。
// 输入格式：
// 多组输入
// 第一行输入树包含的顶点个数n和路径长度d。其中，树包含的顶点我们将其从0到n-1进行编号，0为根节点。
// 接下来的n行分别对应树的第0个顶点到n-1个顶点的孩子节点的信息。
// 每一行第一个元素k表示一共包含k个孩子节点，接下来包含2*k个元素，两两配对分别表示孩子的编号id和边的权重w。
// 除过第一行之外，后面的第i行表示第i-1个节点的孩子节点个数k和对应的孩子节点编号和权重。
struct node
{
    int father;   // 父节点
    int distance; // 到父节点的路长
    int out;      // 出度(孩子节点个数)
    int maxdis;   // 从叶子结点到该节点的最大路径长度
    bool cut;     // 切除标志
};

class dTree
{
    int n, d;
    int result; // 存储结果：要删除顶点个数
    vector<node> tree;
    vector<int> stack; // 存储叶子结点（度为0）

public:
    dTree(int n, int d)
    {
        // 此处为构造函数，初始化构建树。
        result = 0;
        tree.resize(n);
        this->n = n;
        this->d = d;

        // 父节点赋值
        tree[0].father = -1;
        tree[0].distance = 0;

        // 其余节点赋值
        for (int i = 0; i < n; i++)
        {

            cin >> tree[i].out; // 孩子节点个数（出度）
            tree[i].cut = 0;
            tree[i].maxdis = 0;

            for (int j = 0; j < tree[i].out; j++)
            {
                int id, weight;
                cin >> id >> weight;
                tree[id].father = i;
                tree[id].distance = weight;
            }
        }
    }
    void solution()
    {
        // main函数通过调用dTree类的solution函数，通过cout输出结果。
        // 将叶子结点（出度为0节点）入栈
        for (int i = n - 1; i >= 0; i--)
        {
            if (tree[i].out == 0)
                stack.push_back(i);
        }
        while (!stack.empty())
        {
            int cur = stack.back();
            stack.pop_back();

            // 叶子节点父亲及到父节点路径长
            int parent = tree[cur].father;
            int len = tree[cur].distance;

            // 父节点未被删除 | 未到达根节点
            if (!tree[parent].cut && parent != -1)
            {
                // 到父节点距离超限，删除父节点
                if (tree[cur].maxdis + len > d)
                {
                    tree[parent].cut = 1;
                    result++;

                    // 删除父节点后“父节点的父节点”变成新的父节点且其孩子个数减一
                    parent = tree[parent].father;
                    tree[parent].out--;

                    // 父节点的父节点变成叶子结点，入栈
                    if (tree[parent].out == 0)
                        stack.push_back(parent);
                }
                // 未超限，更新最大路长
                else
                {
                    tree[parent].maxdis = max(tree[parent].maxdis, tree[cur].maxdis + len);
                    // 父节点出度-1
                    tree[parent].out--;
                    // 变成新的叶子结点，入栈
                    if (tree[parent].out == 0)
                        stack.push_back(parent);
                }
            }
        }
        cout << result << endl;
    }
};

// 你的代码只需要补全上方dTree类来实现算法

// 类所需要的其他变量、函数可自己定义编写

// 只需要提交这几行代码，其他的都是后台系统自动完成的，类似于 LeetCode，下面为main函数的代码

int main()
{
    int n, d; // n为顶点个数，d为路径长度
    cin >> n >> d;
    dTree dt(n, d); // 构建与初始化树
    dt.solution();  // 通过solution函数输出结果
    return 0;
}