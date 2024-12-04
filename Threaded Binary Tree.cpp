/*
Implement In-order Threaded Binary Tree and traverse it in In-order and Pre-order.
*/

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    bool leftThread;
    bool rightThread;

    Node(int val) {
        data = val;
        left = right = nullptr;
        leftThread = rightThread = false;
    }
};

class ThreadedBinaryTree {
public:
    Node* root;
    
    ThreadedBinaryTree() {
        root = nullptr;
    }

    void insert(int value) {
        if (root == nullptr) {
            root = new Node(value);
        } else {
            insertRec(root, value);
        }
    }

    void insertRec(Node* root, int value) {
        if (value < root->data) {
            if (root->left == nullptr) {
                root->left = new Node(value);
                root->leftThread = false;
                root->left->right = root;
                root->left->rightThread = true;
            } else {
                insertRec(root->left, value);
            }
        } else if (value > root->data) {
            if (root->right == nullptr) {
                root->right = new Node(value);
                root->rightThread = false;
                root->right->left = root;
                root->right->leftThread = true;
            } else {
                insertRec(root->right, value);
            }
        }
    }

    void inorderTraversal() {
        Node* curr = root;
        while (curr != nullptr) {
            while (curr->left != nullptr && !curr->leftThread) {
                curr = curr->left;
            }
            cout << curr->data << " ";
            if (curr->rightThread) {
                curr = curr->right;
            } else {
                curr = curr->right;
            }
        }
    }

    void preorderTraversal() {
        Node* curr = root;
        while (curr != nullptr) {
            cout << curr->data << " ";
            if (!curr->leftThread) {
                curr = curr->left;
            } else if (curr->rightThread) {
                curr = curr->right;
            } else {
                break;
            }
        }
    }
};

int main() {
    ThreadedBinaryTree tbt;
    tbt.insert(50);
    tbt.insert(30);
    tbt.insert(20);
    tbt.insert(40);
    tbt.insert(70);
    tbt.insert(60);
    tbt.insert(80);
    
    cout << "In-order Traversal: ";
    tbt.inorderTraversal();
    cout << endl;

    cout << "Pre-order Traversal: ";
    tbt.preorderTraversal();
    cout << endl;

    return 0;
}
