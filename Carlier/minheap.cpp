#include <iostream> 
#include <climits> 
using namespace std;

#include "task.hpp"
#include "minheap.hpp"

void minHeap::swap(Task *a, Task *b)
{
  Task temp; 
  temp = *a;
  *a = *b;
  *b = temp;
}

minHeap::minHeap(int cap)
{
  size = 0;
  capacity = capacity;
  array = new Task[cap];
}

void minHeap::insertNode(int tdata, int torder)
{
  if (size == capacity) 
  {
    cout << "ERROR: Heap overflow";
    return;
  }

  size++;
  int i = size - 1;
  Task task;
  task.data = tdata;
  task.order = torder;
  array[i] = task;

  while (i != 0 && array[parent(i)].data > array[i].data)
  {
    swap(&array[i], &array[parent(i)]);
    i = parent(i);
  }
}

void minHeap::deleteNode (int i)
{
  Task min;
  min.data = min.order = INT_MIN;
  array[i] = min;
  while (i != 0 && array[parent(i)].data > array[i].data)
  {
    swap(&array[i], &array[parent(i)]);
    i = parent(i);
  }
  extractMin();
}

Task minHeap::extractMin()
{
  Task min;
  min.data = min.order = INT_MIN;
  if (size <= 0)
  {
    cout << "SIZE ZERO!" << endl;
    return min;
  }
  if (size == 1)
  {
    size--;
    return array[0];
  }

  Task root = array[0];
  array[0] = array[size-1];
  size--;
  minHeapify(0);

  return root;
} 

void minHeap::minHeapify(int i) 
{ 
    int l = leftChild(i); 
    int r = rightChild(i); 
    int smallest = i; 
    if (l < size && array[l].data < array[i].data) 
        smallest = l; 
    if (r < size && array[r].data < array[smallest].data) 
        smallest = r; 
    if (smallest != i) 
    { 
        swap(&array[i], &array[smallest]); 
        minHeapify(smallest); 
    } 
} 