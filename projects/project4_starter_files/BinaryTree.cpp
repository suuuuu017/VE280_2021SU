#include "BinaryTree.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* ================================== Node =================================== */
Node::Node(const int &val, Node *left, Node *right):val(val), left(left), right(right){
}

int Node::getVal() const {
    return val;
}

void Node::setVal(const int &newVal){
    this->val = newVal;
}

Node* Node::getLeft() const {
    return left;
}

void Node::setLeft(const int &newVal) {
    if(!left){
        left = new Node(newVal);
    }
    else{
        left->setVal(newVal);
    }
}

Node* Node::getRight() const {
    return right;
}

void Node::setRight(const int &newVal) {
    if(!right){
        right = new Node(newVal);
    }
    else{
        right->setVal(newVal);
    }
}
/* =============================== Binary Tree =============================== */

BinaryTree::BinaryTree(const int &rootValue):root(new Node(rootValue)){
}

BinaryTree::BinaryTree(Node *node):root(node){
}

Node* copyNodeHelper(const Node* source){
    if(!source){
        return nullptr;
    }
    Node * newNode = new Node(source->getVal(), copyNodeHelper(source->getLeft()),
                                copyNodeHelper(source->getRight()));
    return newNode;
}


BinaryTree::BinaryTree(const BinaryTree &tree) {
    this->root = copyNodeHelper(tree.root);
}

//Node * constructFromList(std::vector<nodeValue> &source, int i, int length, Node * node){
//    if(i > length){
//        return node;
//    }
//    node->setVal(const_cast<const int&>(source.at(i)));
////    node->setLeft(source[2 * i + 1]);
//    constructFromList(source, 2 * i + 1, length, node->getLeft());
////    node->setRight(source[2 * 1 + 2]);
//    constructFromList(source, 2 * i + 2, length, node->getRight());
//    return node;
//}

BinaryTree::BinaryTree(std::vector<nodeValue> &source) {
    this->root = createFromVariant(source, 0);
}

void deleteHelper(Node * node){
    if(node){
        deleteHelper(node->getLeft());
        deleteHelper(node->getRight());
        delete node;
    }
}

BinaryTree::~BinaryTree() {
    deleteHelper(this->root);
}

bool BinaryTree::empty() const {
    return !root;
}

Node* findHelper(const int &key, Node * node){
    if(!node){
        return nullptr;
    }
    if(node->getVal() == key){
        return node;
    }
    else{
        Node* left = findHelper(key, node->getLeft());
        if(left){
            return left;
        }
        Node* right = findHelper(key, node->getRight());
        if(right){
            return right;
        }
    }
}

Node *BinaryTree::find(const int &key) const {
    if(!this->root){
        return nullptr;
    }
    return findHelper(key, this->root);
}

bool findPathHelper(const int &value, Node * node, std::string & output){
    if(!node){
//        cout << output<< endl;
        return false;
    }
    if(node->getVal() == value){
//        cout << node->getVal()<< endl;
        return true;
    }
    output.push_back('0');
//    cout << "here" << endl;
    if(findPathHelper(value, node->getLeft(), output)){
        return true;
    }
    output.pop_back();
    output.push_back('1');
    if(findPathHelper(value, node->getRight(), output)){
        return true;
    }
    output.pop_back();
    return false;
}

std::string BinaryTree::findPath(const int &value) const {
    std::string output;
    findPathHelper(value, this->root, output);
    return output;
}

Node * visitThroughHelper(string &path, Node *node){
    if(path.empty() && node){
        return node;
    }
    else if(node && (!path.empty())){
        char next = path.back();
        path.pop_back();
        if(next == '0'){
            visitThroughHelper(path, node->getLeft());
        }
        else if(next == '1'){
            visitThroughHelper(path, node->getRight());
        }
    }
//    return nullptr;
}

Node *BinaryTree::visitThroughPath(const string &path) const {
    if(path.empty()){
        return this->root;
    }
    string tmpPath = path;
    reverse(tmpPath.begin(), tmpPath.end());
    return visitThroughHelper(tmpPath, this->root);
}

