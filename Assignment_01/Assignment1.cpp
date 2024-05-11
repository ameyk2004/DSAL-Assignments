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
    Node(int val=0) : data(val), left(nullptr), right(nullptr) {}
    friend class BinaryTree;
};

class BinaryTree{
    public:
    Node* root;

    BinaryTree()
    {
        root = nullptr;
        root = createTree(root);
    }

    Node* createTree(Node* root)
    {
        int data = 0;

        cout<<"Enter data : ";
        cin>>data;

        if(data == -1)
            return nullptr;

        root = new Node(data);

        cout<<"Enter data for left of "<<data<<endl;
        root->left = createTree(root->left);
        cout<<"Enter data for right of "<<data<<endl;
        root->right = createTree(root->right);

        return root;
    }

    //Traversals

    //1. Recursive Travesals
    
    void RecursivePreorder(Node* root)
    {
        if(!root)
            return;

        cout<<root->data<<" ";
        RecursivePreorder(root->left);
        RecursivePreorder(root->right);
    }

    void RecursiveInorder(Node* root)
    {
        if(!root)
            return;

        RecursiveInorder(root->left);
        cout<<root->data<<" ";
        RecursiveInorder(root->right);
    }

    void RecursivePostorder(Node* root)
    {
        if(!root)
            return;

        RecursivePostorder(root->left);
        RecursivePostorder(root->right);
        cout<<root->data<<" ";
    }

    //2. Iterative Traversals

    void IterativePreorder()
    {
        if (root == nullptr)
        return;

        Node* treePtr = this->root;
        stack<Node*> nodeStack;

        nodeStack.push(treePtr);

        while(!nodeStack.empty())
        {
            treePtr = nodeStack.top();
            nodeStack.pop();

            cout<<treePtr->data<<" ";
            
            if(treePtr->right)
            {
                nodeStack.push(treePtr->right);
            }
            if(treePtr->left)
            {
                nodeStack.push(treePtr->left);
            }
        }
    
        cout<<endl;
    }

    void IterativeInorder()
    {
        if (root == nullptr)
        return;

        Node* curr = root;
        stack<Node*> nodeStack;

        while(!nodeStack.empty() || curr!=nullptr)
        {
            
            while (curr!=nullptr)
            {
                nodeStack.push(curr);
                curr = curr->left;
            }

            curr = nodeStack.top();
            cout<<curr->data<<" ";
            nodeStack.pop();

            curr = curr->right;
        }
        cout<<endl;
    }

    void IterativePostorder()
    {
        if (root == nullptr)
        return;

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
           {
            nodeStack_1.push(curr->left);
           }

           if(curr->right)
           {
            nodeStack_1.push(curr->right);
           }
        
        }

        while (!nodeStack_2.empty())
        {
            curr = nodeStack_2.top();
            nodeStack_2.pop();
            cout<<curr->data<<" ";
        }
        
        cout<<endl;

    }

    void LevelOrderTraversal()
    {
        Node* curr = root;
        queue<Node*> nodeQueue;

        nodeQueue.push(root);
        nodeQueue.push(nullptr);

        while (!nodeQueue.empty())
        {
            curr = nodeQueue.front();
            nodeQueue.pop();

            if(!curr)
            {
                cout<<endl;

                if(!nodeQueue.empty())
                nodeQueue.push(nullptr);
            }
            else{
                cout<<curr->data<<" ";
                if(curr->left)
                    nodeQueue.push(curr->left);
                if(curr->right)
                    nodeQueue.push(curr->right);
            }
            
        }
    }

    //Height 

    int height(Node* root)
    {
        if (!root)
            return 0;

        int l_height = height(root->left);
        int r_height = height(root->right);

        return 1 + max(l_height, r_height);
    }

    //Leaf Nodes 
    int countLeafNodes(Node* root)
    {
        if(!root)
            return 0;

        int num = 0;

        if(root->left == nullptr  && root->right == nullptr)
        {
            num = 1;
        }

        return num+countLeafNodes(root->left)+countLeafNodes(root->right);;
    }

    int countInternalNodes(Node* root)
    {
        if(!root)
            return 0;

        int num = 0;

        if(root->left != nullptr  || root->right != nullptr)
        {
            num = 1;
        }

        return num+countInternalNodes(root->left)+countInternalNodes(root->right);;
    }

    void swapTree(Node* root)
    {
        if(!root)
            return;

        Node* temp = root->left;
        root->left = root->right;
        root->right = temp;
        
    }

};
class Menu {
public:
    void displayMenu() {
        cout << "\n\n\nBinary Tree Operations Menu" << endl;
        cout << "1. Perform Recursive Preorder Traversal" << endl;
        cout << "2. Perform Recursive Inorder Traversal" << endl;
        cout << "3. Perform Recursive Postorder Traversal" << endl;
        cout << "4. Perform Iterative Preorder Traversal" << endl;
        cout << "5. Perform Iterative Inorder Traversal" << endl;
        cout << "6. Perform Iterative Postorder Traversal" << endl;
        cout << "7. Perform Level Order Traversal" << endl;
        cout << "8. Display Height of the Tree" << endl;
        cout << "9. Display Number of Leaf Nodes" << endl;
        cout << "10. Display Number of Internal Nodes" << endl;
        cout << "11. Swap Left and Right Children of Every Node" << endl;
        cout << "12. Exit" << endl;
    }

    void performOperation(BinaryTree& tree, int choice) {
        switch(choice) {
            case 1:
                cout << "\nRecursive Preorder Traversal: ";
                tree.RecursivePreorder(tree.root);
                cout << endl;
                break;
            case 2:
                cout << "\nRecursive Inorder Traversal: ";
                tree.RecursiveInorder(tree.root);
                cout << endl;
                break;
            case 3:
                cout << "\nRecursive Postorder Traversal: ";
                tree.RecursivePostorder(tree.root);
                cout << endl;
                break;
            case 4:
                cout << "\nIterative Preorder Traversal: ";
                tree.IterativePreorder();
                cout << endl;
                break;
            case 5:
                cout << "\nIterative Inorder Traversal: ";
                tree.IterativeInorder();
                cout << endl;
                break;
            case 6:
                cout << "\nIterative Postorder Traversal: ";
                tree.IterativePostorder();
                cout << endl;
                break;
            case 7:
                cout << "\nLevel Order Traversal: ";
                tree.LevelOrderTraversal();
                cout << endl;
                break;
            case 8:
                cout << "\nHeight of the Tree: " << tree.height(tree.root) << endl;
                break;
            case 9:
                cout << "\nNumber of Leaf Nodes: " << tree.countLeafNodes(tree.root) << endl;
                break;
            case 10:
                cout << "\nNumber of Internal Nodes: " << tree.countInternalNodes(tree.root) << endl;
                break;
            case 11:
                tree.swapTree(tree.root);
                cout << "\nLeft and Right Children of Every Node Swapped." << endl;
                break;
            case 12:
                cout << "\nExiting..." << endl;
                exit(0);
            default:
                cout << "Invalid choice! Please enter a valid option." << endl;
        }
    }

    void run(BinaryTree& tree) {
        int choice;
        do {
            displayMenu();
            cout << "Enter your choice: ";
            cin >> choice;
            performOperation(tree, choice);
            cout << endl;
        } while(choice != 12);
    }
};

int main() {
    BinaryTree tree;
    Menu menu;
    menu.run(tree);
    return 0;
}