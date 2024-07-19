// picking the best quality lemons
// converting vectors to priority queue
// Mikhail Nesterenko
// 2/17/2023


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <queue>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;
using std::priority_queue;
using std::ostream;


struct Lemon {
    double quality;
    Lemon(double q) : quality(q) {}
    friend bool operator<(const Lemon& left, const Lemon& right) {
        return left.quality < right.quality;
    }
    friend ostream& operator<<(ostream& os, const Lemon& lemon) {
        os << lemon.quality;
        return os;
    }
};

const int maxBoxSize = 30;
const int highestQuality = 10;

int main() {
    srand(time(nullptr));
    priority_queue <Lemon> box;                                                                     
    int boxSize = rand() % maxBoxSize + 1;

    // random quality assingment
    for (int i = 0; i < boxSize; ++i) {
        double randomQuality = static_cast<double>(rand()) / RAND_MAX * highestQuality;
        //cout << randomQuality;
        box.push(Lemon(randomQuality));
    }

    cout << "Here are the lemons (best first): ";

    // replace this code with priority queue
    while (!box.empty()) {
        cout << box.top() << ", ";
        box.pop();
    }
    cout << endl;
}