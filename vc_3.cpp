#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct TreeNode {
    string name;
    vector<TreeNode*> children;
    TreeNode(string n) : name(n) {}
};

map<string, TreeNode*> nodeMap;
TreeNode* root = nullptr;

void printTree(TreeNode* node, int depth = 0) {
    if (!node) return;
    for (int i = 0; i < depth; ++i) cout << "  ";
    cout << node->name << endl;
    for (auto child : node->children) {
        printTree(child, depth + 1);
    }
}

// 1. 조선의 왕을 순서대로 출력
void printKingsInOrder(TreeNode* node) {
    if (!node) return;
    cout << node->name << endl;
    for (auto child : node->children) {
        printKingsInOrder(child);
    }
}

// 2. 조선의 왕을 역순으로 출력
void printKingsInReverseOrder(TreeNode* node) {
    if (!node) return;

    vector<string> result;
    function<void(TreeNode*)> dfs = [&](TreeNode* curr) {
        if (!curr) return;
        result.push_back(curr->name);
        for (auto child : curr->children) {
            dfs(child);
        }
    };

    dfs(node);
    reverse(result.begin(), result.end());
    for (const string& name : result) {
        cout << name << endl;
    }
}

// 3. 조선의 왕 수
int countKings(TreeNode* node) {
    if (!node) return 0;
    
    int count = 1; // 자기 자신
    for (auto child : node->children) {
        count += countKings(child);
    }
    return count;
}

// 4. 인조의 후손 출력
void printDescendants(TreeNode* node) {
    if (!node) return;
    for (auto child : node->children) {
        cout << child->name << endl;
        printDescendants(child);
    }
}

void printDescendantsOfInjo(TreeNode* root) {
    TreeNode* injo = nodeMap["인조"];
    if (!injo) {
        cout << "인조를 찾을 수 없습니다." << endl;
        return;
    }

    printDescendants(injo);
}

// 5. 직계 후손이 왕이 되지 못한 왕들 출력
bool isKing(TreeNode* node) {
    return nodeMap.find(node->name) != nodeMap.end();
}

bool hasRoyalChild(TreeNode* node) {
    for (auto child : node->children) {
        if (isKing(child)) return true;
    }
    return false;
}

void printKingsWithNoRoyalChildren(TreeNode* node) {
    if (!node) return;

    if (!hasRoyalChild(node)) {
        cout << node->name << endl;
    }

    for (auto child : node->children) {
        printKingsWithNoRoyalChildren(child);
    }
}

// 6. 직계 후손 중 왕이 가장 많은 왕
int countRoyalChildren(TreeNode* node) {
    int count = 0;
    for (auto child : node->children) {
        if (nodeMap.find(child->name) != nodeMap.end()) {
            count++;
        }
    }
    return count;
}

void printKingWithMostRoyalDescendants(TreeNode* node) {
    if (!node) return;

    string maxKing;
    int maxCount = 0;

    function<void(TreeNode*)> dfs = [&](TreeNode* cur) {
        int royalChildren = countRoyalChildren(cur);
        if (royalChildren > maxCount) {
            maxCount = royalChildren;
            maxKing = cur->name;
        }
        for (auto child : cur->children) {
            dfs(child);
        }
    };

    dfs(node);

    cout << maxKing << " (" << maxCount << "명)" << endl;
}

// 7. 정종의 형제로 왕이 된 사람
void printSiblingsOfJeongjongWhoBecameKing(TreeNode* root) {
    TreeNode* jeongjong = nodeMap["정종"];
    if (!jeongjong) {
        cout << "정종을 찾을 수 없습니다." << endl;
        return;
    }

    // 정종의 부모를 찾아야 함
    TreeNode* parent = nullptr;
    for (const auto& [name, node] : nodeMap) {
        for (auto child : node->children) {
            if (child == jeongjong) {
                parent = node;
                break;
            }
        }
        if (parent) break;
    }

    if (!parent) {
        cout << "정종의 부모를 찾을 수 없습니다." << endl;
        return;
    }

    for (auto sibling : parent->children) {
        if (sibling->name != "정종") {
            cout << sibling->name << endl;
        }
    }
}


