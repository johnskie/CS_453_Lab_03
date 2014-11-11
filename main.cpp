#include <iostream>
#include <fstream>
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
        if(s[i] == '\t')
        {
            const char* ss = s.substr(pos, i - pos).c_str();
            cnt++;
            pos = i + 1;
        }
        else if (i == s.length())
        {
            const char * ss = s.substr(pos, i - pos).c_str();
            results[cnt] = atoi(ss);
        }
    }
}


int main(int argc, char* args[])
{
    bool valid = false, valid2 = false;
    string in = "", nQueues;
    int numQueues, at, quantum;

    cout << "Which scheduling algorithm would you like to use? (m = mfqs)" << endl;
    while (!valid)
    {
        getline(cin, in);

        if((in.compare("m") == 0))
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


            }
        }
    }
}
