#include <iostream>
using namespace std;


int* a = NULL;

void swap(int a[], int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

//partition: 以基准元素a[p]对子数组a[p:r]划分
int partition(int p, int r)
{
	int i = p;
	int j = r + 1;
	int x = a[p];
	while (1)
	{
		while (a[++i] < x && i < r);
		while (a[--j] > x);	//因为a[0]=x，故不会越界
		if (i >= j)
			break;
		swap(a, i, j);
	}
	a[p] = a[j];
	a[j] = x;
	return j;
}

void qSort(int p, int r)
{
	if (p < r)
	{
		int q = partition(p, r);
		qSort(p, q - 1);	//左半段排序
		qSort(q + 1, r);	//右半段排序
	}
}

//采用随机选择策略
int ramdomizedPartition(int p, int r)
{
	int i = rand() % (r - p + 1) + p;
	swap(a, i, p);
	return partition(p, r);
}


void ramdomizedQsort(int p, int r)
{
	if (p < r)
	{
		int q = ramdomizedPartition(p, r);
		ramdomizedQsort(p, q - 1);	//左半段排序
		ramdomizedQsort(q + 1, r);	//右半段排序
	}
}

int main()
{
	int n = 0;
	cout << "请输入要排序的元素个数：";
	cin >> n;
	a = new int[n];

	cout << "请输入排序元素：";
	for (int i = 0; i < n; i++)
		cin >> a[i];

	//qSort(0, n - 1);
	ramdomizedQsort(0, n - 1);

	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;

	delete[] a;
	return 0;
}