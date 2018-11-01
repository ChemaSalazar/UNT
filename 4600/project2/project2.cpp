/*
  Jose Salazar
  CSCE4600 Project 2

    Simulate 3 out of 5 scheduling algorithms.

    ===============================================================
    This project will simulate the following scheduling algorithms:

    *FIFO
    *SJF
    *Priority

    ===============================================================
    Program will read input from an input file containing
    data in the following format:

    <ProcessID> <ArrivalTime> <RunTime> <Priority>

    ===============================================================
    Datatype for the format:

    <ProcessID> - will allow up to 20 C-string characters.
    <ArrivalTime> - integers.
    <RunTime> - integers.
    <Priority> - integers.

    ===============================================================
    Program will read up to 50 processes from input file.
    And it is assumed that input is sorted by arrival time.

    ===============================================================
    This program will output the ProcessID, ArrivalTime, RunTime,
    Priority, StartTime, EndTime, TurnAround, WaitingTime, And
    ResponceTime for each job.

    In addition the following will also be displayed:
    AverageTurnAroundTime, AverageWaitingTime, AverageResponceTime,
    and NumberOfContextSwitches(for preemptive deployment).

    ===============================================================
*/

//libaries
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

//global variables
string ProcessID[50];
int  ArrivalTime[50]={0};
int  RunTime[50];
int  Priority[50]={0};
int x=0; //this is known as the total number of processes.
string userfile; //this string holds the name of the inputfile.


int TurnAround[50];
int WaitingTime[50];
int StartTime[50];
int EndTime[50];
int ResponceTime[50];
int ContextSwitches=0;
int AverageTurnAroundTime=0;
int AverageWaitingTime=0;
int AverageResponceTime=0;




//function declarations
void ReadFromFile(string userfile);
void FirstInFirstOut();
void ShortestJobFirst();
void PrioritySchedule();

//main function
int main(int argc, char* argv[])
{
  //we guarantee that the program accepts only 2 arguments.
  if (argc != 2)
  {
    //we let the user know their input was incorrect.
    printf("\nThis program requires 2 arguments of the following format:\n");
    printf("./a.out <InputFile>\n");
  }
  else
  {
    //user arguments are acceptable, now we read input file.
    printf("InputFile=%s\n\n\n",argv[1]);
    userfile = argv[1];
    ReadFromFile(userfile);

    //simulations will execute.
    FirstInFirstOut();  //complete
    ShortestJobFirst(); //not done
    PrioritySchedule(); //not done
  }

  return 0;
}

void ReadFromFile(string userfile)
{
  //testing phase
  //printf("\n[Reading data from file]\n");

  //create string that will be used to scan the inputfile
  string line;
  ifstream inputfile(userfile.c_str());//string converted to c-string before utilization.

  //we open the filename argument from main and read.
  //check if file is valid
  if(inputfile.is_open())
  {

    while(getline(inputfile,line))
    {
      //get input data line by line and store to variables.
      istringstream ss(line);
      ss >> ProcessID[x] >> ArrivalTime[x] >> RunTime[x] >> Priority[x];

      //testing the data read from file.
      //cout << ProcessID[x] << ArrivalTime[x] << RunTime[x] << Priority[x] << "\n";
      x++;
    }

    //safely close the inputfile.
    inputfile.close();
  }

  //this condition will run if the file specified is not valid.
  else
  {
    cout << "unable to open file[ " << userfile << " ]\n";
    exit(EXIT_FAILURE);
  }

/*===============================================================
  This section is for testing our arrays.
  In the finished program, this will be disabled by default.
===============================================================*/

/*
  cout << "\nPulling from memory: \n";
  for(int y=0; y < x; y++)
  {
    cout << ProcessID[y] << " "<<ArrivalTime[y] <<" "<< RunTime[y] <<" " << Priority[y] <<"\n";
  }
  */
}


/*===============================================================
This section is the FIFO scheduling implementation
===============================================================*/

