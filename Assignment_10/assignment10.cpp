#include<iostream>
using namespace std;

class Heap{
    int size;
    int* arr;

    public:
    Heap(int s, int* arr)
    {
        size = s +1;
        this->arr = new int[s+1]; 
         this->arr[0] = -1;
        for(int i=0;i<size;i++)
        {
            this->arr[i+1] = arr[i];
        }
    }

    void heapify(int i, int n)
    {
        int largest = i;
        int left = 2*i;
        int right = 2*i+1;

        if(arr[largest] < arr[left])
            largest = left;

        if(arr[largest] < arr[right])
            largest = right;

        if(largest !=i)
        {
            swap(arr[largest], arr[i]);
            heapify(largest, n);
        }
        
    }

    void make_heap()
    {
        int n = size -1;
        for(int i=n/2;i>0;i--)
        {
            heapify(i,n);
        }
    }

    void heapSort()
    {
        int n=size-1;
        while(n>1)
        {
           swap(this->arr[1], this->arr[n]);
           n--;
           heapify(1,n);
        }


    }

    void print()
    {
        cout<<"\n";
        for(int i=1;i<size;i++)
        {
            cout<<this->arr[i]<<" ";
        }
    }

    //5
    //4 1 
};


int main()
{
    int arr[] = {4,2,1,5,3};
    Heap heap(5,arr);
    heap.print();
    heap.make_heap();
    heap.print();
    heap.heapSort();
    heap.print();
    

}
