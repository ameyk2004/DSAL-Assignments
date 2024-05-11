#include<iostream>
#include<limits.h>

using namespace std;

class Node{
    int k;
    int p;
    int q;
    Node* left;
    Node* right;
public:
    Node() {}
    Node(int k, int p, int q) : k(k), p(p), q(q), left(nullptr), right(nullptr){} //Node created
    friend class OBST;
};

class MatrixElement{
    int weight;
    int cost;
    int root;

    public:
    MatrixElement() {}
    MatrixElement(int w, int c, int r) : weight(w), cost(c), root(r) {}

    friend class OBST;
};

class OBST{
    MatrixElement** matrix;
    int nodes;
    
    Node* nodeList;

    public:
    Node* root;
    OBST(int n=0) : nodes(n+1)
    {
        root = nullptr;
        matrix = new MatrixElement*[nodes];
        nodeList = new Node[nodes];

        for(int i=0;i<nodes;i++)
        {
            matrix[i] = new MatrixElement[nodes];
        }
    }

    void instantiateNodeList()
    {
        cout<<"Ener values of k, p and q"<<endl;
        int k=-1;
        int p=-1;
        int q=-1;
        for(int i = 0;i<nodes;i++)
        {
            if(i!=0)
            {
                cout<<"Enter k"<<i<<" : ";
                cin>>k;
                cout<<"Enter p"<<i<<" : ";
                cin>>p;
            }
            cout<<"Enter q"<<i<<" : ";
            cin>>q;

            nodeList[i] = Node(k,p,q);
        }
    }

    void instantiateMatrix()
    {
        for(int i=0;i<nodes;i++)
        {
            for(int j=0;j<nodes;j++)
            {
                if(i==j)
                {
                    // cout<<i<<" "<<j<<endl;
                    matrix[i][j] = MatrixElement(nodeList[i].q,0,-1);
                }
                else
                {
                  matrix[i][j] = MatrixElement(-1,-1,-1);
                }
                
            }
        }

    }

    void optimise()
    {
        for(int diff = 0; diff<nodes;diff++)
        {
            for(int i = 0; i<nodes;i++)
            {
               for(int j = 0; j<nodes;j++)
               {
                    if(diff==j-i)
                    {
                        C(i,j);
                    }
               }
            }
        }
    }

    int C(int i, int j)
    {
        if(i>=j) return 0;
        if(matrix[i][j].cost != -1) return matrix[i][j].cost;

        int minCost = INT_MAX;
        int minRoot = -1;

        for(int k=i+1;k<=j;k++)
        {
            int cost = C(i,k-1) + C(k,j) + W(i,j);

            if(cost < minCost)
            {
                minCost = cost;
                minRoot = k;
            }
        }

        matrix[i][j].root = minRoot;
        matrix[i][j].cost = minCost;



        return minCost;

    }

    int W(int i, int j)
    {
        if(i>j) return 0;
        if(i==j) return matrix[i][j].weight;

        if(matrix[i][j].weight!=-1) return matrix[i][j].weight;

        int weight = W(i,j-1) + nodeList[j].p + nodeList[j].q;

        matrix[i][j].weight = weight;
        // cout<<"Weight for "<<i<<" "<<j<<" = "<<weight<<endl;
        return weight;
    }

    void dispNodeList()
    {
        for(int i=0;i<nodes;i++)
        {
            cout<<nodeList[i].k<<" "<<nodeList[i].p<<" "<<nodeList[i].q<<endl;
        }
    }
    
    Node* createTree(int i, int j)
    {
        cout<<"i = "<<i<<" j = "<<j<<endl;
        if(i>=j) return nullptr;
        int k = matrix[i][j].root;
        // cout<<"i = "<<i<<" j = "<<j<<" "<<k<<" "<<endl;
        Node* node = &nodeList[k];
        node->left = createTree(i,k-1);
        node->right = createTree(i,j);

        return node;
    }

    void inorder(Node* node){
        if(!node) return;
        inorder(node->left);
        cout<<node->k<<" ";
        inorder(node->right);
    }

    void printMatrix()
    {
        cout<<"\n\n";
        for(int i=0;i<nodes;i++)
        {
            for(int j=0;j<nodes;j++)
            {
                cout<<matrix[i][j].cost<<" ";
            }

            cout<<endl;
        }
    }

};

int main()
{
    OBST tree(4);
    tree.instantiateNodeList();
    tree.instantiateMatrix();
    tree.printMatrix();
    // tree.dispNodeList();
    tree.optimise();

    tree.printMatrix();
    tree. root = tree.createTree(0,4);
    tree.inorder(tree.root);
}