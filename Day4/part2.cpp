#include <iostream>
#include <string>
#include <stack>
using namespace std;
const int n = 138;

int main()
{
    char mat[n][n];
    string s;
    for (int i = 0; i < n; ++i)
    {
        cin >> s;
        for (int j = 0; j < n; ++j)
        {
            mat[i][j] = s[j];
        }
    }

    int ans = 0;
    // we don't need to remove per "phases"
    // to get the result, it's valid to remove a roll
    // once we realize we can remove it
    bool rollsWereRemoved = true;
    while (rollsWereRemoved)
    {
        rollsWereRemoved = false;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (mat[i][j] == '.')
                    continue;

                int adjacentRolls = 0;
                for (int dx = -1; dx <= 1; ++dx)
                {
                    for (int dy = -1; dy <= 1; ++dy)
                    {
                        // the cell itself
                        if (dx == 0 && dy == 0)
                            continue;
                        // out of bounds
                        if (i + dx == -1 || i + dx == n || j + dy == -1 || j + dy == n)
                            continue;

                        if (mat[i + dx][j + dy] == '@')
                            ++adjacentRolls;
                    }
                }
                if (adjacentRolls < 4)
                {
                    ++ans;
                    mat[i][j] = '.';
                    rollsWereRemoved = true;
                }
            }
        }
    }
    cout << ans << endl;
}