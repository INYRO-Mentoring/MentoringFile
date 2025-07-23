#include <iostream>
#include <cstring>

using namespace std;

const int MAX_NODES = 50;
const int MAX_NAME_LEN = 20;

struct TreeNode {
    char name[MAX_NAME_LEN];
    TreeNode* children[MAX_NODES];
    int childCount;

    TreeNode(const char* n) {
        strncpy(name, n, MAX_NAME_LEN);
        name[MAX_NAME_LEN - 1] = '\0';
        childCount = 0;
    }
};

TreeNode* nodeList[MAX_NODES];
int nodeCount = 0;
TreeNode* root = nullptr;

TreeNode* findOrCreateNode(const char* name) {
    for (int i = 0; i < nodeCount; ++i) {
        if (strcmp(nodeList[i]->name, name) == 0) {
            return nodeList[i];
        }
    }
    TreeNode* newNode = new TreeNode(name);
    nodeList[nodeCount++] = newNode;
    return newNode;
}

void buildTree() {
    const char* data[][2] = {
        {"태조", ""},
        {"정종", "태조"},
        {"태종", "태조"},
        {"세종", "태종"},
        {"문종", "세종"},
        {"단종", "문종"},
        {"세조", "세종"},
        {"예종", "세조"},
        {"성종", "세조"},
        {"연산군", "성종"},
        {"중종", "성종"},
        {"인종", "중종"},
        {"명종", "중종"},
        {"선조", "중종"},
        {"광해군", "선조"},
        {"인조", "선조"},
        {"효종", "인조"},
        {"현종", "효종"},
        {"숙종", "현종"},
        {"경종", "숙종"},
        {"영조", "숙종"},
        {"정조", "영조"},
        {"순조", "정조"},
        {"헌종", "순조"},
        {"철종", "영조"},
        {"고종", "인조"},
        {"순종", "고종"}
    };

    int n = sizeof(data) / sizeof(data[0]);

    for (int i = 0; i < n; ++i) {
        const char* childName = data[i][0];
        const char* parentName = data[i][1];

        TreeNode* child = findOrCreateNode(childName);

        if (strlen(parentName) == 0) {
            root = child;
        } else {
            TreeNode* parent = findOrCreateNode(parentName);
            parent->children[parent->childCount++] = child;
        }
    }
}

void printTreePretty(TreeNode* node, const char* prefix = "", bool isLast = true) {
    if (!node) return;

    // └─ or ├─
    cout << prefix;
    cout << (isLast ? "└─ " : "├─ ");
    cout << node->name << endl;

    // 다음 prefix: "   " or "│  "
    char nextPrefix[100];
    strcpy(nextPrefix, prefix);
    strcat(nextPrefix, isLast ? "   " : "│  ");

    for (int i = 0; i < node->childCount; ++i) {
        bool childIsLast = (i == node->childCount - 1);
        printTreePretty(node->children[i], nextPrefix, childIsLast);
    }
}

// 1. 조선의 왕을 순서대로 출력
void collectKingsInOrder(TreeNode* node, vector<string>& result) {
    if (!node) return;
    result.push_back(node->name);
    for (auto child : node->children) {
        collectKingsInOrder(child, result);
    }
}

void printKingsInOrder(TreeNode* node) {
    if (!node) return;
    cout << node->name << endl;
    for (int i = 0; i < node->childCount; ++i) {
        printKingsInOrder(node->children[i]);
    }
}

// 2. 조선의 왕을 역순으로 출력
void collectKings(TreeNode* node, char result[][MAX_NAME_LEN], int& count) {
    if (!node) return;

    strncpy(result[count], node->name, MAX_NAME_LEN);
    result[count][MAX_NAME_LEN - 1] = '\0'; // 안전
    count++;

    for (int i = 0; i < node->childCount; ++i) {
        collectKings(node->children[i], result, count);
    }
}

