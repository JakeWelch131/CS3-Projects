// drink class to be used in Coffee Shack lab
// Jacob Welch
// 4/12/2024

#include <iostream>
#include <string>
#include <vector>
using std::string; using std::cout; using std::cin; using std::endl; using std::vector;
enum class DrinkType {small, medium, large};

std::string drinkTypeToString(DrinkType type) {
    switch (type) {
        case DrinkType::small:
            return "Small";
        case DrinkType::medium:
            return "Medium";
        case DrinkType::large:
            return "Large";
        default:
            return "Unknown";
    }
}

// base interface
class Drink{
public:
   Drink(DrinkType type=DrinkType::small, int price=0):
                 type_(type), price_(price){}
   virtual int getPrice() const = 0;
   virtual std::string getName() const = 0;
   virtual std::string getDesc() const = 0;
   virtual vector<char> getIngredients() const = 0;
private: 
   int price_;
   DrinkType type_;
   std::string description_;
   vector<char> ingredientVec_;
};

// concrete implementations
class SmallDrink: public Drink{
    public:
        SmallDrink(DrinkType type=DrinkType::small, int price = 5, string desc= "small coffee with ") : type_(type), price_(price), description_(desc){}
        int getPrice() const override { return price_; }
        std::string getName() const override { return drinkTypeToString(type_); }
        string getDesc() const override { return description_; }
        vector<char> getIngredients() const override { return ingredientVec_; }
    private:
        int price_;
        DrinkType type_;
        std::string description_;
        vector<char> ingredientVec_;
};

class MediumDrink: public Drink{
    public:
        MediumDrink(DrinkType type=DrinkType::medium, int price = 7, string desc= "medium coffee with ") : type_(type), price_(price), description_(desc){}
        int getPrice() const override { return price_; }
        std::string getName() const override { return drinkTypeToString(type_); }
        string getDesc() const override { return description_; }
        vector<char> getIngredients() const override { return ingredientVec_; }
    private:
        int price_;
        DrinkType type_;
        std::string description_;
        vector<char> ingredientVec_;
};

class LargeDrink: public Drink{
    public:
        LargeDrink(DrinkType type=DrinkType::large, int price = 10, string desc= "large coffee with ") : type_(type), price_(price), description_(desc){}
        int getPrice() const override { return price_; }
        std::string getName() const override { return drinkTypeToString(type_); }
        string getDesc() const override { return description_; }
        vector<char> getIngredients() const override { return ingredientVec_; }
    private:
        int price_;
        DrinkType type_;
        std::string description_;
        vector<char> ingredientVec_;
};

// decorator base
class DrinkDecorator: public Drink {
    public:
        DrinkDecorator(const Drink* drinkPtr): wrapped_(drinkPtr){}
        int getPrice() const override { return wrapped_->getPrice(); }
        std::string getName() const override {
            return wrapped_->getName();
        }
        string getDesc() const override { return wrapped_->getDesc(); }
        vector<char> getIngredients() const override { return wrapped_->getIngredients(); }
    private:
        const Drink *wrapped_;
};

// concrete decorator base adds sugar
class SugarDecorator: public Drink {
    public:
        SugarDecorator(const Drink* drinkPtr): wrapped_(drinkPtr){}
        int getPrice() const override { return wrapped_->getPrice() + 1; }
        std::string getName() const override {
            return wrapped_->getName();
        }
        string getDesc() const override { return wrapped_->getDesc() + "sugar, "; }
        vector<char> getIngredients() const override { 
            vector<char> ingredientVector =  wrapped_->getIngredients(); 
            ingredientVector.push_back('s');
            return ingredientVector;
        }
    private:
        const Drink *wrapped_;
};

class CreamDecorator: public Drink {
    public:
        CreamDecorator(const Drink* drinkPtr): wrapped_(drinkPtr){}
        int getPrice() const override { return wrapped_->getPrice() + 2; }
        std::string getName() const override {
            return wrapped_->getName();
        }
        string getDesc() const override { return wrapped_->getDesc() + "cream, "; }
        vector<char> getIngredients() const override { 
            vector<char> ingredientVector =  wrapped_->getIngredients(); 
            ingredientVector.push_back('c');
            return ingredientVector;
        }
    private:
        const Drink *wrapped_;
};

