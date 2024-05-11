#include<iostream>
using namespace std;

class Node{
    private:
    string data;
    string value;
    Node* left;
    Node* right;
    int height;

    public:
    Node(string d, string v) {
        data = d;
        value = v;
        left = nullptr;
        right = nullptr;
        height = 1;
    }

    friend class AVLTree;
};

class AVLTree{
    Node* root;

    public:
    AVLTree()
    {
        root = nullptr;
    }

    Node* rotateRight(Node* A)
    {
        Node* B = A->left;
        Node* C = B->right;

        A->left = C;
        B->right = A;

        A->height = 1 + max(getHeight(A->left), getHeight(A->right));
        B->height = 1 + max(getHeight(B->left), getHeight(B->right));

        return B;
    }

    Node* rotateLeft(Node* A)
    {
        Node* B = A->right;
        Node* C = B->left;

        A->right = C;
        B->left = A;

        A->height = 1 + max(getHeight(A->left), getHeight(A->right));
        B->height = 1 + max(getHeight(B->left), getHeight(B->right));

        return B;
    }



    Node* insert(Node* node, string d, string v)
    {
        if(!node)
        {
            return new Node(d,v);
        }

        if(d < node->data)
        {
            node->left =  insert(node->left, d, v);
        }
        else if(d > node->data)
        {
           node->right = insert(node->right, d, v);
        }
        else{
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int bf = getBalanceFactor(node);

        if(bf > 1 && d<node->left->data)
        {
            cout<<"LL Rotation"<<endl;
            return rotateRight(node);
        }
        else if(bf > 1 && d>node->left->data)
        {
            node->left = rotateLeft(node->left);
            cout<<"LR Rotation"<<endl;
            return rotateRight(node);
        }
        else if(bf < -1 && d<node->right->data)
        {
            node->right = rotateRight(node->right);
            cout<<"RL Rotation"<<endl;
            return rotateLeft(node);
        }
        else if(bf < -1 && d>node->right->data)
        {
            cout<<"RR Rotation"<<endl;
            return rotateLeft(node);
        }
        else
        {
            return node;
        }

    }

    int getHeight(Node* node)
    {
        if(!node) return 0;
        return node->height;
    }

    int getBalanceFactor(Node* node)
    {
        return getHeight(node->left) - getHeight(node->right);
    }

    void insert(string d, string v)
    {
        root = insert(root,d,v);
    }

     void inorder(Node* node){
        if(!node) return;
        inorder(node->left);
        cout<<node->data<<" : "<<node->value<<endl;
        inorder(node->right);
    }

    void inorder(){
        cout<<"==== Inorder ===="<<endl;
        inorder(root);
        cout<<endl;
    }



    
};

int main()
{
    AVLTree tree;
    tree.insert("a","apple");
    tree.insert("b","ball");
    tree.insert("c","cat");
    tree.insert("d","dog");
    tree.insert("e","elephant");
    tree.insert("f","frog");
    tree.insert("g","girl");
    tree.insert("h","horse");
    tree.insert("i","india");
    tree.insert("j","joker");
    tree.insert("k","knife");
    tree.insert("l","lamp");
    tree.insert("m","mango");
    tree.insert("n","noon");
    tree.insert("o","orange");
    
    
    tree.inorder();
}