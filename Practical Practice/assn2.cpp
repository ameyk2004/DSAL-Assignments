// Construct binary search tree. Provide facility for adding new entries, deleting any element. 
// Provide facility to display whole data sorted in ascending order using non- recursive traversal. 
// Search an element present in a tree and display number of comparisons required to search.
#include<iostream>
#include<stack>
#include<queue>
using namespace std;

class Node{
    int data;
    Node* left;
    Node* right;

    public:
        Node(int val=0) : data(val), left(nullptr), right(nullptr) {}

    friend class BinarySearchTree;

};
class BinarySearchTree{
    public:
    Node* root;


    BinarySearchTree()
    {
        root = createTree(nullptr);
    }

    Node* createTree(Node* root)
    {
        int d = 0;
        cout<<"Enter data (-1 to Stop ) : ";
        cin>>d;

        while (d!=-1)
        {
            insert(root, d);
            cout << "\nEnter : ";
            cin>>d;
            
        }

        return root;
        
    }

    Node* insert(Node* &node, int data)
    {
        if(!node)
        {
            node = new Node(data);
            return node;   
        }

        if(data < node->data)
        {
            node->left = insert(node->left, data);
        }
        else
        {
            node->right = insert(node->right, data);
        }

        return node;
    }

    void RecursivePreorder(Node* root)
    {
        if (!root)
        return;

        cout<<root->data<<" ";
        RecursivePreorder(root->left);
        RecursivePreorder(root->right); 
    }

    void RecursiveInorder(Node* root)
    {
        if (!root)
        return;

        RecursiveInorder(root->left);
        cout<<root->data<<" ";
        RecursiveInorder(root->right);
    }

    void RecursivePostorder(Node* root)
    {
        if (!root)
        return;

        RecursivePostorder(root->left);
        RecursivePostorder(root->right);
        cout<<root->data<<" ";
    }

    void IterativePreorder()
    {
        Node* curr = root;
        stack<Node*> nodeStack;

        nodeStack.push(curr);

        while(!nodeStack.empty()){
            curr = nodeStack.top();
            cout<<curr->data<<" ";
            nodeStack.pop();

            if(curr->right)
            {
                nodeStack.push(curr->right);
            }

            if(curr->left)
            {
                nodeStack.push(curr->left);
            }
        }

        cout<<endl;
    }

    void IterativeInorder()
    {
        Node* curr = root;
        stack<Node*> nodeStack;

        while(!nodeStack.empty() || curr !=nullptr)
        {
            while(curr)
            {
                nodeStack.push(curr);
                curr = curr->left;
            }
            
            curr = nodeStack.top();
            nodeStack.pop();
            cout<<curr->data<<" ";

            curr = curr->right;
        }
        cout<<endl;
    }

    void IterativePostorder()
    {
        Node* curr = root;
        stack<Node*> nodeStack_1;
        stack<Node*> nodeStack_2;
        nodeStack_1.push(curr);

        while (!nodeStack_1.empty())
        {
            curr = nodeStack_1.top();
            nodeStack_1.pop();
            nodeStack_2.push(curr);

            if(curr->left)
                nodeStack_1.push(curr->left);

            if(curr->right)
                nodeStack_1.push(curr->right);

        }
         while (!nodeStack_2.empty())
        {
            curr = nodeStack_2.top();
            cout<<curr->data<<" ";
            nodeStack_2.pop();
        }
        
    }

    void LevelOrderTraversal()
    {
        Node* curr = root;
        queue<Node*> nodeQueue;

        nodeQueue.push(root);
        nodeQueue.push(nullptr);

        while(!nodeQueue.empty())
        {
            curr = nodeQueue.front();
            nodeQueue.pop();

            if(!curr)
            {
                cout<<"\n";

                if(!nodeQueue.empty())
                {
                    nodeQueue.push(nullptr);
                }
            }
            else
            {
                cout<<curr->data<<" ";

                if(curr->left)
                    nodeQueue.push(curr->left);

                if(curr->right)
                    nodeQueue.push(curr->right);
            }
        }
    }

    Node* searchInTree(Node* node, int data, int &attempts) {
        if (!node || node->data == data) {
            return node;
        }

        attempts++;

        if (data < node->data) {
            return searchInTree(node->left, data, attempts);
        }
        else {
            return searchInTree(node->right, data, attempts);
        }
    }

    Node* deleteNode(Node* root, int data)
    {
        if(!root)
            return root;

        if(data < root->data)
        {
            root->left = deleteNode(root->left, data);
        }
        else if(data > root->data)
        {
            root->right = deleteNode(root->right, data);
        }
        else if(data == root->data)
        {
            if(!root->left)
            {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if(!root->right)
            {
                Node* temp = root->left;
                delete root;
                return temp;    
            }
            else
            {
                Node* minNode = leftmost(root->right);
                root->data = minNode->data;
                root->right = deleteNode(root->right, minNode->data);
            }

            
           
        }
        cout<<"Node not found"<<endl;
        return root;
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
    
};

int main()
{
    BinarySearchTree tree;
    cout<<endl;
    tree.RecursiveInorder(tree.root);
    cout<<endl;
    tree.RecursivePreorder(tree.root);
    cout<<endl;
    tree.RecursivePostorder(tree.root);
    cout<<endl;
    cout<<endl;
    cout<<endl;
    tree.IterativePreorder();
    tree.IterativeInorder();
    tree.IterativePostorder();
    cout<<endl;
    cout<<endl;
    tree.LevelOrderTraversal();
    int attempts = 0;
    Node* res = tree.searchInTree(tree.root, 100, attempts);
    if(res)
        cout<<"Ele found searches required : "<<attempts<<endl;

    else
        cout<<"ele not found"<<endl;

    tree.root = tree.deleteNode(tree.root,300);
    tree.IterativeInorder();


}


