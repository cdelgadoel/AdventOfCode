#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;
typedef int64_t ll;

struct node
{
    ll x, y, z;
    node(ll a, ll b, ll c) : x(a), y(b), z(c) {};
};
vector<node> nodes;

struct edge
{
    int i, j;
    edge(const int a, const int b) : i(a), j(b) {}

    ll euclideanDistance() const
    {
        return (nodes[i].x - nodes[j].x) * (nodes[i].x - nodes[j].x) +
               (nodes[i].y - nodes[j].y) * (nodes[i].y - nodes[j].y) +
               (nodes[i].z - nodes[j].z) * (nodes[i].z - nodes[j].z);
    }

    bool operator<(const edge &other) const
    {
        return this->euclideanDistance() < other.euclideanDistance();
    }
};

vector<node> readNodes()
{
    ll x, y, z;
    char c;
    while (cin >> x)
    {
        cin >> c >> y >> c >> z;
        nodes.push_back(node(x, y, z));
    }
    return nodes;
}

vector<edge> getSortedEdges(const vector<node> &nodes)
{
    vector<edge> edges;
    int n = nodes.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            edges.push_back(edge(i, j));
        }
    }

    sort(edges.begin(), edges.end());
    return edges;
}

// =========== UNION FIND
vector<int> root;
vector<int> clusterSize;
int find(int indx)
{
    return root[indx] == indx ? indx : root[indx] = find(root[indx]);
}

int unite(int i, int j)
{
    int root_i = find(i), root_j = find(j);
    if (root_i == root_j)
        return clusterSize[root_i];
    clusterSize[root_i] += clusterSize[root_j];
    root[root_j] = root_i;
    return clusterSize[root_i];
}
// ==================== UNION FIND END

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<node> nodes = readNodes();
    vector<edge> edges = getSortedEdges(nodes);

    // unite nodes until we have an MST
    clusterSize.resize(nodes.size(), 1);
    root.resize(nodes.size());
    for (int i = 0; i < nodes.size(); ++i)
    {
        root[i] = i;
    }

    bool allConnected = false;
    ll answer = 1;
    int itEdges = 0, clusterSize;
    while (!allConnected)
    {
        clusterSize = unite(edges[itEdges].i, edges[itEdges].j);
        if (clusterSize == nodes.size())
        {
            allConnected = true;
            answer = nodes[edges[itEdges].i].x * nodes[edges[itEdges].j].x;
        }
        ++itEdges;
    }

    cout << answer << endl;
    return 0;
}