// vector and list algorithms with map
// Jacob Welch
// 2/15/2024

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <map>
#include <algorithm> 
#include <utility>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;


class Student{
public:
                    Student(string firstName, string lastName): 
                    firstName_(firstName), lastName_(lastName) {}
 
   // move constructor, not really needed, generated automatically
                    Student(Student && org) noexcept:
                    firstName_(move(org.firstName_)),
                    lastName_(move(org.lastName_))
                    {}
  
   // force generation of default copy constructor
                    Student(const Student & org) = default;

    // needed for unique() and for remove()
    friend bool     operator== (Student left, Student right){
                        return left.lastName_ == right.lastName_ &&
                            left.firstName_ == right.firstName_;
                            }    

   // needed for sort()
   friend bool      operator< (Student left, Student right){
                        return left.firstName_ < right.firstName_ ||
                            (left.firstName_ == right.firstName_ && 
                            left.lastName_ < right.lastName_);
                    }
    
    list<string>    getClasses() const { return classes_;}
    string          getName() const {return firstName_ + " " + lastName_;}
    void            addClasses(string course) {classes_.push_back(course);}
private:
   string firstName_;
   string lastName_;
   list<string> classes_;
};




// reading a list from a fileName
void readRoster(std::map<Student, list<string>>& roster, string fileName);  
// printing a list out
void printRoster(const std::map<Student, list<string>>& roster); 

void printList(const list<string>& classes);

void oldReadRoster(list<string>& roster, string fileName);

void oldPrintRoster(const list<string>& roster);

int main(int argc, char* argv[]){

   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

   // vector of courses of students

   std::map<Student, list<string>> courseStudents; 
   for(int i = 1; i < argc - 1; ++i){
      readRoster(courseStudents, argv[i]);  
      //cout << "Read: " << argv[i] << endl;  
   }

   vector <list<string>> vectorList; 
   for(int i=1; i < argc-1; ++i){
      list<string> roster;
      oldReadRoster(roster, argv[i]);  
      vectorList.push_back(move(roster));
   }

   // reading in dropouts
   list<string> dropouts; 
   oldReadRoster(dropouts, argv[argc-1]); 

   // master list of students
   std::list<std::string> allStudents;

    // Move elements from courseStudents to allStudents without leaving courseStudents empty
    for (const auto& lst : vectorList) {
        allStudents.insert(allStudents.end(), lst.begin(), lst.end());
    }

   // sorting master list
   allStudents.sort();
 
   // eliminating duplicates
   allStudents.unique(); 

   // removing individual dropouts
   for (const auto& str : dropouts)  
      allStudents.remove(str);                                                                                                              // allStudents now has all the students we need 

    for (auto it = courseStudents.begin(); it != courseStudents.end();) {                                                                   // iterate through the map, we need to get rid of students that only exist in the courseStudents map because those students are dropouts
        string studentName = it->first.getName();                                                                                           // access the Object's name though the "key"
        if (std::find(allStudents.begin(), allStudents.end(), studentName) == allStudents.end()) {                                          // this checks if the student in courseStudents is in the allStudents list
            it = courseStudents.erase(it);                                                                                                  // if the student was not in the allStudents list, then they are a dropout and they get erased from the map
            //cout << "something erased" << endl;                                                                                           // .erase() returns an iterator pointing to the next element after the erased element
        } else {
            ++it;                                                                                                                           // if the student was in both lists, then nothing needs done and we can move to the next name
        }
    }
    
    std::map<Student, list<string>, std::less<Student>> sortedCourseStudents(courseStudents.begin(), courseStudents.end());                 // declares a map that uses the std::less comparator to use the overloaded '<' operator
                                                                                                                                            // and then we initialize sortedCourseStudents with all elements in courseStudents
    printRoster(sortedCourseStudents);                                                                                                      // this effectively creates a copy of courseStudents and then sorts it by first name alphabetically

}

void oldReadRoster(list<string>& roster, string fileName){
   ifstream course(fileName);
   string first, last;
   while(course >> first >> last) {
      roster.push_back(first + ' ' + last);
   }
   course.close();
}

void readRoster(std::map<Student, list<string>>& roster, string fileName){
   ifstream course(fileName);
   string first, last;
   string className = fileName.substr(0, 3);                                                                    //gets rid of .txt


   while(course >> first >> last) {                                                                             // reads first line until whitespace (firstname) and the second line until whitespace (lastName)
    bool found = false;                                                                                         // defualt value of found set to false in order to add new students to the roster
    string studentName = first + " " + last;                                                                    // creates a string from the two values read in from the file

    for (auto& pair : roster) {                                                                                 // iterate through each element in the map

        if (pair.first.getName() == studentName) {                                                              // accesses the name of the student using map's first notation to access the object and .getName() to return the name
            found = true;                                                                                       // then set the found value to be true
            pair.second.push_back(className);                                                                   // access the list of courses in the Student object, and add the className to the course list
            break;                                                                                              // no need to keep iterating through
        }
    }
        if (!found) {                                                                                           // if found is false (there are no people with that name in the list)
            Student new_kid(first, last);                                                                       // create a new instance of the Student class and contruct it with the names read in 
            new_kid.addClasses(className);
            roster.insert({std::move(new_kid), std::move(new_kid.getClasses())});                               // insert the new instance of Student we made as the key, and the class the Student was found in as the value component                      
        }
    }
   course.close();
}

// printing a list out
void printRoster(const std::map<Student, list<string>>& roster){
   for(const auto& student : roster) {
        cout << student.first.getName() << " ";
        printList(student.second);
        cout << endl;
   }
}

void printList(const list<string>& classes) {
        for (auto& className : classes) {
            cout << className << " ";
        }
    };

void oldPrintRoster(const list<string>& roster){
   for(const auto& str : roster)
      cout << str << endl;
}