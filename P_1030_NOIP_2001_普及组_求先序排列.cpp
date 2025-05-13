#include <iostream>
#include <string>
using namespace std;

//已知二叉树中序和后序序列，求先序遍历序列

void dfs(string midstr, string aftstr)
{
    int n = midstr.length();
    if (n <= 0)
        return;
    else
    {
        char root = aftstr.back();
        int rootpos = 0;
        for (rootpos = 0; rootpos < n; rootpos++)
            if (midstr[rootpos] == root)
                break;
        string leftmidstr = midstr.substr(0, rootpos);
        string rightmidstr = midstr.substr(rootpos + 1);
        string leftaftstr = aftstr.substr(0, rootpos);
        string rightaftstr = aftstr.substr(rootpos, n - rootpos - 1);

        cout << root;
        
        dfs(leftmidstr, leftaftstr);

        dfs(rightmidstr, rightaftstr);
    }
}

int main()
{
    string midstr;
    string aftstr;

    cin >> midstr;
    cin >> aftstr;

    dfs(midstr, aftstr);

    return 0;
}