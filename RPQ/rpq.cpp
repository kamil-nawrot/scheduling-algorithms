#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unistd.h>
using namespace std;

struct rpq {
  int R, P, Q;
  int order;
};

vector<rpq> inputRPQ;
int N;
int currentData = 0;

int t = 0, Cmax = 0, Cfinal = 0;
vector<rpq> ready; vector<rpq> sorted;
rpq e;

ostream& operator<<(ostream& stream, rpq element) {
  stream << element.R << " " << element.P << " " << element.Q << 
         ", order: " << element.order << endl;
  return stream;
}

// auxiliary functions //////////////////////////////////////////////
bool initialSort (rpq i, rpq j) { 
  if (i.R != j.R) return i.R < j.R;
  else return i.P > j.P;
  }
bool reverseSort (rpq i, rpq j) {
  if (i.R != j.R) return i.R > j.R;
  else return i.P < j.P;
}
bool initialSortQ (rpq i, rpq j) {
  if (i.Q != j.Q) return i.Q < j.Q;
  else return i.P > j.P;
}
bool reverseSortQ (rpq i, rpq j) {
  if (i.Q != j.Q) return i.Q > j.Q;
  else return i.P < j.P;
}

rpq findMinR (vector<rpq>& input) {
  stable_sort(input.begin(), input.end(), initialSort);
  return input[0];
}

rpq findMaxQ (vector<rpq>& input) {
  stable_sort(input.begin(), input.end(), reverseSortQ);
  return input[0];
}
/////////////////////////////////////////////////////////////////////

// Schrage algorithm ////////////////////////////////////////////////
void addToReady () {
  e = findMinR(inputRPQ);
  ready.push_back(e);
  stable_sort(inputRPQ.begin(), inputRPQ.end(), reverseSort);
  inputRPQ.pop_back();
}

void addToSorted () {
  e = findMaxQ(ready);
  stable_sort(ready.begin(), ready.end(), initialSortQ);
  ready.pop_back();
  sorted.push_back(e);
}

void schrage () {
  stable_sort(inputRPQ.begin(), inputRPQ.end(), initialSort);
  while (ready.size() != 0 || inputRPQ.size() != 0) {
    while (inputRPQ.size() != 0 && findMinR(inputRPQ).R <= t) {
      addToReady();
      }
      while (ready.size() == 0) {
        addToReady();
      } 
      addToSorted();
      t = max(e.R, t) + e.P;
      Cmax = max(Cmax, t + e.Q);
  }
}
/////////////////////////////////////////////////////////////////////

int main() {

  string datasets [4] = {"data.1", "data.2", "data.3", "data.4"};
  
  for (int dataset=0; dataset<4; dataset++) {
    ifstream inputData ("rpq_data.txt"); 
  
    // Reading data from file:
    string setCaret = "";
    while (setCaret != datasets[dataset])   inputData >> setCaret; 
    inputData >> N;

    if (inputData) {
      rpq tempRPQ;
      int tempOrder = 1;
      int tempR, tempP, tempQ;
      while (inputData >> tempR >> tempP >> tempQ) {
        tempRPQ.R = tempR;
        tempRPQ.P = tempP;
        tempRPQ.Q = tempQ;
        tempRPQ.order = tempOrder;
        inputRPQ.push_back(tempRPQ);
        tempOrder++;
      }
    }

    schrage();
    cout << "Cmax = " << Cmax << endl;
    for (int i=0; i< sorted.size(); i++) cout << sorted[i].order << " ";
    cout << endl;

    Cfinal += Cmax;

    ready.clear();  sorted.clear();
    inputRPQ.clear();
    Cmax = 0; t = 0;

    currentData++;

    inputData.close();
    inputData.clear();
  }

  cout << "Cmax - final value: " << Cfinal << endl;
  return 0;
}