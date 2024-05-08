/*
Implement all the functions of a dictionary (ADT) using open hashing technique: separate 
chaining using linked list Data: Set of (key, value) pairs, Keys are mapped to values, Keys 
must be comparable, and Keys must be unique. Standard Operations: Insert (key, value), 
Find(key), Delete(key). 

Use hash function as H(x) = (3x+5) % 10
*/
#include<iostream>
#include<string>
using namespace std;

class DictNode{
    string key;
    string value;
    DictNode* next;

    public:
    DictNode(): key(""), value(""), next(nullptr) {}
    DictNode(string k, string v): key(k), value(v), next(nullptr) {}
    DictNode(string k, string v, DictNode* n): key(k), value(v), next(n) {}
    friend class Dictionary;
};

class Dictionary{
    private:
    int tableSize;
    DictNode **table; //table to store head of linked list in open hashing

    public:
    Dictionary(int size=10) : tableSize(size) {
        table = new DictNode*[tableSize];
        for(int i=0;i<tableSize;i++)
        {
            table[i] = new DictNode();
        }
    }

    void printTable()
    {
        cout<<"\n\n"<<endl;
        for(int i = 0; i<tableSize;i++)
        {
            cout<<"----------------------"<<endl;
            DictNode* temp = table[i];
            cout<<i<<" : "<<endl;
            
            while(temp)
            {
                
                if(temp->key!="")
                cout<<temp->key<<" : "<<temp->value<<endl;
                temp = temp->next;
                
            }
            
        }
    }

    string toLowerString(string k)
    {
        string newStr = "";
        for(int i = 0; i<k.length();i++)
        {
            char ch = k[i];
            newStr+=tolower(ch);
        }
        return newStr;
    }
    int calculateHash(string key)
    {
        int hash = 0;
        for(int i = 0; i<key.length();i++)
        {
            char ch = key[i];
            hash = hash+= (int) ch;
        }
        return hash;
    }

    int hashFunction(string key)
    {
        int index = 0;
        int x = calculateHash(key);

        index = (3*x + 5) % tableSize;
        return index;
    }

    void insert(string key, string value)
    {
        key = toLowerString(key);
        int index = hashFunction(key);

        if(table[index]->key == "")
        {
            table[index] = new DictNode(key, value);
            cout<<"Key Inserted"<<endl;
            return;
        }
        else
        {
            DictNode* temp =  table[index];
            DictNode* prev = nullptr;

            while(temp)
            {
                if(temp->key == key)
                {
                    cout<<"key "<<key<<" aldready present"<<endl;
                    return;
                }
                prev = temp;
                temp = temp->next;
            }
            
            DictNode* newNode = new DictNode(key, value);
            prev->next = newNode;
        }
    
    }

    void searchKey(string key)
    {
        key = toLowerString(key);
        int index = hashFunction(key);

        DictNode* temp = table[index];

        while(temp)
        {
            if(temp->key == key)
            {
                cout<<"\n\nRecord Found"<<endl;
                cout<<key<<" : "<<temp->value<<endl;
                return;
            }
            temp = temp->next;
        }

        cout<<"Key does not exist"<<endl;

    }

    void deleteKey(string key)
    {
        key = toLowerString(key);
        int index = hashFunction(key);

        DictNode* temp = table[index];
        DictNode* prev = temp;

        if(temp->key == key) // to delete first node
        {
            table[index] = temp->next;
            cout<<"deleted"<<endl;
            return;
        }
        

        while(temp)
        {
            if(temp->key == key)
            {
                prev->next  = temp->next;
                cout<<"deleted"<<endl;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        cout<<"Key does not exist"<<endl;
    }

};

class Menu {
public:
    static void displayMenu(Dictionary &dict) {
        int choice;
        string key, value;

        do {
            cout << "\n\nOperations to do:" << endl;
            cout << "1. Insert" << endl;
            cout << "2. Display Table" << endl;
            cout << "3. Search Key" << endl;
            cout << "4. Delete Key" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch(choice) {
                case 1:
                    cout << "\nEnter key: ";
                    cin >> key;
                    cout << "Enter value: ";
                    cin >> value;
                    dict.insert(key, value);
                    break;
                case 2:
                    dict.printTable();
                    break;
                case 3:
                    cout << "\nEnter key to search: ";
                    cin >> key;
                    dict.searchKey(key);
                    break;
                case 4:
                    cout << "Enter key to delete: ";
                    cin >> key;
                    dict.deleteKey(key);
                    break;
                case 5:
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << "Invalid choice!" << endl;
            }
        } while(choice != 5);
    }
};
int main()
{
    Dictionary dict;
    Menu::displayMenu(dict);
}
