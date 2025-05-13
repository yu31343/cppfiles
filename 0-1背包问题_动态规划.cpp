#include <iostream>
using namespace std;
#include <vector>

//前i个物品装入容量为j的背包，所能获得的最大价值用m[i][j]来表示
void knapsack(vector<int>& w, vector<int>& v,int c,int **m)
{
	int n = w.size()-1;
	//i=0||j=0	m[i][j]=0
	for (int j = 0; j <= c; j++)	m[0][j] = 0;
	for (int i = 1; i <= n; i++)	m[i][0] = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			if (w[i] > j)
			{
				//装不下第i个物品
				m[i][j] = m[i - 1][j];
			}
			else
			{
				//可装可不装，取价值最大的情况
				m[i][j] = m[i - 1][j] > m[i - 1][j - w[i]] + v[i] ? m[i - 1][j] : m[i - 1][j - w[i]] + v[i];
			}
		}
	}
}

//构造最优解
void traceback(vector<int>& w, int** m, int x[], int c)
{
	int n = w.size()-1;
	int j = c;
	for (int i = n; i >= 1; i--)
	{
		if (m[i][j] == m[i - 1][j])
			//第i个物品没有装
			x[i-1] = 0;
		else
		{
			x[i-1] = 1;
			j -= w[i];	//剩余容量更新
		}
	}
}

int main()
{
	vector<int> w;	//w[i]表示第i个物品重量
	vector<int> v;	//v[i]表示第i个物品价值
	w.push_back(0);	//下标从1开始
	v.push_back(0);	//填充0位


	int n = 0;	//物品个数
	int c = 0;	//背包容量(能装我物品最大重量)
	//cout << "物品个数：";
	cin >> n;
	//cout << "背包容量：";
	cin >> c;
	//cout << "请输入各个物品的重量与价值：";
	for (int i = 0; i < n; i++)
	{
		int w0, v0;
		cin >> w0 >> v0;
		w.push_back(w0);
		v.push_back(v0);
	}
	int** m = new int* [n + 1];
	for (int i = 0; i <= n; i++)
	{
		m[i] = new int[c+1];
	}
	int* x = new int[n];
	knapsack(w, v, c, m);
	traceback(w, m, x, c);

	//cout << "最优解：";
	//for (int i = 0; i < n; i++)
	//{
	//	cout << x[i] << " ";
	//}
	//cout << endl;
	//cout << "最大价值：" << m[n][c] << endl;
    cout << m[n][c] << endl;
    return 0;
}