/**********************************************
 * Last Name:   Zhang
 * First Name:  QiYue
 * Student ID:  10131658
 * Course:      CPSC 457
 * Tutorial:    T05
 * Assignment:  3
 * Question:    Q7
 *
 * File name: scheduler.cpp
 * Usage:
 *   $ ./scheduler filename.txt RR quantum
 *   $ ./scheduler filename.txt SJF
 *********************************************/

/// counts number of primes from standard input
///
/// compile with:
///   $ gcc count.cpp -O2 -o count -lm
///

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <deque>
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
     char status = ' ';
     int waitTime = 0; // finishTime - arrivalTime - burstTime
     bool operator<(const a& p2) const { num1 < p2.num1; }
};

struct vector<process> processList;
struct queue<process> readyQueue; // contains pid

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

void printStats(int time) {
     cout << " " << time << "  ";
     for(int i = 0; i < processList.size(); i++) {
          cout << processList[i].status << "     ";
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
          bool occupied == false;
          int arrival = 0;
          struct process current;
          int timeout = 0;
          for(int i = 0; i < totalTime; i++) {


               //check for arrivals at time i
               for(arrival; arrival < processList.size(); arrival ++) {
                    if(processsList[arrival].arrivalTime == i) {
                         readyQueue.push_back(processList[arrival]);
                         processList[arrival].status = '+';
                    }
                    if(processsList[arrival].arrivalTime > i) break;
               }

               if(readyQueue.size() > 0 && !occupied) {
                    // the currently executing process
                    current = readyQueue.front();
                    processList[current.pid - 1].status = '.'
                    readyQueue.pop_front();
                    occupied = true;
               }

               printStats();
               current.burstTime--;

               if(current.burstTime == 0) {
                    processList[current.pid - 1].status = ' ';
                    processList[current.pid - 1].waitTime = (i + 1) - processList[current.pid - 1].burstTime - current.arrivalTime;
                    occupied = false;
                    current = NULL;
               } else if (timeout == quantum - 1) {
                    // switch processes
                    readyQueue.push_back(current);
                    processList[current.pid - 1].status = '+';
                    occupied = false;
                    current = NULL;
               }

               // // if none running find shortest job in readyQueue and execute
               // if (!occupied) {
               //      // index in processList is pid - 1
               //      current = readyQueue.front();
               //      readyQueue.pop_front();
               //      processList[current.pid - 1].status = '.';
               //      occupied = true;
               // }

               // printStats(i);
               // current.burstTime--;
               // if(current.burstTime == 0) {
               //
               //      // waitTime = finishTime - burstTime - arrivalTime
               //      processList[current.pid - 1].status = ' ';
               //      processList[current.pid - 1].waitTime = (i+1) - proccesList[current.pid - 1].burstTime - current.arrivalTime;
               //      occupied == false;
               //      current = NULL;
               // }
          }

     } else if (SJF) {
          bool occupied = false;
          int arrival = 0;
          struct process current;
          for(int i = 0; i < totalTime; i++) {


               //check for arrivals at time i
               for(arrival; arrival < processList.size(); arrival ++) {
                    if(processsList[arrival].arrivalTime == i) {
                         //push into readyQueue with sorting by burstTime
                         for(int j = 0; j < readyQueue.size(); j++) {
                              if (processList[arrival].burstTime < readyQueue.at(j).burstTime) {
                                   readyQueue.insert(j, processList[arrival]);
                                   processList[arrival].status = '+';
                              }
                         }
                    }
                    if(processsList[arrival].arrivalTime > i) break;
               }

               // if none running find shortest job in readyQueue and execute
               if (!occupied && readyQueue.size() > 0) {
                    // index in processList is pid - 1
                    current = readyQueue.front();
                    readyQueue.pop_front();
                    processList[current.pid - 1].status = '.';
                    occupied = true;
               }

               printStats(i);
               current.burstTime--;
               if(current.burstTime == 0) {

                    // waitTime = finishTime - burstTime - arrivalTime
                    processList[current.pid - 1].status = ' ';
                    processList[current.pid - 1].waitTime = (i+1) - proccesList[current.pid - 1].burstTime - current.arrivalTime;
                    occupied = false;
                    current = NULL;
               }
          }

     } else {
          cout << "How?" << endl;
     }











     return 0;
}
