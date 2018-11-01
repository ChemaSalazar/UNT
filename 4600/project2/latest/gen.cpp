#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

string ProcessID[50];
int ArrivalTime[50];
int RunTime[50];
int Priority[50];

int main()
{
    int x;  //Processes
    int a;  //ArrivalTime
    int r;  //RunTime
    int p;  //Priority
    int m; //determines how arrival time is created. m for "method".

    srand(time(NULL)); //initialize random seed
    x = rand()%50 + 1; //randomize value for total processes. P0-P49(max).
    m = 1;//rand()%2;      //possible values 0 or 1

    //cout << "\n\nx = " << x << endl << endl;

    //cout << "PID\tArrT\tRunT\tPrior" << endl;


    //ofstream OutputFile ("gen_data_1.txt");
    //ofstream OutputFile ("gen_data_2.txt");
    //ofstream OutputFile ("gen_data_3.txt");
    //ofstream OutputFile ("gen_data_4.txt");
    ofstream OutputFile ("gen_data_5.txt");  //CHANGE FILE NAME HERE

    for(int i=0; i < x; i++)
    {
        //generate random RunTime
        if (m == 0)
        {
            a = 0;
        }
        else
        {
        a = i+m;
        }
        r = rand()%1500+1;
        p = rand()%11;


        ProcessID[i]= "P"+ to_string(i);
        ArrivalTime[i] = a;
        RunTime[i] = r;
        Priority[i] = p;
       // cout << ProcessID[i] << "\t" << ArrivalTime[i] << "\t" << RunTime[i] << "\t" << Priority[i] << endl;
        OutputFile << ProcessID[i] << " " << ArrivalTime[i] << " " << RunTime[i] << " " << Priority[i] << endl;
    }

    OutputFile.close();

    return 0;
}
