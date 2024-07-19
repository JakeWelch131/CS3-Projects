// mediator-based air traffic control
// Mikhail Nesterenko
// 11/30/2022

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <map>

// for timed sleep
#include <thread>
#include <chrono>


using std::cout; using std::cin; using std::endl;
using std::string;



// abstract mediator
class Controller{
public:
   virtual void join(class Flight*)=0;
   virtual void leave(class Flight*)=0;
   virtual void broadcast() = 0;
   virtual void observe() = 0;
};


// concrete mediator
// tower, runway clearance
class Tower: public Controller{
public:
   void join(class Flight*) override; 
   void leave(class Flight*) override;
   void broadcast() override;
   void observe() override;
private:
   std::set<class Flight*> waiting_;
};


// abstract flyweight
class Flight {
public:
Flight() {};
 Flight(Controller *controller):controller_(controller), status_(Status::waiting){
      task_ = rand() % 2 ? Task::taxiing : Task::approaching;
      controller_->join(this);
   }
   void receive(const string &msg){
      if (msg.find(FlightNo_) != string::npos || msg.find("all") != string::npos){
         if(msg.find("clear") != string::npos){
            cout << FlightNo_ << " roger that, ";
            cout << (task_ == Task::taxiing ? "taking off" : "landing") << endl;
            status_ = Status::cleared;
         } else if(msg.find("status") != string::npos) {
            cout << FlightNo_
            << (status_ == Status::waiting ? " waiting to " : " cleared to ")   
                  << (task_ == Task::taxiing ? "take off" : "land") << endl;
         } else
            cout << "Tower, this is " << FlightNo_ << " please repeat." << endl;
      }
   }
   bool isCleared() const {return status_ == Status::cleared;}
   void proceed(){
      std::this_thread::sleep_for(std::chrono::seconds(rand()%3+1)); // wait a while    
      cout << "..." << image() 
	   << (task_ == Task::taxiing ? " takes off" : " lands") << "..."
	   << endl; 
      controller_->leave(this);
   }

   virtual string image() = 0;

protected:
   string FlightNo_;
   Controller *controller_;
   enum class Task {taxiing, approaching};  Task task_;
   enum class Status {waiting, cleared};    Status status_;
};

// concrete flyweights
class AirFrance: public Flight{
public:
   AirFrance() {};
   AirFrance(Tower *tower): Flight(tower){
    FlightNo_ = "AirFrance" +
	          std::to_string(rand() % 1000);
      cout << FlightNo_ << " requesting "
	   << (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
   }

   string image() {return "AIRFRANCE";}
};

class KLM: public Flight{
public:
KLM() {};
   KLM(Tower *tower): Flight(tower){
    FlightNo_ = "KLM" +
	          std::to_string(rand() % 1000);
      cout << FlightNo_ << " requesting "
	   << (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
   }

   string image() {return "KLM";}
};

class Aeroflot: public Flight{
public:
Aeroflot() {};
   Aeroflot(Tower *tower): Flight(tower){
    FlightNo_ = "Aeroflot" +
	          std::to_string(rand() % 1000);
      cout << FlightNo_ << " requesting "
	   << (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
   }

   string image() {return "AEROFLOT";}
};

class Lufthansa: public Flight{
public:
   Lufthansa() {};
   Lufthansa(Tower *tower): Flight(tower){
    FlightNo_ = "Lufthansa" +
	          std::to_string(rand() % 1000);
      cout << FlightNo_ << " requesting "
	   << (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
   }

   string image() {return "LUFTHANSA";}
};

class Delta: public Flight{
public:
Delta() {};
   Delta(Tower *tower): Flight(tower){
    FlightNo_ = "Delta" +
	          std::to_string(rand() % 1000);
      cout << FlightNo_ << " requesting "
	   << (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
   }

   string image() {return "DELTA";}
};

class United: public Flight{
public:
United() {};
   United(Tower *tower): Flight(tower){
    FlightNo_ = "United" +
	          std::to_string(rand() % 1000);
      cout << FlightNo_ << " requesting "
	   << (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
   }

   string image() {return "UNITED";}
};


class JetBlue: public Flight{
public:
   JetBlue() {};
   JetBlue(Tower *tower): Flight(tower){
    FlightNo_ = "JetBlue" +
	          std::to_string(rand() % 1000);
      cout << FlightNo_ << " requesting "
	   << (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
   }

   string image() {return "JETBLUE";}
};

enum class flight {airFrance, kLM, aeroflot, lufthansa, delta, united, jetBlue};

// factory
class Hanger{
public:
   static Flight *makeFlight (flight f, Tower *tower_){
     // if officer Flight not found
	 switch(f){
	 case flight::airFrance:
	    return new AirFrance(tower_); break;
	 case flight::kLM:
	    return new KLM(tower_); break;
	 case flight::aeroflot:
	    return new Aeroflot(tower_); break;
	 case flight::lufthansa:
	    return new Lufthansa(tower_); break;
    case flight::delta:
	    return new Delta(tower_); break;
    case flight::united:
	    return new United(tower_); break;
    case flight::jetBlue:
	    return new JetBlue(tower_); break;
	 }
   }
}; 




// member functions for Tower
void Tower::broadcast() {
   cout << "Tower: ";
   string msg;
   getline(cin,msg);
   if(!msg.empty())
      for(auto f: waiting_) f->receive(msg);
}


void Tower::observe() {
   auto findCleared = [](Flight *f){return f->isCleared();};
   
   auto toProceed = std::find_if(waiting_.begin(),waiting_.end(), findCleared);
   
   while (toProceed != waiting_.end()){ // found a cleared Flight
      (*toProceed) -> proceed();
      toProceed = std::find_if(waiting_.begin(), waiting_.end(), findCleared);
      if(toProceed != waiting_.end())
	 cout << "MAYDAY! MAYDAY! MAYDAY! " << endl; // more than a single Flight cleared
   }
}


void Tower::join(Flight *f) {
   waiting_.insert(f);
}


void Tower::leave(Flight *f) {
   waiting_.erase(f);
   delete f;
}

int main(){
   srand(time(nullptr));
   Tower jfk;
   Hanger factory;

   for (int i = 0; i < 4; ++i) {
      int randomIndex = std::rand() % 7;
      flight randomFlight = static_cast<flight>(randomIndex);
      factory.makeFlight(randomFlight, &jfk);
   }

   while(true){
      jfk.broadcast();
      jfk.observe();
   }
}