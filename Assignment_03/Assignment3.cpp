#include<iostream>
using namespace std;

class Node{
    private:
    Node* left;
    Node* right;
    bool lthread;
    bool rthread;
    int data;

    Node(int d = 0) : data(d), left(nullptr), right(nullptr), lthread(true), rthread(true) {}

    friend class TBST;
};

class TBST{
    Node* header;

    void insertAtLeft(Node* parent, Node* child) // copy left attributes
    {
        //lthread and left la copy kar
        child->left = parent->left;
        child->lthread = parent->lthread;

        parent->lthread = false;
        parent->left = child;

        child->right = parent;
        child->rthread = true;

    }

    void insertAtRight(Node* parent, Node* child) // copy RIGHT attributes
    {
        //Rthread and RIGHT la copy kar
        child->right = parent->right;
        child->rthread = parent->rthread;

        parent->rthread = false;
        parent->right = child;

        child->left = parent;
        child->lthread = true;
    }

    Node* leftMost(Node* root)
    {
        while(root->left && !root->lthread)
        {
            root = root->left;
        }

        return root;
    }

public:
    TBST()
    {
        header = new Node(-1);
        header->left = header;
        header->right = header;
    }

    void insert(int val)
    {
        Node* newNode = new Node(val);

        if(header->lthread)
        {
            insertAtLeft(header, newNode);
            cout<<"Node Inserted with value : "<<val<<" and parent "<<header->data<<endl;
            return;
        }

        Node* root = header->left;

        while(root)
        {
            if(val < root->data && root->lthread)
            {
                insertAtLeft(root, newNode);
                cout<<"Node Inserted with value : "<<val<<" and parent "<<root->data<<endl;
                return;
            }
            else if(val < root->data)
            {
                root = root->left;
            }
            else if(val > root->data && root->rthread)
            {
                insertAtRight(root, newNode);
                cout<<"Node Inserted with value : "<<val<<" and parent "<<root->data<<endl;
                return;
            }
            else if(val > root->data)
            {
                root = root->right;
            }
            else{
                cout<<"DUPLICATE"<<endl;
                return;
            }
        }

    }

    void inorderTraversal()
    {
        Node* root = header->left;
        Node* curr = leftMost(root);
        cout<<"\nInorder : ";
        while(curr!=header)
        {
            cout<<curr->data<<" ";
            if(curr->rthread)
                curr = curr->right;

            else
                curr = leftMost(curr->right);
        }
    }

    void preorderTraversal()
    {
        if(header->lthread)
        {
            cout<<"TREE IS EMPTY"<<endl;
            return;
        }

        Node* root = header->left;
         cout<<"\n\nPreorder : ";
        while(root)
        {
            cout<<root->data<<" ";
            if(!root->lthread)
            {
                root = root->left;
            }
            else if(!root->rthread)
            {
                root = root->right;
            }
            else
            {
                while(root!=header && root->rthread)
                {
                    root = root->right;
                }

                if(root == header) break;

                root = root->right;
            }
        }
    }

};

int main()
{
    TBST tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(25);
    tree.insert(15);
    tree.insert(35);
    tree.insert(20);
    tree.insert(28);
    tree.insert(26);
    tree.insert(29);
    tree.insert(27);
    tree.inorderTraversal();
    tree.preorderTraversal();
}