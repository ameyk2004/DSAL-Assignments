#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Student{
    int roll;
    string name;
    int loc;

    public:
    Student(){
        roll = -1;
        name = "";
        loc = -1;
    }
    Student(int roll, string name, int loc){
        this->roll = roll;
        this->name = name;
        this->loc = loc;
    }

    friend class Table;
    friend fstream &operator<<(fstream &f, Student &s);
    friend fstream &operator>>(fstream &f, Student &s);
};

fstream &operator<<(fstream &f, Student &s){
    f<<s.roll<<endl;
    f<<s.name<<endl;
    f<<s.loc<<endl;
    return f;
}

fstream &operator>>(fstream &f, Student &s){
    f>>s.roll;
    f>>s.name;
    f>>s.loc;
    return f;
}

class Table{
    Student *arr;
    int tableSize;

    public:

    //constructor to set all the values to 0
    Table(int tableSize){
        this->tableSize = tableSize;
        arr = new Student[tableSize];
    }

    int hashFunction(int x){
        return x%tableSize;
    }

    void insert(Student s){
        int r = s.roll;
        int h = hashFunction(r);
        if(arr[h].roll==-1){
            arr[h] = s;
            return;
        }
        for(int i=0; i<tableSize-1; i++){
            h = (h+1)%tableSize;
            if(arr[h].roll==-1){
                arr[h] = s;
                return;
            }
        }
        cout<<"Table is full!";
        return;
    }

    void deleteStudent(int roll){
        Student str[tableSize];
        fstream f1;
        f1.open("data.txt", ios::in);
        for(int i=0; i<tableSize; i++){
            f1>>str[i];
        }
        f1.close();
        f1.open("data.txt", ios::out);
        for(int i=0; i<tableSize; i++){
            if(str[i].roll!=roll)
            f1<<str[i];
        }

        int h = hashFunction(roll);
        if(arr[h].roll == roll){
            arr[h].name = "";
            arr[h].roll = -1;
            arr[h].loc = -1;
        }
        else{
            for(int i=0; i<tableSize-1; i++){
                h = (h+1)%tableSize;
                if(arr[h].roll == roll){
                arr[h].name = "";
                arr[h].roll = -1;
                arr[h].loc = -1;
        }
            }
        }
    }

    int search(int roll){
        int h = hashFunction(roll);
        if(arr[h].roll == roll)
        return arr[h].loc;
        for(int i=0; i<tableSize-1; i++){
            h = (h+1)%tableSize;
            if(arr[h].roll == roll)
            return arr[h].loc;
        }
        return -1;
    }

    void printTable(){
        for(int i=0; i<tableSize; i++){
            cout<<arr[i].roll<<" : "<<arr[i].name<<" @ "<<arr[i].loc<<endl;
        }
    }
};

void showStudent(Table &t, int roll){
        int loc = t.search(roll);
        if(loc == -1){
            cout<<"Student not found!";
            return;
        }
        fstream f1;
        f1.open("data.txt", ios::in);
        f1.seekp(loc);
        string line;
        for(int i=0; i<2; i++){
            getline(f1, line);
            cout<<line<<endl;
        }
    }

int main(){
    Table t1(5);
    Student adv;
    int roll;
    string name;
    fstream f1;
    f1.open("data.txt", ios::out);
    for(int i=0; i<5; i++){
        cin>>roll>>name;
        Student s(roll, name, f1.tellg());
        t1.insert(s);
        f1<<s;
    }
    f1.close();
    // t1.printTable();
    // t1.deleteStudent(12);
    t1.printTable();
    t1.deleteStudent(28);
    showStudent(t1, 29);
    cout<<"after deletion:"<<endl;
    t1.printTable();
}