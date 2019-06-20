class maxHeap 
{
  Task *array;
  int capacity;
  int size;

  public:
    maxHeap(int cap);

    Task extractMax();
    void deleteNode(int i);
    void insertNode(int data, int order);
    void maxHeapify(int i);
    int getSize() { return size; }

    int parent (int i) { return (i-1)/2; }
    int leftChild (int i) { return (2*i + 1); }
    int rightChild (int i) { return (2*i + 2); }
    Task getRoot() { return array[0]; }
    void swap (Task *a, Task *b);
};