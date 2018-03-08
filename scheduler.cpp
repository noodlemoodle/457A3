#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <map>
#include <math.h>
#include <cstring>
#define _USE_MATH_DEFINES
using namespace std;

int RR = 0;
int SJF = 0;
int quantum = 0;
int totalTime = 0;

// 1.  verify cmd arg
// 2.  verify file
// 3.  process file, add to struct
// 4.  check cmd arg
// 5a. RR ?
//   RR scheduler + output
// 5b. SJF ?
//   SJF scheduler + output

struct process {
     int pid;
     int arrivalTime;
     int burstTime;
};

struct vector<process> processList;
queue<int> readyQueue; // contains pid

// read config file
void readFile(string f) {
     if(f.empty()) {
          cerr << "ERROR: blank filename" << endl;
          exit(0);
     }
     // try to open the file
     ifstream file;
     file.open( f, fstream::in );
     // didn't work? fail!
     if ( file.fail() ) {
          cerr << "ERROR: Couldn't load \"" << f << "\"." << endl;
          exit(0);
     }
     int buffer = 0;
     string line;
     int lineNum = 0;
     while( file.good() && lineNum < 30) {
          getline( file, line ); // while we have data, read in a line

          stringstream ss(line);
          vector<int> words;
          while(ss >> buffer) {
               words.push_back(buffer);
          }
          if (words.size() == 2) {
               processList.push_back(process());
               processList[processList.size()-1].pid = lineNum + 1;
               processList[processList.size()-1].arrivalTime = words[0];
               processList[processList.size()-1].burstTime = words[1];
               buffer = 0;
               lineNum++;
          } else if (words.size() == 0) {
               continue;
          } else {
               cout << "ERROR in file format in line : "<< lineNum+1 << ", line not read" << endl;
          }
     }
}

void printStats(int time, vector<string> stats) {
     cout << " " << time << "  ";
     for(int i = 0; i < stats.size(); i++) {
          cout<<stats[i] << "     ";
     }
     cout<<endl;
}

int main( const int argc, const char** argv ) {

     // Verify commandline args
     if ((argc != 4 && argc != 3)|| (!strcmp(argv[2], "RR") == 0 && !strcmp(argv[2], "SJF") == 0)) {
          cout << "USAGE: ./scheduler config.txt RR 3 (For RR scheduling)\nUSAGE: ./scheduler config.txt SJF (For SJF scheduling)" << endl;
          return 1;
     }
     if (strcmp(argv[2], "RR") == 0 && argc == 4) {
          stringstream ss(argv[3]);
          if(ss >> quantum) {
               RR = 1;
          } else {
               cout << "USAGE: ./scheduler config.txt RR 3 (For RR scheduling)\nUSAGE: ./scheduler config.txt SJF (For SJF scheduling)" << endl;
               return 1;
          }
     } else if (strcmp(argv[2], "SJF") == 0) {
          SJF = 1;
     } else {
          cout<<argv[2];
          cout << "USAGE: ./scheduler config.txt RR 3 (For RR scheduling)\nUSAGE: ./scheduler config.txt SJF (For SJF scheduling)" << endl;
          return 1;
     }

     // read file
     readFile(argv[1]);
     if(processList.size() == 0) { cout << "ERROR: Invalid/empty file" << endl; }
     for(int i = 0; i < processList.size(); i++) {
          totalTime += processList[i].burstTime;
     }

     // print output header
     cout << "Time  ";
     for(int i = 0; i < processList.size(); i++) {
          cout<<"P"<<i+1<<"    ";
     }
     cout<<endl<<"--------------------------------------------------------------------------------------------"<<endl;

     if (RR) {

          for(int i = 0; i < totalTime; i++) {

          }

     } else if (SJF) {

          for(int i = 0; i < totalTime; i++) {
               // check for new arrivals
               // sort queue
               // execute current process
          }

     } else {
          cout << "How?" << endl;
     }











     return 0;
}
