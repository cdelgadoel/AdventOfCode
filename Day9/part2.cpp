#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <unordered_set>
using namespace std;

typedef int64_t ll;
typedef pair<ll, ll> pll;

vector<pll> tiles;

void readTiles()
{
    int row, col;
    int64_t a;
    char c;
    while (cin >> col)
    {
        cin >> c >> row;
        tiles.push_back({row, col});
    }
}

bool isExterior(int row, int col)
{
    // check how many vertical lines does the line x cross to the right of y
    int intersectionsParity = 0;
    int n = tiles.size();
    for (int i = 0; i < n; ++i)
    {
        if (tiles[i].second == tiles[(i + 1) % n].second // columns must be the same
            && col < tiles[i].second                     // column must be to the right
            && (tiles[i].first - row) * (tiles[(i + 1) % n].first - row) <= 0)
            intersectionsParity ^= 1;

        // if you are on a column, your are inside
        if (tiles[i].second == tiles[(i + 1) % n].second // columns must be the same
            && col == tiles[i].second                    // column must be to the right
            && (tiles[i].first - row) * (tiles[(i + 1) % n].first - row) <= 0)
        {
            return false;
        }
        // if you are on a row, your are inside
        if (tiles[i].first == tiles[(i + 1) % n].first // rows must be the same
            && row == tiles[i].first && (tiles[i].second - col) * (tiles[(i + 1) % n].second - col) <= 0)
        {
            return false;
        }
    }
    return intersectionsParity == 0; // even -> exterior
}

bool isInsideCase1(ll a, ll b, ll c, ll d)
{
    int n = tiles.size();
    // check (a,b) -> (a,d)
    // we check for vertical lines that make symbols of the line part of an edge
    for (int i = 0; i < n; ++i)
    {
        if (tiles[i].second == tiles[(i + 1) % n].second   // columns must be the same
            && b <= tiles[i].second && tiles[i].second < d // column must be in range. not equal to d as we check the right cell
            && (tiles[i].first - a) * (tiles[(i + 1) % n].first - a) <= 0 && isExterior(a, tiles[i].second + 1))
        {
            return false;
        }
    }

    // check (c,b) <- (c,d)
    for (int i = 0; i < n; ++i)
    {
        if (tiles[i].second == tiles[(i + 1) % n].second   // columns must be the same
            && b < tiles[i].second && tiles[i].second <= d // column must be in range
            && (tiles[i].first - c) * (tiles[(i + 1) % n].first - c) <= 0 && isExterior(c, tiles[i].second - 1))
        {
            return false;
        }
    }

    // check (a,b) -> (c,b)
    // we check for horizontal lines that make symbols of the line part of an edge
    for (int i = 0; i < n; ++i)
    {
        if (tiles[i].first == tiles[(i + 1) % n].first   // rows must be the same
            && a <= tiles[i].first && tiles[i].first < c // row must be in range
            && (tiles[i].second - b) * (tiles[(i + 1) % n].second - b) <= 0 && isExterior(tiles[i].first + 1, b))
        {
            return false;
        }
    }

    // check (a,d) <- (c,d)
    for (int i = 0; i < n; ++i)
    {
        if (tiles[i].first == tiles[(i + 1) % n].first   // rows must be the same
            && a < tiles[i].first && tiles[i].first <= c // row must be in range
            && (tiles[i].second - d) * (tiles[(i + 1) % n].second - d) <= 0 && isExterior(tiles[i].first - 1, d))
        {
            return false;
        }
    }
    return true;
}

bool isInsideCase2(ll a, ll b, ll c, ll d)
{
    int n = tiles.size();
    // check (a,b) -> (a,d)
    // we check for vertical lines that make symbols of the line part of an edge
    for (int i = 0; i < n; ++i)
    {
        if (tiles[i].second == tiles[(i + 1) % n].second   // columns must be the same
            && b <= tiles[i].second && tiles[i].second < d // column must be in range
            && (tiles[i].first - a) * (tiles[(i + 1) % n].first - a) <= 0 && isExterior(a, tiles[i].second + 1))
        {
            return false;
        }
    }

    // check (c,b) <- (c,d)
    for (int i = 0; i < n; ++i)
    {
        if (tiles[i].second == tiles[(i + 1) % n].second   // columns must be the same
            && b < tiles[i].second && tiles[i].second <= d // column must be in range
            && (tiles[i].first - c) * (tiles[(i + 1) % n].first - c) <= 0 && isExterior(c, tiles[i].second - 1))
        {
            return false;
        }
    }

    // check (a,b) -> (c,b)
    // we check for horizontal lines that make symbols of the line part of an edge
    for (int i = 0; i < n; ++i)
    {
        if (tiles[i].first == tiles[(i + 1) % n].first   // rows must be the same
            && c < tiles[i].first && tiles[i].first <= a // row must be in range
            && (tiles[i].second - b) * (tiles[(i + 1) % n].second - b) <= 0 && isExterior(tiles[i].first - 1, b))
        {
            return false;
        }
    }

    // check (a,d) <- (c,d)
    for (int i = 0; i < n; ++i)
    {
        if (tiles[i].first == tiles[(i + 1) % n].first   // rows must be the same
            && c <= tiles[i].first && tiles[i].first < a // row must be in range
            && (tiles[i].second - d) * (tiles[(i + 1) % n].second - d) <= 0 && isExterior(tiles[i].first + 1, d))
        {
            return false;
        }
    }
    return true;
}

bool isInside(int i, int j)
{
    if (j - i == 1)
        return true;
    // we check that all sides of the rectangle are in
    if (tiles[i].first <= tiles[j].first)
    {
        if (tiles[i].second <= tiles[j].second)
            return isInsideCase1(tiles[i].first, tiles[i].second, tiles[j].first, tiles[j].second);
        else
            return isInsideCase2(tiles[j].first, tiles[j].second, tiles[i].first, tiles[i].second);
    }
    else
    {
        if (tiles[i].second <= tiles[j].second)
            return isInsideCase2(tiles[i].first, tiles[i].second, tiles[j].first, tiles[j].second);
        else
            return isInsideCase1(tiles[j].first, tiles[j].second, tiles[i].first, tiles[i].second);
    }
}

int main()
{
    readTiles();
    ll ans = 0, dx, dy;
    for (int i = 0; i < tiles.size(); ++i)
    {
        for (int j = i + 1; j < tiles.size(); ++j)
        {
            if (isInside(i, j))
            {
                // cout<<"inside"<<endl;
                dx = abs(tiles[i].first - tiles[j].first) + 1;
                dy = abs(tiles[i].second - tiles[j].second) + 1;
                ans = max(ans, dx * dy);
            }
        }
    }
    cout << ans << "\n";
    return 0;
}