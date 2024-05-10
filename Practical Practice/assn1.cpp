// Beginning with an empty binary tree, construct binary tree by inserting the values in the order given. After constructing a binary tree perform following operations on it-
// • Perform non-recursive inorder traversal, recursive postorder
// • Level wise printing
// • Display and count leaf nodes
// • Display and count internal nodes

#include<iostream>
#include<stack>
#include<queue>
using namespace std;
class Node{
    int data;
    Node* left;
    Node* right;

    public:
    Node(int data = 0) : data(data), left(nullptr), right(nullptr) {} 

    friend class BinaryTree;
};

class BinaryTree{
    private:
    

    public:
    Node* root;
    BinaryTree()
    {
        root = nullptr;
        root = createTree(root);
    }

    Node* createTree(Node* root)
    {
        int d;
        cout<<"Enter data : ";
        cin>>d;

        if(d==-1)
            return nullptr;

        root = new Node(d);

        cout<<"Enter data to left of "<<d<<endl;
        root->left = createTree(root->left);
        cout<<"Enter data to right of "<<d<<endl;
        root->right = createTree(root->right);

        return root;
    }

    void Preorder(Node* root)
    {
        stack<Node*> s;
        s.push(root);

        cout<<"\nPreorder : ";
        while (!s.empty())
        {
            Node* curr = s.top();
            s.pop();

            cout<<curr->data<<" ";

            if(curr->right)
                s.push(curr->right);

            if(curr->left)
                s.push(curr->left);
        }
        cout<<endl;
    }

    void Inorder(Node* root)
    {
        stack<Node*> s;
        Node* curr = root;

        cout<<"\nInorder : ";
        while (!s.empty() || curr!=nullptr)
        {
            while(curr)
            {
                s.push(curr);
                curr = curr->left;
            }

            curr = s.top();
            s.pop();

            cout<<curr->data<<" ";

           
            curr = curr->right;
            
        }
        cout<<endl;
    }

    void Postorder(Node* root)
    {
        cout<<"\nPostorder : ";
        stack<Node*> s1;
        stack<Node*> s2;
        s1.push(root);

        
        while (!s1.empty())
        {
            Node* curr = s1.top();
            s1.pop();
            s2.push(curr);

            if(curr->left)
                s1.push(curr->left);

            if(curr->right)
                s1.push(curr->right);     
        }

        while (!s2.empty())
        {
            Node* curr = s2.top();
            s2.pop();
            cout<<curr->data<<" ";
        }
        cout<<endl;
    }

    void LevelOrderTraversal(Node* root)
    {
        queue<Node*> q;
        q.push(root);
        q.push(nullptr);

        while(!q.empty())
        {
            Node* curr = q.front();
            q.pop();

            if(!curr)
            {
                cout<<endl;

                if(!q.empty())
                {
                    q.push(nullptr);
                }
            }
            else
            {
                cout<<curr->data<<" ";

                if(curr->left) q.push(curr->left);
                if(curr->right) q.push(curr->right);
            }

        }

    }

    int height(Node* root)
    {
        if(!root)
            return 0;

        int l_height = height(root->left);
        int r_height = height(root->right);

        return 1+max(l_height, r_height);
    }

    void swapTree(Node* root)
    {
        if(!root)
            return;

        Node* temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
    int countLeafNodes(Node* root)
    {
        if(!root)
        return 0;

        int num = 0;

        if(!root->left && !root->right)
        {
            num = 1;
        }

        return num + countLeafNodes(root->left) + countLeafNodes(root->right);
    }

    int countInternalNodes(Node* root)
    {
        if(!root)
        return 0;

        int num = 0;

        if(root->left || root->right)
        {
            num = 1;
        }

        return num + countInternalNodes(root->left) + countInternalNodes(root->right);
    }



};

int main()
{
    BinaryTree tree;
    tree.Preorder(tree.root);
    tree.Inorder(tree.root);
    tree.Postorder(tree.root);
    tree.LevelOrderTraversal(tree.root);

    cout<<"\nHeight : "<<tree.height(tree.root)<<endl;
    cout<<"\nLeaf Nodes : "<<tree.countLeafNodes(tree.root)<<endl;
    cout<<"\nInternal : "<<tree.countInternalNodes(tree.root)<<endl;

    tree.swapTree(tree.root);
    tree.Inorder(tree.root);
    
}
