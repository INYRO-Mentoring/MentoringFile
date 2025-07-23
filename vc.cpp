#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

using namespace std;

const int MAX_NODES = 50;
const int MAX_NAME_LEN = 20;

struct TreeNode {
    string name;
    vector<TreeNode*> children;
    TreeNode* parent;  // 부모 노드 참조 추가

    TreeNode(const string& n) : name(n), parent(nullptr) {}
    
    // 자식 추가 시 부모 설정
    void addChild(TreeNode* child) {
        children.push_back(child);
        child->parent = this;
    }
};

class JoseonDynastyTree {
private:
    unordered_map<string, TreeNode*> nodeMap;  // 빠른 검색을 위한 해시맵
    vector<unique_ptr<TreeNode>> nodes;        // 메모리 관리를 위한 스마트 포인터
    TreeNode* root;
    
    // 왕 이름 목록을 unordered_set으로 변경하여 O(1) 검색
    unordered_map<string, bool> kingSet;

public:
    JoseonDynastyTree() : root(nullptr) {
        // 왕 이름들을 해시셋에 저장
        vector<string> kingNames = {
            "태조", "정종", "태종", "세종", "문종", "단종", "세조", "예종", "성종",
            "연산군", "중종", "인종", "명종", "선조", "광해군", "인조", "효종",
            "현종", "숙종", "경종", "영조", "정조", "순조", "헌종", "철종", "고종", "순종"
        };
        
        for (const auto& name : kingNames) {
            kingSet[name] = true;
        }
    }

    // O(1) 시간복잡도로 노드 찾기
    TreeNode* findNode(const string& name) {
        auto it = nodeMap.find(name);
        return (it != nodeMap.end()) ? it->second : nullptr;
    }

    // 노드 생성 또는 찾기
    TreeNode* findOrCreateNode(const string& name) {
        TreeNode* node = findNode(name);
        if (node) return node;
        
        auto newNode = make_unique<TreeNode>(name);
        TreeNode* rawPtr = newNode.get();
        nodes.push_back(move(newNode));
        nodeMap[name] = rawPtr;
        return rawPtr;
    }

