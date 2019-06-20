#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <conio.h>
#include <vector>

using namespace std;

void dispArray(int *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
}

int binToDec(int *binArr, int size)
{
	int dec = 0;
	int i = 0;
	do
	{
		dec += (binArr[size - 1]) * pow(2, i);
		i++;
		size--;
	} while (size > 0);
	return dec;
}

vector<int> optimalOrder(int problem, int *arrF, int *arrP, int *arrW, int *arrD, int *arrC, int subID)
{
	vector<int> order;

	int const _buffBinSize = 32;
	int _buffDec = problem;			// numer problemu w formie dziesietnej
	int _buffBin[_buffBinSize];		// numer problemu w formie binarnej
	int _buffBinRev[_buffBinSize];	// korekta numeru problemu w formie binarnej

	int j = 0;
	while (_buffDec)				//zamiana z decymalnego na binarny
	{
		_buffBinRev[j] = _buffDec % 2;
		_buffDec /= 2;

		j++;
	} 

	int binNumberSize = j;
	while (binNumberSize < _buffBinSize)
	{
		_buffBinRev[binNumberSize] = 0;
		binNumberSize++;
	}
	
	for (int k = binNumberSize - 1, i = 0; k >= 0 || i < binNumberSize; k--, i++)
	{
		_buffBin[i] = _buffBinRev[k];
	}

	int F_max = 99999;
	int subproblem;			// numer aktulnie sprawdzango podproblemu wchodzacego w sklad problemu
	int minSubproblem;		// numer podproblemu z minimalna kara
	int minSubproblemID;	// numer problemu elementarnego, dla ktorego znaleziono minimum

	for (int i = 0; i < j; i++)
	{
		int n = i + (binNumberSize - j);						//skorygowane indeksy
		int m = binNumberSize - 1 - i - (binNumberSize - j);	//
		if (_buffBin[n] == 1)		// sprawdzanie po kolei kazdego podproblemu (1111 -> 0111, 1011, 1101, 1110);
		{
			_buffBin[n] = 0;
			
			subproblem = binToDec(_buffBin, binNumberSize);
			int cost = arrF[subproblem] + ( arrW[m] * max(0, arrC[problem] - arrD[m]) );
			
			if (F_max > cost)		// czy minimum?
			{
				minSubproblemID = binNumberSize - n ;
				minSubproblem = subproblem;
				F_max = cost;
			}
			_buffBin[n] = 1;
		}
	}
		
	if (problem > 0)
	{
		order = optimalOrder(minSubproblem, arrF, arrP, arrW, arrD, arrC, minSubproblemID); 	// uporzadkowanie podproblemu
		order.push_back(minSubproblemID);	// ukladanie problemow elementarnych w ostatecznej kolejnosci
	}

	return order;
}

int main()
{

	int N, perm;
	string datasets[11] = { "data.10:", "data.11:", "data.12:", "data.13:", "data.14:",
		"data.15:", "data.16:", "data.17:", "data.18:", "data.19:", "data.20:" };

	for (int data = 0; data < 11; data++)
	{
		ifstream inputData("witi.data.txt");
		string setCaret = "";
		while (setCaret != datasets[data])
			inputData >> setCaret;
		inputData >> N;

		int *P = new int[N];
		int *W = new int[N];
		int *D = new int[N];
		

		for (int i = 0; i < N; i++)
			inputData >> P[i] >> W[i] >> D[i];
		inputData.close();

		perm = pow(2, N);
		int *F = new int[perm];
		int *C = new int[perm];

		int Cmax, minDel, cost;

		F[0] = 0;
		C[0] = 0;
		int *order = new int[N];

		for (int j = 1; j < perm; ++j)
		{
			Cmax = 0;
			for (int k = 0, bit = 1; bit <= j; bit *= 2, k++)
				if (j & bit)
					C[j] = Cmax += P[k];
			
			minDel = 99999;
			for (int k = 0, bit = 1; bit <= j; bit *= 2, k++)
			{
				if (j & bit)
				{
					cost = F[j - bit] + (W[k] * max(0, Cmax - D[k]));
					if (cost < minDel)
					{
						minDel = cost;
					}
				}
			}

			F[j] = minDel;
		}

		cout << F[perm - 1] << endl;
		
		vector<int> optOrder;
		optOrder = optimalOrder(perm - 1, F, P, W, D, C, 0);

		for (int i = 0; i < optOrder.size(); i++)
		{
			cout << optOrder[i] << " ";
		}

		cout << endl << "##############" << endl;

		delete[] P;
		delete[] W;
		delete[] D;
		delete[] C;
		delete[] F;
	}

	_getch();
}