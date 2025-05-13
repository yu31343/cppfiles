#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
// 线性时间选择：在给定数组a[0:n-1]中寻找第k小的元素

// 划分算法:以a[p]为基准对a[p:r]进行划分
// 比a[p]小的元素在前，大的在后
// 返回划分后a[p]的放置位置标号j
vector<int> a;

int partition(int p, int r, int x)
{
    int i = p;
    int j = r + 1; // 后面先对j-1再取值，故提前+1
    int idx;
    //找到x的下标
    for (idx = p; idx <= r; idx++)
        if (a[idx] == x)
        {
            swap(a[p], a[idx]);
            break;
        }

    // 将<x的元素放到左边
    //>x的元素放到右边
    while (1)
    {
        while (a[++i] < x && i < r)    //等号可取可不取
            ;
        while (a[--j] > x) // 不可能越界，到p时相等必退出（前提：此处不能取等号）
            ;
        if (i >= j)
            break; // 已经满足条件 或 交换已经结束
        swap(a[i], a[j]);
    }
    a[p] = a[j];
    a[j] = x; // 将x放置于j处
    return j;
}

// 线性时间选择  p-r选择范围 第k小
// 每5个元素划为一组，记满5个元素的组合数为i（0-i）
// 则i=(r-p-4)/5     （向下取整）
int select(int p, int r, int k)
{
    // 仅剩一个组合
    if (r - p < 5)
    {
        // 直接用某个简单排序算法对a[p:r]排序
        sort(a.begin() + p, a.begin() + r + 1); // 注意sort函数对左闭右开区间进行排序
        return a[p + k - 1];
    }

    // 将a[p+5i]至a[p+5i+4]的第三小元素与a[p+i]交换位置
    // 即将第i组的中位数与第0组的第i个数交换位置
    // 当前算法未考虑剩余不满5个的最后一组元素
    for (int i = 0; i <= (r - p - 4) / 5; i++)
    {
        int s = p + 5 * i; // 组左边界
        int t = s + 4;     // 组右边界
        // 对该组排序，找出中位数a[s+2]
        sort(a.begin() + s, a.begin() + t + 1);
        swap(a[p + i], a[s + 2]);
    }

    // 找出第1组（即中位数集合）的中位数
    // 作为partition划分的基准元素，注意x是元素值不是下标
    int x = select(p, p + (r - p - 4) / 5, (r - p + 6) / 10);
    int i = partition(p, r, x);


    
    int j = i - p + 1;
    if (k <= j)
        return select(p, i, k);
    else
        return select(i + 1, r, k - j);
}

int main()
{
    int count, k;
    cin >> count >> k;
    int input;
    for (int i = 0; i < count; i++)
    {
        cin >> input;
        a.push_back(input);
    }
    vector<int> b(a);
    sort(b.begin(), b.end());
    cout << b[k - 1] << endl;
    cout << select(0, count - 1, k);
    return 0;
}