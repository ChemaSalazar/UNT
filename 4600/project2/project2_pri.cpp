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
int ArrivalTime[50]={0};
int RunTime[50];
int Priority[50]={0};
int x=0; //this is known as the total number of processes.
string userfile; //this string holds the name of the inputfile.
int SCHEDULE_KEY;

//scheduling arrays and variables.
int TurnAround[50];
int WaitingTime[50];
int StartTime[50];
int EndTime[50];
int ResponceTime[50];
int ContextSwitches=0;
int AverageTurnAroundTime=0;
int AverageWaitingTime=0;
int AverageResponceTime=0;

//ShortestJobFirst variables.
int SJF_RunTime[50]; //this is the array containing the sorted data.
string SJF_ProcessID[50];
int SJF_ArrivalTime[50];
int SJF_Priority[50];
int SJF_StartTime[50];
int SJF_EndTime[50];
int SJF_WaitingTime[50];
int SJF_TurnAround[50];
int SJF_ResponceTime[50];
int PivotElement;
int SJF_AverageTurnAroundTime=0;
int SJF_AverageWaitingTime=0;
int SJF_AverageResponceTime=0;

//PrioritySchedule variables.
int PRI_RunTime[50];
string PRI_ProcessID[50];
int PRI_ArrivalTime[50];
int PRI_Priority[50];
int PRI_StartTime[50];
int PRI_EndTime[50];
int PRI_WaitingTime[50];
int PRI_TurnAround[50];
int PRI_ResponceTime[50];
int PRI_PivotElement;
int PRI_AverageTurnAroundTime=0;
int PRI_AverageWaitingTime=0;
int PRI_AverageResponceTime=0;


//function declarations
void ReadFromFile(string userfile);
void FirstInFirstOut();
void ShortestJobFirst();
void PrioritySchedule();
void Quicksort(int First, int Last);
void SwapS(string& a, string& b);
void Swap(int& a, int& b);
int Pivot(int First, int Last);


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
      SJF_RunTime[x] = RunTime[x];
      SJF_ProcessID[x] = ProcessID[x];
      SJF_ArrivalTime[x] = ArrivalTime[x];
      SJF_Priority[x] = Priority[x];
      PRI_RunTime[x] = RunTime[x];
      PRI_ProcessID[x] = ProcessID[x];
      PRI_ArrivalTime[x] = ArrivalTime[x];
      PRI_Priority[x] = Priority[x];

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

Since SJF bases its processes execution by the smallest
run time first (priority), we will implement a quicksort
algorithm that will order the RunTime input array to a
SJF_RunTime array.
===============================================================*/
void ShortestJobFirst()
{
  //testing phase
  SCHEDULE_KEY=0;
  Quicksort(0,x-1);


  //calculate StartTime for SJF.
  int temp=0;
  for(int s=0; s < x; s++)
  {
    if (s==0)
    {
        SJF_StartTime[s]=0;
    }
    if (s==1)
    {
      SJF_StartTime[s]= SJF_RunTime[s-1];
    }
    if (s==2)
    {
      SJF_StartTime[2]= SJF_RunTime[0]+SJF_RunTime[1];
      temp = SJF_StartTime[2];
    }
    else
    {
      SJF_StartTime[s] = SJF_RunTime[s-1]+temp;
      temp = SJF_StartTime[s];
    }
    //cout << "StartTime for [" << ProcessID[s] << "] = " << StartTime[s] << endl;
  }

  //calculate EndTime
  temp=0;
  for(int e=0; e < x; e++)
  {
    if (e==x-1)
    {
      SJF_EndTime[e]=SJF_StartTime[e]+SJF_RunTime[e];
    }
    else
    {
      SJF_EndTime[e]=SJF_StartTime[e+1];
    }
  }

  //calculate TurnAround time = EndTime - ArrivalTime
  for(int t=0; t < x; t++)
  {
    SJF_TurnAround[t]=SJF_EndTime[t]-SJF_ArrivalTime[t];
    SJF_AverageTurnAroundTime+=SJF_TurnAround[t];
  }

  //calculate WaitingTime = StartTime - ArrivalTime
  for(int w=0; w < x; w++)
  {
    SJF_WaitingTime[w]=SJF_StartTime[w]-SJF_ArrivalTime[w];
    SJF_AverageWaitingTime+=SJF_WaitingTime[w];
  }

  //calculate ResponceTime, In FIFO, this is basically the StartTime.
  for(int r=0; r < x; r++)
  {
    SJF_ResponceTime[r]=SJF_StartTime[r];
    SJF_AverageResponceTime+=SJF_ResponceTime[r];
  }


  //test print
  /*for(int i=0; i < x; i++)
  {
    cout << "SJF_ProcessID[" << SJF_ProcessID[i] << "]\t" << "SJF_RunTime[" << i << "] =" << SJF_RunTime[i] << endl;
  }*/

  //Display All Results:
  /*===============================================================
  This section will be the final output for ShortestJobFirst Schedule
  ===============================================================*/
  cout << "===>ShortestJobFirst" << endl << endl;
  cout << "Job\t" << "ArivT\t   " << setw(10) << "RunT" << setw(10) << "Prio" << setw(10) << "StrT";
  cout << setw(10) << "EndT" << setw(10)<< "Turn" << setw(10) << "Wait" << setw(10) << "Resp" << endl;
  cout << "+=========================================================================================+" <<endl;
  for(int d=0; d < x; d++)
  {
    cout << setw(10) << left << SJF_ProcessID[d] << setw(10)  << SJF_ArrivalTime[d] << setw(10) << SJF_RunTime[d] << setw(10) << SJF_Priority[d];
    cout << setw(10) << SJF_StartTime[d] << setw(10) << SJF_EndTime[d] << setw(10) << SJF_TurnAround[d] << setw(10);
    cout << SJF_WaitingTime[d] << setw(10) << SJF_ResponceTime[d] << endl;
  }
  cout << "+=========================================================================================+" <<endl;
  cout << "AverageTurnAroundTime = " << SJF_AverageTurnAroundTime/x << endl;
  cout << "AverageWaitingTime = " << SJF_AverageWaitingTime/x << endl;
  cout << "AverageResponceTime = " << SJF_AverageResponceTime/x << endl;
  cout << "Number Context Switches = " << ContextSwitches << endl << endl;
}

