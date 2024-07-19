// vector and list algorithms
// Jacob Welch
// 2/9/2024

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <algorithm>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;

// reading a list from a fileName
void readRoster(list<string>& roster, string fileName);  

// printing a list out
void printRoster(const list<string>& roster); 

std::string SubstringAfterColon(const std::string& input);

int main(int argc, char* argv[]){

   if (argc <= 1){ 
      cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" 
      << endl;
      exit(1);
   }

   // vector of courses of students
   vector <list<string>> courseStudents; 

   for(int i=1; i < argc-1; ++i){
      list<string> roster;
      readRoster(roster, argv[i]);  
      courseStudents.push_back(move(roster));
   }

   // reading in dropouts
   list<string> dropouts; 
   readRoster(dropouts, argv[argc-1]); 

   // master list of students
   std::list<std::string> allStudents;

    // Move elements from courseStudents to allStudents without leaving courseStudents empty
    for (const auto& lst : courseStudents) {
        allStudents.insert(allStudents.end(), lst.begin(), lst.end());
    }

   // sorting master list
   allStudents.sort();
 
   // eliminating duplicates
   allStudents.unique(); 

   // removing individual dropouts
   for (const auto& str : dropouts)  
      allStudents.remove(str);

   std::list<std::string> nameWithClass;                                                                    // this list will contain all names and the classes they appear in

    for (auto it = allStudents.begin(); it != allStudents.end(); ++it) {                                    // iterate through the allStudents list
        std::string studentName = (*it).substr(0, (*it).find(':'));                                         // assign a string to a substring that only contains the actual name (weird bug)

        for (size_t i = 0; i < courseStudents.size(); ++i) {                                                // iterate through the courseStudents vector in order to extract each list and assign the classNames based on the list's position in the vector
            list<string>& course = courseStudents[i];                                                       // each course is a list in the courseStudents vector i.e. courseStudents[0] = cs1.txt
            
            // Iterate over each string in the 'course' list
            for (auto course_it = course.begin(); course_it != course.end(); ++course_it) {                 
                // Compare the value pointed to by 'it' with each string in 'course'
                std::string studentInCourse = course_it->substr(0, course_it->find(':'));
                if (studentName == studentInCourse) {                                                       // if we find a student in the allStudents list in a course list
                        switch(i) {                                                                         // we will use a switch statement to assign what class that student is in based on the iteration we are in 
                                case 0:
                                    nameWithClass.push_back(*it + "cs1 ");
                                    break;
                                case 1: 
                                    nameWithClass.push_back(*it + "cs2 ");
                                    break;
                                case 2:
                                    nameWithClass.push_back(*it + "cs3 ");
                                    break;
                                case 3:
                                    nameWithClass.push_back(*it + "cs4 ");
                                    break;
                                default:
                                    cout << "something is wrong" << endl;
                        }
                    break; 
                }
            }
        }
    }

    std::list<std::string> resultList;                                                                      // now that we have a list with all the students and their repsective classes, we need to combine the classes between elements with the same name
    for (auto it = allStudents.begin(); it != allStudents.end(); ++it) {
        string courses = "";                                                                                // this string will hold all the courses a single student is enrolled in

        for (auto finalIt = nameWithClass.begin(); finalIt != nameWithClass.end(); ++finalIt) {
            std::string studentInList = finalIt->substr(0, finalIt->find(':') + 1);                         // create a string that finds just the name in the nameWithClass list in order to compare it to the allStudents list

            if (*it == studentInList) {                                                                     // if those two names match
                courses += SubstringAfterColon(*finalIt);                                                   // add the className to the courses string using the SubstringAfterColon function that finds the class name from the nameWithClass list
            }
        }
        resultList.push_back(*it + courses);                                                                // once the name in allStudents has been checked with every element in the nameWithClass list, we can push that name back with the classes that name was associated with
    }
    cout << "result list with courses" << endl;
    printRoster(resultList);                                                                                // once we have checked everyname in the allStudents list, we can print the results
}
    


// reading in a file of *its into a list of strings
void readRoster(list<string>& roster, string fileName){
   ifstream course(fileName);
   string first, last;
   while(course >> first >> last) {
      roster.push_back(first + ' ' + last + ":");
   }
   course.close();
}

// printing a list out
void printRoster(const list<string>& roster){
   for(const auto& str : roster)
      cout << str << endl;
}

std::string SubstringAfterColon(const std::string& input) {
    size_t colonPos = input.find(':');                                                                     // assings a variable to the position in which the : is found
    
    if (colonPos != std::string::npos) {                                                                    // ensures the colon was found
        return input.substr(colonPos + 1);                                                                 // returns the substring starting from 1 position to the right of the colon to the end of the string
    } else {
        return "";
    }
}