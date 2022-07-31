#include <vector>
#include <iostream>
#include <string>
#include "Bin.h"

// rotations from module 4: balanced trees stepik solutions
using namespace std;

// Red-Black Tree BST Representation
template <typename T>
class BST {
private:
    struct Node {
        string data;
        T* recipe = nullptr;
        Node* left;
        Node* right;
        bool black = true;
        Node() : data(), left(nullptr), right(nullptr) {}
        Node(string d) : data(d), left(nullptr), right(nullptr) {}
        Node(string d, bool black) : data(d), black(black), left(nullptr), right(nullptr) {}
        Node(string d, T* rec, bool black) : data(d), recipe(rec), black(black) {}
    };
    Node* root = nullptr;

    // rotations
    Node* rotateLeft(Node* node) {

        Node* rightChild = node->right;
        node->right = rightChild->left;
        rightChild->left = node;

        // swap grandfather and parent colors if necessary
        if (rightChild->black && !node->black) {
            node->black = true;
            rightChild->black = false;
        } else if (!rightChild->black && node->black) {
            node->black = false;
            rightChild->black = true;
        }

        return rightChild;

    }
    Node* rotateRight(Node* node) {

        Node* leftChild = node->left;
        node->left = leftChild->right;
        leftChild->right = node;

        // swap grandfather and parent colors if necessary
        if (leftChild->black && !node->black) {
            node->black = true;
            leftChild->black = false;
        } else if (!leftChild->black && node->black) {
            node->black = false;
            leftChild->black = true;
        }

        return leftChild;

    }
    Node* rotateLeftRight(Node* node) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    Node* rotateRightLeft(Node* node) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

public:
    T* search(string d) {
        return searchHelper(this->root, d);
    }
    T* searchHelper(Node* head, string d) {
        if (head == nullptr)
            return nullptr;
        else if (head->data == d)
            return head->recipe;
        else if (d < head->data)
            return search(head->left, d);
        else
            return search(head->right, d);
    }
    void insert(string data, T* recipe) {
        this->root = insertHelper(this->root, data, recipe);
        this->root->black = true; // update root color to always black
    }
    Node* insertHelper(Node* head, string data, T* recipe) {
        // if new node is root, color black, else color red and adjust color if necessary
        if (root == nullptr)
            return new Node(data, recipe, true);
        else if (head == nullptr)
            return new Node(data, recipe, false);
        else if (data < head->data)
            head->left = insertHelper(head->left, data);
        else
            head->right = insertHelper(head->right, data);

        // update relationships of head node
        Node* child_L = head->left;
        Node* child_R = head->right;
        Node* grandChild_LL = nullptr;
        Node* grandChild_LR = nullptr;
        Node* grandChild_RL = nullptr;
        Node* grandChild_RR = nullptr;

        if (child_L != nullptr) {
            grandChild_LL = child_L->left;
            grandChild_LR = child_L->right;
        }
        if (child_R != nullptr) {
            grandChild_RL = child_R->left;
            grandChild_RR = child_R->right;
        }

        // find grandparent of newly inserted node
        // if node's uncle is red: change parent and uncle colour to black, grandfather to red
        // if node's uncle is black: left, right, left-right, right-left rotation based on tree structure, swap parent and grandfather colors if possible
        if (child_L != nullptr) {
            if (grandChild_LL != nullptr) {
                if (grandChild_LL->data == data) { // grandChild is newly inserted node
                    if (child_R != nullptr) { // uncle exists
                        if (!child_R->black) { // uncle is red
                            child_L->black = true;
                            child_R->black = true;
                            head->black = false;
                        } else { // uncle is black
                            head = rotateRight(head);
                        }
                    } else { // uncle is null, therefore black
                        head = rotateRight(head);
                    }
                }
            } else if (grandChild_LR != nullptr) {
                if (grandChild_LR->data == data) {
                    if (child_R != nullptr) {
                        if (!child_R->black) { // uncle is red
                            child_L->black = true;
                            child_R->black = true;
                            head->black = false;
                        } else { // uncle is black
                            head = rotateLeftRight(head);
                        }
                    } else { // uncle is null, therefore black
                        head = rotateLeftRight(head);
                    }
                }
            }
        }

        if (child_R != nullptr) {
            if (grandChild_RR != nullptr) {
                if (grandChild_RR->data == data) { // grandChild is newly inserted node
                    if (child_L != nullptr) { // uncle exists
                        if (!child_L->black) { // uncle is red
                            child_L->black = true;
                            child_R->black = true;
                            head->black = false;
                        } else { // uncle is black
                            head = rotateLeft(head);
                        }
                    } else { // uncle is null, therefore black
                        head = rotateLeft(head);
                    }
                }
            } else if (grandChild_RL != nullptr) {
                if (grandChild_RL->data == data) {
                    if (child_L != nullptr) {
                        if (!child_L->black) { // uncle is red
                            child_L->black = true;
                            child_R->black = true;
                            head->black = false;
                        } else { // uncle is black
                            head = rotateRightLeft(head);
                        }
                    } else { // uncle is null, therefore black
                        head = rotateRightLeft(head);
                    }
                }
            }
        }
        return head;
    }


    // traversals for testing
    void postorder(Node* head, vector<Node*>& post) {
        if (head == nullptr)
            return;
        else {
            postorder(head->left, post);
            postorder(head->right,post);
            post.push_back(head);
        }
    }
    void printPostOrder() {
        vector<Node*> post;
        postorder(this->root, post);
        for (unsigned int i = 0; i < post.size(); i++) {
            if (i == post.size() - 1)
                cout << post[i]->data << endl;
            else
                cout << post[i]->data << ", ";
        }
    }
    void inorder(Node* head, vector<Node*>& in) {
        if (head == nullptr)
            return;
        else {
            inorder(head->left, in);
            in.push_back(head);
            inorder(head->right,in);
        }
    }
    void printInOrder() {
        vector<Node*> in;
        inorder(this->root, in);
        for (unsigned int i = 0; i < in.size(); i++) {
            if (i == in.size() - 1)
                cout << in[i]->data << endl;
            else
                cout << in[i]->data << ", ";
        }
    }
    void preorder(Node* head, vector<Node*>& pre) {
        if (head == nullptr)
            return;
        else {
            pre.push_back(head);
            preorder(head->left, pre);
            preorder(head->right,pre);
        }
    }
    void printPreOrder() {
        vector<Node*> pre;
        preorder(this->root, pre);
        for (unsigned int i = 0; i < pre.size(); i++) {
            if (i == pre.size() - 1)
                cout << pre[i]->data << endl;
            else
                cout << pre[i]->data << ", ";
        }
    }

    // destructor
    ~BST() {
        vector<Node*> post;
        postorder(this->root,post);
        for(unsigned int i = 0; i < post.size(); i++) {
            delete post[i];
        }
    }

};

template <typename T>
class map {
private:
    BST<T> tree;
public:
    void insert(string key, T value) {
        tree.insert(key,value);
    }
    T* search(string key) {
        return tree.search(key);
    }
    ~map(){
        delete tree;
    }
};