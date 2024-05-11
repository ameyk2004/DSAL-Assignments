#include <iostream>
using namespace std;

class Heap{
    private:
    int* arr;
    int size;

    public:
    Heap(int s, int* a)
    {
        size = s+1;
        arr = new int[size];
        arr[0] = -1;
        for(int i=0;i<s;i++)
        {
            arr[i+1] = a[i];
        }
    }

    void heapify(int i, int n)
    {
        int largest = i;
        int left = 2*i;
        int right = 2*i+1;

        if(arr[left] > arr[largest] && left <=n)
        {
            largest = left;
        }
        else if(arr[right] > arr[largest] && right <=n)
        {
            largest = right;
        }

        if(largest!=i)
        {
            swap(arr[largest], arr[i]);
            heapify(largest,n);
        }
    
    }

    void make_heap()
    {
        int n=size-1;
        for(int i =n/2;i>0;i--)
        {
            heapify(i,n);
        }
    }

    void heapSort()
    {
         int n=size-1;
         while (n>1)
         {
            swap(arr[1], arr[n]);
            n--;
            heapify(1,n);
         }
         
    }

    void print(){
        for(int i=1; i<size; i++){
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }
};

int main()
{
    int arr[] = {4,2,1,5,3};
    int size = 5;
    Heap h(size, arr);
    h.print();
    h.make_heap();
    h.print();
    h.heapSort();
    h.print();
}