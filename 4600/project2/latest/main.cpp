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

/*
  GLOBAL VARIABLES
    ===============================================================
    The following section includes all of the global variables
    that this program uses in order to successfully calculate
    simulations for the three scheduling algorithms.

    Variables are separated in 4 categories:

      *Full Globals - These are used throughtout the entire program

      *FIFO Globals - Reserved for FIFO simulation

      *SJF Globals - Reserved for SJF simulation

      *PRI Globals - Reserved for Priority simulation

    ===============================================================

*/

//FULL GLOBAL
int x=0;          //this is known as the total number of processes.
string userfile;  //this string holds the name of the inputfile.
int SCHEDULE_KEY; //this determines which scheduling "mode" used for sorting.

//FIFO GLOBALS
string ProcessID[50];
int ArrivalTime[50]={0};
int RunTime[50];
int Priority[50]={0};
int TurnAround[50];
int WaitingTime[50];
int StartTime[50];
int EndTime[50];
int ResponceTime[50];
int ContextSwitches=0;
int AverageTurnAroundTime=0;
int AverageWaitingTime=0;
int AverageResponceTime=0;

//SJF GLOBALS
int SJF_RunTime[50];
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

//PRI GLOBALS
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

/*
  FUNCTION DECLARATIONS
    ===============================================================
    The following section includes all of the function declarations
    that this program needs in order to compute and simulate
    scheduling algorithms.

    The Calculate_any*(*); Functions are adapted to be called by
    any of the 3 scheduling algorithms, this greatly reduces the
    repetition of code. In addition to this the Display(*);
    is also adpated to be called by any of the algorithms.

    this section also includes ReadFromFile() function which is
    the first function our program will use in order to get a valid
    input from file.

    Quick sort is also used here, this allows us to swap certain
    array values. This is especially helpful when running the
    SJF algorithm as we need to sort the processes by low to high
    values.

    Note, this is also used to sort priority values in our
    Priority algorithm.

    ===============================================================

*/
void FirstInFirstOut();
void ShortestJobFirst();
void PrioritySchedule();

void Calculate_anyStart(int anyStart[50],int anyRunTime[50]);
void Calculate_anyEndTime(int anyEndTime[50], int anyStart[50], int anyRunTime[50]);
void Calculate_anyTurnAround(int anyTurn[50], int anyEndTime[50], int anyArrival[50], int& anyAVG);
void Calculate_anyWaitTime(int anyWait[50], int anyStart[50], int anyArrival[50], int& anyAVG);
void Calculate_Res(int anyRes[50], int anyStart[50], int& anyAVG);
void Calculate_ContextSwitches(int PRI_RunTime[50],int PRI_Priority[50], int& ContextSwitches);
void Display(string PID[50], int A[50], int R[50],int P[50], int S[50], int E[50], int T[50],int W[50], int Res[50],int& ATA, int& AWT, int& ART, int& C);

void ReadFromFile(string userfile);

void Quicksort(int First, int Last);
void SwapS(string& a, string& b);
void Swap(int& a, int& b);
int Pivot(int First, int Last);


/*
  MAIN FUNCTION
    ===============================================================
    This is the code that will call upon the file handling function
    and scheduling functions.

    ===============================================================

*/
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
    ShortestJobFirst(); //complete
    PrioritySchedule(); //complete
  }

  return 0;
}


/*
  FUNCTION IMPLEMENTATION
    ===============================================================
    Below are the functions that have already been declared in the
    beginning of this program.



    ===============================================================

*/


