#include <iostream>
#include <string>
using namespace std;

int getMaxJoltage(string s)
{
    // Get the first digit, then the second
    int firstIndex = 0;
    for (int i = 1; i < s.size() - 1; ++i)
    {
        if (s[firstIndex] < s[i])
            firstIndex = i;
    }
    int secondIndex = firstIndex + 1;
    for (int i = secondIndex + 1; i < s.size(); ++i)
    {
        if (s[secondIndex] < s[i])
            secondIndex = i;
    }
    return 10 * (s[firstIndex] - '0') + (s[secondIndex] - '0');
}

int main()
{
    int ans = 0;
    string s;
    while (cin >> s)
    {
        ans += getMaxJoltage(s);
    }
    cout << ans << "\n";
}