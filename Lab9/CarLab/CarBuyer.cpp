// needed for lab
// Jacob Welch
// 4/4/2024

#include <iostream>
#include <vector>
#include <cstdlib>
#include <array>
#include "CarFactory.hpp"

using std::vector; using std::array;
using std::cout; using std::endl; using std::string;

class CarLot{
public:
   CarLot();
   Car *testDriveCar(){return car4sale_;}

   // if a car is bought, requests a new one
   Car *buyCar(){ 
      Car *bought = car4sale_;
      car4sale_ = 
        factories_[rand()%factories_.size()]->requestCar();
      return bought;
   }

   int lotSize() {
    return maxCars;
   }

   Car* nextCar() {
    carPos++;
    car4sale_ = carsInLot[carPos % maxCars];
    return car4sale_;
   }
		     
private:
   Car *car4sale_; // single car for sale at the lot
   vector<CarFactory *> factories_;
   vector<Car *> carsInLot;
   static const int maxCars = 8;
   static int carPos;
};

int CarLot::carPos = -1;

CarLot::CarLot(){
   // creates 2 Ford factories and 2 Toyota factories 
   factories_.push_back(new FordFactory());   
   factories_.push_back(new ToyotaFactory());
   factories_.push_back(new FordFactory());
   factories_.push_back(new ToyotaFactory());

   // fills lot with cars
   for (int i = 0; i < maxCars; ++i) {
    carsInLot.push_back(factories_[rand() % factories_.size()] -> requestCar());
   }
}



CarLot *carLotPtr = nullptr; // global pointer instantiation


void buyCar() {
   if (carLotPtr == nullptr)
      carLotPtr = new CarLot();

   string requestedMake = (rand() % 2 == 1) ? "Ford" : "Toyota";
   string requestedModel;
   array<string, 4> fordModels= {"Focus", "Mustang", "Explorer", "F-150"};
   array<string, 5> toyotaModels = {"Corolla", "Camry", "Prius", "4Runner", "Yaris"};
   if (requestedMake == "Ford") {
      requestedModel = fordModels[rand() % 4];
   }
   else {
      requestedModel = toyotaModels[rand() % 5];
   }

   cout << "Customer wants to buy a " << requestedMake << " " << requestedModel << endl;

   for (int i = 0; i < carLotPtr->lotSize(); ++i){
      
      Car *toBuy = carLotPtr->nextCar();
      cout << "customer is looking at " << toBuy->getMake() << " " << toBuy->getModel() << endl;
      if (toBuy->getMake() == requestedMake && toBuy->getModel() == requestedModel) {
         toBuy = carLotPtr->buyCar();
         cout << "Customer bought a " << toBuy->getMake() << " " << toBuy->getModel() << endl;
         break;
      }
      else {
         cout << "no thanks" << endl;
         cout << "=======================" << endl;
      }
   }
   

   
}

// test-drives a car
// buys it if Toyota
void toyotaLover(int id){
   if (carLotPtr == nullptr)
      carLotPtr = new CarLot();

   Car *toBuy = carLotPtr -> testDriveCar(); 

   cout << "Jill Toyoter" << id << endl;
   cout << "test driving " 
	<< toBuy->getMake() << " "
	<< toBuy->getModel();

   if (toBuy->getMake() == "Toyota"){
      cout << " love it! buying it!" << endl;
      carLotPtr -> buyCar();
   } else
      cout << " did not like it!" << endl;
}

// test-drives a car
// buys it if Ford
void fordLover(int id){
   if (carLotPtr == nullptr)
      carLotPtr = new CarLot();

   Car *toBuy = carLotPtr -> testDriveCar();
   
   cout << "Jack Fordman " << id << endl;
   cout << " test driving "
	<< toBuy->getMake() << " "
        << toBuy->getModel();
   
   if (toBuy->getMake() == "Ford"){
      cout << " love it! buying it!" << endl;
      carLotPtr -> buyCar();
   } else
      cout << " did not like it!" << endl;
}



int main() {
   srand(time(nullptr));

   const int numBuyers=5;
   for(int i=0; i < numBuyers; ++i)
      buyCar();
  
}