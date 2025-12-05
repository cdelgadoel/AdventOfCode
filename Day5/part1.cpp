#include <iostream>
#include <vector>
#include <algorithm>
#include <format>
#include <string>

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

vector<ll> readIds()
{
    vector<ll> ids;
    ids.push_back(toInt(firstId));

    string s;
    while (cin >> s)
    {
        // cout << "add id " << s << endl;
        ids.push_back(toInt(s));
    }
    return ids;
}

int main()
{
    vector<pll> ranges = readRanges();
    sort(ranges.begin(), ranges.end());

    vector<ll> ids = readIds();
    sort(ids.begin(), ids.end());

    int itRanges = 0, itIds = 0;
    int ans = 0;
    ll id, start, end;
    while (itIds != ids.size() && itRanges != ranges.size())
    {
        id = ids[itIds];
        start = ranges[itRanges].first;
        end = ranges[itRanges].second;
        // spoiled, go to next id
        if (id < start)
        {
            ++itIds;
        }
        // we no longer need this range
        else if (end < id)
        {
            ++itRanges;
        }
        // fresh, go to next id
        else
        {
            ++ans;
            ++itIds;
        }
    }
    cout << ans << "\n";
}