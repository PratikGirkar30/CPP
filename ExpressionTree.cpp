/*
Construct an Expression Tree from postfix and prefix expression. Perform recursive and nonrecursive In-order, pre-order and post-order traversals.
*/

#include <iostream>
#include <stack>
#include <cstring>
#include <cctype>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;
    
    Node(char val) {
        data = val;
        left = right = nullptr;
    }
};

class ExpressionTree {
public:
    Node* constructFromPostfix(string postfix) {
        stack<Node*> s;
        for (int i = 0; i < postfix.length(); i++) {
            char ch = postfix[i];
            if (isalnum(ch)) {
                s.push(new Node(ch));
            } else {
                Node* right = s.top(); s.pop();
                Node* left = s.top(); s.pop();
                Node* root = new Node(ch);
                root->left = left;
                root->right = right;
                s.push(root);
            }
        }
        return s.top();
    }

    Node* constructFromPrefix(string prefix) {
        stack<Node*> s;
        for (int i = prefix.length() - 1; i >= 0; i--) {
            char ch = prefix[i];
            if (isalnum(ch)) {
                s.push(new Node(ch));
            } else {
                Node* left = s.top(); s.pop();
                Node* right = s.top(); s.pop();
                Node* root = new Node(ch);
                root->left = left;
                root->right = right;
                s.push(root);
            }
        }
        return s.top();
    }

    void inorder(Node* root) {
        if (root == nullptr) return;
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }

    void inorderNonRecursive(Node* root) {
        if (root == nullptr) return;
        stack<Node*> s;
        Node* curr = root;
        while (curr != nullptr || !s.empty()) {
            while (curr != nullptr) {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top();
            s.pop();
            cout << curr->data << " ";
            curr = curr->right;
        }
    }

    void preorder(Node* root) {
        if (root == nullptr) return;
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }

    void preorderNonRecursive(Node* root) {
        if (root == nullptr) return;
        stack<Node*> s;
        s.push(root);
        while (!s.empty()) {
            Node* curr = s.top();
            s.pop();
            cout << curr->data << " ";
            if (curr->right) s.push(curr->right);
            if (curr->left) s.push(curr->left);
        }
    }

    void postorder(Node* root) {
        if (root == nullptr) return;
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }

    void postorderNonRecursive(Node* root) {
        if (root == nullptr) return;
        stack<Node*> s;
        Node* prev = nullptr;
        do {
            while (root != nullptr) {
                s.push(root);
                root = root->left;
            }
            while (root == nullptr && !s.empty()) {
                root = s.top();
                if (root->right == nullptr || root->right == prev) {
                    cout << root->data << " ";
                    s.pop();
                    prev = root;
                    root = nullptr;
                } else {
                    root = root->right;
                }
            }
        } while (!s.empty());
    }
};

int main() {
    ExpressionTree tree;
    
    string postfix = "ab+c*";
    Node* rootPostfix = tree.constructFromPostfix(postfix);
    cout << "Postfix Expression Tree Traversals: \n";
    
    cout << "In-order (Recursive): ";
    tree.inorder(rootPostfix);
    cout << "\nIn-order (Non-Recursive): ";
    tree.inorderNonRecursive(rootPostfix);
    
    cout << "\nPre-order (Recursive): ";
    tree.preorder(rootPostfix);
    cout << "\nPre-order (Non-Recursive): ";
    tree.preorderNonRecursive(rootPostfix);
    
    cout << "\nPost-order (Recursive): ";
    tree.postorder(rootPostfix);
    cout << "\nPost-order (Non-Recursive): ";
    tree.postorderNonRecursive(rootPostfix);
    
    cout << "\n\n";
    
    string prefix = "*+abcd";
    Node* rootPrefix = tree.constructFromPrefix(prefix);
    cout << "Prefix Expression Tree Traversals: \n";
    
    cout << "In-order (Recursive): ";
    tree.inorder(rootPrefix);
    cout << "\nIn-order (Non-Recursive): ";
    tree.inorderNonRecursive(rootPrefix);
    
    cout << "\nPre-order (Recursive): ";
    tree.preorder(rootPrefix);
    cout << "\nPre-order (Non-Recursive): ";
    tree.preorderNonRecursive(rootPrefix);

    cout << "\nPost-order (Recursive): ";
    tree.postorder(rootPrefix);
    cout << "\nPost-order (Non-Recursive): ";
    tree.postorderNonRecursive(rootPrefix);
    
    return 0;
}
