#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

// 算法要求：请编写一段代码，能够在最坏情况下用 O(n)时间找出 n 个元素的带权中位数

// 函数原型：

// mysort至多对5个元素排序，时间复杂度为常数O(1)
void mysort(vector<int> &num, vector<double> &weight, int p, int r)
{
    for (int i = p; i <= r - 1; i++)
    {
        for (int j = i + 1; j <= r; j++)
        {
            if (num[i] > num[j])
            {
                swap(num[i], num[j]);
                swap(weight[i], weight[j]);
            }
        }
    }
}

// 以x为基准元素(不是索引，是元素值)，对数组划分
int partition(vector<int> &num, vector<double> &weight, int p, int r, int x)
{
    int i = p;
    int j = r + 1; // 后面先对j-1再取值，故提前+1
    int idx;
    for (idx = p; idx <= r; idx++)
    {
        if (num[idx] == x)
        {
            break;
        }
    }
    swap(num[p], num[idx]);
    swap(weight[p], weight[idx]);

    while (1)
    {
        while (num[++i] < x && i < r)
            ;
        while (num[--j] > x) // 不可能越界，到p时相等必退出
            ;
        if (i >= j)
            break; // 已经满足条件 或 交换已经结束
        swap(num[i], num[j]);
        swap(weight[i], weight[j]);
    }

    swap(num[p], num[j]);
    swap(weight[p], weight[j]);
    return j;
}

// 找出中位数的中位数作为基准元素
int selectPivot(vector<int> &num, vector<double> &weight, int p, int r)
{
    if (r - p < 5)
    {
        mysort(num, weight, p, r);
        return num[(p + r) / 2];
    }
    for (int i = 0; i <= (r - p - 4) / 5; i++)
    {
        int s = p + 5 * i;
        int t = s + 4;
        mysort(num, weight, s, t);
        swap(num[p + i], num[s + 2]);
        swap(weight[p + i], weight[s + 2]);
    }
    return selectPivot(num, weight, p, p + (r - p - 4) / 5);
}

int selectw(vector<int> &num, vector<double> &weight, int p, int r, double half)
{
    if (p == r)
        return num[p];
    int x = selectPivot(num, weight, p, r); // 利用线性时间选择选出基准x
    int q = partition(num, weight, p, r, x);

    double leftsum = 0.0;

    for (int i = p; i < q; i++)
        leftsum += weight[i];

    if (leftsum < half && leftsum + weight[q] >= half)
        return num[q];
    else if (leftsum >= half)
        return selectw(num, weight, p, q - 1, half);
    else
        return selectw(num, weight, q + 1, r, half - leftsum - weight[q]);
}

void WeightMedian(int length, vector<int> num, vector<double> weight, int index)
{
    double total = 0.0;
    for (int i = 0; i < length; i++)
        total += weight[i];
    double half = total / 2.0;
    cout << selectw(num, weight, index, length - 1, half) << endl;
}

// 你的代码只需要补全上方函数来实现算法

// 其中length为输入长度，num是包含n个互不相同元素值的向量，weight是包含元素值对应的权重的向量，index为递归调用时的索引(下标)

// 只需要提交这几行代码，其他的都是后台系统自动完成的。类似于 LeetCode
#include <map>
void WeightMedian1(int length, vector<int> num, vector<double> weight, int index)
{
    int n = length;
    map<int, double> m;
    for (int i = 0; i < n; i++)
    {
        m.insert(make_pair(num[i], weight[i]));
    }
    double sum;
    map<int, double>::iterator it = m.begin();
    for (int i = 0; i < n; i++)
    {
        sum += it->second;
        if (sum > 0.5)
        {
            cout << it->first << endl;
            break;
        }
        it++;
    }
}

int main()
{

    // 后台自动给出测试代码放在这里，无需同学编写

    // 测试代码将测试用例的三行数据分别导入length，num，和weight中

    // 调用WeightMedian(length,num, weight,index)函数，函数内部使用cout输出得到的中位数，测试代码默认index初始值为0
    int n;
    cin >> n;
    vector<int> num(n, 0);
    vector<double> weight(n, 0);
    for (int i = 0; i < n; i++)
        cin >> num[i];
    for (int i = 0; i < n; i++)
        cin >> weight[i];
    
    //线性时间选择算法
    WeightMedian(n, num, weight, 0);
    
    //非线性复杂度算法
    //WeightMedian1(n, num, weight, 0);
    return 0;
}