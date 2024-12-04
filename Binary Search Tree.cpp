/*
Implement binary search tree and perform following operations:
a) Insert (Handle insertion of duplicate entry)
b) Delete
c) Search
d) Display tree (Traversal)
e) Display - Depth of tree
f) Display - Mirror image
g) Create a copy
h) Display all parent nodes with their child nodes
i) Display leaf nodes
j) Display tree level wise
(Note: Insertion, Deletion, Search and Traversal are compulsory, from rest of operations, perform
Any three)
*/

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

class BinarySearchTree {
public:
    Node* root;
    
    BinarySearchTree() {
        root = nullptr;
    }

    Node* insert(Node* root, int value) {
        if (root == nullptr) return new Node(value);
        if (value < root->data)
            root->left = insert(root->left, value);
        else if (value > root->data)
            root->right = insert(root->right, value);
        return root;
    }

    Node* deleteNode(Node* root, int value) {
        if (root == nullptr) return root;
        if (value < root->data)
            root->left = deleteNode(root->left, value);
        else if (value > root->data)
            root->right = deleteNode(root->right, value);
        else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    bool search(Node* root, int value) {
        if (root == nullptr) return false;
        if (root->data == value) return true;
        if (value < root->data)
            return search(root->left, value);
        return search(root->right, value);
    }

    void inorder(Node* root) {
        if (root == nullptr) return;
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }

    void preorder(Node* root) {
        if (root == nullptr) return;
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }

    void postorder(Node* root) {
        if (root == nullptr) return;
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }

    int depth(Node* root) {
        if (root == nullptr) return 0;
        int leftDepth = depth(root->left);
        int rightDepth = depth(root->right);
        return max(leftDepth, rightDepth) + 1;
    }

    void mirrorImage(Node* root) {
        if (root == nullptr) return;
        swap(root->left, root->right);
        mirrorImage(root->left);
        mirrorImage(root->right);
    }

    Node* copy(Node* root) {
        if (root == nullptr) return nullptr;
        Node* newNode = new Node(root->data);
        newNode->left = copy(root->left);
        newNode->right = copy(root->right);
        return newNode;
    }

    void displayParents(Node* root) {
        if (root == nullptr) return;
        if (root->left != nullptr) cout << root->data << " -> " << root->left->data << endl;
        if (root->right != nullptr) cout << root->data << " -> " << root->right->data << endl;
        displayParents(root->left);
        displayParents(root->right);
    }

    void displayLeafNodes(Node* root) {
        if (root == nullptr) return;
        if (root->left == nullptr && root->right == nullptr)
            cout << root->data << " ";
        displayLeafNodes(root->left);
        displayLeafNodes(root->right);
    }

    void displayLevelWise(Node* root) {
        if (root == nullptr) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            cout << current->data << " ";
            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
    }
};

int main() {
    BinarySearchTree bst;
    bst.root = bst.insert(bst.root, 50);
    bst.root = bst.insert(bst.root, 30);
    bst.root = bst.insert(bst.root, 20);
    bst.root = bst.insert(bst.root, 40);
    bst.root = bst.insert(bst.root, 70);
    bst.root = bst.insert(bst.root, 60);
    bst.root = bst.insert(bst.root, 80);

    cout << "In-order Traversal: ";
    bst.inorder(bst.root);
    cout << endl;

    cout << "Pre-order Traversal: ";
    bst.preorder(bst.root);
    cout << endl;

    cout << "Post-order Traversal: ";
    bst.postorder(bst.root);
    cout << endl;

    cout << "Search 40: " << (bst.search(bst.root, 40) ? "Found" : "Not Found") << endl;
    
    cout << "Depth of tree: " << bst.depth(bst.root) << endl;

    cout << "Mirror Image: ";
    bst.mirrorImage(bst.root);
    bst.inorder(bst.root);
    cout << endl;

    Node* copiedTree = bst.copy(bst.root);
    cout << "Copied Tree In-order: ";
    bst.inorder(copiedTree);
    cout << endl;

    cout << "Parents with Children: ";
    bst.displayParents(bst.root);
    cout << endl;

    cout << "Leaf Nodes: ";
    bst.displayLeafNodes(bst.root);
    cout << endl;

    cout << "Level-wise Display: ";
    bst.displayLevelWise(bst.root);
    cout << endl;

    bst.root = bst.deleteNode(bst.root, 20);
    cout << "After Deletion of 20, In-order: ";
    bst.inorder(bst.root);
    cout << endl;

    return 0;
}
