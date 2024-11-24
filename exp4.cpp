#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>

using namespace std;

// 图的邻接表表示
class Graph {
public:
    unordered_map<int, vector<int>> adjList;

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void printGraph() {
        for (const auto& pair : adjList) {
            cout << pair.first << ": ";
            for (int v : pair.second) {
                cout << v << " ";
            }
            cout << endl;
        }
    }
};

// BFS
void bfs(const Graph& graph, int start) {
    unordered_map<int, bool> visited;
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int neighbor : graph.adjList.at(node)) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}

// DFS
void dfsHelper(const Graph& graph, int node, unordered_map<int, bool>& visited) {
    visited[node] = true;
    cout << node << " ";

    for (int neighbor : graph.adjList.at(node)) {
        if (!visited[neighbor]) {
            dfsHelper(graph, neighbor, visited);
        }
    }
}

void dfsWrapper(const Graph& graph, int start) {
    unordered_map<int, bool> visited;
    dfsHelper(graph, start, visited);
    cout << endl;
}

// Dijkstra
vector<int> dijkstra(const Graph& graph, int start) {
    unordered_map<int, int> dist;
    for (const auto& pair : graph.adjList) {
        dist[pair.first] = INT_MAX;
    }
    dist[start] = 0;

    auto comp = [&dist](int left, int right) { return dist[left] > dist[right]; };
    priority_queue<int, vector<int>, decltype(comp)> pq(comp);

    pq.push(start);

    while (!pq.empty()) {
        int node = pq.top();
        pq.pop();

        for (int neighbor : graph.adjList.at(node)) {
            int newDist = dist[node] + 1;  // 假设每条边的权重是1
            if (newDist < dist[neighbor]) {
                dist[neighbor] = newDist;
                pq.push(neighbor);
            }
        }
    }

    vector<int> result;
    for (const auto& pair : dist) {
        result.push_back(pair.second);
    }
    return result;
}

// 并查集
class UnionFind {
public:
    UnionFind(int size) {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);  // 路径压缩
        }
        return parent[u];
    }

    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV) {
            // 按秩合并
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }

private:
    vector<int> parent;
    vector<int> rank;
};

// Kruskal 算法（最小生成树）
vector<pair<int, int>> kruskal(const Graph& graph) {
    vector<pair<int, pair<int, int>>> edges;
    for (const auto& pair : graph.adjList) {
        int u = pair.first;
        for (int v : pair.second) {
            if (u < v) {
                edges.push_back({1, {u, v}});  // 假设边的权重为1
            }
        }
    }

    sort(edges.begin(), edges.end());  // 按边的权重排序

    UnionFind uf(graph.adjList.size());
    vector<pair<int, int>> mst;  // 仅存储最小生成树的边（无权重）

    for (const auto& edge : edges) {
        int u = edge.second.first;
        int v = edge.second.second;
        if (uf.find(u) != uf.find(v)) {
            uf.unionSets(u, v);
            mst.push_back({u, v});  // 只存储端点
        }
    }

    return mst;
}

// 主函数
int main() {
    Graph graph;

    // 创建一个无向图
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 5);
    graph.addEdge(3, 6);

    // 打印图
    graph.printGraph();

    // BFS
    cout << "BFS Traversal: ";
    bfs(graph, 0);

    // DFS
    cout << "DFS Traversal: ";
    dfsWrapper(graph, 0);

    // Dijkstra
    vector<int> dist = dijkstra(graph, 0);
    cout << "Dijkstra Shortest Path from node 0: ";
    for (int d : dist) {
        cout << d << " ";
    }
    cout << endl;

    // Kruskal
    vector<pair<int, int>> mst = kruskal(graph);
    cout << "Minimum Spanning Tree (Kruskal's Algorithm): ";
    for (const auto& edge : mst) {
        cout << "(" << edge.first << ", " << edge.second << ") ";
    }
    cout << endl;

    return 0;
}
