#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef int64_t ll;

vector<pair<ll, ll>> readTiles()
{
    ll x, y;
    char c;
    vector<pair<ll, ll>> tiles;
    while (cin >> x)
    {
        cin >> c >> y;
        tiles.push_back({x, y});
    }

    return tiles;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll ans = 0;

    vector<pair<ll, ll>> tiles = readTiles();
    for (int i = 0; i < tiles.size(); ++i)
    {
        for (int j = i + 1; j < tiles.size(); ++j)
        {
            ll dx = abs(tiles[i].first - tiles[j].first) + 1;
            ll dy = abs(tiles[i].second - tiles[j].second) + 1;
            ans = max(ans, dx * dy);
        }
    }
    cout << ans << "\n";

    return 0;
}