#include<iostream>
using namespace std;
class Node{
    int data;
    Node* left;
    Node* right;

    public:
    Node(int data = 0) : data(data), left(nullptr), right(nullptr) {} 

    friend class BST;
};

class BST{
    
    public:
    Node* root;
    BST() : root(nullptr) {
        root = createTree(root);
    }

    Node* createTree(Node* root)
    {
        int d;
        do
        {
            cout<<"Enter data (-1 to stop) : "<<endl;
            cin>>d;
            if(d!=-1)
            root = insert(root,d);
        }
        while(d!=-1);

        return root;
    }

    Node* insert(Node* root, int data)
    {
        if(!root)
        {
            return new Node(data);
        }

        if(data < root->data)
            root->left = insert(root->left, data);
        else if(data > root->data)
            root->right = insert(root->right, data);
        else
            cout<<"Duplicate"<<endl;


        return root;
    }

    void inorder(Node* root)
    {
        if(!root)
            return;

        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }

    Node* search(Node* root, int data, int attempts)
    {
        attempts+=1;
        if(root->data == data)
        {
            cout<<"Element found"<<endl;
            cout<<"attempts : "<<attempts<<endl;
            return root;
        }

        if(data < root->data)
                search(root->left, data, attempts);

        else
                search(root->right, data, attempts);

        cout<<"Ele not found"<<endl;
    
    }

    Node* leftmost(Node* root)
    {
        Node* curr = root;

        while(curr->left)
        {
            curr = curr->left;
        }
        return curr;
    }

    Node* deleteNode(Node* root, int data)
{
    if (!root)
        return nullptr;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else
    {
        // Case 1: Node to be deleted has no children or only one child
        if (!root->left)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (!root->right)
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        
        // Case 2: Node to be deleted has two children
        // Find the inorder successor (smallest node in the right subtree)
        Node* temp = leftmost(root->right);
        root->data = temp->data;
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}


};

int main()
{
    BST tree;
    tree.inorder(tree.root);
    tree.deleteNode(tree.root,150);
    cout<<endl;
    tree.inorder(tree.root);
}