// 8. 순종의 직계 선조 모두 출력
void printAncestorsOfSunjong(TreeNode* root) {
    TreeNode* current = nodeMap["순종"];
    if (!current) {
        cout << "순종을 찾을 수 없습니다." << endl;
        return;
    }

    vector<string> ancestors;

    while (true) {
        TreeNode* parent = nullptr;
        for (const auto& [name, node] : nodeMap) {
            for (auto child : node->children) {
                if (child == current) {
                    parent = node;
                    break;
                }
            }
            if (parent) break;
        }

        if (!parent) break;
        ancestors.push_back(parent->name);
        current = parent;
    }

    for (const string& name : ancestors) {
        cout << name << endl;
    }
}


// 9. 직계 후손이 2명 이상 왕이 된 왕 수
int countKingsWithMultipleRoyalChildren(TreeNode* node) {
    if (!node) return 0;

    int count = 0;
    int royalChildCount = countRoyalChildren(node);

    if (royalChildCount >= 2) {
        cout << node->name << " (" << royalChildCount << "명의 자식이 왕이 됨)" << endl;
        count++;
    }

    for (auto child : node->children) {
        count += countKingsWithMultipleRoyalChildren(child);
    }

    return count;
}

// 10. 예종은 태종의 몇 대 후손인가?
int generationDistance(TreeNode* ancestor, const string& descendantName) {
    if (!ancestor) return -1;
    if (ancestor->name == descendantName) return 0;

    for (auto child : ancestor->children) {
        int dist = generationDistance(child, descendantName);
        if (dist != -1) {
            return dist + 1;
        }
    }

    return -1; // 후손이 아님
}

// 앞뒤 공백 제거
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    return (first == string::npos) ? "" : str.substr(first, last - first + 1);
}

int main() {
    ifstream file("/Users/yse/Desktop/바이브 코딩/vive_coding/vive_coding/조선왕조.txt");
    if (!file.is_open()) {
        cerr << "파일 열기 실패" << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        line = trim(line);
        if (line.empty()) continue;

        istringstream iss(line);
        string child, parent;
        iss >> child;
        if (!(iss >> parent)) {
            // 부모가 없는 경우 (태조)
            if (nodeMap.find(child) == nodeMap.end())
                nodeMap[child] = new TreeNode(child);
            root = nodeMap[child];
        } else {
            if (nodeMap.find(parent) == nodeMap.end())
                nodeMap[parent] = new TreeNode(parent);
            if (nodeMap.find(child) == nodeMap.end())
                nodeMap[child] = new TreeNode(child);
            nodeMap[parent]->children.push_back(nodeMap[child]);
        }
    }

    file.close();

    cout << "조선 왕조 계보 트리:" << endl;
    printTree(root);
    
    cout << "\n1. 조선의 왕을 순서대로 출력하시오.\n";
    printKingsInOrder(root);

    cout << "\n2. 조선의 왕을 역순으로 출력하시오.\n";
    printKingsInReverseOrder(root);
   
    cout << "\n3. 조선의 왕은 모두 몇 명인가?\n";
    cout << countKings(root) << "명" << endl;
    
    cout << "\n4. 조선의 왕 중에서 인조의 후손은 누구누구인가?\n";
    printDescendantsOfInjo(root);

    cout << "\n5. 직계 후손이 왕이 되지 못한 왕은 누구누구인가?\n";
    printKingsWithNoRoyalChildren(root);

    cout << "\n6. 직계 후손이 왕이 된 수가 가장 많은 왕은 누구인가?\n";
    printKingWithMostRoyalDescendants(root);

    cout << "\n7. 정종의 형제로 조선의 왕이 된 사람은 누구인가?\n";
    printSiblingsOfJeongjongWhoBecameKing(root);

    cout << "\n8. 순종의 직계 선조를 모두 출력하시오.\n";
    printAncestorsOfSunjong(root);

    cout << "\n9. 직계 후손이 2명 이상 왕이 된 왕은 몇 명인가?\n";
    cout << countKingsWithMultipleRoyalChildren(root) << "명" << endl;

    cout << "\n10. 예종은 태종의 몇 대 후손인가?\n";
    cout << generationDistance(nodeMap["태종"], "예종") << "대 후손" << endl;

    return 0;
}
