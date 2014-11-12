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
            cnt++;
            pos = i + 1;
        }
        else if (i == s.length())
        {
            const char *ss = s.substr(pos, i - pos).c_str();
            results[cnt] = atoi(ss);
        }
    }
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
    	if(inf != "")
    	{
    		validInput = true;
    	}
    }

    cout << "Loading " << inf << endl;

    // get last item of file so we can figure out how many processes there are in the file
    string last = "";
    ifstream fin;
    fin.open(inf);
    if(fin.is_open())
    {
    	fin.seekg(-1,ios_base::end);

    	validInput = false;
    	while (!validInput)
    	{
    		char c;
    		fin.get(c);

    		if((int)fin.tellg() <= 1)
    		{
    			fin.seekg(0);
    			validInput = true;
    		}
    		else if(c == '\n')
    		{
    			validInput = true;
    		}
    		else
    		{
    			fin.seekg(-2,ios_base::cur);
    		}
    	}

    	getline(fin,last);
    	fin.close();
    }

    cout << "Last line: " << last << endl;

    // now that we have the last line, get the pid of it (which is the size of the array)
    int results[6];
    int noProcesses = 0;
    inputParser(last, results);
    noProcesses = results[0];

    cout << "PID of last process: " << noProcesses << endl;

    









    return 0;
}
