#include <iostream>
#include <vector>
#include <string>
typedef int64_t ll;

using namespace std;

ll toInt(string s)
{
    ll ans = 0;
    for (char c : s)
    {
        ans = ans * 10 + (c - '0');
    }
    return ans;
}

// checks if its invalid by dividing into blocks
// of size d
bool isInvalid(string number, ll d)
{
    for (ll i = d; i < number.size(); ++i)
    {
        if (number[i] != number[i - d])
            return false;
    }
    return true;
}

bool isInvalid(string number)
{
    if (number.size() == 1)
        return false;
    // check for all divisors if its invalid because of its
    // blocks of size d, where d is the divisor
    if (isInvalid(number, 1))
        return true;
    for (ll d = 2; d * d <= number.size(); ++d)
    {
        if (number.size() % d == 0 && (isInvalid(number, d) || isInvalid(number, number.size() / d)))
        {
            return true;
        }
    }
    return false;
}

ll sumRange(ll a, ll b)
{
    ll ans = 0;
    for (ll i = a; i <= b; ++i)
    {
        if (isInvalid(to_string(i)))
            ans += i;
    }
    return ans;
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
        ans += sumRange(toInt(a), toInt(b));
    }
    cout << ans << endl;

    return 0;
}