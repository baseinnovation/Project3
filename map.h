#include <vector>
#include <iostream>
#include <string>

// rotations from module 4: balanced trees stepik solutions
using namespace std;

struct Node {
    string data;
    Node* left;
    Node* right;
    bool black = true;
    Node() : data(), left(nullptr), right(nullptr) {}
    Node(string d) : data(d), left(nullptr), right(nullptr) {}
    Node(string d, bool black) : data(d), black(black), left(nullptr), right(nullptr) {}
};


// Red-Black Tree BST Representation
class BST {
private:
    Node* root = nullptr;
    // rotations
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeftRight(Node* node);
    Node* rotateRightLeft(Node* node);

public:
    Node* insertHelper(Node* head, Node* parent, string data);
    void insert(string data);
    void remove(Node* head);
    void search(Node* head);
    void postorder(Node* head, vector<Node*>& post);
    void printPostOrder();
    ~BST();

};

void BST::printPostOrder() {
    vector<Node*> post;
    postorder(this->root, post);
    for (unsigned int i = 0; i < post.size(); i++) {
        if (i == post.size() - 1)
            cout << post[i]->data << endl;
        else
            cout << post[i]->data << ", ";
    }
}

void BST::postorder(Node* head, vector<Node*>& post) {
    if (head == nullptr)
        return;
    else {
        postorder(head->left, post);
        postorder(head->right,post);
        post.push_back(head);
    }
}

BST::~BST() {
    vector<Node*> post;
    postorder(this->root,post);
    for(unsigned int i = 0; i < post.size(); i++) {
        delete post[i];
    }
}


Node* BST::rotateLeft(Node* node) {

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

Node* BST::rotateRight(Node* node) {

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

Node* BST::rotateLeftRight(Node* node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

Node* BST::rotateRightLeft(Node* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}





void BST::insert(string data) {
    this->root = insertHelper(this->root, this->root, data);
    this->root->black = true; // update root color to always black
}

Node* BST::insertHelper(Node* head, Node* parent, string data) {
    // if new node is root, color black, else color red and adjust color if necessary
    if (root == nullptr)
        return new Node(data, true);
    else if (head == nullptr)
        return new Node(data, false);
    else if (data < head->data && head == root)
        head->left = insertHelper(head->left, root, data);
    else if (data > head->data && head == root)
        head->right = insertHelper(head->right, root, data);
    else if (data < head->data && head != root)
        head->left = insertHelper(head->left, head, data);
    else
        head->right = insertHelper(head->right, head, data);

    // check
    // node's uncle is red: change parent and uncle colour to black, grandfather to red
    // node's uncle is black: left, right, left-right, right-left rotation based on tree structure, swap parent and grandfather colors if possible
    if (parent->left != nullptr) {
        if (parent->left == head && parent->right != nullptr) { // parent of new child
            if (!parent->right->black) { // uncle is red
                parent->left->black = true;
                parent->right->black = true;
                parent->black = false;
            } else if (parent->right->black) { // uncle exists and black
                if (head->left != nullptr) {
                    if (head->left->data == data)
                        parent = rotateRight(parent);
                } else if (head->right != nullptr) {
                    if (head->right->data == data)
                        parent = rotateLeftRight(parent);
                }
            }
        } else if (parent->left == head && parent->right == nullptr) { // uncle is null and black
            if (head->left != nullptr)
                if (head->left->data == data)
                    parent = rotateRight(parent);
            else if (head->right != nullptr)
                if (head->right->data == data)
                    parent = rotateLeftRight(parent);
        }

    } else if (parent->right != nullptr) {
        if (parent->right == head && parent->left != nullptr) { // parent of new child
            if(!parent->left->black) { // uncle is red
                parent->right->black = true;
                parent->left->black = true;
                parent->black = false;
            } else if (parent->left->black) { // uncle exists and black
                if (head->right != nullptr) {
                    if (head->right->data == data)
                        parent = rotateLeft(parent);
                }
            } else if (head->left != nullptr) {
                if (head->left->data == data)
                    parent = rotateRightLeft(parent);
            }
        } else if (parent->right == head && parent->left == nullptr) { // uncle is null and black
            if (head->right != nullptr)
                if(head->right->data == data)
                    parent = rotateLeft(parent);
            else if (head->left != nullptr)
                if(head->left->data == data)
                    parent = rotateRightLeft(parent);

        }
    }

    return head;
}


class map {
private:
    BST tree;
public:
    map operator=(const map& m);

    map();
    ~map();
};