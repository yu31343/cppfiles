#include <iostream>
using namespace std;
#include <vector>

//ǰi����Ʒװ������Ϊj�ı��������ܻ�õ�����ֵ��m[i][j]����ʾ
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
				//װ���µ�i����Ʒ
				m[i][j] = m[i - 1][j];
			}
			else
			{
				//��װ�ɲ�װ��ȡ��ֵ�������
				m[i][j] = m[i - 1][j] > m[i - 1][j - w[i]] + v[i] ? m[i - 1][j] : m[i - 1][j - w[i]] + v[i];
			}
		}
	}
}

//�������Ž�
void traceback(vector<int>& w, int** m, int x[], int c)
{
	int n = w.size()-1;
	int j = c;
	for (int i = n; i >= 1; i--)
	{
		if (m[i][j] == m[i - 1][j])
			//��i����Ʒû��װ
			x[i-1] = 0;
		else
		{
			x[i-1] = 1;
			j -= w[i];	//ʣ����������
		}
	}
}

int main()
{
	vector<int> w;	//w[i]��ʾ��i����Ʒ����
	vector<int> v;	//v[i]��ʾ��i����Ʒ��ֵ
	w.push_back(0);	//�±��1��ʼ
	v.push_back(0);	//���0λ


	int n = 0;	//��Ʒ����
	int c = 0;	//��������(��װ����Ʒ�������)
	//cout << "��Ʒ������";
	cin >> n;
	//cout << "����������";
	cin >> c;
	//cout << "�����������Ʒ���������ֵ��";
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

	//cout << "���Ž⣺";
	//for (int i = 0; i < n; i++)
	//{
	//	cout << x[i] << " ";
	//}
	//cout << endl;
	//cout << "����ֵ��" << m[n][c] << endl;
    cout << m[n][c] << endl;
    return 0;
}