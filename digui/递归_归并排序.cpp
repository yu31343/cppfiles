#include <iostream>
using namespace std;

void merge(int a[], int b[], int left,int mid ,int right)
{
	int i = left, j = mid + 1, k = 0;
	while (i <= mid && j <= right)
	{
		if (a[i] <= a[j])
			b[k++] = a[i++];
		else
			b[k++] = a[j++];
	}
	while (i <= mid)
		b[k++] = a[i++];
	while (j <= right)
		b[k++] = a[j++];
}

void copy(int a[], int b[], int left, int right)
{
	for (int i = left, k = 0; i <= right; i++,k++)
		a[i] = b[k];
}

void mergeSort(int list[], int left, int right)
{
	//只有一个元素，无操作
	//至少两个元素
	if (left < right)
	{
		int i = (left + right) / 2;		//取中点
		mergeSort(list, left, i);	//左半部分排序
		mergeSort(list, i + 1, right);	//右半部分排序
		
		//合并到数组b
		int* b = new int[right - left + 1];
		merge(list, b, left, i, right);

		//复制回数组a
		copy(list, b, left, right);
		delete[] b;
	}
}

int main()
{
	int n;
	cout << "请输入数组的大小：";
	cin >> n;

	int* list = new int[n];
	cout << "请输入数组元素：";
	for (int i = 0; i < n; i++)
	{
		cin >> list[i];
	}

	mergeSort(list, 0, n - 1);

	cout << "排序后的数组：";
	for (int i = 0; i < n; i++)
	{
		cout << list[i] << " ";
	}
	cout << endl;

	delete[] list;

	return 0;
}