// jamming peaches
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko

// 9/30/2021


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque; 

struct Peaches{
   double weight; // oz
   bool ripe;  // ripe or not
   void print() const { cout << (ripe?"ripe":"green") << ", " <<  weight << endl; }
};



int main(){
   srand(time(nullptr));
   const double minWeight = 3.;
   const double maxWeight = 8.;

   cout << "Input basket size: ";
   int size;
   cin >> size;

   vector <Peaches> basket(size);

   generate(basket.begin(), basket.end(), [minWeight, maxWeight]() mutable {                                 // generates a basket of peaches with a random weight in between 3-8 and a ripeness of true or false
      Peaches peach;                                                                                         // creates an instance of peach to put into vector
      peach.weight = minWeight + static_cast<double>(rand()) / RAND_MAX * (maxWeight - minWeight);           // assigns the weight of the peach to a random number between 3.0 and 8.0
      peach.ripe = rand() % 2;                                                                               // assigns the ripeness of the peach to true or false
      return peach;
   });

   // for_each() possibly
   for_each(basket.begin(), basket.end(), [](auto e){e.print();});                                             // for each element in the basket, invoke the print() function on it
   cout << endl;
   // moving all the ripe peaches from basket to peck
   // remove_copy_if() with back_inserter()/front_inserter() or equivalents
   deque<Peaches> peck;                                                                                                          //declare a deque of peaches

   remove_copy_if(basket.begin(), basket.end(), std::back_inserter(peck), [](Peaches peach){return !peach.ripe;});              // iterates through the basket vector, and insert the element into the peck deque if the lambda returns true (if the element is ripe)
   basket.erase(remove_if(basket.begin(), basket.end(), [](Peaches peach){return peach.ripe;}), basket.end());                  // iterates through the basket vector and erases the elements that make the lambda return false

   // for_each() possibly
   cout << "peaches left in basket" << endl;
   for_each(basket.begin(), basket.end(), [](auto e){e.print();});


   cout << endl;

   // for_each() possibly
   cout << "peaches moved to the peck"<< endl;
   for_each(peck.begin(), peck.end(), [](auto e){e.print();});



   // prints every "space" peach in the peck
   const int space=3; 
   cout << "\nevery " << space << "\'d peach in the peck"<< endl;

   // replace with advance()/next()/distance()
   // no explicit iterator arithmetic
   auto it=peck.cbegin(); int count = 0; int peckSize = peck.size(); 

   while(count <= peckSize - 3){                                                                                                 // prints every third peach in the peck
      advance(it, 2);
      it->print();
      advance(it, 1);
      count += 3;
   }


   // putting all small ripe peaches in a jam
   // use a binder to create a functor with configurable max weight
   // accumulate() or count_if() then remove_if()
   
   const double weightToJam = 10.0;
   double jamWeight = 0.0; 
   /*for(auto it=peck.begin(); it != peck.end();)
      if(it->weight < weightToJam){
	 jamWeight += it->weight;
	 it=peck.erase(it);
      }else
	 ++it;*/

   
   //auto compare = bind(std::less<double>(), ) 
   
   jamWeight = accumulate(peck.begin(), peck.end(), 0.0, [weightToJam]                                                          
                                                      (double accumulator, Peaches& peach){
                                                         std::less<double> lessThan;
                                                         bool less = lessThan(peach.weight, weightToJam);
                                                         if (less == true) {
                                                            return accumulator += peach.weight;
                                                         }
                                                         else {
                                                            return accumulator;
                                                         }
                                                      });                                                            // jamWeight is the sum of all of the weights of peaches that weight less than 10
   cout << "Weight of jam is: " << jamWeight << endl;

   auto deleteEnd = remove_if(peck.begin(), peck.end(), [weightToJam](Peaches& peach) {
                                                   std::less<double> lessThan;
                                                   return lessThan(peach.weight, weightToJam);
                                                   });                                                               // deleteEnd is the first iterator of the section of the deque that contains all of the elements that weigh less than 10
   peck.erase(deleteEnd, peck.end());                                                                                // deletes the peaches that weigh less than 10 by using range-based erase
   std::size_t numElements = peck.size();
   cout << "Number of peaches left in peck after erase: " << numElements << endl;
}
