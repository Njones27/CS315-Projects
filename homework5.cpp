#include <iostream>

using namespace std;

class Node {
public:
    explicit Node(int value)
        : first(value), hasSecond(false), second(0), left(nullptr), middle(nullptr), right(nullptr) {}

    void addValue(int value) {
        if (hasSecond) {
            return;
        }
        if (value < first) {
            second = first;
            first = value;
        } else {
            second = value;
        }
        hasSecond = true;
    }

    bool isTwoValued() const { return hasSecond; }

    int first;
    bool hasSecond;
    int second;
    Node* left;
    Node* middle;
    Node* right;
};

class TernaryTree {
public:
    TernaryTree() : root(nullptr) {}

    ~TernaryTree() { clear(root); }

    void insert(int value) { root = insert(root, value); }

    void printInorder() const {
        inorder(root);
        cout << '\n';
    }

private:
    Node* insert(Node* node, int value) {
        if (!node) {
            return new Node(value);
        }

        if (!node->isTwoValued()) {
            node->addValue(value);
            return node;
        }

        if (value <= node->first) {
            node->left = insert(node->left, value);
        } else if (value <= node->second) {
            node->middle = insert(node->middle, value);
        } else {
            node->right = insert(node->right, value);
        }

        return node;
    }

    void inorder(const Node* node) const {
        if (!node) {
            return;
        }

        if (node->isTwoValued()) {
            if (node->left) {
                cout << '(';
                inorder(node->left);
                cout << ')';
                cout << ' ';
            }

            cout << node->first;
            cout << ' ';

            if (node->middle) {
                cout << '(';
                inorder(node->middle);
                cout << ')';
                cout << ' ';
            }

            
            if (node->right) {
                cout << node->second;
                cout << ' ';
                cout << '(';
                inorder(node->right);
                cout << ')';
            }
        } else {
            cout << node->first;
        }
    }

    void clear(Node* node) {
        if (!node) {
            return;
        }
        clear(node->left);
        clear(node->middle);
        clear(node->right);
        delete node;
    }

    Node* root;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    TernaryTree tree;
    for (int i = 0; i < n; ++i) {
        int value;
        if (!(cin >> value)) {
            break;
        }
        tree.insert(value);
    }

    tree.printInorder();
    return 0;
}
