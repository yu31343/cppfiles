#include <iostream>
using namespace std;
#include <vector>
#include <climits>
#define vector2 vector<vector<int>>

int n;  //作业数
vector2 m;  //各作业在各机器所需处理时间 2xn
int f1; //机器1完成处理时刻
vector<int> f2; //机器2完成处理时刻
int f;      //机器2完成时刻和
int bestf;  //当前最优值
vector<int> x;  //当前作业调度 即1,2,...,n的全排列
vector<int> bestx;  //当前最优作业调度
void myswap(vector<int>& x,int i,int j)
{
    int temp = x[i];
    x[i] = x[j];
    x[j] = temp;
}


void backtrack(int i)
{
    //到达最下层，产生更优解
    if(i>n)
    {
        bestf = f;  //已剪枝，无需比较大小，必然相等或更优
        bestx = x;  //vector直接拷贝
        
        return;   //return 可有可无，因为后面else不会执行，同样返回空
    }
    else
    {
        for (int j = i; j <= n;j++)
        {
            f1 += m[x[j]][1];
            f2[i] = max(f2[i - 1], f1) + m[x[j]][2];
            f += f2[i];
            if(f<bestf)  //当前处理时刻和若已超过bestf，一定更劣
            {
                myswap(x, i, j);
                backtrack(i + 1);
                myswap(x, i, j);
            }
            f1 -= m[x[j]][1];
            f -= f2[i];
        }
    }

}


int main()
{
    cin >> n;
    m.resize( n+1,vector<int>(3));    //不使用m[0][] & m[][0]
    for (int i = 1; i <= n;i++)
    {
        cin >> m[i][1] >> m[i][2];
    }
    x.resize(n + 1);
    f2.resize(n + 1);

    for(int i=1;i<=n;i++)
        x[i] = i;   //初始调度方案为[1,2,3]

    bestf = INT_MAX;

    backtrack(1);
    cout << bestf << endl;

    return 0;
}
