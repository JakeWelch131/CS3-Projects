// drink class to be used in Coffee Shack lab
// Jacob Welch
// 4/12/2024

#include <iostream>
#include <string>
using std::string; using std::cout; using std::cin; using std::endl;
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
private: 
   int price_;
   DrinkType type_;
   std::string description_;
};

// concrete implementations
class SmallDrink: public Drink{
    public:
        SmallDrink(DrinkType type=DrinkType::small, int price = 5, string desc= "small coffee with ") : type_(type), price_(price), description_(desc){}
        int getPrice() const override { return price_; }
        std::string getName() const override { return drinkTypeToString(type_); }
        string getDesc() const override { return description_; }
    private:
        int price_;
        DrinkType type_;
        std::string description_;
};

class MediumDrink: public Drink{
    public:
        MediumDrink(DrinkType type=DrinkType::medium, int price = 7, string desc= "medium coffee with ") : type_(type), price_(price), description_(desc){}
        int getPrice() const override { return price_; }
        std::string getName() const override { return drinkTypeToString(type_); }
        string getDesc() const override { return description_; }
    private:
        int price_;
        DrinkType type_;
        std::string description_;
};

class LargeDrink: public Drink{
    public:
        LargeDrink(DrinkType type=DrinkType::large, int price = 10, string desc= "large coffee with ") : type_(type), price_(price), description_(desc){}
        int getPrice() const override { return price_; }
        std::string getName() const override { return drinkTypeToString(type_); }
        string getDesc() const override { return description_; }
    private:
        int price_;
        DrinkType type_;
        std::string description_;
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

    private:
        const Drink *wrapped_;
};