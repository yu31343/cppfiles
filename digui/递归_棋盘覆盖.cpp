#include <iostream>
using namespace std;

int tile = 0;
int **board = NULL;

// tr:棋盘左上角方格的行号
// tc:棋盘左上角方格的列号
// dr:特殊方格所在的行号
// dc:特殊方格所在的列号
// size:棋盘规格size*size，size取2的整数幂
void chessBoard(int tr, int tc, int dr, int dc, int size)
{
    // 边界条件
    if (size == 1)
        return;
    int t = ++tile;   // 放置一个L形骨牌，编号为t
    int s = size / 2; // 划分棋盘

    // 分别覆盖四个字棋盘：

    // 覆盖左上角子棋盘
    if (dr < tr + s && dc < tc + s)
    {
        // 特殊方格在此棋盘
        chessBoard(tr, tc, dr, dc, s);
    }
    else
    {
        // 此棋盘中无特殊方格
        // 用t号骨牌覆盖 右下角 方格
        board[tr + s - 1][tc + s - 1] = t;
        // 继续覆盖其它方格
        chessBoard(tr, tc, tr + s - 1, tc + s - 1, s);
    }

    // 覆盖右上角子棋盘
    if (dr < tr + s && dc >= tc + s)
    {
        // 特殊方格在此棋盘
        chessBoard(tr, tc + s, dr, dc, s);
    }
    else
    {
        // 此棋盘中无特殊方格
        // 用t号骨牌覆盖 左下角 方格
        board[tr + s - 1][tc + s] = t;
        // 继续覆盖其它方格
        chessBoard(tr, tc + s, tr + s - 1, tc + s, s);
    }

    // 覆盖左下角子棋盘
    if (dr >= tr + s && dc < tc + s)
    {
        // 特殊方格在此棋盘
        chessBoard(tr + s, tc, dr, dc, s);
    }
    else
    {
        // 此棋盘中无特殊方格
        // 用t号骨牌覆盖 右上角 方格
        board[tr + s][tc + s - 1] = t;
        // 继续覆盖其它方格
        chessBoard(tr + s, tc, tr + s, tc + s - 1, s);
    }

    // 覆盖右下角子棋盘
    if (dr >= tr + s && dc >= tc + s)
    {
        // 特殊方格在此棋盘
        chessBoard(tr + s, tc + s, dr, dc, s);
    }
    else
    {
        // 此棋盘中无特殊方格
        // 用t号骨牌覆盖 左上角 方格
        board[tr + s][tc + s] = t;
        // 继续覆盖其它方格
        chessBoard(tr + s, tc + s, tr + s, tc + s, s);
    }
}

int main()
{
    int dr, dc, size;
    cout << "请输入棋盘边长：";
    cin >> size;
    // 创建一个动态二维数组表示棋盘
    board = new int *[size];
    for (int i = 0; i < size; i++)
    {
        board[i] = new int[size]();
    }

    cout << "请输入特殊方格位置(从1开始编号)：\n行号：";
    cin >> dr;
    cout << "列号：";
    cin >> dc;
    // board[dr][dc] = 0;

    // 开始棋盘覆盖
    chessBoard(0, 0, dr - 1, dc - 1, size);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < size; i++)
    {
        delete[] board[i];
    }
    delete board;

    return 0;
}