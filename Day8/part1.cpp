#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;
typedef int64_t ll;
const int EDGES_TO_CONSIDER = 1000;

struct node
{
    ll x, y, z;
    node(ll a, ll b, ll c) : x(a), y(b), z(c) {};
};
vector<node> nodes;

// we use squared euclidean distance to avoid floating point operations
struct edge
{
    int i, j;
    edge(const int a, const int b) : i(a), j(b) {}
    // Define the < operator for edge

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

vector<edge> computeSmallestEdges(const vector<node> &nodes)
{

    // Use default comparator with priority_queue
    priority_queue<edge> maxHeap;

    vector<edge> edges;
    int n = nodes.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            maxHeap.push(edge(i, j));
            if (maxHeap.size() > EDGES_TO_CONSIDER)
            {
                maxHeap.pop();
            }
        }
    }

    while (!maxHeap.empty())
    {
        edges.push_back(maxHeap.top());
        maxHeap.pop();
    }

    return edges;
}

// =========== UNION FIND
vector<int> root;
vector<int> clusterSize;
int find(int indx)
{
    return root[indx] == indx ? indx : root[indx] = find(root[indx]);
}

void unite(int i, int j)
{
    int root_i = find(i), root_j = find(j);
    if (root_i == root_j)
        return;
    clusterSize[root_i] += clusterSize[root_j];
    root[root_j] = root_i;
}
// ==================== UNION FIND END

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<node> nodes = readNodes();
    vector<edge> edges = computeSmallestEdges(nodes);

    // unite nodes for smallest edges
    clusterSize.resize(nodes.size(), 1);
    root.resize(nodes.size());
    for (int i = 0; i < nodes.size(); ++i)
    {
        root[i] = i;
    }

    for (edge e : edges)
    {
        unite(e.i, e.j);
    }

    // get three biggest circuits
    priority_queue<int, vector<int>, greater<int>> longestCircuits;
    for (int i = 0; i < nodes.size(); ++i)
    {
        if (root[i] == i)
        {
            longestCircuits.push(clusterSize[i]);
            if (longestCircuits.size() > 3)
                longestCircuits.pop();
        }
    }

    ll answer = 1;
    while (!longestCircuits.empty())
    {
        answer *= longestCircuits.top();
        longestCircuits.pop();
    }
    cout << answer << endl;
    return 0;
}