// selecting oranges
// converting vectors to multimaps
// Mikhail Nesterenko
// 9/26/2022


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;
using std::multimap;

enum class Variety {orange, pear, apple};
vector<string> colors = {"red", "green", "yellow"};

int main(){
   srand(time(nullptr));
   multimap <Variety, string> tree;
   int mapElements = (rand()%100+1);

   // random fruit and color selection

   for (int i = 0; i < mapElements; ++i) {
      Variety fruit = static_cast<Variety>(rand() % 3);
      int color = rand() % 3;
      tree.emplace(fruit, colors[color]);
   }

   /*auto range = tree.equal_range(Variety::orange);
   
   for (auto it = range.first; it != range.second; ++it) {
      cout << it->second << endl;
   }*/

   for(auto it=tree.lower_bound(Variety::orange); it != tree.upper_bound(Variety::orange); ++it)
      cout << it->second << endl;
}
