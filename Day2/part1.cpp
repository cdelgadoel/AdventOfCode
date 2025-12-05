#include <iostream>
#include <vector>
#include <string>
typedef int64_t ll;

using namespace std;
int pow(ll x, int power)
{
    ll ans = 1, pot = x;
    while (power > 0)
    {
        if (power & 1)
            ans *= pot;
        pot *= pot;
        power >>= 1;
    }
    return ans;
}

ll toInt(string s)
{
    ll ans = 0;
    for (char c : s)
    {
        ans = ans * 10 + (c - '0');
    }
    return ans;
}

int nextPossible(string number)
{
    int n = number.size();
    // odd number of digits
    if (n & 1)
    {
        return pow(10, (n - 1) >> 1);
    }
    // even number of difits
    else
    {
        string halfNumber = number.substr(0, n >> 1);
        return number <= halfNumber + halfNumber ? toInt(halfNumber) : toInt(halfNumber) + 1;
    }
}

int previousPossible(string number)
{
    int n = number.size();
    // odd number of digits
    if (n & 1)
    {
        return pow(10, (n - 1) >> 1) - 1;
    }
    // even number of difits
    else
    {
        string halfNumber = number.substr(0, n >> 1);
        return halfNumber + halfNumber <= number ? toInt(halfNumber) : toInt(halfNumber) - 1;
    }
}

int numDigits(int a)
{
    return to_string(a).size();
}

ll gaus(int n)
{
    return (((ll)n) * (n + 1)) >> 1;
}

// this assumes that a and b have the same number of digits
ll sumRange(int a, int b)
{
    if (a > b)
        return 0;
    return (gaus(b) - gaus(a - 1)) * (pow(10, numDigits(a)) + 1);
}

int main()
{
    int n;
    cin >> n;
    string a, b;
    ll ans = 0;
    for (int i = 0; i < n; ++i)
    {
        cin >> a >> b;
        ans += sumRange(nextPossible(a), previousPossible(b));
    }
    cout << ans << "\n";
    return 0;
}