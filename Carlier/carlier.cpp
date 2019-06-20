#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
using namespace std;

#include "task.hpp"
#include "minheap.hpp"
#include "maxheap.hpp"

ostream &  operator<< (ostream &out, const Task &task) {
  out << "[" << task.data << ", " << task.order << "]";
}

int schrage (int* R, int* P, int* Q, int* order, int N)
{
  minHeap minR(100);
  maxHeap maxQ(100);

  vector<Task> finalOrder;
  
  for (int i=0; i<N; i++) minR.insertNode(R[i], order[i]);
  int Cmax = 0, t = minR.getRoot().data;
  while (minR.getSize() != 0 || maxQ.getSize() != 0)
  {
    step_back:
    while (minR.getSize() != 0 && minR.getRoot().data <= t)
    {
      Task getMinR = minR.extractMin();
      maxQ.insertNode(Q[getMinR.order], order[getMinR.order]);
    }
    while (maxQ.getSize() == 0) 
    {
      cout << "IM HERE" << endl;
      t = minR.getRoot().data;
      goto step_back;
    }
    Task getMaxQ = maxQ.extractMax();

    finalOrder.push_back(getMaxQ);
    t += P[getMaxQ.order];
    Cmax = max(Cmax, t+getMaxQ.data);
  }

  for (int i=0; i<finalOrder.size(); i++) cout << finalOrder[i].order+1 << " ";
  cout << endl;
  return Cmax;
}

int main()
{
  int N;
  ifstream inputData("carl.data.txt");
  string setCaret = "";
  string dataset = "data.000:";
  while(setCaret != dataset)  inputData >> setCaret;
  inputData >> N;
  int R[N], P[N], Q[N], order[N];
  if (inputData) for (int i=0; i<N; i++) {
    inputData >> R[i] >> P[i] >> Q[i];
    order[i] = i;
  }

  cout << schrage(R, P, Q, order, N) << endl;

}