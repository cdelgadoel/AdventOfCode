#include <iostream>
#include <string>
using namespace std;
typedef int64_t ll;
const int length = 12;

int getBestNthIndex(string &s, int n, int startIndex)
{
    int index = startIndex;
    for (int i = startIndex + 1; i + (length - 1 - n) < s.size(); ++i)
    {
        if (s[index] < s[i])
            index = i;
    }
    return index;
}

ll getMaxJoltage(string &s)
{
    ll ans = 0;
    int nextStartIndex = 0;
    for (int i = 0; i < length; ++i)
    {
        int index = getBestNthIndex(s, i, nextStartIndex);
        ans = 10 * ans + (s[index] - '0');
        nextStartIndex = index + 1;
    }
    return ans;
}

int main()
{
    ll ans = 0;
    string s;
    while (cin >> s)
    {
        ans += getMaxJoltage(s);
    }
    cout << ans << "\n";
}