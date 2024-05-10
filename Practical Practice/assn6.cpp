#include<iostream>
#include<queue>
#include<stack>
using namespace std;

class Node{
    int vertex;
    int weight;
    Node* next;

    public:
    Node() {}
    Node(int v, int w) : vertex(v), weight(w) {}

    friend class Graph;
    
};

class Graph{
    Node** adj;
    string* cityNames;
    bool direction;
    int nodes;

public:
    Graph(int n, bool d)
    {
        nodes = n;
        direction = d;
        cityNames = new string[nodes];
        adj = new Node*[nodes];
        for(int i=0;i<nodes;i++)
        {
            adj[i] = nullptr;
            cityNames[i] = "";
        }
    }

    void push_back(int u, int v, int w)
{
    Node* newNode = new Node(v, w);
    if (!adj[u])
    {
        adj[u] = newNode;
        return;
    }
    Node* temp = adj[u];
    while (temp->next)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

    void addEdge(int u, int v, int w)
    {
        if(u>=nodes || v>=nodes || u<0 || v<0 )
        {
            cout<<"Invalid edge"<<endl;
            return;

        }

        if(!direction)
        {
            push_back(v,u,w);
        }
        push_back(u,v,w);

    }

    void addCities(string* cities)
    {
        for(int i=0;i<nodes;i++)
        {
            cityNames[i] = cities[i];
        }
    }

    void printAdjacencyList()
    {
        cout<<"\n\nAdjacency List"<<endl;
        for(int i = 0; i<nodes; i++)
        {
            cout<<cityNames[i]<<" -> ";
            Node* temp = adj[i];

            while(temp)
            {
                cout<<cityNames[temp->vertex];
                cout<<"("<<temp->weight<<") ";
                temp = temp->next;
            }
            
            cout<<endl;
        }
    }

    void bfs(int start = 0)
    {
        queue<int> q;

        bool* visited = new bool[nodes];
        for(int i=0;i<nodes;i++)
        {
            visited[i] = false;
        }
        
        q.push(start);
        visited[start] = true;
        cout<<"\nBFS : ";
        while(!q.empty())
        {
            int vertex = q.front();
            q.pop();

            cout<<cityNames[vertex]<<" ";

            Node* temp = adj[vertex];
            while(temp)
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

    void dfsRec(int v, bool* &visited)
    {
        cout<<cityNames[v]<<" ";
        visited[v] = true;

        Node* temp = adj[v];
        while(temp)
        {
            if (!visited[temp->vertex])
            {
                dfsRec(temp->vertex,visited);
            }
            
            temp = temp->next;
        }

    }

    void dfs(int start = 0)
    {
        stack<int> s;

        bool* visited = new bool[nodes];
        for(int i=0;i<nodes;i++)
        {
            visited[i] = false;
        }
        
        s.push(start);
        visited[start] = true;
        cout<<"\nDFS : ";
        while (!s.empty())
        {
            int vertex = s.top();
            s.pop();

            
            cout<<cityNames[vertex]<<" ";

            Node* temp = adj[vertex];
            while(temp)
            {
                if(!visited[temp->vertex])
                {
                    s.push(temp->vertex);
                    visited[temp->vertex] = true;
                }
                    temp = temp->next;
            }

        }  
        cout<<endl;    
    }

    void dfcRecHelper(int start=0)
    {
        bool* visited = new bool[nodes];
        for(int i=0;i<nodes;i++)
        {
            visited[i] = false;
        }
        cout<<"\nDFS REC : ";
        dfsRec(start, visited);
    }

    void primsMST(int start = 0)
{
    bool* visited = new bool[nodes];
    int* parent = new int[nodes];
    int* key = new int[nodes]; 

    for (int i = 0; i < nodes; i++)
    {
        visited[i] = false;
        parent[i] = -1;
        key[i] = INT_MAX;
    }

    key[start] = 0;
    parent[start] = -1;
    int totalWeight = 0;

    for (int i = 0; i < nodes; i++)
    {
        int minVertex = -1;
        int minKey = INT_MAX;

        for (int j = 0; j < nodes; j++)
        {
            if (!visited[j] && key[j] < minKey)
            {
                minKey = key[j];
                minVertex = j;
            }
        }

        if (minVertex == -1)
            break;

        totalWeight += minKey;
        visited[minVertex] = true;

        Node* curr = adj[minVertex];
        while (curr)
        {
            if (!visited[curr->vertex] && curr->weight < key[curr->vertex])
            {
                key[curr->vertex] = curr->weight;
                parent[curr->vertex] = minVertex;
            }
            curr = curr->next;
        }
    }

    for (int i = 0; i < nodes; i++)
    {
        if (parent[i] != -1)
            cout << cityNames[parent[i]] << " - " << cityNames[i] << " (" << key[i] << ") " << endl;
    }

    cout << "--- TOTAL WEIGHT = " << totalWeight << " ---" << endl << endl;

    // Deallocate memory
    delete[] visited;
    delete[] parent;
    delete[] key;
}

    


};

int main()
{
    string cities[] = {"a","b","c","d","e","f","g"};
    Graph G(7,0);
    G.addCities(cities);
    G.addEdge(0, 3, 4);
    G.addEdge(0, 5, 5);
    G.addEdge(0, 1, 2);
    G.addEdge(1, 3, 1);
    G.addEdge(1, 5, 8);
    G.addEdge(1, 4, 3);
    G.addEdge(1, 2, 7);
    G.addEdge(1, 6, 4);
    G.addEdge(2, 4, 10);
    G.addEdge(2, 6, 6);
    G.addEdge(3, 4, 2);
    G.addEdge(5, 6, 1);
    G.printAdjacencyList();
    G.bfs();
    G.dfs();
    G.dfcRecHelper();
    G.primsMST();
    
}