/*===============================================================
This section is Priority scheduling implementation
===============================================================*/
void PrioritySchedule()
{
  //testing phase
  //printf("\n[Running Priority scheduling]\n\n");
  SCHEDULE_KEY=1;
  Quicksort(0,x-1);

  //test print
  /*for(int i=0; i < x; i++)
  {
    cout << "PRI_ProcessID[" << PRI_ProcessID[i] << "]\t" << "PRI_Priority[" << i << "] =" << PRI_Priority[i] << endl;
  }*/

  //calculate StartTime for SJF.
  int temp=0;
  for(int s=0; s < x; s++)
  {
    if (s==0)
    {
        PRI_StartTime[s]=0;
    }
    if (s==1)
    {
      PRI_StartTime[s]= PRI_RunTime[s-1];
    }
    if (s==2)
    {
      PRI_StartTime[2]= PRI_RunTime[0]+PRI_RunTime[1];
      temp = PRI_StartTime[2];
    }
    else
    {
      PRI_StartTime[s] = PRI_RunTime[s-1]+temp;
      temp = PRI_StartTime[s];
    }
    //cout << "StartTime for [" << ProcessID[s] << "] = " << StartTime[s] << endl;
  }

  //calculate EndTime
  temp=0;
  for(int e=0; e < x; e++)
  {
    if (e==x-1)
    {
      PRI_EndTime[e]=PRI_StartTime[e]+PRI_RunTime[e];
    }
    else
    {
      PRI_EndTime[e]=PRI_StartTime[e+1];
    }
  }

  //calculate TurnAround time = EndTime - ArrivalTime
  for(int t=0; t < x; t++)
  {
    PRI_TurnAround[t]=PRI_EndTime[t]-PRI_ArrivalTime[t];
    PRI_AverageTurnAroundTime+=PRI_TurnAround[t];
  }

  //calculate WaitingTime = StartTime - ArrivalTime
  for(int w=0; w < x; w++)
  {
    PRI_WaitingTime[w]=PRI_StartTime[w]-PRI_ArrivalTime[w];
    PRI_AverageWaitingTime+=PRI_WaitingTime[w];
  }

  //calculate ResponceTime, In FIFO, this is basically the StartTime.
  for(int r=0; r < x; r++)
  {
    PRI_ResponceTime[r]=PRI_StartTime[r];
    PRI_AverageResponceTime+=PRI_ResponceTime[r];
  }

 int tempRUNTIME = PRI_RunTime[0];
  //calculate ContextSwitches
  for(int c=0; c < x; c++)
  {
    for(int f=0; f < x; f++)
    {
      if (PRI_Priority[c] == PRI_Priority[f+1])//checks if current and next priority are same
      {
        if (tempRUNTIME < PRI_RunTime[f+1])//when same lv priority run time is less than next, switch
        {
          PRI_Priority[c]=PRI_Priority[c]+1; //raise current process's priority level.
          ContextSwitches++;
        }
      }
      tempRUNTIME=PRI_RunTime[c]-1;
    }
  }

  //Display All Results:
  /*===============================================================
  This section will be the final output for PrioritySchedule
  ===============================================================*/
  cout << "===>PrioritySchedule" << endl << endl;
  cout << "Job\t" << "ArivT\t   " << setw(10) << "RunT" << setw(10) << "Prio" << setw(10) << "StrT";
  cout << setw(10) << "EndT" << setw(10)<< "Turn" << setw(10) << "Wait" << setw(10) << "Resp" << endl;
  cout << "+=========================================================================================+" <<endl;
  for(int d=0; d < x; d++)
  {
    cout << setw(10) << left << PRI_ProcessID[d] << setw(10)  << PRI_ArrivalTime[d] << setw(10) << PRI_RunTime[d] << setw(10) << PRI_Priority[d];
    cout << setw(10) << PRI_StartTime[d] << setw(10) << PRI_EndTime[d] << setw(10) << PRI_TurnAround[d] << setw(10);
    cout << PRI_WaitingTime[d] << setw(10) << PRI_ResponceTime[d] << endl;
  }
  cout << "+=========================================================================================+" <<endl;
  cout << "AverageTurnAroundTime = " << PRI_AverageTurnAroundTime/x << endl;
  cout << "AverageWaitingTime = " << PRI_AverageWaitingTime/x << endl;
  cout << "AverageResponceTime = " << PRI_AverageResponceTime/x << endl;
  cout << "Number Context Switches = " << ContextSwitches << endl << endl;


}



