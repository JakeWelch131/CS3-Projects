// observer pattern using a signup registry
// Mikhail Nesterenko
// 4/22/2014

#include <set>
#include <map>
#include <iostream>
#include <string>
#include <algorithm>

using std::cout; using std::endl;
using std::map; using std::set;
using std::string; using std::pair;

class Observer;
class Subject;

class EventRegistry{
public:
   static void registerObserver(string, Observer*);
   static void deregisterObserver(string, Observer*);
   static void handleMessage(Subject*);
   static map<Subject*, set<Observer*>> getMap();
   static Subject* getSubject(string);
private:
   static map<Subject*, set<Observer*>> observerMap_;
};

// initialize the static map
map<Subject*, set<Observer*>> EventRegistry::observerMap_;


class Observer{
public:
   Observer(const string &name): name_(name) {}
   string getName() const {return name_;}
   void subscribe(string subjectName) {EventRegistry::registerObserver(subjectName, this);}
   void unsubscribe(string subjectName){EventRegistry::deregisterObserver(subjectName, this);}
   void handleMessage(Subject*);
private:
   string name_;
};

class Subject{
public:
   Subject(const string &name): name_(name) {}
   string getName() const {return name_;}
   void generateMessage(){
      cout << name_ << " sent a message" << endl;
      EventRegistry::handleMessage(this);}
private:
   string name_;
};

struct CompareSubjectByName {
    CompareSubjectByName(const string& name) : name_(name) {}

    bool operator()(const pair<Subject*, set<Observer*>>& element) const {
        return (element.first && element.first->getName() == name_);
    }

    const string& name_;
};

void EventRegistry::registerObserver(string name, Observer* o){
    auto it = find_if(observerMap_.begin(), observerMap_.end(), CompareSubjectByName(name));
   if (it != observerMap_.end()) {
    Subject* subject = it->first;                                                                       // checks to make sure the same name does not get made into duplicate subjects
    observerMap_[subject].insert(o);
    cout << o->getName() << " subscribed to " << subject->getName() << endl;
   }
   else {        
    Subject* subject = new Subject(name);
   observerMap_[subject].insert(o);
   cout << o->getName() << " subscribed to " << subject->getName() << endl;
    }
}

void EventRegistry::deregisterObserver(string name, Observer* o){
    auto it = find_if(observerMap_.begin(), observerMap_.end(), CompareSubjectByName(name));
    if (it != observerMap_.end()) {
        Subject* subject = it->first;                                                                       // checks to make sure the same name does not get made into duplicate subjects
        observerMap_[subject].erase(o);
        cout << o->getName() << " unsubscribed from " << subject->getName() << endl;
   }
   
}

void EventRegistry::handleMessage(Subject *s){
   for (auto e: observerMap_[s])
      e->handleMessage(s);
}

map<Subject*, set<Observer*>> EventRegistry::getMap() {
    return observerMap_;
}
Subject* EventRegistry::getSubject(string name) {
    auto it = find_if(observerMap_.begin(), observerMap_.end(), CompareSubjectByName(name));
   if (it != observerMap_.end()) {
    Subject* subject = it->first;                                                                       // checks to make sure the same name does not get made into duplicate subjects
    return subject;
   }
}

void Observer::handleMessage(Subject *s) {
   cout << name_ << " received message from " << s->getName() << endl;
}




int main() {
    auto registry = new EventRegistry;
   //Subject  sue("Subject Sue"),  steve("Subject Steve");
   Observer olaf("Observer Olaf"), olga("Observer Olga");


   olaf.subscribe("Subject Sue"); olaf.subscribe("Subject Steve");
   olga.subscribe("Subject Sue");

   auto map = registry->getMap();
   cout << "Number of subjects in map: " << map.size() << endl;

   cout << endl;

   
   auto sue = registry->getSubject("Subject Sue");
   auto steve = registry->getSubject("Subject Steve");
   sue->generateMessage();
   steve->generateMessage();
   cout << endl;
   
   
   olga.unsubscribe("Subject Sue");
   sue->generateMessage();   
 
}