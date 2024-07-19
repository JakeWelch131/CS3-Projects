// hashmap test file
// implementation basic hashmap (unordered container)
// Jacob Welch
// 3/15/2024

#include "hashmap.hpp"
#include <iostream>
#include <string>
#include <cassert>

using std::string;

int main() {

   //
   // <int, int> hashmap test
   //
   /*hashmap<int, int> myHash;
   
   // test inserts
   //pair<typename list<pair<const int, int>>::iterator, bool> result;

   auto result = myHash.insert(make_pair(4, 40));
   assert(result.second);
   assert(result.first->first == 4);
   assert(result.first->second == 40);

   result = myHash.insert(make_pair(105, 1050));
   assert(result.second);
   assert(result.first->first == 105);
   assert(result.first->second == 1050);

   result = myHash.insert(make_pair(6, 60));
   assert(result.second);
   assert(result.first->first == 6);
   assert(result.first->second == 60);

   result = myHash.insert(make_pair(107, 1070));
   assert(result.second);
   assert(result.first->first == 107);
   assert(result.first->second == 1070);

   result = myHash.insert(make_pair(90, 900));
   assert(result.second);
   assert(result.first->first == 90);
   assert(result.first->second == 900);

   result = myHash.insert(make_pair(95, 950));
   assert(result.second);
   assert(result.first->first == 95);
   assert(result.first->second == 950);

   result = myHash.insert(make_pair(6, 70)); // insert with a duplicate key
   assert(!result.second);
   assert(result.first->first == 6);
   assert(result.first->second == 60);


   // searching map
   // x will have type hashmap<int, int>::value_type*
   auto x = myHash.find(4);
   assert(x != nullptr);
   assert(x->second == 40);

   x = myHash.find(5);
   assert(x == nullptr);


   // test deletes
   auto result1 = myHash.erase(4); // delete with next element in same bucket
   assert(result1.second);
   assert(result1.first->first == 105);
   assert(result1.first->second == 1050);

   auto result2 = myHash.erase(107); // delete the last element in a bucket
   assert(result2.second);
   assert(result2.first->first == 90);
   assert(result2.first->second == 900);

   auto result3 = myHash.erase(6);
   assert(result3.second);
   assert(result3.first->first == 90);
   assert(result3.first->second == 900);

   auto result4 = myHash.erase(105);
   assert(result4.second);
   assert(result4.first->first == 90);
   assert(result4.first->second == 900);

   auto result5 = myHash.erase(95); // erase the last element in the container
   assert(result5.second);
   //assert(result.first == nullptr);

   auto result6 = myHash.erase(90); // erased all elements in container
   assert(result6.second);
   //assert(result.first == nullptr);

   auto result7 = myHash.erase(5); // erase key not in container
   assert(!result.second);
   // first is unspecified
*/


   // <integer, string> hashmap test
   
   hashmap<int, string> employees;
   
   // add tests for insert using the <integer, string> hashmap
    employees.insert(std::make_pair(1, "Bill"));
    employees.insert(std::make_pair(2, "Dave"));
    employees.insert(std::make_pair(3, "Gloria"));
    employees.insert(std::make_pair(4, "Elmer"));
    employees.insert(std::make_pair(5, "Daffy"));

   // add tests for find using the <integer, string> hashmap
   auto it = employees.find(3);
    if (it != nullptr) {
        std::cout << "Key 3 found. Value: " << it->second << std::endl;
    } else {
        std::cout << "Key 3 not found." << std::endl;
    }
   // add tests for erase using the <integer, string> hashmap
   auto result3 = employees.erase(4);
   assert(result3.second);
   assert(result3.first->first == 5);
   assert(result3.first->second == "Daffy");
   std::cout << "erase passes" << std::endl;
   // add tests for [] operator using the <integer, string> hashmap
   employees[123] = "Mike";
   employees[345] = "Charlie";
   employees[192] = "Joe";
   employees[752] = "Paul";
   auto find = employees.find(123);
   assert(find->second == "Mike");
   std::cout << "index operator test successful" << std::endl;
   // add tests for rehash
   employees.rehash(300);
   std::cout << "Rehash test Succesful" << std::endl;
   // check the hashmap is still correct and all operations still work after rehash
   auto result4 = employees.erase(1);
   assert(result4.second);
   std::cout << result4.first->first << std::endl;
   assert(result4.first->first == 2);
   
   assert(result4.first->second == "Dave");
   std::cout << "erase passes again" << std::endl;
    std::cout << "Tests passed" << std::endl;
}