void ReadFromFile(string userfile)
{
  //testing phase
  printf("\n[Data from file:]\n");

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
      if(ProcessID[x].length() <= 20)
      {
      SJF_RunTime[x] = RunTime[x];
      SJF_ProcessID[x] = ProcessID[x];
      SJF_ArrivalTime[x] = ArrivalTime[x];
      SJF_Priority[x] = Priority[x];
      PRI_RunTime[x] = RunTime[x];
      PRI_ProcessID[x] = ProcessID[x];
      PRI_ArrivalTime[x] = ArrivalTime[x];
      PRI_Priority[x] = Priority[x];

      //testing the data read from file.
      cout << ProcessID[x] << " "<< ArrivalTime[x] << " " << RunTime[x] << " " << Priority[x] << "\n";
      x++;
      }
      else
      {
	cout << userfile << " contains a ProcessID that exceeds 20 characters!" << endl;
	cout << "Found at line [" << x+1 << "] with data ==> ";
        cout << ProcessID[x] << " "<< ArrivalTime[x] << " " << RunTime[x] << " " << Priority[x] << "\n";
	cout << "\n Please correct the line or use a different inputfile!\n\n";
	inputfile.close();
	exit(EXIT_SUCCESS);
      }
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

/* //DISABLED BY DEFAULT.


  //  This code snippet allows us to check and make sure the data read in was
  //  properly assigned to our global variable arrays.
  //  Note this is only displaying data for FIFO, in order to check initial
  //  assignment of SJF and PRI arrays, you can simplly add either
  //  SJF_ or PRI_ before any of the variables below.

  cout << "\nPulling from memory: \n";
  for(int y=0; y < x; y++)
  {
    cout << ProcessID[y] << " "<<ArrivalTime[y] <<" "<< RunTime[y] <<" " << Priority[y] <<"\n";
  }
  */
}


/*===============================================================
  This section is the FIFO scheduling implementation

  This function calls multiple other functions that work and
  generate values with the given input data.
  Function names describe the operation implemented.

  In FIFO, we focus on start time and arrival time to calculate
  the order the completed array should be in when displaying to
  the output.
===============================================================*/

void FirstInFirstOut()
{
  Calculate_anyStart(StartTime,RunTime);
  Calculate_anyEndTime(EndTime,StartTime,RunTime);
  Calculate_anyTurnAround(TurnAround,EndTime,ArrivalTime,AverageTurnAroundTime);
  Calculate_anyWaitTime(WaitingTime,StartTime,ArrivalTime,AverageWaitingTime);
  Calculate_Res(ResponceTime,StartTime,AverageResponceTime);

  //Display All Results:
  cout << "===>FirstInFirstOut" << endl << endl;
  Display(ProcessID,ArrivalTime,RunTime,Priority,StartTime,EndTime,TurnAround,WaitingTime, ResponceTime,AverageTurnAroundTime, AverageWaitingTime, AverageResponceTime, ContextSwitches);

}//end of FIFO

/*===============================================================
  This section is the SJF scheduling implementation

  Since SJF bases its processes execution by the smallest
  run time first , we will implement a quicksort
  algorithm that will order the RunTime input array to a
  SJF_RunTime array.

  This particular algorithm will utilitize SCHEDULE_KEY = 0
  Which will tell some of the funtions to run code specificically
  for SJF scheduling.
===============================================================*/
void ShortestJobFirst()
{
  //testing phase
  SCHEDULE_KEY=0;
  Quicksort(0,x-1);
  Calculate_anyStart(SJF_StartTime, SJF_RunTime);
  Calculate_anyEndTime(SJF_EndTime,SJF_StartTime,SJF_RunTime);
  Calculate_anyTurnAround(SJF_TurnAround,SJF_EndTime,SJF_ArrivalTime,SJF_AverageTurnAroundTime);
  Calculate_anyWaitTime(SJF_WaitingTime,SJF_StartTime,SJF_ArrivalTime,SJF_AverageWaitingTime);
  Calculate_Res(SJF_ResponceTime,SJF_StartTime,SJF_AverageResponceTime);

  //Display All Results:
  cout << "===>ShortestJobFirst" << endl << endl;
  Display(SJF_ProcessID,SJF_ArrivalTime,SJF_RunTime,SJF_Priority,SJF_StartTime,SJF_EndTime,SJF_TurnAround,SJF_WaitingTime, SJF_ResponceTime,SJF_AverageTurnAroundTime, SJF_AverageWaitingTime, SJF_AverageResponceTime, ContextSwitches);

}

