#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    // read input
    vector<string> input;
    string inputLine;
    while (cin >> inputLine)
    {
        input.push_back(inputLine);
        cin >> inputLine;
    }

    // this is a DP like problem
    // let DP(i, j) be the number of paths a beam can take if starting at row i and column j
    // then DP(i,j) =
    //     - DP(i+1, j) if there's no division at (i,j)
    //     - DP(i+1, j-1) + DP(i+1, j+1) if there's a division at (i,j)
    // the base case is the last row, where there's only one path for each position

    // I compute this starting from the bottom row up to the top
    // We only need to keep track of the current and next row
    // so we only use two arrays

    int columns = input[0].size();
    int64_t base[columns], foo[columns];
    // we use this pointers to swap the arrays easily
    int64_t *current = foo;
    int64_t *next = base;

    // we fill the base case
    fill(base, base + columns, 1);

    // we compute the DP from the bottom to the top
    for (int i = input.size() - 1; i >= 1; --i)
    {
        for (int j = 0; j <= columns; ++j)
        {
            // DP(i, j) = division? DP(i+1, j-1) + DP(i+1, j+1) : DP(i+1, j)
            current[j] = input[i][j] == '^' ? next[j - 1] + next[j + 1] : next[j];
        }
        swap(current, next);
    }

    int initialIndex = input[0].find('S');
    cout << next[initialIndex] << endl;
}