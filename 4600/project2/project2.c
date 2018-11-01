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
#include <stdio.h>
#include <stdlib.h>

//global variables
char*  ProcessID[50];
int   ArrivalTime[50];
int   RunTime[50];
int   Priority[50];

//function declarations
void ReadFromFile(char* argv[]);
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
    printf("\nArguments Accepted!\n");
    printf("argv[1]=%s\n",argv[1]);
    ReadFromFile(argv);
    FirstInFirstOut();
    ShortestJobFirst();
    PrioritySchedule();
  }

  return 0;
}

void ReadFromFile(char* argv[])
{
  //testing phase
  printf("\n[Reading data from file]\n");

  //creating 2 streams for input an output
  FILE *inputfile, *outputfile;
  //forced name of output file.
  char outputfileName[] = "Results.txt";
  //"states" or "modes" for file.
  char *read = "r", *write = "w";

  //we open the filename argument from main and read.
  inputfile = fopen(argv[1],read);
  //check if file is valid
  if(inputfile == NULL)
  {
    fprintf(stderr, "cannot open %s\n",argv[1]);
    //force program to return exit status 1.
    exit(1);
  }
  /*===============================================================
  this section runs if input file is valid.
  ===============================================================*/
  char pID[20];
  char TempID[50];
  int a,r,p,x=0;

  while (!feof(inputfile))
  {
    if(fscanf(inputfile, "%s %d %d %d",pID,&a,&r,&p)==4)
    {
      ProcessID[x] = pID;
    //  TempID[x] = pID;
      ArrivalTime[x] = a;
      RunTime[x] = r;
      Priority[x] = p;
    //  printf("\nPID=%s AT=%d RT=%d PR=%d\n", ProcessID[x],ArrivalTime[x],RunTime[x],Priority[x]);
      x++;
    }
  }


  /*===============================================================
  This section is for the writting to output file.
  ===============================================================*/
  /*
  outputfile = fopen(outputfileName, write);
  if(outputfile == NULL)
  {
    fprintf(stderr, "cannot open %s!\n",outputfileName);
    exit(1);
  }
  */


  //close file(s)
  //fclose(inputfile);
  //fclose(outputfile);
  /*===============================================================
  This section is for testing our arrays.
  ===============================================================*/
  int y;
  for(y=0; y < x; y++)
  {
    printf("\nPID=%s AT=%d RT=%d PR=%d\n", ProcessID[y],ArrivalTime[y],RunTime[y],Priority[y]);
  }
  fclose(inputfile);
}


/*===============================================================
This section is the FIFO scheduling implementation
===============================================================*/

void FirstInFirstOut()
{
  //testing phase
  printf("\n[Running FIFO scheduling]\n");
}

/*===============================================================
This section is the SJF scheduling implementation
===============================================================*/
void ShortestJobFirst()
{
  //testing phase
  printf("\n[Running SJF scheduling]\n");
}

/*===============================================================
This section is Priority scheduling implementation
===============================================================*/
void PrioritySchedule()
{
  //testing phase
  printf("\n[Running Priority scheduling]\n\n");
}
