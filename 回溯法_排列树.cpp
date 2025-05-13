#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

vector<int> x; // 元素集合
int n;         // 元素个数
int sum;       // 结果个数

// 无重复元素的全排列 n!种情况
void backtrack1(int t)
{
    // 到达叶子结点，产生一种排列
    if (t > n)
    {
        for (int i = 1; i <= n; i++)
        {
            cout << x[i] << " ";
        }
        cout << endl;
        sum++;
    }
    // 内部结点
    else
    {
        // 将x[t:n]依次放到x[t]的位置上，再对剩余元素进行排列
        for (int i = t; i <= n; i++)
        {
            swap(x[t], x[i]);
            backtrack1(t + 1);
            swap(x[i], x[t]);
        }
    }
}

// 无重复元素的全排列 n!种情况 输出按字典序排序 引入visited数组标记是否已使用
void backtrack1(int t, vector<bool> &visited)
{
    static vector<int> des(x);
    // 到达叶子结点，产生一种排列
    if (t > n)
    {
        for (int i = 1; i <= n; i++)
        {
            cout << x[i] << " ";
        }
        cout << endl;
        sum++;
    }
    // 内部结点
    else
    {
        for (int i = 1; i <= n; i++)
        {
            if (!visited[i])
            {
                visited[i] = true;
                x[t] = des[i];
                backtrack1(t + 1, visited);
                visited[i] = false;
            }
        }
    }
}

// 含重复元素全排列  n!/n1!n2!...种情况
void backtrack2(int t)
{
    if (t > n)
    {
        for (int i = 1; i <= n; i++)
        {
            cout << x[i] << " ";
        }
        cout << endl;
        sum++;
    }
    else
    {
        for (int i = t; i <= n; i++)
        {
            bool isalone = true;
            // 检查x[i]与x[t]-x[i-1]是否存在重复
            for (int j = t; j <= i - 1; j++)
            {
                if (x[i] == x[j])
                {
                    isalone = false;
                    break;
                }
            }
            // 若有重复，直接跳过
            if (isalone)
            {
                swap(x[i], x[t]);
                backtrack2(t + 1);
                swap(x[i], x[t]);
            }
        }
    }
}

void backtrack3(int t)
{
    if (t == n) // 到n-1时就已经结束！
    {
        for (int i = 1; i <= n; i++)
        {
            cout << x[i] << " ";
        }
        cout << endl;
        sum++;
    }
    else
    {
        // 直接取到n-1即可，因为尾元素已经排好
        for (int i = t; i <= n - 1; i++)
        {
            swap(x[i], x[t]);
            backtrack3(t + 1);
            swap(x[i], x[t]);
        }
    }
}

// 允许镜像排列
void test1()
{
    cin >> n;
    x.resize(n + 1, 0);
    vector<bool> visited(n + 1, false);
    sum = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i];
    }
    sort(x.begin(), x.end());
    backtrack1(1);
    // backtrack2(1);
    cout << sum << endl;
}

void test2()
{
    cin >> n;
    x.resize(n + 1, 0);
    sum = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i];
    }
    sort(x.begin(), x.end());

    backtrack2(1);

    cout << sum << endl;
}

// 不允许镜像排列：仅需保证首元素一定大于尾元素/首元素一定小于尾元素即可
void test3()
{
    cin >> n;
    x.resize(n + 1, 0);
    sum = 0;
    for (int i = 1; i <= n; i++)
        cin >> x[i];
    sort(x.begin(), x.end());

    // 先对首尾元素排列
    // 假设首元素必须小于尾元素
    // 则首元素取i时,尾元素只能取i+1~n
    // 首元素
    for (int i = 1; i <= n - 1; i++)
    {
        swap(x[1], x[i]);
        // 尾元素
        for (int j = i + 1; j <= n; j++)
        {
            swap(x[j], x[n]);
            backtrack3(2); // 首元素已经放置，直接从第2层开始
            swap(x[j], x[n]);
        }
        swap(x[1], x[i]);
    }
    cout << sum << endl;
}

// nCk,只取k个元素，所有元素相同即视为同一排列
int k;
vector<int> path;
void backtrack_k(int t, int start)
{
    if (t > k)
    {
        for (int i = 1; i <= k; i++)
        {
            cout << path[i] << " ";
        }
        cout << endl;
        sum++;
    }
    else
    {
        for (int i = start; i <= n; i++)
        {
            path[t] = x[i];

            backtrack_k(t + 1, i + 1);
        }
    }
}

void test4()
{
    cin >> n >> k;
    x.resize(n + 1, 0);
    path.resize(k + 1, 0);
    sum = 0;
    for (int i = 1; i <= n; i++)
        cin >> x[i];
    sort(x.begin(), x.end());

    backtrack_k(1, 1);

    cout << sum << endl;
}

int main()
{
    test1();

    return 0;
}