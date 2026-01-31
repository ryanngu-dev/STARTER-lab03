// intbst.cpp
// Implements class IntBST
// Ryan Nguyen, 1/27/2026

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
    root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
    root = nullptr;
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (!n) return;
    clear(n->left);
    clear(n->right);  
    delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if (root == nullptr){
        root = new Node(value);
        return true;
    }
    return insert(value, root);

}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->info){
        return false;
    }

    if (value > n->info){
        if (n->right == nullptr){
            n->right = new Node(value);
            n->right->parent = n;
            return true;
        }
        return insert(value, n->right);
    } else {
        if (n->left == nullptr){
            n->left = new Node(value);
            n->left->parent = n;
            return true;
        }
        return insert(value, n->left);
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (!n) return;
    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if (!n) return;
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if (!n) return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if (!n) return 0;
    
    return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if (!n) return 0;

    return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if (!n) return nullptr;

    if (value == n->info){
        return n;
    }

    if (n->info > value){
        return getNodeFor(value, n->left);
    } else {
        return getNodeFor(value, n->right);
    }

    return nullptr;
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    if (getNodeFor(value, root) == nullptr){
        return false;
    } else {
        return true;
    }
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* val = getNodeFor(value, root);
    if (val == nullptr) return nullptr;

    if (val->left){
        Node* temp = val->left;
        while (temp->right){
            temp = temp->right;
        }
        return temp;
    } else {
        Node* parent = val->parent;
        while (parent && (val == parent->left)){
            val = parent;
            parent = parent->parent;
        }
        return parent;
    }
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* temp = getPredecessorNode(value);
    if (!temp){
        return 0;
    } else {
        return temp->info;
    }
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* val = getNodeFor(value, root);
    if (val == nullptr) return nullptr;

    if (val->right){
        Node* temp = val->right;
        while (temp->left){
            temp = temp->left;
        }
        return temp;
    } else {
        Node* parent = val->parent;
        while (parent && (val == parent->right)){
            val = parent;
            parent = parent->parent;
        }
        return parent;
    }
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* temp = getSuccessorNode(value);
    if (temp == nullptr){
        return 0;
    } else {
        return temp->info;
    }
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    Node* temp = getNodeFor(value, root);
    
    if (!temp) return false;

    Node* parent = temp->parent;

    if (!parent){
        if (temp->left && temp->right){
            Node* pred = getPredecessorNode(value);
            temp->info = pred->info;
            Node* p = pred->parent;

            if (p->left == pred){
                p->left = pred->left;
            } else {
                p->right = pred->left;
            }

            if (pred->left) pred->left->parent = p;
            delete pred;
            return true;
        } else if (!temp->left){
            root = temp->right;
            if (root) root->parent = nullptr;
            delete temp;
            return true;
        } else {
            root = temp->left;
            if (root) root->parent = nullptr;
            delete temp;
            return true;
        }
    } else {
        if (temp->left && temp->right){
            Node* pred = getPredecessorNode(value);
            temp->info = pred->info;
            Node* p = pred->parent;

            if (p->left == pred){
                p->left = pred->left;
            } else {
                p->right = pred->left;
            }

            if (pred->left) pred->left->parent = p;
            delete pred;
            return true;
        } else if (!temp->left){
            if (parent->left == temp){
                parent->left = temp->right;
            } else {
                parent->right = temp->right;
            }

            if (temp->right) temp->right->parent = parent;
            delete temp;
            return true;
        } else {
            if (parent->left == temp) {
                parent->left = temp->left;
            } else {
                parent->right = temp->left;
            }

            if (temp->left) temp->left->parent = parent;
            delete temp;
            return true;
        }
    }
}
