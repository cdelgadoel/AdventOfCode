#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stack>

using namespace std;
typedef int64_t ll;

vector<vector<int>> adjacencyList;
int svr, fft, dac, out;

void readAdjacencyList()
{
    unordered_map<string, int> nodeToId;

    string line;
    int nextId = 0;
    // Read input line by line
    while (getline(cin, line))
    {
        istringstream iss(line);
        string node;

        // Extract the node (key)
        if (getline(iss, node, ':'))
        {
            if (nodeToId.find(node) == nodeToId.end())
                nodeToId[node] = nextId++;
            vector<int> adjacent;
            string neighbors;
            // Extract the neighbors (values)
            if (getline(iss, neighbors))
            {
                istringstream neighborsStream(neighbors);
                string neighbor;
                while (neighborsStream >> neighbor)
                {
                    if (nodeToId.find(neighbor) == nodeToId.end())
                        nodeToId[neighbor] = nextId++;
                    adjacent.push_back(nodeToId[neighbor]);
                }
            }
            if (nodeToId[node] >= adjacencyList.size())
                adjacencyList.resize(nodeToId[node] + 1);
            adjacencyList[nodeToId[node]] = adjacent;
        }
    }
    svr = nodeToId["svr"];
    out = nodeToId["out"];
    fft = nodeToId["fft"];
    dac = nodeToId["dac"];
}

vector<int> getIncomingDegrees(int startId)
{
    vector<int> incomingDegree(adjacencyList.size(), 0);
    bool visited[adjacencyList.size()];
    fill(visited, visited + adjacencyList.size(), false);

    stack<int> dfs;
    dfs.push(startId);
    while (!dfs.empty())
    {
        int current = dfs.top();
        dfs.pop();
        if (visited[current])
            continue;
        visited[current] = true;

        for (int neighbor : adjacencyList[current])
        {
            ++incomingDegree[neighbor];
            if (!visited[neighbor])
                dfs.push(neighbor);
        }
    }
    return incomingDegree;
}

ll calculateNumberOfPaths(int startId, int endId)
{
    ll pathCount = 0;
    stack<string> readyToProcess;

    // calculate incoming degrees
    vector<int> incomingDegree = getIncomingDegrees(startId);

    stack<int> nextToProcess;
    nextToProcess.push(startId);

    vector<ll> totalPaths(adjacencyList.size(), 0);
    totalPaths[startId] = 1;

    int current;
    while (!nextToProcess.empty())
    {
        current = nextToProcess.top();
        nextToProcess.pop();
        if (current == endId)
            return totalPaths[current];

        for (int neighbor : adjacencyList[current])
        {
            totalPaths[neighbor] += totalPaths[current];
            --incomingDegree[neighbor];
            if (incomingDegree[neighbor] == 0)
                nextToProcess.push(neighbor);
        }
    }
    return totalPaths[endId];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    readAdjacencyList();
    // we count separately paths that contain svr->fft->dac->out
    // and paths that contain svr->dac->fft->out
    ll case1 = calculateNumberOfPaths(svr, fft) * calculateNumberOfPaths(fft, dac) * calculateNumberOfPaths(dac, out);
    ll case2 = calculateNumberOfPaths(svr, dac) * calculateNumberOfPaths(dac, fft) * calculateNumberOfPaths(fft, out);
    cout << case1 + case2 << "\n";

    return 0;
}