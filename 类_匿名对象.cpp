#include <iostream>
#include <string>
using namespace std;

class Person
{
    string name;
    int age;

public:
    Person(string name,int age)
    {
        this->name = name;
        this->age = age;
        cout << this->name <<" "<< this->age << endl;
    }
};

class Person1
{
    int age;

public:
    Person1(int age)
    {
        this->age = age;
        cout<< this->age << endl;
    }
};

int main()
{
    int n;
    string str = "sada";
    n = 23;
    Person{str, n};

    //此处不能使用Person(n)
    //会视为Person n()
    //只能使用花括号Person{n}或(void)Person1(n)
    Person1(2);
    (void)Person1(n);

    return 0;
}