#include <iostream>
using namespace std;


//计算A[i:j]所需的最少数乘次数为m[i][j]
void MatrixChain(int* p, int n, int** m, int** s)
{
	//i=j的情况	不需要相乘(规模r=1情况)
	for (int i = 1; i <= n; i++)
		m[i][i] = 0;

	//r控制规模：r个矩阵连乘情况
	for (int r = 2; r <= n; r++)
	{
		for (int i = 1; i <= n - r + 1; i++)
		{
			int j = i + r - 1;	//指向最后一个矩阵

			//取特殊情况赋一个初值	取i处断开
			m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];	//m[i][i]=0省略
			s[i][j] = i;
			//从i+1处断开遍历至j-1处断开
			for (int k = i + 1; k < j; k++)
			{
				int t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[i];
				if (t < m[i][j])
				{
					m[i][j] = t;
					s[i][j] = k;	//k处断开更优
				}
			}
		}
	}
}

//利用s[][]回溯
void traceback(int** s, int i, int j)
{
	if (i == j) return;
	traceback(s, i, s[i][j]);
	traceback(s, s[i][j] + 1, j);
	//matrix.insert(make_pair(i, '('));
	//matrix.insert(make_pair(j, ')'));
	if (i != s[i][j])
		cout << i << "," << s[i][j];
	else
		cout << i;
	cout << "and";
	if (s[i][j]+1 != j)
		cout << s[i][j] + 1 << "," << j << endl;
	else
		cout << j << endl;
}

int main()
{
	int p[7] = { 30,35,15,5,10,20,25 };

	//for(int i=1;i<7;i++)
	//	matrix.insert(make_pair(i, 'A'));

	int** m = new int* [7];
	int** s = new int* [7];
	for(int i = 0; i < 7; i++)
	{
		s[i] = new int[7];
		m[i] = new int[7];
	}
	MatrixChain(p, 6, m, s);

    cout << m[1][6] << endl;
    traceback(s, 1, 6);

	return 0;
}