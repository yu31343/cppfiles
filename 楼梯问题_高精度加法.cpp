#include <iostream>
using namespace std;
#include <vector>
#include <string>
#include <algorithm>

// char转换成int
void char_to_int(vector<int> &v, const string &c)
{
    for (int i = 0; i < c.length(); i++)
    {
        v.push_back(c[i] - '0');
    }
}

// 两个数组int高精度加法
string plus_cint(const string &ca, const string &cb)
{
    vector<int> a, b;
    string cc;
    char_to_int(a, ca);
    char_to_int(b, cb);

    // 先反转，方便相加
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    int alen = a.size();
    int blen = b.size();
    int mlen = max(alen, blen);

    // 设置成相同长度，方便相加
    a.resize(mlen, 0);
    b.resize(mlen, 0);

    vector<int> c;
    c.resize(mlen + 1, 0);

    int i = 0;
    for (i = 0; i < mlen; i++)
    {
        c[i] += a[i] + b[i];
        c[i + 1] = c[i] / 10;
        c[i] = c[i] % 10;
    }

    // 无进位去掉末尾0
    if (c.back() == 0)
        c.pop_back();
    reverse(c.begin(), c.end());

    for (int i = 0; i < c.size(); i++)
        cc += '0' + c[i];

    return cc;
}

vector<string> v;

string count_floor(int n)
{
    if (n == 0)
        return "0";
    if (n == 1)
        return "1";
    if (n == 2)
        return "2";

    if (v[n] == "0")
        v[n] = plus_cint(count_floor(n - 1), count_floor(n - 2));
    return v[n];
}

int main()
{
    int n;
    cin >> n;

    v.resize(n + 1, "0");
    cout << count_floor(n) << endl;

    return 0;
}