/*===============================================================
This section is Quicksorting algorithm which works along with
 the Pivot function in order to organize arrays accourdingly.

  This function will filter with a "SCHEDULE_KEY" which
  allows the program to know for which Schedule we are sorting for.

  Example:

    SCHEDULE_KEY=0  This means we are wanting to run the Pivot
                    for ShortestJobFirst schedule ONLY.

    SCHEDULE_KEY=1  This will run the Pivot specifically for
                    PrioritySchedule ONLY.
===============================================================*/
void Quicksort(int First, int Last)
{
  if(First < Last)
  {
    if(SCHEDULE_KEY==0)//Runs for ShortestJobFirst
    {
      PivotElement = Pivot(First,Last);
      Quicksort(First,PivotElement-1);
      Quicksort(PivotElement+1,Last);
    }
    if(SCHEDULE_KEY==1)//Runs for PrioritySchedule
    {
      PRI_PivotElement = Pivot(First,Last);
      Quicksort(First,PRI_PivotElement-1);
      Quicksort(PRI_PivotElement+1,Last);
    }
  }
}


/*===============================================================
SwapS function swaps strings.
This will help us swap the values from ProcessID's
===============================================================*/
void SwapS(string& a, string& b)
{
  string temp = a;
  a = b;
  b = temp;
}

/*===============================================================
Swap function swamps integer values.
This will be helpful when sort and swapping for
RunTimes, Prioritys, StartTimes, EndTimes, etc.
===============================================================*/
void Swap(int& a, int& b)
{
  int temp = a;
  a = b;
  b = temp;
}


/*===============================================================
Pivot allows us to quick sort and compare values fed into the
function. This function will filter with a "SCHEDULE_KEY" which
allows the program to know for which Schedule we are sorting for.

Example:

  SCHEDULE_KEY=0  This means we are wanting to run the Pivot
                  for ShortestJobFirst schedule ONLY.

  SCHEDULE_KEY=1  This will run the Pivot specifically for
                  PrioritySchedule ONLY.

===============================================================*/
int Pivot(int First, int Last)
{
  //int q = First;
  int p = First;
  PivotElement = SJF_RunTime[First];
  PRI_PivotElement = PRI_Priority[First];

  for(int i= First+1; i <= Last; i++)
  {
    if(SCHEDULE_KEY==0)
    {
      if(SJF_RunTime[i] <= PivotElement)
      {
        p++;
        Swap(SJF_RunTime[i], SJF_RunTime[p]);
        SwapS(SJF_ProcessID[i], SJF_ProcessID[p]); //changes the ProcessID with RunTime swap
        Swap(SJF_ArrivalTime[i],SJF_ArrivalTime[p]);
        Swap(SJF_Priority[i],SJF_Priority[p]);
      }
    }
    if(SCHEDULE_KEY==1)
    {
      if(PRI_Priority[i] <= PRI_PivotElement)
      {
        p++;
        //PRI
        Swap(PRI_RunTime[i],PRI_RunTime[p]);
        SwapS(PRI_ProcessID[i], PRI_ProcessID[p]); //changes the ProcessID with RunTime swap
        Swap(PRI_ArrivalTime[i],PRI_ArrivalTime[p]);
        Swap(PRI_Priority[i],PRI_Priority[p]);
      }
    }
  }
  if(SCHEDULE_KEY==0)
  {
    Swap(SJF_RunTime[p],SJF_RunTime[First]);
    SwapS(SJF_ProcessID[p],SJF_ProcessID[First]);  //ditto.
    Swap(SJF_ArrivalTime[p],SJF_ArrivalTime[First]);
    Swap(SJF_Priority[p],SJF_Priority[First]);
  }
  if (SCHEDULE_KEY==1)//PRI
  {
    Swap(PRI_RunTime[p],PRI_RunTime[First]);
    SwapS(PRI_ProcessID[p], PRI_ProcessID[First]); //changes the ProcessID with RunTime swap
    Swap(PRI_ArrivalTime[p],PRI_ArrivalTime[First]);
    Swap(PRI_Priority[p],PRI_Priority[First]);
  }
  return p;
}
