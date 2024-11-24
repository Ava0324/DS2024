#include <iostream>
#include <vector>

// 图的模板类
template <typename T>
class Graph {
private:
    // 用邻接表来表示图，每个顶点对应一个邻接顶点的列表
    std::vector<std::vector<T>> adjList;

public:
    // 构造函数，初始化一个空图
    Graph() {}

    // 添加顶点到图中
    void addVertex(const T& vertex) {
        // 在邻接表中添加一个新的空列表，表示新顶点的邻接顶点列表
        adjList.push_back(std::vector<T>());
        // 给新添加的顶点对应的列表添加一个特殊标记值 -1 来表示初始状态
        adjList.back().push_back(-1);
    }

    // 添加边连接两个顶点
    void addEdge(const T& vertex1, const T& vertex2) {
        // 找到两个顶点在邻接表中的索引
        int index1 = getIndex(vertex1);
        int index2 = getIndex(vertex2);

        if (index1!= -1 && index2!= -1) {
            // 在两个顶点的邻接列表中互相添加对方
            adjList[index1].push_back(vertex2);
            adjList[index2].push_back(vertex1);
        } else {
            std::cout << "One or both vertices not found in the graph." << std::endl;
        }
    }

    // 辅助函数，用于获取顶点在邻接表中的索引
    int getIndex(const T& vertex) {
        for (size_t i = 0; i < adjList.size(); ++i) {
            if (adjList[i][0] == vertex) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    // 遍历图并打印每个顶点及其邻接顶点
    void printGraph() {
        // 先检查adjList是否为空，避免空指针访问
        if (adjList.empty()) {
            std::cout << "Graph is empty." << std::endl;
            return;
        }

        for (size_t i = 0; i < adjList.size(); ++i) {
            // 检查每个顶点对应的邻接列表是否为空，避免空指针访问
            if (!adjList[i].empty()) {
                std::cout << adjList[i][0] << " -> ";
                for (size_t j = 1; j < adjList[i].size(); ++j) {
                    std::cout << adjList[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
    }

    // 检查索引是否在有效范围内的辅助函数
    bool isIndexValid(int index) {
        return index >= 0 && index < static_cast<int>(adjList.size());
    }
};
