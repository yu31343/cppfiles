#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m, T;


class Node
{
public:
    int value; // 价值
    int x;
    int y; // 坐标
    Node(int value, int x, int y)
    {
        this->value = value;
        this->x = x;
        this->y = y;
    }
};

class Compare
{
public:
    bool operator()(Node *a, Node *b)
    {
        return a->value < b->value;
    }
};

// 大顶堆
priority_queue<Node *, vector<Node *>, Compare> heap;


int solution()
{
   
    int valuesum = 0;   //最大价值
    int step = 0;   //已走步数
    int x, y, new_x, new_y; //上一步位置、这一步位置

    x = 0;
    y = (heap.top()->y);

    int curvalue=0;     //当前位置价值

    while (!heap.empty())
    {
        Node node = *heap.top();
        heap.pop();
        new_x = node.x;
        new_y = node.y;
        curvalue = node.value;
        
        step = step + abs(new_x - x) + abs(new_y - y) +1;

        if(step+new_x>T)
        {
            break;
        }
        
        valuesum += curvalue;

        x = new_x;
        y = new_y;

    }

    return valuesum;
}


int main()
{
    cin >> m >> n >> T;     //m X n 矩阵,最大步数T
    int val;

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> val;
            if(val!=0)
            {
                Node *node = new Node(val, i, j);
                heap.push(node);
            }
        }
    }

    cout << solution() << endl;


    // while(!heap.empty())
    // {
    //     Node node = *heap.top();
    //     heap.pop();
    //     cout << node.value << " " << node.x << " " << node.y << endl;
    // }
    // return 0;
}


