// Consider telephone book database of N clients. 
// Make use of a hash table implementation to quickly look up client‘s telephone number. 
// Make use of two collision handling techniques and compare them using number of comparisons 
// required to find a set of telephone numbers (Note: Use linear probing with replacement and without replacement). Perform following operations
// 1) Insert
// 2) Display
// 3) Search (number of comparisons required to search)
// Use Hash function as H(x) = (3*x + 5)%10

#include<iostream>
#include<string>
using namespace std;

class Record{
    long telNum;
    string name;

    public:
    Record() : name(""), telNum(0) {}
    Record(long int tel, string n) : telNum(tel), name(n) {}

    friend class TelephoneBook;
};
class TelephoneBook{
    Record* table;
    int size;
    bool replacement;

    public:
    TelephoneBook(int s = 10, bool r = false) 
    {
        size = s;
        replacement = r;

        table = new Record[size];
    }

    void printTable()
    {
         cout<<"\n\nIndex\tTelephone Num\tClient Name"<<endl;
        for(int i = 0;i<this->size;i++)
        {

            Record currRecord = table[i];
            cout<<i<<"\t"<<currRecord.telNum<<"\t\t"<<currRecord.name<<endl;
        }
    }

    int hashFunction(long int telNum)
    {
        int x = telNum%10;
        return (3*x + 5)%size;
    }

    void insert(long telNum, string n)
    {
        int index = hashFunction(telNum);

        if(table[index].telNum == 0)
        {
            Record newRecord(telNum, n);
            table[index] = newRecord;
            cout<<"Record Inserted"<<endl;
            return;
        }
        else if(table[index].telNum == telNum)
        {
            cout<<"Repeat Entry not allowed for "<<endl;
            return;
        }
        else if(replacement == true && hashFunction(table[index].telNum) !=index)
        {
            long replaceTelNum = table[index].telNum;
            string replaceName = table[index].name;
            table[index] = Record(telNum, n);
            insert(replaceTelNum, replaceName);
            return;
        }
        for(int i=(index+1)%size;i!=index;i=(i+1)%size)
        {
            if(table[i].telNum == 0)
            {
                table[i] = Record(telNum, n);
                cout<<"Inserted successfuly"<<endl;
                return;
            }
            else if(table[i].telNum == telNum)
            {
                cout<<"Aldready Present"<<endl;
                return;
            }
                
        }
         cout<<"No Empty Space in the Table"<<endl;
        return;
    
    }

    void searchKey(long telNum) 
    {
        int comparisons = 0;    
        int index = hashFunction(telNum);
        comparisons++;
        if(table[index].telNum == telNum)
        {
            
            cout<<"\n\nRecord Found"<<endl;
            cout<<"Comparisons required : "<<comparisons<<endl;
            cout<<telNum<<" ---- "<<table[index].name<<endl;
            return;
        }
        for(int i = (index+1)%size; i!=index; i = (i+1)%size)
        {
            comparisons++;
            if(table[i].telNum == telNum)
            {
                cout<<"\n\nRecord Found"<<endl;
                cout<<"Comparisons required : "<<comparisons<<endl;
                cout<<telNum<<" ---- "<<table[i].name<<endl;
                return;
            }
        }

        cout<<"Record not found"<<endl;
        
    }



};
int main()
{
   //Use from TestCase.md
}
