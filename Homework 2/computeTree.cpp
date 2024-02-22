#include <iostream>
using namespace std;

class node {
public:
    int data;
    node* left;
    node* right;
};

class treeNode : public node {};

node* newNode(int data)
{
    node* Node = new node();
    Node->data = data;
    Node->left = NULL;
    Node->right = NULL;
    return (Node);
}

int totalNodes(node* root){
    if(root == nullptr){return 0;}
    return 1 + totalNodes(root->left) + totalNodes(root->right);
}

int totalLeaves(node* root){
    if(root->left == nullptr && root->right == nullptr){return 1;}
    return totalLeaves(root->left) + totalLeaves(root->right);
}

void printNodes(node* T, int k1, int k2){
    if(T == nullptr){return;}

    printNodes(T->left, k1, k2);
    if(k1 <= T->data && T->data <= k2)
        cout << T->data << endl;
    printNodes(T->right, k1, k2);
}

int main(){
    node* root = newNode(5);
    root->left = newNode(3);
    root->right = newNode(11);
    root->left->left = newNode(1);
    root->left->right = newNode(4);
    root->right->left = newNode(8);
    root->right->right = newNode(15);
    root->left->left->left = newNode(-5);
    root->left->left->right = newNode(2);
    // cout << totalNodes(root) << endl;
    // cout << totalLeaves(root) << endl;
    printNodes(root, -10, 15);
    return 0;
}