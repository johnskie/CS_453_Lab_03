#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "Process.h"
#include "mfqs.h"

using namespace std;

void inputParser(string s, int results[])
{
    int cnt = 0;
    int pos = 0;
    for (int i = 0; i <= s.length(); i++)
    {
        if (s[i] == '\t')
        {
            const char *ss = s.substr(pos, i - pos).c_str();
            results[cnt] = atoi(ss);
            cnt++;
            pos = i + 1;
        }
        else if (i == s.length())
        {
            const char *ss = s.substr(pos, i - pos).c_str();
            results[cnt] = atoi(ss);
        }
    }

    for (int i = 0; i < 6; i++)
    {
        cout << results[i] << endl;
    }
}

void shiftRight(Process *arr, int low, int high)
{
    int root = low;
    while ((root * 2) + 1 <= high)
    {
        int leftChild = (root * 2) + 1;
        int rightChild = leftChild + 1;
        int swapIdx = root;
        /*Check if root is less than left child*/
        if (arr[swapIdx].getArrivalTime() < arr[leftChild].getArrivalTime())
        {
            swapIdx = leftChild;
        }
        /*If right child exists check if it is less than current root*/
        if ((rightChild <= high) && (arr[swapIdx].getArrivalTime() < arr[rightChild].getArrivalTime()))
        {
            swapIdx = rightChild;
        }
        /*Make the biggest element of root, left and right child the root*/
        if (swapIdx != root)
        {
            Process tmp = arr[root];
            arr[root] = arr[swapIdx];
            arr[swapIdx] = tmp;
            /*Keep shifting right and ensure that swapIdx satisfies
            heap property aka left and right child of it is smaller than
            itself*/
            root = swapIdx;
        }
        else
        {
            break;
        }
    }
    return;
}
void heapify(Process *arr, int low, int high)
{
    /*Start with middle element. Middle element is chosen in
    such a way that the last element of array is either its
    left child or right child*/
    int midIdx = (high - low - 1) / 2;
    while (midIdx >= 0)
    {
        shiftRight(arr, midIdx, high);
        --midIdx;
    }
    return;
}
void heapSort(Process *arr, int size)
{
    /*This will put max element in the index 0*/
    heapify(arr, 0, size - 1);
    int high = size - 1;
    while (high > 0)
    {
        /*Swap max element with high index in the array*/
        Process tmp = arr[high];
        arr[high] = arr[0];
        arr[0] = tmp;
        --high;
        /*Ensure heap property on remaining elements*/
        shiftRight(arr, 0, high);
    }
    return;
}


int main(int argc, char *args[])
{
    bool valid = false, valid2 = false;
    string in = "", nQueues;
    int numQueues, age, quantum;

    cout << "Which scheduling algorithm would you like to use? (m = mfqs)" << endl;
    while (!valid)
    {
        getline(cin, in);

        if (in == "m")
        {
            while (!valid2)
            {
                cout << "Enter number of queues (MAX 5)" << endl;
                cin >> numQueues;

                if (numQueues <= 5)
                {
                    valid2 = true;
                }
                else
                {
                    cout << "Invalid number of queues" << endl;
                }
            }

            valid2 = false;

            while (!valid2)
            {
                cout << "Enter time for ageing: " << endl;
                cin >> age;
                if (age > 0)
                {
                    valid2 = true;
                }

            }

            valid2 = false;
            while (!valid2)
            {
                cout << "Enter quantum: " << endl;
                cin >> quantum;

                if (quantum > 0)
                {
                    valid2 = true;
                    valid = true;
                }
            }
        }
        else if (in == "r")
        {
            // do RTS stuff
            valid = true;
        }
        else if (in == "wh")
        {
            // do windows hybrid
            valid = true;
        }
        else
        {
            cout << "Invalid input. Please select: m = MFQS, r = RTS, wh = Windows Hybrid" << endl;
        }
    }

    bool validInput = false;
    string inf = "";

    cout << "Enter input file: " << endl;
    while (!validInput)
    {
        getline(cin, inf);
        if (inf != "")
        {
            validInput = true;
        }
    }

    cout << "Loading " << inf << endl;

    // get last item of file so we can figure out how many processes there are in the file
    // http://stackoverflow.com/questions/11876290/c-fastest-way-to-read-only-last-line-of-text-file
    string lastLine;
    ifstream fin;
    const char *fileIn = inf.c_str();
    fin.open(fileIn);
    if (fin.is_open())
    {
        fin.seekg(-1, ios_base::end);

        validInput = false;
        while (!validInput)
        {
            char c;
            fin.get(c);

            if ((int)fin.tellg() <= 1)
            {
                fin.seekg(0);
                validInput = true;
            }
            else if (c == '\n')
            {
                validInput = true;
            }
            else
            {
                fin.seekg(-2, ios_base::cur);
            }
        }

        getline(fin, lastLine);
        fin.close();
    }
    else
    {
        cout << "unable to open file" ;
        exit(1);
    }

    cout << "Last line: " << lastLine << endl;

    // now that we have the last line, get the pid of it (which is the size of the array)
    int results[6];
    int numberProcesses = 0;
    inputParser(lastLine, results);
    numberProcesses = results[0];

    Process *processList;
    processList = new Process[numberProcesses + 1];

    int count = 0;
    string currentLine = "";

    fin.open(fileIn);
    if (fin.is_open())
    {
        // ignore the very first line because it is just headings
        getline(fin, currentLine);
        // while there is still something to read in the file
        while (fin.good())
        {
            getline(fin, currentLine);

            inputParser(currentLine, results);
            processList[count].setPID(results[0]);
            processList[count].setArrivalTime(results[2]);
            processList[count].setBurstTime(results[1]);
            processList[count].setBurstRemaining(results[1]);
            processList[count].setLastTime(results[2]);
            processList[count].setIO(results[5]);
            processList[count].setPriority(results[3]);
            processList[count].setDeadline(results[4]);
            count++;
        }
        fin.close();
    }

    // sort processes
    cout << "Array :" << endl << "[ ";
    for (int i = 0; i < numberProcesses; i++)
    {
        cout << processList[i].getPID() << "|" << processList[i].getArrivalTime() << endl;
    }
    cout << "]" << endl;
    heapSort(processList, numberProcesses);

    cout << "Sorted Array :" << endl << "[ ";
    for (int i = 0; i < numberProcesses; i++)
    {
        cout << processList[i].getPID() << "|" << processList[i].getArrivalTime() << endl;
    }
    cout << "]" << endl;



    if (in == "m")
    {
        cout << "Doing MFQS with " << numQueues << " queues." << endl;
        MFQS test = MFQS(numQueues, age, quantum, processList);
        cout << "created" << endl;
        test.scheduleProcesses();
        cout << "done" << endl;
    }



    return 0;
}
