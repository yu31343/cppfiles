#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// 哈夫曼树节点
struct Node
{
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f)
        : ch(c), freq(f), left(nullptr), right(nullptr) {}
    Node(int f, Node *l, Node *r)
        : ch('\0'), freq(f), left(l), right(r) {}
};

// 比较器：最小堆
class Compare
{
public:
    bool operator()(Node *a, Node *b)
    {
        return a->freq > b->freq;
    }
};

// 递归生成哈夫曼编码
void generateCodes(Node *root, const string &code, unordered_map<char, string> &huffmanCode)
{
    if (!root)
        return;
    if (!root->left && !root->right && root->ch != '\0')
    {
        huffmanCode[root->ch] = code;
    }
    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

int main()
{
    int n;
    cout << "请输入字符个数: ";
    cin >> n;
    vector<pair<char, int>> input(n);
    cout << "请输入字符和权值（如 a 5）:" << endl;
    for (int i = 0; i < n; ++i)
    {
        cin >> input[i].first >> input[i].second;
    }

    // 构建最小堆
    priority_queue<Node *, vector<Node *>, Compare> minHeap;
    for (auto &p : input)
    {
        minHeap.push(new Node(p.first, p.second));
    }

    // 构建哈夫曼树
    while (minHeap.size() > 1)
    {
        Node *left = minHeap.top();
        minHeap.pop();
        Node *right = minHeap.top();
        minHeap.pop();
        Node *parent = new Node(left->freq + right->freq, left, right);
        minHeap.push(parent);
    }
    Node *root = minHeap.top();

    // 生成哈夫曼编码
    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    // 输出编码
    cout << "每个字符的哈夫曼编码为：" << endl;
    for (auto &p : input)
    {
        cout << p.first << ": " << huffmanCode[p.first] << endl;
    }

    system("pause");
    return 0;
}