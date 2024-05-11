#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//class student stores all the info of a student --obviously
class Student{
    int roll;
    string name;

    public:
    Student(){
        roll = 0;
        name = "";
    }
    Student(int roll, string name){
        this->roll = roll;
        this->name = name;
    }

    //make it static so instance of student not required for call

    static void display(){

        //create instance of fstream 

        fstream f;

        //OPEN IN "IN" AS WE JUST NEED TO DISPLAY
        f.open("file.txt", ios::in);
        string line;

        //print the info line by line
        while(getline(f, line))
            cout<<line<<endl;
        f.close();
    }

    static void deleteStudent(int roll){
        fstream f;

        //first copy all the info into an array of Student
        f.open("file.txt", ios::in);
        Student arr[5];
        for(int i=0; i<5; i++){
            f >> arr[i];
        }
        f.close();

        //reopen the file, this time in OUT mode
        f.open("file.txt", ios::out);
        for(int i=0; i<5; i++){
            //using the overloaded << operator, copy only the data of students whose roll number does not match with the one that is to be deleted
            if(arr[i].roll != roll)
            f << arr[i];
        }
        f.close();
    }

    static void searchStudent(int roll){
        fstream f;
        f.open("file.txt", ios::in);
        Student s1;
        int found = 0;
        for(int i=0; i<5; i++){

            //get info of students one by one in the Student object s1, compare with given roll, if matches display all the info and break the loop
            f >> s1;
            if(s1.roll == roll){
                cout<<s1.roll<<" : "<<s1.name<<endl;
                found = 1;
                break;
            }
        }
        f.close();

        //if not found, display message
        if(!found){
            cout<<"Student not found!"<<endl;
        }
    }

    //IMPORTANT:: Operator overloading mathods declared as friends and defined outside the class
    friend fstream &operator<<(fstream &f, Student &s);
    friend fstream &operator>>(fstream &f, Student &s);
};

//to write details of Student s in fstream object f
fstream &operator<<(fstream &f, Student &s){
    f<< s.roll << endl;
    f<< s.name << endl;
    f<<endl;
    return f;
}

//to write details from fstream object f into student s
fstream &operator>>(fstream &f, Student &s){
    f >> s.roll;
    f >> s.name;
    return f;
}

int main(){
    string name;
    int roll;
    fstream f1;
    f1.open("file.txt",ios::out);
    for(int i=0; i<5; i++){
        cin>>roll;
        cin>>name;
        Student s(roll, name);
        f1<<s;
    }
    Student::display();
    Student::searchStudent(3);
    Student::deleteStudent(3);
    Student::display();
    Student::searchStudent(4);
    Student::searchStudent(3);
    f1.close();
    return 0;
}