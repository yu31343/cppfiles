#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 给一 n×n 的字母方阵，内可能蕴含多个 yizhong 单词。单词在方阵中是沿着同一方向连续摆放的。摆放可沿着 8 个方向的任一方向，同一单词摆放时不再改变方向，单词与单词之间可以交叉，因此有可能共用字母。输出时，将不是单词的字母用 * 代替，以突出显示单词。
// 输入格式
// 第一行输入一个数 n。(7≤n≤100)。
// 第二行开始输入 n×n 的字母矩阵。

// 输出格式
// 突出显示单词的 n×n 矩阵

const string word = "yizhong";
int n;
vector<vector<char>> input, output;

int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

void solution()
{
    int len = word.length();
    bool isfit;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)    //遍历每个方格作为起始
        {
            //可省
            if(input[i][j]!=word[0])    continue;


            for (int k = 0; k < 8; k++)
            {
                //遍历8个方向
                isfit = true;
                if (i + dx[k] * (len - 1) > n || i + dx[k] * (len - 1) < 1 ||
                     j + dy[k] * (len - 1) > n || j + dy[k] * (len - 1) < 1)
                    continue;   //该方向越界，不可能有方案

                for (int p = 0; p <= len - 1; p++)
                {
                    if (input[i + p * dx[k]][j + p * dy[k]] != word[p]) //出现相异字符
                    {
                        isfit = false;
                        break;
                    }
                }
                if (isfit)
                {
                    for (int p = 0; p <= len - 1; p++)
                    {
                        output[i + p * dx[k]][j + p * dy[k]] = input[i + p * dx[k]][j + p * dy[k]];
                    }
                }
            }
        }
    }
}

int main()
{
    cin >> n;
    input.resize(n + 1, vector<char>(n + 1, '*'));
    output.resize(n + 1, vector<char>(n + 1, '*'));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> input[i][j];
        }
    }

    solution();

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << output[i][j];
        }
        cout << endl;
    }

    return 0;
}