    void buildTree() {
        vector<pair<string, string>> data = {
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

        for (const auto& [childName, parentName] : data) {
            TreeNode* child = findOrCreateNode(childName);
            
            if (parentName.empty()) {
                root = child;
            } else {
                TreeNode* parent = findOrCreateNode(parentName);
                parent->addChild(child);
            }
        }
    }

    // 트리 예쁘게 출력
    void printTreePretty(TreeNode* node = nullptr, const string& prefix = "", bool isLast = true) {
        if (!node) node = root;
        if (!node) return;

        cout << prefix;
        cout << (isLast ? "└─ " : "├─ ");
        cout << node->name << endl;

        string nextPrefix = prefix + (isLast ? "   " : "│  ");

        for (size_t i = 0; i < node->children.size(); ++i) {
            bool childIsLast = (i == node->children.size() - 1);
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

    void printKingsInOrder() {
        vector<string> result;
        collectKingsInOrder(root, result);
        for (const auto& name : result) {
            cout << name << endl;
        }
    }

    // 2. 조선의 왕을 역순으로 출력
    void printKingsInReverseOrder() {
        vector<string> result;
        collectKingsInOrder(root, result);
        for (auto it = result.rbegin(); it != result.rend(); ++it) {
            cout << *it << endl;
        }
    }

    // 3. 조선의 왕 수
    int countKings(TreeNode* node = nullptr) {
        if (!node) node = root;
        if (!node) return 0;
        
        int count = 1;
        for (auto child : node->children) {
            count += countKings(child);
        }
        return count;
    }

    // 4. 특정 왕의 후손 출력
    void printDescendants(const string& ancestorName) {
        TreeNode* ancestor = findNode(ancestorName);
        if (!ancestor) {
            cout << ancestorName << "을(를) 찾을 수 없습니다." << endl;
            return;
        }
        printDescendantsHelper(ancestor);
    }

private:
    void printDescendantsHelper(TreeNode* node) {
        for (auto child : node->children) {
            cout << child->name << endl;
            printDescendantsHelper(child);
        }
    }

    bool isKing(const string& name) {
        return kingSet.find(name) != kingSet.end();
    }

    bool hasRoyalChild(TreeNode* node) {
        for (auto child : node->children) {
            if (isKing(child->name)) return true;
        }
        return false;
    }

    int countRoyalChildren(TreeNode* node) {
        int count = 0;
        for (auto child : node->children) {
            if (isKing(child->name)) count++;
        }
        return count;
    }

public:
    // 5. 직계 후손이 왕이 되지 못한 왕들 출력
    void printKingsWithNoRoyalChildren(TreeNode* node = nullptr) {
        if (!node) node = root;
        if (!node) return;

        if (!hasRoyalChild(node) && isKing(node->name)) {
            cout << node->name << endl;
        }

        for (auto child : node->children) {
            printKingsWithNoRoyalChildren(child);
        }
    }

    // 6. 직계 후손 중 왕이 가장 많은 왕
    void printKingWithMostRoyalDescendants() {
        TreeNode* result = nullptr;
        int maxCount = 0;
        findKingWithMostRoyalChildren(root, result, maxCount);

        if (result) {
            cout << result->name << " (" << maxCount << "명)" << endl;
        }
    }

private:
    void findKingWithMostRoyalChildren(TreeNode* node, TreeNode*& result, int& maxCount) {
        if (!node) return;

        int royalCount = countRoyalChildren(node);
        if (royalCount > maxCount && isKing(node->name)) {
            maxCount = royalCount;
            result = node;
        }

        for (auto child : node->children) {
            findKingWithMostRoyalChildren(child, result, maxCount);
        }
    }

public:
    // 7. 특정 왕의 형제로 왕이 된 사람들
    void printSiblingsWhoAreKings(const string& targetName) {
        TreeNode* target = findNode(targetName);
        if (!target || !target->parent) {
            cout << targetName << "의 형제를 찾을 수 없습니다." << endl;
            return;
        }

        TreeNode* parent = target->parent;
        for (auto sibling : parent->children) {
            if (sibling != target && isKing(sibling->name)) {
                cout << sibling->name << endl;
            }
        }
    }

    // 8. 특정 왕의 직계 선조 모두 출력
    void printAncestors(const string& descendantName) {
        TreeNode* current = findNode(descendantName);
        if (!current) {
            cout << descendantName << "을(를) 찾을 수 없습니다." << endl;
            return;
        }

        vector<string> ancestors;
        TreeNode* parent = current->parent;
        
        while (parent) {
            ancestors.push_back(parent->name);
            parent = parent->parent;
        }

        for (const auto& ancestor : ancestors) {
            cout << ancestor << endl;
        }
    }

    // 9. 직계 후손이 2명 이상 왕이 된 왕 수
    int countKingsWithMultipleRoyalChildren(TreeNode* node = nullptr) {
        if (!node) node = root;
        if (!node) return 0;

        int count = 0;
        int royalChildCount = countRoyalChildren(node);

        if (royalChildCount >= 2 && isKing(node->name)) {
            cout << node->name << " (" << royalChildCount << "명)" << endl;
            count++;
        }

        for (auto child : node->children) {
            count += countKingsWithMultipleRoyalChildren(child);
        }

        return count;
    }

    // 10. 특정 왕은 다른 왕의 몇 대 후손인가?
    int getGenerationDistance(const string& ancestorName, const string& descendantName) {
        TreeNode* ancestor = findNode(ancestorName);
        if (!ancestor) return -1;
        
        return generationDistanceHelper(ancestor, descendantName);
    }

private:
    int generationDistanceHelper(TreeNode* ancestor, const string& descendantName) {
        if (!ancestor) return -1;
        if (ancestor->name == descendantName) return 0;

        for (auto child : ancestor->children) {
            int dist = generationDistanceHelper(child, descendantName);
            if (dist != -1) {
                return dist + 1;
            }
        }

        return -1; // 후손이 아님
    }

public:
    TreeNode* getRoot() { return root; }
};

int main() {
    JoseonDynastyTree tree;
    tree.buildTree();
    
    cout << "조선 왕조 트리:" << endl;
    tree.printTreePretty();
    
    cout << "\n1. 조선의 왕을 순서대로 출력하시오.\n";
    tree.printKingsInOrder();

    cout << "\n2. 조선의 왕을 역순으로 출력하시오.\n";
    tree.printKingsInReverseOrder();
   
    cout << "\n3. 조선의 왕은 모두 몇 명인가?\n";
    cout << tree.countKings() << "명" << endl;
    
    cout << "\n4. 조선의 왕 중에서 인조의 후손은 누구누구인가?\n";
    tree.printDescendants("인조");

    cout << "\n5. 직계 후손이 왕이 되지 못한 왕은 누구누구인가?\n";
    tree.printKingsWithNoRoyalChildren();

    cout << "\n6. 직계 후손이 왕이 된 수가 가장 많은 왕은 누구인가?\n";
    tree.printKingWithMostRoyalDescendants();

    cout << "\n7. 정종의 형제로 조선의 왕이 된 사람은 누구인가?\n";
    tree.printSiblingsWhoAreKings("정종");

    cout << "\n8. 순종의 직계 선조를 모두 출력하시오.\n";
    tree.printAncestors("순종");

    cout << "\n9. 직계 후손이 2명 이상 왕이 된 왕은 몇 명인가?\n";
    int result = tree.countKingsWithMultipleRoyalChildren();
    cout << "총 " << result << "명" << endl;

    cout << "\n10. 예종은 태종의 몇 대 후손인가?" << endl;
    int dist = tree.getGenerationDistance("태종", "예종");

    if (dist == -1) {
        cout << "예종은 태종의 후손이 아닙니다." << endl;
    } else {
        cout << dist << "대 후손" << endl;
    }
    
    return 0;
}
