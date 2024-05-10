#include<iostream>
#include<fstream>
using namespace std;

class Student{
    int loc;
    int rollno;
    string name;

    public:
    Student() : loc(-1), rollno(-1), name("") {}
    Student(string n, int r, int l) : loc(l), rollno(r), name(n) {}

    friend class HashTable;
    friend class DirectAccessFile;
    friend fstream &operator<<(fstream& file, Student &s);
    friend fstream &operator>>(fstream& file, Student &s);
};

class HashTable{
    Student* table;
    int tableSize;

public:
    HashTable(int size) : tableSize(size)
    {
        table = new Student[tableSize];
    }

    int hashFunction(int rollNum)
    {
        return rollNum % tableSize;
    }

    void insert(Student s)
    {
        int index = hashFunction(s.rollno);
        if(table[index].rollno == -1)
        {
            table[index] = s;
            return;
        }

        for(int i=(index+1)%tableSize; i!=index; i=(i+1)%tableSize)
        {
            if(table[i].rollno == -1)
            {
                table[i] = s;
                return;
            }

        }
    }

    void displayTable()
    {
        cout<<"\nHash Table"<<endl;
        for(int i=0; i<tableSize;i++)
        {
            cout<<i<<" : "<<table[i].name<<endl;
        }

    }
    friend class DirectAccessFile;
};

fstream &operator<<(fstream& file, Student &s) {
        file << s.rollno << endl;
        file << s.name << endl;
        file << s.loc << endl;
        return file;
}

fstream &operator>>(fstream& file,Student &s) {
        file >> s.rollno;
        file >> s.name ;
        file >> s.loc ;
        return file;
}

class DirectAccessFile{
    public:
    HashTable studData;
    fstream file;
    string fileName;
    Student* s;

    DirectAccessFile(int size, string f) : studData(size), fileName(f) {
        s = new Student[size];
        for(int i=0;i<size;i++)
        {
            writeInFile();
        }
    }

    void writeInFile()
    {
        {
            cout<<"Enter data name , roll"<<endl;
            file.open(fileName+".txt", ios::out | ios::app);
            string name;
            int r;
            cin>>name>>r;
            Student s(name,r,file.tellg());
            file<<s;
            studData.insert(s);
            studData.displayTable();
            file.close();
        }
    }

    void deleteStudent(int roll)
    {
        int index = studData.hashFunction(roll);
        file.open(fileName+".txt",ios::in);
        for(int i=0;i<studData.tableSize;i++)
        {
            file>>s[i];
        }
        file.close();
        file.open(fileName+".txt",ios::out);
        for(int i=0;i<studData.tableSize;i++)
        {
            if(s[i].rollno != roll)
                file<<s[i];
        }
        file.close();

        if(studData.table[index].rollno == roll)
        {
            studData.table[index] = Student();
        }
        else
        {
            for(int i=(index+1)%studData.tableSize;i!=index;i=(i+1)%studData.tableSize)
            {
                if(studData.table[i].rollno == roll)
                {
                    studData.table[i] = Student();
                }
            }
        }

    }

};
int main()
{
    int no_of_stud;
    cout<<"Enter number of students : "<<endl;
    cin>>no_of_stud;
    DirectAccessFile f(no_of_stud,"data");
    f.deleteStudent(21237);
    f.studData.displayTable();

    //2 A 21237 B 21238
}