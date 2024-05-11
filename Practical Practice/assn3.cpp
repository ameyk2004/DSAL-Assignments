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
    friend class Pair;
};

class Pair{
    Node* parent;
    Node* child;

    public:
    Pair(Node* p, Node* c) : parent(p), child(c) {}
    friend class TBST;
};

class TBST{
    Node* header;
    public:

    TBST()
    {
        header = new Node(-1);
        header->left = header;
        header->right = header;
    }

    void insertAtLeft(Node* parent, Node* child)
    {
        
        child->left = parent->left;
        child->lthread = parent->lthread;

        parent->left = child;
        parent->lthread = false;

        child->right = parent;
    }

    void insertAtRight(Node* parent, Node* child)
    {
        child->right = parent->right;
        child->rthread = parent->rthread;

        parent->right = child;
        parent->rthread = false;

        child->left = parent;
    }

    void insert(int data)
    {
        Node* newnode = new Node(data);
        if(header->lthread)
        {
            insertAtLeft(header,newnode);
            return;
        }

        Node* root = header->left;

        while(root)
        {
            if(data < root->data && !root->lthread)
            {
                root = root->left;
            }
            else if(data > root->data && !root->rthread)
            {
                root = root->right;
            }
            else if(data < root->data && root->lthread)
            {
                insertAtLeft(root, newnode);
                break;
            }
            else if(data > root->data && root->rthread)
            {
                insertAtRight(root, newnode);
                break;
            }
            else{
                cout<<"DUPLICATE"<<endl;
                return;
            }
        }
            
    }

    Node* leftmost(Node* node){
        if(!node) return NULL;
        while(!node->lthread){
            node = node->left;
        }
        return node;
    }
    
    Node* rightmost(Node* node){
        if(!node) return NULL;
        while(!node->rthread){
            node = node->right;
        }
        return node;
    }

    void inorder()
    {
        Node* curr = leftmost(header->left);

        while(curr!=header)
        {
            cout<<curr->data<<" ";
            if(curr->rthread)
            curr = curr->right;
            else
            curr = leftmost(curr->right);
        }
    }

    void Preorder()
    {
        Node* curr = header->left;
        cout<<"\n\n"<<endl;
        while (curr!=header)
        {
           cout<<curr->data<<" ";

           if(!curr->lthread)
           {
                curr = curr->left;
           }
           else if(!curr->rthread)
           {
                curr = curr->right;
           }
           else{
            while(curr->rthread && curr!=header)
            {
                curr = curr->right;
            }

            if(curr==header) break;

            curr = curr->right;
           }

        }
        

    }

    Pair search(int data){
        if(header->lthread){
            return Pair(NULL,NULL);
        }
        
        Node* parent = header;
        Node* curr = header->left;
        while(curr->data != data){
            parent = curr;
            if(curr->data > data && curr->lthread) return Pair(NULL, NULL);
            else if(curr->data > data) curr = curr->left;
            else if(curr->data < data && curr->rthread) return Pair(NULL,NULL);
            else curr = curr->right;
        }
        return Pair(parent, curr);
    }

    void deleteNode(int data)
    {
        Pair p = search(data);
        Node* parent = p.parent;
        Node* curr = p.child;

        if(curr->lthread && curr->rthread)
        {
            noChildCase(parent, curr);
        }
        else if(curr->lthread || curr->rthread)
        {
            oneChildCase(parent, curr);
        }
        else
        {
            bothChildCase(parent, curr);
        }

    }

    void noChildCase(Node* parent, Node* child)
    {
        if(parent->left){
            parent->left = child->left;
            parent->lthread = child->lthread;
            return;
        }
        else if(parent->right){
            parent->right = child->right;
            parent->rthread = child->rthread;
            return;
        }
    }

    void oneChildCase(Node* A, Node* B)
    {
        Node* C;
        if(!B->lthread) C=B->left;
        else C = B->right;

        if(A->left == B && C == B->left )
        {
            A->left = C;
            C = rightmost(C);
            C->right = A;
        }
        else if(A->left == B && C == B->right)
        {
            A->left = C;
            C = leftmost(C);
            C->left = B->left;
        }
        else if(A->right == B && C == B->left)
        {
            A->right = C;
            C = rightmost(C);
            C->right = B->right;
        }
        else if(A->right == B && C == B->right)
        {
            A->right = C;
            C = leftmost(C);
            C->left = A;
        }
    }

    void bothChildCase(Node* parent, Node* curr)
    {
       Node* inorderSuccessor = curr->right;
        Node* parentOfInorderSuccessor = curr;
        while(!inorderSuccessor->lthread){
            parentOfInorderSuccessor = inorderSuccessor;
            inorderSuccessor = inorderSuccessor->left;
        }
        
        curr->data = inorderSuccessor->data;
        
        if(!inorderSuccessor->lthread&&!inorderSuccessor->rthread){
            noChildCase(parentOfInorderSuccessor, inorderSuccessor);
        }
        else if(!inorderSuccessor->lthread || !inorderSuccessor->rthread){
            oneChildCase(parentOfInorderSuccessor, inorderSuccessor);
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
    tree.inorder();
    // tree.Preorder();
    tree.deleteNode(28);

    cout<<endl;
    cout<<endl;

    cout<<endl;
    tree.inorder();


}