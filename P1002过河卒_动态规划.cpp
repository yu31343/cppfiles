#include <iostream>
using namespace std;

// 棋盘上 A 点有一个过河卒，需要走到目标 B 点。卒行走的规则：可以向下、或者向右。同时在棋盘上 C 点有一个对方的马，该马所在的点和所有跳跃一步可达的点称为对方马的控制点。因此称之为“马拦过河卒”。
//  棋盘用坐标表示，A 点(0, 0)、B 点(n, m)，同样马的位置坐标是需要给出的。
//  现在要求你计算出卒从 A 点能够到达 B 点的路径的条数，假设马的位置是固定不动的，并不是卒走一步马走一步。
//  输入格式
//  一行四个正整数，分别表示 B 点坐标和马的坐标。
//  输出格式
//  一个整数，表示所有的路径条数。

// void put_horse(int p, int q, long long **s)
// {
//     int a = p + 2;
//     int b = q + 2;
//     s[a][b] = s[a - 2][b - 1] = s[a - 1][b - 2] = s[a + 1][b + 2] = s[a + 2][b + 1] = s[a - 2][b + 1] = s[a + 1][b - 2] = s[a + 2][b - 1] = s[a - 1][b + 2] = 0;
// }    //需要多申请外围空间

void put_horse(int p, int q,int n,int m, long long **s)
{
    // 原棋盘坐标 (p, q) 对应 s[p+2][q+2]
    int horse_x = p + 2;
    int horse_y = q + 2;
    s[horse_x][horse_y] = 0; // 标记马自身

    // 8个控制点相对原坐标的偏移
    int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
    int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};

    for (int k = 0; k < 8; k++)
    {
        int x = p + dx[k] + 2; // 原坐标转 s 数组坐标
        int y = q + dy[k] + 2;
        if (x >= 0 && x <= n + 2 && y >= 0 && y <= m + 2)
        {
            s[x][y] = 0;
        }
    }
}

void solution(int n, int m, int p, int q, long long **s)
{
    put_horse(p, q,n,m, s);

    for (int i = 1; i < m + 3; i++)
    {
        s[1][i] = 0;
    }
    for (int i = 1; i < n + 3; i++)
    {
        s[i][1] = 0;
    }

    

    for (int i = 2; i < n + 3; i++)
    {
        for (int j = 2; j < m + 3; j++)
        {
            if (s[i][j] == 0)
                continue;
            if(i==2&&j==2&&s[2][2]!=0)
            {
                s[2][2] = 1;
                continue;
            }
            s[i][j] = s[i - 1][j] + s[i][j - 1];
        }
    }
}

int main()
{
    int n, m, p, q;
    cin >> n >> m >> p >> q;


    //当n接近20时，结果非常大，防止溢出故用long long
    long long **s = new long long *[n + 3];
    for (int i = 0; i < n + 3; i++)
        s[i] = new long long[m + 3];    //put_horse不判断最外层界则申请n+5，m+5空间

    for (int i = 0; i < n + 3; i++)
    {
        for (int j = 0; j < m + 3; j++)
        {
            s[i][j] = -1;
        }
    }

    solution(n, m, p, q, s);

    for (int i = 2; i < n + 3; i++)
    {
        for (int j = 2; j < m + 3; j++)
        {
            cout << s[i][j] << "\t";
        }
        cout << endl;
    }

    cout << s[n+2][m+2] << endl;

    for (int i = 0; i < n + 3; i++)
        delete[] s[i];
    delete[] s;
    return 0;
}