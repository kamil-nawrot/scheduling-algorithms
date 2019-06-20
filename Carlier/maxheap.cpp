#include <iostream> 
#include <climits> 
using namespace std; 

#include "task.hpp"
#include "maxheap.hpp"

void maxHeap::swap(Task *a, Task *b)
{
  Task *temp; 
  *temp = *a;
  *a = *b;
  *b = *temp;
}

maxHeap::maxHeap(int cap)
{
  size = 0;
  capacity = capacity;
  array = new Task[cap];
}

void maxHeap::insertNode(int data, int order)
{
  if (size == capacity) 
  {
    cout << "ERROR: Heap overflow";
    return;
  }
  size++;
  int i = size -1;
  Task task;
  task.data = data;
  task.order = order;
  cout << "assigning task to array..." << endl;
  cout << "ARRAY: " << array[i].data << " " << array[i].order << endl;
  array[i] = task;
  cout << "I: " << i << endl;
  cout << "TASK: [" << task.data << " " << task.order << "]" << endl;
  cout << "[" << array[i].data << " " << array[i].order << "]" << endl;
  while (i != 0 && array[parent(i)].data < array[i].data)
  {
    swap(&array[i], &array[parent(i)]);
    i = parent(i);
  }
}

void maxHeap::deleteNode (int i)
{
  Task max;
  max.data = max.order = INT_MAX;
  array[i] = max;
  while (i != 0 && array[parent(i)].data < array[i].data)
  {
    swap(&array[i], &array[parent(i)]);
    i = parent(i);
  }
  extractMax();
}

Task maxHeap::extractMax()
{
  Task max;
  max.data = max.order = INT_MAX;
  if (size <= 0) 
  {
    cout << "SIZE ZERO!" << endl;
    return max;
  } 
  if (size == 1)
  {
    size--;
    return array[0];
  }

  Task root = array[0];
  array[0] = array[size-1];
  size--;
  maxHeapify(0);

  return root;
} 

void maxHeap::maxHeapify(int i) 
{ 
    int l = leftChild(i); 
    int r = rightChild(i); 
    int largest = i; 
    if (l < size && array[l].data > array[i].data) 
        largest = l; 
    if (r < size && array[r].data > array[largest].data) 
        largest = r; 
    if (largest != i) 
    { 
        swap(&array[i], &array[largest]); 
        maxHeapify(largest); 
    } 
} 