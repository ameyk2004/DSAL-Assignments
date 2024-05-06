// Beginning with an empty binary tree, construct binary tree by inserting the values in the order given. After constructing a binary tree perform following operations on it-
// • Perform non-recursive inorder traversal, recursive postorder
// • Level wise printing
// • Display and count leaf nodes
// • Display and count internal nodes
#include<iostream>
using namespace std;

class Node
{
    private:
    int data;
    Node* left;
    Node* right;

    public:
    Node(int val=0) : left(nullptr), right(nullptr), data(val) {}
    
    friend class BinaryTree;
};

class BinaryTree
{
    public:
    Node* root;

    public:
    BinaryTree() : root(nullptr) {
        root = createTree(this->root);
    }

    Node* createTree(Node* root)
    {
        int d;
        cout<<"Enter the data :  ";
        cin>>d;

        if(d == -1)
            return nullptr;

        root = new Node(d);

        cout<<"Enter the data for left of "<<d<<endl;
        root->left = createTree(root->left);
        cout<<"Enter the data for right of "<<d<<endl;
        root->right = createTree(root->right);

        return root;
    }

    void RecursivePreorder(Node* root)
    {
        if(!root)
            return;

        cout<<root->data<<" ";
        RecursivePreorder(root->left);
        RecursivePreorder(root->right);
    }

    void RecursiveInorder(Node* root)
    {
        if(!root)
            return;

        RecursiveInorder(root->left);
        cout<<root->data<<" ";
        RecursiveInorder(root->right);
    }

    void RecursivePostorder(Node* root)
    {
        if(!root)
            return;

        RecursivePostorder(root->left);
        RecursivePostorder(root->right);
        cout<<root->data<<" ";
    }
   
};

int main()
{
    BinaryTree tree;
    tree.RecursivePreorder(tree.root);
    tree.RecursivePostorder(tree.root);
    tree.RecursiveInorder(tree.root);
}