#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <iomanip>
using namespace std;
using namespace chrono;

#define DATASETS 121

void display2DArray(int **array, int m, int p)
{
    for (int i = 0; i < p; i++)
    {
        for (int k = 0; k < m; k++)
            cout << array[i][k] << " ";
        cout << endl;
    }
}

bool isInArray(int *array, int p, int element)
{
    for (int i = 0; i < p; i++)
    {
        if (array[i] == element)
            return true;
    }
    return false;
}

int findMaxTask(int **array, int *ordered, int m, int p)
{
    int maxTask = 0, maxWeight = 0, totalWeight = 0;

    for (int i = 0; i < p; i++)
    {
        for (int k = 0; k < m; k++)
            totalWeight += array[i][k];
        if (totalWeight > maxWeight && isInArray(ordered, p, i + 1) == false)
        {
            maxWeight = totalWeight;
            maxTask = i + 1;
        }
        totalWeight = 0;
    }

    return maxTask;
}

int findCMax(int **array, int **arrayC, int *order, int m, int p)
{
    for (int i = 1; i <= p; i++)
    {
        for (int k = 1; k <= m; k++)
        {
            int currentTask = order[i - 1];
            arrayC[i][k] = max(arrayC[i][k - 1], arrayC[i - 1][k]) + array[currentTask - 1][k - 1];
        }
    }

    return arrayC[p][m];
}

void swapIndex(int *array, int a)
{
    int temp;
    temp = array[a];
    array[a] = array[a - 1];
    array[a - 1] = temp;
}

void NEH(int **array, int *order, int m, int p)
{
    int minCMax, bestPosition;

    int **arrayC = new int *[p + 1];
    for (int i = 0; i <= p; i++)
    {
        arrayC[i] = new int[m + 1];
        for (int k = 0; k <= m; k++)
            arrayC[i][k] = 0;
    }

    for (int i = 0; i < p; i++)
    {
        bestPosition = i;
        int maxTask = findMaxTask(array, order, m, p);
        order[i] = maxTask;
        minCMax = findCMax(array, arrayC, order, m, i + 1);
        for (int k = 0; k < i; k++)
        {
            swap(order[i - k], order[i - k - 1]);
            int CMax = findCMax(array, arrayC, order, m, i + 1);
            if (CMax <= minCMax)
            {
                minCMax = CMax;
                bestPosition = i - k - 1;
            }
        }
        int currentTask = order[0];
        for (int j = 1; j <= bestPosition; j++)
        {
            order[j - 1] = order[j];
        }
        order[bestPosition] = currentTask;
    }

    cout << "######### FINAL RESULTS #########" << endl;
    cout << "CMAX: " << minCMax << endl;
    for (int i = 0; i < p; i++)
        cout << order[i] << " ";
    cout << endl;
}

int main()
{
    int nMachines = 0;
    int nProcesses = 0;

    string data[DATASETS];
    for (int i = 0; i < DATASETS; i++)
    {
        stringstream stream;
        stream << setw(3) << setfill('0') << i;
        data[i] = stream.str();
    }

    auto start = steady_clock::now();
    for (int i = 0; i < DATASETS; i++)
    {
        ifstream inputData("neh.data.txt");
        string setCaret = "";
        string dataset = "data." + data[i] + ":";
        while (setCaret != dataset)
            inputData >> setCaret;
        inputData >> nProcesses >> nMachines;

        int **Task = new int *[nProcesses];
        int *orderedTasks = new int[nProcesses];

        for (int i = 0; i < nProcesses; i++)
        {
            Task[i] = new int[nMachines];
            for (int k = 0; k < nMachines; k++)
                inputData >> Task[i][k];
        }
        inputData.close();

        int *sortedTasks = new int[nProcesses];

        NEH(Task, sortedTasks, nMachines, nProcesses);
    }
    auto end = steady_clock::now();
    auto elapsedTime = duration_cast<milliseconds>(end - start).count();
    cout << "ELAPSED TIME: " << elapsedTime << endl;

}