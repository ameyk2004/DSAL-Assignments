// Write menu driven C++ program to
// 1) Represent a given graph using adjacency list/Adjacency Matrix. 
//    Use the map of the area around the college as the graph
// 2) Display Graph
// 3) Perform DFS traversal using recursive/non-recursive algorithm.
// 4) Perform BFS traversal.

// Note: Write your own Queue class

#include<iostream>
#include<queue>
#include<stack>
using namespace std;

class Node{
    int vertex;
    Node* next;

    public:
    Node(int v = 0, Node* n = nullptr): vertex(v), next(n) {}

    friend class Graph;
};
class Graph{
    private:
    Node **adj;
    bool direction;
    int nodes;

    public:
        Graph(int n, bool d) : nodes(n), direction(d) {
            adj = new Node*[nodes];

            for(int i = 0; i<nodes; i++)
            {
                adj[i] = nullptr;
            }
            cout<<"adjacency list initialized"<<endl;
        }

        void displayGraph()
        {
            cout<<"\n\nGraph Adjacency List"<<endl;
            cout<<"----------------------------"<<endl;
            for(int i=0;i<nodes;i++)
            {
                cout<<i<<" -> ";
                Node* head = adj[i];

                while(head)
                {
                    cout<<head->vertex<<" ";
                    head = head->next;
                }
                cout<<endl;
            }
            cout<<"----------------------------"<<endl;
        }

        void push_back(int u, int v)
        {
            Node* newNode = new Node(v);
            if(adj[u] == nullptr)
            {
                
                adj[u] = newNode;
                return; 
            }

            Node* temp = adj[u];
            Node* prev = nullptr;
            while (temp)
            {
                prev = temp;
                temp = temp->next;
            }

            prev->next = newNode;

        }

        void addEdge(int u, int v)
        {
            // cout<<u<<" "<<v<<endl;

            if(u>=nodes || v>=nodes || u<0 || v<0)
            {
                cout<<u<<" -> "<<v<<" edge is NOT VALID"<<endl;
                return;
            }

            if(direction)
            {
                push_back(u,v);
            }
            else
            {
                push_back(u,v);
                push_back(v,u);
            }
            cout<<"edge created "<<endl;
        }


        void bfs(int start = 0)
        {
            if(start < 0 || start > nodes)
            {
                cout<<"Invalid Start Index "<<endl;
                return;
            }

            bool* visited = new bool[nodes];

            for(int i=0;i<nodes;i++)
            {
                visited[i] = false;
            }

            queue<int> q;
            q.push(start);
            visited[start] = true;

            cout<<"BFS Traversal : ";

            while(!q.empty())
            {
                int u = q.front();
                cout<<u<<" ";
                q.pop();

                Node* temp = adj[u];

                while (temp)
                {
                    if(!visited[temp->vertex])
                    {
                        q.push(temp->vertex);
                        visited[temp->vertex] = true;
                    }
                    temp = temp->next;
                }
            }
            cout<<endl;



        }

};


int main()
{
    Graph G(5,1);
    G.addEdge(0,1);
    G.addEdge(0,4);
    G.addEdge(0,3);
    G.addEdge(4,3);
    G.addEdge(1,3);
    G.addEdge(3,2);    
    G.addEdge(1,2);
    G.displayGraph();
    G.bfs();


}