void FirstInFirstOut()
{
  //testing phase
  //cout << "FIFO>>\n";

  //calculate TurnAround
  //THIS FUNCTION HAS BEEN REPLACED.
  /*for(int y=0; y < x; y++ )
  {
    TurnAround[y]=RunTime[y]+WaitingTime[y];
    AverageWaitingTime+=WaitingTime[y];
    AverageTurnAroundTime+=TurnAround[y];
  }*/

  //calculate StartTime
  int temp=0;
  for(int s=0; s < x; s++)
  {
    if (s==0)
    {
        StartTime[s]=0;
    }
    if (s==1)
    {
      StartTime[s]= RunTime[s-1];
    }
    if (s==2)
    {
      StartTime[2]= RunTime[0]+RunTime[1];
      temp = StartTime[2];
    }
    else
    {
      StartTime[s] = RunTime[s-1]+temp;
      temp = StartTime[s];
    }
    //cout << "StartTime for [" << ProcessID[s] << "] = " << StartTime[s] << endl;
  }
  //cout << endl;
  //calculate EndTime
  temp=0;
  for(int e=0; e < x; e++)
  {
    if (e==x-1)
    {
      EndTime[e]=StartTime[e]+RunTime[e];
    }
    else
    {
      EndTime[e]=StartTime[e+1];
    }
    //cout << "EndTime for [" << ProcessID[e] << "] = " << EndTime[e] << endl;
  }
  //cout << endl;
  //calculate TurnAround time = EndTime - ArrivalTime
  for(int t=0; t < x; t++)
  {
    TurnAround[t]=EndTime[t]-ArrivalTime[t];
    AverageTurnAroundTime+=TurnAround[t];
    //cout << "TurnAround for [" << ProcessID[t] << "] = " << TurnAround[t] <<endl;
  }
  //cout << "AverageTurnAroundTime = " << AverageTurnAroundTime/x << endl;
  //cout << endl;

  //calculate WaitingTime = StartTime - ArrivalTime
  for(int w=0; w < x; w++)
  {
    WaitingTime[w]=StartTime[w]-ArrivalTime[w];
    AverageWaitingTime+=WaitingTime[w];
    //cout << "WaitingTime for [" << ProcessID[w] << "] = " << WaitingTime[w] <<endl;
  }
  //cout << "AverageWaitingTime = " << AverageWaitingTime/x << endl;

  //calculate ResponceTime, In FIFO, this is basically the StartTime.
  for(int r=0; r < x; r++)
  {
    ResponceTime[r]=StartTime[r];
    AverageResponceTime+=ResponceTime[r];
    //cout << "ResponceTime for [" << ProcessID[r] << "] = " << ResponceTime[r] <<endl;
  }
  //cout << "AverageResponceTime = " << AverageResponceTime/x << endl;

  //Display All Results:
  /*===============================================================
  This section will be the final output for FIFO Schedule
  ===============================================================*/
  cout << "===>FirstInFirstOut" << endl << endl;
  cout << "Job" << setw(10) << "ArivT" << setw(10) << "RunT" << setw(10) << "Prio" << setw(10) << "StrT" << setw(10) << "EndT" << setw(10)<< "Turn" << setw(10) << "Wait" << setw(10) << "Resp" << endl;
  cout << "+=========================================================================================+" <<endl;
  for(int d=0; d < x; d++)
  {
    cout << setw(10) << left << ProcessID[d] << setw(10)  << ArrivalTime[d] << setw(10) << RunTime[d] << setw(10) << Priority[d];
    cout << setw(10) << StartTime[d] << setw(10) << EndTime[d] << setw(10) << TurnAround[d] << setw(10);
    cout << WaitingTime[d] << setw(10) << ResponceTime[d] << endl;
  }
  cout << "+=========================================================================================+" <<endl;
  cout << "AverageTurnAroundTime = " << AverageTurnAroundTime/x << endl;
  cout << "AverageWaitingTime = " << AverageWaitingTime/x << endl;
  cout << "AverageResponceTime = " << AverageResponceTime/x << endl;
  cout << "Number Context Switches = " << ContextSwitches << endl << endl;


}//end of FIFO

/*===============================================================
This section is the SJF scheduling implementation
===============================================================*/
void ShortestJobFirst()
{
  //testing phase
  //printf("\n[Running SJF scheduling]\n");
}

/*===============================================================
This section is Priority scheduling implementation
===============================================================*/
void PrioritySchedule()
{
  //testing phase
  //printf("\n[Running Priority scheduling]\n\n");
}
