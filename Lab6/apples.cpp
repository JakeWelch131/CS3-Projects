// multimap examples
// Mikhail Nesterenko
// 3/16/2014

#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using std::cout; using std::endl;
using std::make_pair; using std::multimap;


int main () {
   multimap<char,int> myMM;
   srand(time(nullptr));

   for(int i=0; i < 10; ++i)
      myMM.insert(make_pair('a'+ rand() % 5, rand()%100)); 

   //  myMM['a']=55; // not allowed
   
   // print content
   cout << "elements in myMM:" << endl;
   for_each(myMM.begin(), myMM.end(), [](auto e){cout << e.first << " " << e.second << endl;});

   
   cout << "all elements in myMM with key 'c'" << endl;
   for_each(myMM.lower_bound('c'), myMM.upper_bound('c'), [](auto e){cout << e.first << '\t' << e.second << endl;});

   // erasing all elements with key 'a'
   cout << "erasing a " << endl;
   cout << myMM.erase('a') << endl;
   
   // erasing all elements with key 'b'
   cout << "erasing b " << endl;
   cout << myMM.erase('b') << endl;
   
   //erase c
   cout << "erasing c " << endl;
   myMM.erase(myMM.lower_bound('c'), myMM.upper_bound('c'));
   
   // print content
   cout << "only d and e left" << endl;
   for_each(myMM.begin(), myMM.end(), [](auto e){cout << e.first << " " << e.second << endl;});

   
}