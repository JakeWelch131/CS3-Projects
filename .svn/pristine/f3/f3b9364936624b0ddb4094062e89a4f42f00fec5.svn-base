#include "coffeeShack.hpp"

int main() {
    srand(time(nullptr));
    Employee *ep = new JuniorBarista(new SeniorBarista(new Manager));
    vector<Drink*> drinkVector = ep->getDrinkVector();
    vector<Customer*> customerVector = ep->getCustomerVector();
    const int maxCustomer = 3;
    int customerNum = 0;

    do {
        int selection = rand() % 2;                                                                                                                                                     // decides whether to finish order or take another order
                                                                                             
        if (selection == 0 && customerNum != maxCustomer){                                                                                                                              // take order
            char size;
            Drink* drink = nullptr;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
            cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee?" << endl;
            cin >> size;

            switch (size) {
                case 'l':
                    drink = new LargeDrink();
                    break;
                case 'm':
                    drink = new MediumDrink();
                    break;
                case 's':
                    drink = new SmallDrink();
                    break;
            }

            char ingredients = ' ';
            int cost = drink->getPrice();
            string description = drink->getDesc();
            vector<char> ingredientVec = drink->getIngredients();

            while (ingredients != 'd') {
                cout << "Would you like to add [s]ugar, [c]ream, [h]oney, or [d]one?" << endl;
                cin >> ingredients;

                switch (ingredients) {
                case 's':
                    drink = new SugarDecorator(drink);
                    cost = drink->getPrice();
                    description = drink->getDesc();
                    ingredientVec = drink->getIngredients();
                    break;
                case 'c':
                    drink = new CreamDecorator(drink);
                    cost = drink->getPrice();
                    description = drink->getDesc();
                    ingredientVec = drink->getIngredients();
                    break;
                case 'h':
                    drink = new HoneyDecorator(drink);
                    cost = drink->getPrice();
                    description = drink->getDesc();
                    ingredientVec = drink->getIngredients();
                    break;
                case 'd':
                    break;
                }
            }

            string name;
            cout << "Can I get your name?" << endl;
            cin >> name;
            
            drinkVector.push_back(drink);
            Customer *newCustomer = new Customer(ep, drink, name);
            customerVector.push_back(newCustomer);

            if (customerNum < 3)
                ++customerNum;
        }
        else if (selection == 1 && customerVector.size() > 0) {                                                                                                                         // completes an order
                                                                                                           
            int randomDrink = rand() % drinkVector.size();
            
            Drink* drink = drinkVector[randomDrink];                                                                                                                                    // select a random drink
            
            string orderDesc = drink->getDesc();
            
            vector<char> ingredientVec = drink->getIngredients();                                                                                                                       // get ingredients for random drink
            
            Customer *newCustomer = customerVector[randomDrink];                                                                                                                        // selects customer that matches with drink

            if (ingredientVec.size() > 1) {
                string shavedStr = orderDesc.substr(0, orderDesc.length() - 2);                                                                                                         // gets rid of comma on the last ingredient

                ep->handleRequest(ingredientVec);
               
                ep->notifyObservers();

                for(auto customers : customerVector)                                                                                                                                    // goes through every customer and checks if the current drink is theirs
                    customers->checkDrink(drink);

                cout << newCustomer->getName() << " your " << shavedStr << " is ready. It will be $" << drink->getPrice() << ", please." << endl;

                customerVector.erase(customerVector.begin() + randomDrink);
                drinkVector.erase(drinkVector.begin() + randomDrink);
                
            }
            else {
                string shavedStr = orderDesc.substr(0, orderDesc.length() - 1);                                                                                                         // gets rid of comma on the last ingredient

                ep->handleRequest(ingredientVec);
               
                ep->notifyObservers();

                for(auto customers : customerVector)                                                                                                                                    // goes through every customer and checks if the current drink is theirs
                    customers->checkDrink(drink);
                
                cout << newCustomer->getName() << " your " << shavedStr << " nothing is ready. It will be $" << drink->getPrice() << ", please." << endl;

                customerVector.erase(customerVector.begin() + randomDrink);
                drinkVector.erase(drinkVector.begin() + randomDrink);
                
            }
        }
    } while (customerNum < maxCustomer || !customerVector.empty());                                                                                                                     // when customerVec.empty resolves to true or 3 customers have been made


    
   
  
}

