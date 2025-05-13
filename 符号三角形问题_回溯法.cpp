#include <iostream>
#include <vector>
using namespace std;
typedef vector<vector<int>> vector2;

int n;     // 第一行符号个数
int count; // 当前-号个数
vector2 p; // 符号三角形矩阵，1代表-号，0代表+号
long sum;  // 已找到符号条件符号三角形个数
int half;  // 总符号数的一半 即n*(n+1)/4

void backtrack(int t)
{
    // 修改剪枝条件：仅检查当前"-"号是否超过一半
    if (count > half||(t*(t-1)/2-count>half))
        return;

    // 到达叶子结点，产生可行解
    if (t > n)
        sum++;
    else
    {
        // 第一行第i位为加号或减号时 i=0/1
        for (int i = 0; i <= 1; i++)
        {
            p[1][t] = i; // 放置符号
            count += i;  // 减号数变化

            // 拓展符号三角形，补充最外层边缘处符号
            for (int j = 2; j <= t; j++)
            {
                // 相同为+即0，相异为-即1
                p[j][t - j + 1] = p[j - 1][t - j + 1] ^ p[j - 1][t - j + 2];
                count += p[j][t - j + 1];
            }

            backtrack(t + 1); // 向下回溯

            // 返回上层节点，还原count
            for (int j = 2; j <= t; j++)
                count -= p[j][t - j + 1]; // 还原外层
            count -= i; // 撤销第一行第t个符号
        }
    }
}

int main()
{
    cin >> n;
    half = n * (n + 1) / 2;

    // 总符号数为奇数，不存在可行解，直接返回0
    if (half % 2 == 1)
    {
        cout << 0 << endl;
        return 0;
    }
    half = half / 2;

    count = 0;
    sum = 0;
    p.resize(n + 1, vector<int>(n + 1, 0)); // 从1开始标号

    backtrack(1);

    cout << sum << endl;
    return 0;
}