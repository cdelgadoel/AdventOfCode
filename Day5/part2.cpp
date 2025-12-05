#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef int64_t ll;
typedef pair<ll, ll> pll;
string firstId;

ll toInt(string s)
{
    ll ans = 0;
    for (char c : s)
    {
        ans = ans * 10 + (c - '0');
    }
    return ans;
}

vector<pair<ll, ll>> readRanges()
{
    vector<pll> ranges;
    ll start, end;
    string s;
    int index;
    while (cin >> s && (s.find('-') != string::npos))
    {
        index = s.find('-');
        start = toInt(s.substr(0, index));
        end = toInt(s.substr(index + 1));
        // cout << "Add " << start << " " << end << endl;
        ranges.push_back(pll(start, end));
    }
    firstId = s;
    return ranges;
}

int main()
{
    vector<pll> ranges = readRanges();
    sort(ranges.begin(), ranges.end());

    int itRanges = 0;
    ll start, end, ans = 0;
    while (itRanges != ranges.size())
    {
        // we will process all the next ranges that overlap
        // for easier counting
        start = ranges[itRanges].first;
        end = ranges[itRanges].second;

        // while overlap, mix into a bigger range
        // since they are sorted, start of second is guaranteed to be after the
        // "start" variable value
        ++itRanges;
        while (itRanges != ranges.size() && ranges[itRanges].first <= end)
        {
            end = max(end, ranges[itRanges].second);
            ++itRanges;
        }

        // count all fresh ids
        ans += end - (start - 1);
    }
    cout << ans << endl;
}