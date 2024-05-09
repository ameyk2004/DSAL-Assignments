#include<iostream>
using namespace std;

class Node{
    private:
    int data;
    Node* left;
    Node* right;
    bool lthread;
    bool rthread;

    Node(int val=0) : data(val), left(nullptr), right(nullptr), lthread(true), rthread(true) {}

    friend class TBST;
};

class TBST{
    private:
    Node* header;

    void insertAtLeft(Node* parent, Node* child)
    {
        child->left = parent->left;
        child->lthread = parent->lthread;

        child->rthread = true;
        child->right = parent;

        parent->lthread = false;
        parent->left = child;
    }

    void insertAtRight(Node* parent, Node* child)
    {
        child->right = parent->right;
        child->rthread = parent->rthread;

        child->lthread = true;
        child->left = parent;

        parent->rthread = false;
        parent->right = child;
    }

    Node* leftmost(Node* curr)
    {

        while(curr->left && !curr->lthread)
        {
            curr = curr->left;
        }
        return curr;
    }


    public:
    TBST()
    {
        header = new Node(-1);
        header->left = header;
        header->right = header;
    }

    void insert(int data)
    {
        Node* newNode = new Node(data);

        if(header->lthread)
        {
            insertAtLeft(header, newNode);
            cout<<"Inserted value "<<data<<" with parent Header at left"<<endl;
            return;
        }

        Node* root = header->left;

        while(root)
        {

        
            if(data < root->data && root->lthread)
            {
                insertAtLeft(root, newNode);
                cout<<"Inserted value "<<data<<" with parent "<<root->data<<" at left"<<endl;
                return;
            }
            else if(data < root->data)
            {
                root = root->left;
            }
            else if(data > root->data && root->rthread)
            {
                insertAtRight(root, newNode);
                cout<<"Inserted value "<<data<<" with parent "<<root->data<<" at right"<<endl;
                return;
            }
            else if(data > root->data)
            {
                root = root->right;
            }
            else
            {
                cout<<"Duplicate val not allowed"<<endl;
                return;
            }
        }
    }

    void inorderTraversal()
    {
        Node* root = header->left;
        Node* curr = leftmost(root->left);

        while (curr!=header)
        {
            cout<<curr->data<<" ";

            if(curr->rthread)
            {
                curr = curr->right;
            }
            else{
                curr = leftmost(curr->right);
            }
        }
        cout<<endl;
    }

    void preorderTraversal()
    {
        Node* root = header->left;


        while(root!=header)
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
            else{
                while(root->rthread && root!=header)
                {
                    root = root->right;
                }

                if(root==header) break;

                root = root->right;
            }
        }

        cout<<endl;

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
    cout<<endl;
    tree.inorderTraversal();
    tree.preorderTraversal();
    

}