/*===============================================================
  This section is Priority scheduling implementation

  This function uses input priority values as a way to sort the
  output array.

  In this algorithm we will utilize Calculate_ContextSwitches();

  This particular algorithm will utilitize SCHEDULE_KEY = 1
  Which will tell some of the funtions to run code specificically
  for Priority scheduling.
===============================================================*/
void PrioritySchedule()
{
  SCHEDULE_KEY=1;
  Quicksort(0,x-1);
  Calculate_anyStart(PRI_StartTime,PRI_RunTime);
  Calculate_anyEndTime(PRI_EndTime,PRI_StartTime,PRI_RunTime);
  Calculate_anyTurnAround(PRI_TurnAround,PRI_EndTime,PRI_ArrivalTime, PRI_AverageTurnAroundTime);
  Calculate_anyWaitTime(PRI_WaitingTime,PRI_StartTime,PRI_ArrivalTime,PRI_AverageWaitingTime);
  Calculate_Res(PRI_ResponceTime,PRI_StartTime,PRI_AverageResponceTime);
  Calculate_ContextSwitches(PRI_RunTime,PRI_Priority,ContextSwitches);


  //Display All Results:
  cout << "===>PrioritySchedule" << endl << endl;
  Display(PRI_ProcessID,PRI_ArrivalTime,PRI_RunTime,PRI_Priority,PRI_StartTime,PRI_EndTime,PRI_TurnAround,PRI_WaitingTime, PRI_ResponceTime,PRI_AverageTurnAroundTime, PRI_AverageWaitingTime, PRI_AverageResponceTime, ContextSwitches);

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


void Calculate_anyStart(int anyStart[50], int anyRunTime[50])
{
  int temp=0;
  for(int s=0; s < x; s++)
  {
    if (s==0)
    {
        anyStart[s]=0;
    }
    if (s==1)
    {
      anyStart[s]= anyRunTime[s-1];
    }
    if (s==2)
    {
      anyStart[2]= anyRunTime[0]+anyRunTime[1];
      temp = anyStart[2];
    }
    else
    {
      anyStart[s] = anyRunTime[s-1]+temp;
      temp = anyStart[s];
    }
  }
}

void Calculate_anyEndTime(int anyEndTime[50], int anyStart[50], int anyRunTime[50])
{
    for(int e=0; e < x; e++)
  {
    if (e==x-1)
    {
      anyEndTime[e]=anyStart[e]+anyRunTime[e];
    }
    else
    {
      anyEndTime[e]=anyStart[e+1];
    }
  }
}

void Calculate_anyTurnAround(int anyTurn[50], int anyEndTime[50], int anyArrival[50], int& anyAVG)
{
   for(int t=0; t < x; t++)
  {
    anyTurn[t]=anyEndTime[t]-anyArrival[t];
    anyAVG+=anyTurn[t];
  }
}

void Calculate_anyWaitTime(int anyWait[50], int anyStart[50], int anyArrival[50], int& anyAVG)
{
   for(int w=0; w < x; w++)
  {
    anyWait[w]=anyStart[w]-anyArrival[w];
    anyAVG+=anyWait[w];
  }
}

void Calculate_Res(int anyRes[50], int anyStart[50], int& anyAVG)
{
   for(int r=0; r < x; r++)
  {
    anyRes[r]=anyStart[r];
    anyAVG+=anyRes[r];
  }
}

void Calculate_ContextSwitches(int PRI_RunTime[50],int PRI_Priority[50], int& ContextSwitches)
{
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
          //PRI_Priority[c]=PRI_Priority[c]+1; //raise current process's priority level.NOT USED ANYMORE.
          ContextSwitches++;
        }
      }
      tempRUNTIME=PRI_RunTime[c]-1;
    }
  }
}


void Display(string PID[50], int A[50], int R[50],int P[50], int S[50], int E[50], int T[50],int W[50], int Res[50],int& ATA, int& AWT, int& ART, int& C)
{
  cout << setw(10) << left << "Job" << setw(10) << "AriT" << setw(10) << "RunT" << setw(10) << "Prio" << setw(10);
  cout << "StrT" << setw(10) << "EndT" << setw(10)<< "Turn" << setw(10) << "Wait" << setw(10) << "Resp" << endl;
  cout << "+=========================================================================================+" <<endl;
  for(int d=0; d < x; d++)
  {
    cout << setw(10) << left << PID[d] << setw(10)  << A[d] << setw(10) << R[d] << setw(10) << P[d];
    cout << setw(10) << S[d] << setw(10) << E[d] << setw(10) << T[d] << setw(10);
    cout << W[d] << setw(10) << Res[d] << endl;
  }
  cout << "+=========================================================================================+" <<endl;
  cout << "AverageTurnAroundTime = " << ATA/x << endl;
  cout << "AverageWaitingTime = " << AWT/x << endl;
  cout << "AverageResponceTime = " << ART/x << endl;
  cout << "Number Context Switches = " << C << endl << endl;

}
