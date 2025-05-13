#include <iostream>
using namespace std;

// c++中允许空结构体，大小为1字节
struct Empty
{
    /* data */
    //c++中结构体可以有成员函数
    void emprint()
    {
        cout << "空结构体▓☀♬ЪЬЭТУГЕИ" << endl;
    }
};

struct test
{
    //c++中结构体成员变量可以赋默认值
    int a=1;
    char b='a';
    void ttprint()
    {
        cout << a << " " << b << endl;
    }


    test(int a,char b)
    {
        this->a = a;
        this->b = b;
    }


    test() {}   //内联成员函数后可不加分号
};

int main()
{
    cout << sizeof(Empty) << endl; // c++中结构体类型可不加struct关键字，直接用名字
    Empty obj;
    obj.emprint();

    test().ttprint();
    test t(2, 'b');
    t.ttprint();


    return 0;
}