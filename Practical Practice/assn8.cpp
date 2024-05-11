// Given sequence k = k1, k2, kn, of n sorted keys, with a successful and unsuccessful
// search probability pi and qi for each key ki. Build the Binary search tree that has the least search cost given the access probability
// for each key.

#include<iostream>
#include<limits.h>
using namespace std;

class Node{
    private:
    int k;
    int p;
    int q;

    public:
    Node() {}
    Node(int k,int p, int q) : k(k), p(p), q(q){}
    friend class OBST;
    friend class MatrixElement;
};

class MatrixElement{
    int weight;
    int cost;
    int root;

    public:
    MatrixElement() {}
    MatrixElement(int w,int c, int r) : weight(w), cost(c), root(r) {}

    friend class OBST;
};

class OBST{
    Node* root;
    MatrixElement **matrix;
    Node* nodeList;
    int nodes;

public:
    void instantiateNodeList()
    {
        cout<<"Enter k p q respectively "<<endl;
        int k=-1,p=-1,q=-1;
        for(int i=0;i<nodes;i++)
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

            Node temp =  Node(k,p,q);
            nodeList[i] = temp;
        
        }
    }

    void instantiateMatrix()
    {
        for(int i=0;i<nodes;i++)
        {
            for(int j=0;j<nodes;j++)
            {
                if(i==j)
                matrix[i][j] = MatrixElement(nodeList[i].q,0,-1);
                else
                matrix[i][j] = MatrixElement(-1,-1,-1);
            }
        }
    }

    void printNodelist()
    {
        cout<<"\nNode List"<<endl;
        for(int i=0;i<nodes;i++)
        {
            Node temp = nodeList[i];
            cout<<temp.k<<" "<<temp.p<<" "<<temp.q<<" "<<endl;
        }
        cout<<endl;
    }

    void printMatrix()
    {
        cout<<"\nMatrix"<<endl;
        for(int i=0;i<nodes;i++)
        {
            for(int j=0;j<nodes;j++)
            {
                cout<<matrix[i][j].cost<<" ";
            }
            cout<<endl;
        }
    }

    void optimise()
    {
        for(int diff=0;diff<nodes;diff++)
        {
            for(int i=0;i<nodes;i++)
            {
                for(int j=0;j<nodes;j++)
                {
                    if(diff == j-i)
                    {
                        cout<<"\nCost "<<i<<" "<<j<<": "<<C(i,j)<<endl;
                        cout<<"Weight "<<i<<" "<<j<<": "<<W(i,j)<<endl;
                    }
                    
                }
            }
        }
    }

    int C(int i, int j)
    {
        if(i>=j) return 0;
        if(matrix[i][j].cost !=-1) return matrix[i][j].cost;
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


        matrix[i][j].cost = minCost;
        matrix[i][j].root = minRoot;

        return minCost;
    }

    int W(int i,int j)
    {
        if(i==j) return matrix[i][j].weight;
        if(i>j) return 0;
        if(matrix[i][j].weight != -1) return matrix[i][j].weight;

        int weight = W(i,j-1) + nodeList[j].p + nodeList[j].q;
        matrix[i][j].weight = weight;
        return weight;
    }

    OBST(int n=4)
    {
        nodes = n+1;
        nodeList = new Node[nodes];
        matrix = new MatrixElement*[nodes];
        for(int i=0;i<nodes;i++)
        {
            matrix[i] = new MatrixElement[nodes];
        }
        instantiateNodeList();
        instantiateMatrix();
        printMatrix();
        printNodelist();
        optimise();
    }
};
int main()
{
    OBST tree;
    

    /*
    Reference Question:
    https://youtu.be/wAy6nDMPYAE?si=Pf7gucJCdujIrt3P&t=3141

        0   1   2   3   4
    k   x   10  20  30  40
    p   x   3   3   1   1
    q   2   3   1   1   1

    Total Cost = 36
    Summation of Probabilities = 16
    Final Cost => 36/16 = 2


    direct i/p : 2 10 3 3 20 3 1 30 1 1 40 1 1
*/
// c(0,2) = c(0,0) + c(1,2) + w(0,2)
                    
tree.printMatrix();

}
