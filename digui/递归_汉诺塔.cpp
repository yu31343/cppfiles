#include <iostream>
using namespace std;

int stepcount = 0;

//n:要移动的圆盘个数	a:源塔座	b:目标塔座	 c:辅助塔座
void hanoi(int n, char a, char b, char c)
{
	if (n > 0)
	{
		hanoi(n - 1, a, c, b);
		cout << ++stepcount << " ";
		cout << "\t将圆盘 " << n << " 从 " << a << " 移动到 " << b << endl;
		hanoi(n - 1, c, b, a);
	}

}

int main()
{
	int n;
	cout << "请输入圆盘个数：";
	cin >> n;
	char a = 'A', b = 'B', c = 'C';
	hanoi(n, a, b, c);
	return 0;
}