int sumHelper(Node * node){
    if(!node){
        return 0;
    }
    return node->getVal() + sumHelper(node->getLeft()) + sumHelper(node->getRight());
}

int BinaryTree::sum() const {
    return sumHelper(this->root);
}

int heightHelper(Node * node){
    if(!node){
        return 0;
    }
    int lDepth = heightHelper(node->getLeft());
    int rDepth = heightHelper(node->getRight());
    if (lDepth < rDepth){
        return(heightHelper(node->getRight()) + 1);
    }
    else{
        return(heightHelper(node->getLeft()) + 1);
    }
}

int BinaryTree::height() const {
    return heightHelper(this->root);
}

void preOrderHelper(Node * node){
    if(!node){
        return;
    }
    cout << node->getVal() << " ";
    preOrderHelper(node->getLeft());
    preOrderHelper(node->getRight());
}

void BinaryTree::preOrder() const {
    preOrderHelper(this->root);
    cout << endl;
}

void inOrderHelper(Node * node){
    if(!node){
        return;
    }
    inOrderHelper(node->getLeft());
    cout << node->getVal() << " ";
    inOrderHelper(node->getRight());
}

void BinaryTree::inOrder() const {
    inOrderHelper(this->root);
    cout << endl;
}

void postOrderHelper(Node * node){
    if(!node){
        return;
    }
    postOrderHelper(node->getLeft());
    postOrderHelper(node->getRight());
    cout << node->getVal() << " ";
}

void BinaryTree::postOrder() const {
    postOrderHelper(this->root);
    cout << endl;
}

bool pathSumGreaterHelper(int sum, Node * node){
    if(!node){
        return true;
    }
    if(!node->getLeft() && !node->getRight()){
        return node->getVal() > sum;
    }
    return pathSumGreaterHelper(sum - node->getVal(), node->getLeft()) &&
            pathSumGreaterHelper(sum - node->getVal(), node->getRight());
}

bool BinaryTree::allPathSumGreater(const int &sum) const {
    int tmpSum = sum;
    pathSumGreaterHelper(tmpSum, this->root);
}

bool coverHelper(Node * thisNode, Node * thatNode){
    if(!thisNode){
        return true;
    }
    else if(thatNode == nullptr && thisNode){
//        cout << "!!" << endl;
        return false;
    }
    else if(thisNode->getVal() != thatNode->getVal()){
//        cout << "!?" << endl;
//        cout << "this " << thisNode->getVal() << endl;
//        cout << "that " << thatNode->getVal() << endl;
        return false;
    }
    return coverHelper(thisNode->getLeft(), thatNode->getLeft()) &&
            coverHelper(thisNode->getRight(), thatNode->getRight());

}

bool BinaryTree::operator<(const BinaryTree &tree) const {
    return coverHelper(this->root, tree.root);
}

bool containHelper(Node * thisnode, Node * thatnode){
//    cout << "this " << thisnode->getVal() << endl;
//    cout << "that " << thatnode->getVal() << endl;
    if(!thatnode){
        return false;
    }
    if(coverHelper(thisnode, thatnode)){
//        cout << "here! " << endl;
        return true;
    }
//    cout << thatnode->getRight()->getVal() << endl;
//    cout << "here.. "  << coverHelper(thisnode, thatnode) << endl;
    return containHelper(thisnode, thatnode->getLeft()) || containHelper(thisnode, thatnode->getRight());
//    return containHelper(thisnode, thatnode->getRight());

}

bool BinaryTree::operator<<(const BinaryTree &tree) const {
    return containHelper(this->root, tree.root);
}

BinaryTree &BinaryTree::operator=(const BinaryTree &tree) {
    deleteHelper(this->root);
    this->root = copyNodeHelper(tree.root);
}

Node *BinaryTree::createFromVariant(const vector<nodeValue> &source, const int &rootIndex) {
    if (rootIndex >= source.size())
        return nullptr;
    auto rootValue = get_if<int>(&source[rootIndex]);
    if (!rootValue)
        return nullptr;
    int rightIndex = 2 * (rootIndex + 1);
    int leftIndex = rightIndex - 1;
    return new Node(*rootValue, createFromVariant(source, leftIndex), createFromVariant(source, rightIndex));
}
