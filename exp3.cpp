#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <cstring>
#include <functional>
#include <algorithm>

// 位图类定义
class Bitmap {
private:
    unsigned char* M;
    int N, _sz;
protected:
    void init(int n) {
        M = new unsigned char[N = (n + 7) / 8];
        memset(M, 0, N);
        _sz = 0;
    }
public:
    Bitmap(int n = 8) { init(n); }
    Bitmap(char* file, int n = 8) {
        init(n);
        FILE* fp = fopen(file, "r");
        fread(M, sizeof(char), N, fp);
        fclose(fp);
        for (int k = 0, _sz = 0; k < n; k++) _sz += test(k);
    }
    ~Bitmap() {
        delete[] M;
        M = nullptr;
        _sz = 0;
    }
    int size() { return _sz; }
    void set(int k) { expand(k); _sz++; M[k >> 3] |= (0x80 >> (k & 0x07)); }
    void clear(int k) { expand(k); _sz--; M[k >> 3] &= ~(0x80 >> (k & 0x07)); }
    bool test(int k) { expand(k); return M[k >> 3] & (0x80 >> (k & 0x07)); }
    void dump(char* file) {
        FILE* fp = fopen(file, "w");
        fwrite(M, sizeof(char), N, fp);
        fclose(fp);
    }
    char* bits2string(int n) {
        expand(n - 1);
        char* s = new char[n + 1];
        s[n] = '\0';
        for (int i = 0; i < n; i++) s[i] = test(i)? '1' : '0';
        return s;
    }
    void expand(int k) {
        if (k < 8 * N) return;
        int oldN = N;
        unsigned char* oldM = M;
        init(2 * k);
        memcpy_s(M, N, oldM, oldN);
        delete[] oldM;
    }
};

// 二叉树节点结构体
struct BinTreeNode {
    char data;
    int freq;
    BinTreeNode* left;
    BinTreeNode* right;

    BinTreeNode(char d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}
};

// 二叉树类
class BinTree {
public:
    BinTreeNode* root;

    BinTree() : root(nullptr) {}

    // 插入节点
    void insert(char data, int freq) {
        root = insertRecursive(root, data, freq);
    }

private:
    BinTreeNode* insertRecursive(BinTreeNode* node, char data, int freq) {
        if (node == nullptr) {
            return new BinTreeNode(data, freq);
        }
        if (freq < node->freq) {
            node->left = insertRecursive(node->left, data, freq);
        }
        else {
            node->right = insertRecursive(node->right, data, freq);
        }
        return node;
    }
};

// 构建 Huffman 树
class HuffTree {
public:
    BinTreeNode* buildHuffmanTree(const std::unordered_map<char, int>& freqMap) {
        auto cmp = [](BinTreeNode* a, BinTreeNode* b) {
            return a->freq > b->freq;
        };
        std::priority_queue<BinTreeNode*, std::vector<BinTreeNode*>, decltype(cmp)> pq(cmp);

        for (const auto& pair : freqMap) {
            pq.push(new BinTreeNode(pair.first, pair.second));
        }

        while (pq.size() > 1) {
            BinTreeNode* left = pq.top();
            pq.pop();
            BinTreeNode* right = pq.top();
            pq.pop();

            BinTreeNode* newNode = new BinTreeNode('\0', left->freq + right->freq);
            newNode->left = left;
            newNode->right = right;

            pq.push(newNode);
        }

        if (!pq.empty()) {
            return pq.top();
        } else {
            return nullptr;
        }
    }
};

// Huffman 二进制编码串类型
class HuffCode {
public:
    std::string code;

    HuffCode() = default;
    HuffCode(const std::string& c) : code(c) {}
};

// Huffman 编码算法
class HuffmanCoding {
public:
    std::unordered_map<char, HuffCode> encode(const std::string& filePath) {
        std::unordered_map<char, int> freqMap;
        std::ifstream file(filePath);
        char c;
        while (file.get(c)) {
            if (isalpha(c)) {
                c = tolower(c);
                freqMap[c]++;
            }
        }
        file.close();

        HuffTree huffTree;
        BinTreeNode* root = huffTree.buildHuffmanTree(freqMap);

        std::unordered_map<char, std::string> codes;
        generateCodes(root, "", codes);

        std::unordered_map<char, HuffCode> huffCodes;
        for (const auto& pair : codes) {
            huffCodes[pair.first] = HuffCode(pair.second);
        }

        return huffCodes;
    }

private:
    void generateCodes(BinTreeNode* node, const std::string& code, std::unordered_map<char, std::string>& codes) {
        if (node == nullptr) {
            return;
        }

        if (node->data!= '\0') {
            codes[node->data] = code;
        }

        generateCodes(node->left, code + "0", codes);
        generateCodes(node->right, code + "1", codes);
    }
};

int main() {
    std::string filePath = "D:\\code\\C++\\.tree\\I have a dream.txt";
    HuffmanCoding huffmanCoding;
    std::unordered_map<char, HuffCode> huffCodes = huffmanCoding.encode(filePath);

    // 存储字母顺序的数组
    char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    // 按照字母顺序输出
    for (char c : alphabet) {
        if (huffCodes.find(c)!= huffCodes.end()) {
            std::cout << "Character: " << c << ", Frequency: " << huffCodes[c].code << std::endl;
        }
    }

    return 0;
}