void printKingsInReverseOrder(TreeNode* node) {
    char result[MAX_NODES][MAX_NAME_LEN];
    int count = 0;

    collectKings(node, result, count);

    for (int i = count - 1; i >= 0; --i) {
        cout << result[i] << endl;
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
// 문자열로 노드 찾기
TreeNode* findNodeByName(const char* name) {
    for (int i = 0; i < nodeCount; ++i) {
        if (strcmp(nodeList[i]->name, name) == 0) {
            return nodeList[i];
        }
    }
    return nullptr;
}

void printDescendants(TreeNode* node) {
    if (!node) return;

    for (int i = 0; i < node->childCount; ++i) {
        cout << node->children[i]->name << endl;
        printDescendants(node->children[i]);
    }
}

void printDescendantsOfInjo() {
    TreeNode* injo = findNodeByName("인조");
    if (!injo) {
        cout << "인조를 찾을 수 없습니다." << endl;
        return;
    }

    printDescendants(injo);
}

// 5, 6번 문제에서 사용
// 왕 이름 목록
const char* kingNames[] = {
    "태조", "정종", "태종", "세종", "문종", "단종", "세조", "예종", "성종",
    "연산군", "중종", "인종", "명종", "선조", "광해군", "인조", "효종",
    "현종", "숙종", "경종", "영조", "정조", "순조", "헌종", "철종", "고종", "순종"
};

const int kingCount = sizeof(kingNames) / sizeof(kingNames[0]);

// 이름이 왕인지 판단
bool isKing(TreeNode* node) {
    for (int i = 0; i < kingCount; ++i) {
        if (strcmp(node->name, kingNames[i]) == 0) return true;
    }
    return false;
}

// 5. 직계 후손이 왕이 되지 못한 왕들 출력
// 자식 중 왕이 있는지 판단
bool hasRoyalChild(TreeNode* node) {
    for (int i = 0; i < node->childCount; ++i) {
        if (isKing(node->children[i])) return true;
    }
    return false;
}

// 조건에 맞는 왕 출력
void printKingsWithNoRoyalChildren(TreeNode* node) {
    if (!node) return;

    if (!hasRoyalChild(node) && isKing(node)) {
        cout << node->name << endl;
    }

    for (int i = 0; i < node->childCount; ++i) {
        printKingsWithNoRoyalChildren(node->children[i]);
    }
}

// 6. 직계 후손 중 왕이 가장 많은 왕
int countRoyalChildren(TreeNode* node) {
    int count = 0;
    for (int i = 0; i < node->childCount; ++i) {
        if (isKing(node->children[i])) {
            count++;
        }
    }
    return count;
}

void findKingWithMostRoyalChildren(TreeNode* node, TreeNode*& result, int& maxCount) {
    if (!node) return;

    int royalCount = countRoyalChildren(node);
    if (royalCount > maxCount) {
        maxCount = royalCount;
        result = node;
    }

    for (int i = 0; i < node->childCount; ++i) {
        findKingWithMostRoyalChildren(node->children[i], result, maxCount);
    }
}

void printKingWithMostRoyalDescendants(TreeNode* root) {
    TreeNode* result = nullptr;
    int maxCount = 0;
    findKingWithMostRoyalChildren(root, result, maxCount);

    if (result) {
        cout << result->name << " (" << maxCount << "명)" << endl;
    }
}

// 7. 정종의 형제로 왕이 된 사람
void printSiblingsOfJeongjongWhoBecameKing(TreeNode* root) {
    TreeNode* jeongjong = findNodeByName("정종");
    if (!jeongjong) {
        cout << "정종을 찾을 수 없습니다." << endl;
        return;
    }

    // 정종의 부모 찾기
    TreeNode* parent = nullptr;
    for (int i = 0; i < nodeCount; ++i) {
        TreeNode* candidate = nodeList[i];
        for (int j = 0; j < candidate->childCount; ++j) {
            if (candidate->children[j] == jeongjong) {
                parent = candidate;
                break;
            }
        }
        if (parent) break;
    }

    if (!parent) {
        cout << "정종의 부모를 찾을 수 없습니다." << endl;
        return;
    }

    for (int i = 0; i < parent->childCount; ++i) {
        TreeNode* sibling = parent->children[i];
        if (sibling != jeongjong && isKing(sibling)) {
            cout << sibling->name << endl;
        }
    }
}

// 8. 순종의 직계 선조 모두 출력
void printAncestorsOfSunjong(TreeNode* root) {
    TreeNode* current = findNodeByName("순종");
    if (!current) {
        cout << "순종을 찾을 수 없습니다." << endl;
        return;
    }

    char ancestors[MAX_NODES][MAX_NAME_LEN];
    int count = 0;

    while (true) {
        TreeNode* parent = nullptr;

        for (int i = 0; i < nodeCount; ++i) {
            TreeNode* candidate = nodeList[i];
            for (int j = 0; j < candidate->childCount; ++j) {
                if (candidate->children[j] == current) {
                    parent = candidate;
                    break;
                }
            }
            if (parent) break;
        }

        if (!parent) break;

        strncpy(ancestors[count], parent->name, MAX_NAME_LEN);
        ancestors[count][MAX_NAME_LEN - 1] = '\0';
        count++;
        current = parent;
    }

    for (int i = 0; i < count; ++i) {
        cout << ancestors[i] << endl;
    }
}

// 9. 직계 후손이 2명 이상 왕이 된 왕 수
int countKingsWithMultipleRoyalChildren(TreeNode* node) {
    if (!node) return 0;

    int count = 0;
    int royalChildCount = countRoyalChildren(node);

    if (royalChildCount >= 2 && isKing(node)) {
        cout << node->name << " (" << royalChildCount << "명)" << endl;
        count++;
    }

    for (int i = 0; i < node->childCount; ++i) {
        count += countKingsWithMultipleRoyalChildren(node->children[i]);
    }

    return count;
}

// 10. 예종은 태종의 몇 대 후손인가?
int generationDistance(TreeNode* ancestor, const char* descendantName) {
    if (!ancestor) return -1;
    if (strcmp(ancestor->name, descendantName) == 0) return 0;

    for (int i = 0; i < ancestor->childCount; ++i) {
        int dist = generationDistance(ancestor->children[i], descendantName);
        if (dist != -1) {
            return dist + 1;
        }
    }

    return -1; // 후손이 아님
}

int main() {
    buildTree();
    
    cout << "조선 왕조 트리:" << endl;
    printTreePretty(root, "", true);
    
    cout << "\n1. 조선의 왕을 순서대로 출력하시오.\n";
    printKingsInOrder(root);

    cout << "\n2. 조선의 왕을 역순으로 출력하시오.\n";
    printKingsInReverseOrder(root);
   
    cout << "\n3. 조선의 왕은 모두 몇 명인가?\n";
    cout << countKings(root) << "명" << endl;
    
    cout << "\n4. 조선의 왕 중에서 인조의 후손은 누구누구인가?\n";
    printDescendantsOfInjo();

    cout << "\n5. 직계 후손이 왕이 되지 못한 왕은 누구누구인가?\n";
    printKingsWithNoRoyalChildren(root);

    cout << "\n6. 직계 후손이 왕이 된 수가 가장 많은 왕은 누구인가?\n";
    printKingWithMostRoyalDescendants(root);

    cout << "\n7. 정종의 형제로 조선의 왕이 된 사람은 누구인가?\n";
    printSiblingsOfJeongjongWhoBecameKing(root);

    cout << "\n8. 순종의 직계 선조를 모두 출력하시오.\n";
    printAncestorsOfSunjong(root);

    cout << "\n9. 직계 후손이 2명 이상 왕이 된 왕은 몇 명인가?\n";
    int result = countKingsWithMultipleRoyalChildren(root);
    cout << "총 " << result << "명" << endl;
    cout << endl;

    cout << "10. 예종은 태종의 몇 대 후손인가?" << endl;
    TreeNode* taejong = findNodeByName("태종");
    int dist = generationDistance(taejong, "예종");

    if (dist == -1) {
        cout << "예종은 태종의 후손이 아닙니다." << endl;
    } else {
        cout << dist << "대 후손" << endl;
    }
    
    return 0;
}
