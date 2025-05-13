#include <iostream>
using namespace std;

struct test
{
    int val;
    string str;

    //默认构造函数
    
    //初始化列表方式赋初值：直接初始化，效率更高
    test():val(0),str("初始化列表方式"){}

    //默认构造+赋值:在函数体内赋值
    test(int x)
    {
        val = x;
        str = "默认构造内赋值方式";
    }

    void testprint();
};

void test::testprint()
{
    cout << val << " " << str << endl;
}

int main()
{
    test t1;
    t1.testprint();

    test t2(2);
    t2.testprint();

    return 0;
}