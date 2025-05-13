#include <iostream>
using namespace std;
#include <string>
#include <vector>
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

    // //较短数补充0占位
    // if(alen<blen)
    // {
    //     for (int i = 0; i < blen - alen;i++)
    //         a.push_back(0);
    // }
    // else
    // {
    //     for (int i = 0; i < alen - blen; i++)
    //         b.push_back(0);
    // }

    // printvector(a);
    // printvector(b);

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

int main()
{
    string ca, cb, cc;
    cout << "请分别输入a和b的值：";
    cin >> ca >> cb;
    // cout << ca.length() << endl;
    // cout << cb.size() << endl;

    cc = plus_cint(ca, cb);

    cout << "a+b的值为：";
    cout << cc << endl;

    return 0;
}