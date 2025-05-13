#include <iostream>
using namespace std;

// 给定1个1000行×20列的0-1矩阵，找出互斥集合A和B使得包含的列总数最大

int a[1001][21];                    // 原矩阵
int n = 20;                         // 列数
int x[21], y[21];                   // 存储A，B中列的下标(从1开始)
int x_size = 0, y_size = 0;         // 当前x和y的大小
int bestx[21], besty[21];           // 存储最优解
int bestx_size = 0, besty_size = 0; // 最优解大小
int bests = 0;                      // A、B当前最大元素个数和

int rows_with_ones[21][1001]; // 每列中值为1的行号
int rows_count[21];           // 每列中1的个数
int judge[21][21];            // judge[i][j]=0表第i、j列互斥

// 判断两列是否互斥
bool is_c_fit(int i, int j)
{
    for (int k = 0; k < rows_count[i]; k++)
    {
        int row_i = rows_with_ones[i][k];
        // 检查该行是否在j列的1中出现
        for (int l = 0; l < rows_count[j]; l++)
        {
            if (rows_with_ones[j][l] == row_i)
            {
                return false;
            }
        }
    }
    return true;
}

// 判断新加入列是否产生互斥  toA表示新加入列是否在A集合中
bool isfit(int t, bool toA)
{
    if (toA)
    {
        for (int i = 0; i < y_size; i++)
        {
            if (!judge[t][y[i]])
                return false;
        }
        return true;
    }
    // 第t列在B中
    else
    {
        for (int i = 0; i < x_size; i++)
        {
            if (!judge[t][x[i]])
                return false;
        }
        return true;
    }
}

void backtrack(int t)
{
    if (t > n)
    {
        if (x_size == 0 || y_size == 0 || x_size < y_size)
            return;
        int s = x_size + y_size;
        bool update = 0;

        // A和B元素列数差的绝对值最小;
        // A的首元素最小
        // A的列数要大于B的列数;
        if (s > bests)
            update = 1;
        else if (s == bests)
        {
            int diffc = (x_size - y_size) - (bestx_size - besty_size);
            if (diffc < 0)
                update = 1;
            else if (diffc == 0)
            {
                if (x[0] < bestx[0])
                    update = 1;
            }
        }

        // 如果需要更新最优解
        if (update)
        {
            bests = s;
            bestx_size = x_size;
            besty_size = y_size;
            for (int i = 0; i < x_size; i++)
                bestx[i] = x[i];
            for (int i = 0; i < y_size; i++)
                besty[i] = y[i];
        }

        return;
    }

    // 第t列给集合A
    x[x_size++] = t;
    if (isfit(t, 1))
    {
        backtrack(t + 1);
    }
    x_size--;

    // 第t列给集合B
    y[y_size++] = t;
    if (isfit(t, 0))
    {
        backtrack(t + 1);
    }
    y_size--;

    // 不选择第t列
    if (x_size + y_size + n - t >= bests)
        backtrack(t + 1);
}

int main()
{
    bests = 0;
    x_size = 0;
    y_size = 0;
    bestx_size = 0;
    besty_size = 0;

    for (int i = 1; i <= 1000; i++)
    {
        for (int j = 1; j <= 20; j++)
            cin >> a[i][j];
    }

    // 预处理
    for (int j = 1; j <= 20; j++)
    {
        rows_count[j] = 0;
        int count = 0;
        for (int i = 1; i <= 1000; i++)
        {
            if (count > 1000 * 0.1) // 1不超过10%
                break;
            if (a[i][j])
            {
                rows_with_ones[j][rows_count[j]++] = i;
                count++;
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            judge[i][j] = judge[j][i] = (int)is_c_fit(i, j);
        }
    }

    backtrack(1);

    for (int i = 0; i < bestx_size; i++)
        cout << bestx[i] - 1 << " ";
    cout << endl;

    for (int i = 0; i < besty_size; i++)
        cout << besty[i] - 1 << " ";
    cout << endl;

    return 0;
}