// roster problem using sets
// Jacob Welch
// 2/17/2024

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <set>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;
using std::set;

// reading a list from a fileName
void readRoster(set<string>& roster, string fileName);  

// printing a list out
void printRoster(const set<string>& roster); 

int main(int argc, char* argv[]){

   if (argc <= 1){ 
      cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" 
      << endl;
      exit(1);
   }

    set<string> masterList;

    for(int i = 1; i < argc - 1; ++i){                              // reads in every name in every file
      readRoster(masterList, argv[i]);   
   }

    set<string> dropOutList;                                        // reads in just the dropouts
    readRoster(dropOutList, argv[argc-1]); 
   
    for (const auto& dropOut : dropOutList) {                       // iterates through the dropout list
        auto found = masterList.find(dropOut);                      // declares and initializes an iterator that points to a name in the dropOuts list that is also in the masterList
        if ( found != masterList.end()) {                           // if the iterator is not at .end() (the dropOut was found in the master list)
            masterList.erase(dropOut);                              // then erase that name from the list
        }
    }
    cout << "Currently enrolled Students" << endl;
    printRoster(masterList);                                        // print out the already sorted list without dropouts in it
}

void readRoster(set<string>& roster, string fileName){
   ifstream course(fileName);
   string first, last;
   while(course >> first >> last) {
      roster.insert(first + ' ' + last);
   }
   course.close();
}

void printRoster(const set<string>& roster){
   for(const auto& str : roster)
      cout << str << endl;
}