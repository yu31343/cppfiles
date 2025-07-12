#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

char judgestr(string str)
{
    if (str.find('1')!=string::npos && str.find('0')!=string::npos)     //成员函数find
                                                                  //返回位置，找不到返回npos
        return 'F';
    else if (find(str.begin(), str.end(), '1') != str.end())       //全局函数find (algorithm)
        return 'I';                                               //返回迭代器，找不到返回end()
    else
        return 'B';
}

void FBI(string str)
{
    int n = str.length();
    if (n > 1)
    {
        string leftstr = str.substr(0, n / 2); // substr第一个参数为开始位置，第二个参数为截取长度
        string rightstr = str.substr(n / 2);   // 省略第二个参数表示直接截取到末尾
        FBI(leftstr);
        FBI(rightstr);
    }
    cout << judgestr(str);
}

int main()
{
    int n;
    cin >> n;
    string str;
    cin >> str;

    FBI(str);

    return 0;
}