class HoneyDecorator: public Drink {
    public:
        HoneyDecorator(const Drink* drinkPtr): wrapped_(drinkPtr){}
        int getPrice() const override { return wrapped_->getPrice() + 3; }
        std::string getName() const override {
            return wrapped_->getName();
        }
        string getDesc() const override { return wrapped_->getDesc() + "honey, "; }
        vector<char> getIngredients() const override { 
            vector<char> ingredientVector =  wrapped_->getIngredients(); 
            ingredientVector.push_back('h');
            return ingredientVector;
         }
    private:
        const Drink *wrapped_;
};

// ===================================== Observer class declarations start here ===============================

class Employee;

// abstract customer (observer)
class AbstractCustomer {
    public:
        AbstractCustomer(class Employee* barista = nullptr, string name_ = "", Drink* order = nullptr) {};
        virtual void notify() const = 0;
};

//  concrete customer (observer)
class Customer : public AbstractCustomer {
    public:
        Customer(class Employee* barista, Drink* order, string name) : barista_(barista), order_(order), name_(name) {}
        void checkDrink(Drink* baristaDrink) {
            if (baristaDrink->getDesc() == order_->getDesc()) {
                cout << name_ << ": This is my drink. Thank you!" << endl;
                //barista_->getDrinkVector().erase(baristaDrink);
            } 
            else {
                cout << name_ << ": This is not my drink" << endl;
            }
        }

        void notify() const {
            cout << name_ <<": I have been notified" << endl;
        }

        Drink* getDrink() { return order_; }
        string getName() { return name_; }

    private:
        Employee* barista_;
        Drink* order_;
        string name_;
};

//abstract class that sets up individual links in the chain

        
class Employee {
    public:
        Employee(Employee *successor = nullptr) : successor_(successor) {}

        virtual void handleRequest(vector<char> v) {
            if (successor_ != nullptr)
                successor_-> handleRequest(v);
            else
                cout << "nobody can handle this request" << endl;
        }

        vector<Drink*> getDrinkVector() { return drinks_; }
        vector<Customer*> getCustomerVector() { return customers_; }

        void notifyObservers() const {
            for(auto e: customers_) e->notify();
        }

        void registerObserver(Customer* customer) { customers_.push_back(customer); }
        void deregisterObserver(int num) {customers_.erase(customers_.begin() + num); }

        void completeOrder(int customerNum) {
            cout << customers_[customerNum]->getName();
            this->notifyObservers();
            this->deregisterObserver(customerNum);
        }

        bool allCustomersServed() { return customers_.empty(); }

    private:
        Employee *successor_;
        static vector<Customer*> customers_;
        static vector<Drink*> drinks_;
};

Employee Employee::*successor_;
vector<Customer*> Employee::customers_;
vector<Drink*> Employee::drinks_;

// derived classes
class JuniorBarista : public Employee{
    public:
        JuniorBarista(Employee *successor = nullptr) : Employee(successor) {}
        void handleRequest(vector<char> v) override {
            if (v.size() == 0)
                cout << "Junior Barista is serving you" << endl;
            else
                Employee::handleRequest(v);
        }
};

class SeniorBarista : public Employee{
    public:
        SeniorBarista(Employee *successor = nullptr) : Employee(successor) {}
        void handleRequest(vector<char> v) override {
            bool honeyExists = false;
            for(char ch : v) {
                if (ch == 'h') {
                    honeyExists = true;
                    break;
                }
                else {
                    continue;
                }
            }
            if (honeyExists == false && v.size() > 0) 
                cout << "Senior Barista is serving you" << endl;
            else
                Employee::handleRequest(v);
        }
};

class Manager : public Employee {
    public:
        Manager(Employee *successor = nullptr) : Employee(successor) {}
        void handleRequest(vector<char> v) override {
            bool honeyExists = false;
            for(char ch : v) {
                if (ch == 'h') {
                    honeyExists = true;
                    break;
                }
            }
            if(honeyExists == true && v.size() > 0) {
                cout << "The manager is serving you" << endl;
            }
            else   
                Employee::handleRequest(v);
        }
};


