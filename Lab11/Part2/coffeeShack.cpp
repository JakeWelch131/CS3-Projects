#include "coffeeShack.hpp"

int main() {
    char size;
    Drink* drink;
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

    char ingredients;
    int cost = drink->getPrice();
    string description = drink->getDesc();
    vector<char> ingredientVec;

    while (ingredients != 'd') {
        cout << "Would you like to add [s]ugar, [c]ream, [h]oney, or [d]one?" << endl;
        cin >> ingredients;
        ingredientVec.push_back(ingredients);

        switch (ingredients) {
        case 's':
            drink = new SugarDecorator(drink);
            cost = drink->getPrice();
            description = drink->getDesc();
            break;
        case 'c':
            drink = new CreamDecorator(drink);
            cost = drink->getPrice();
            description = drink->getDesc();
            break;
        case 'h':
            drink = new HoneyDecorator(drink);
            cost = drink->getPrice();
            description = drink->getDesc();
            break;
        case 'd':
            break;
        }
    }

    string name;
    cout << "Can I get your name?" << endl;
    cin >> name;
    string orderDesc = drink->getDesc();

    Employee *ep = new JuniorBarista(new SeniorBarista(new Manager));


    if (ingredientVec.size() > 1) {
        string shavedStr = orderDesc.substr(0, orderDesc.length() - 2);                                                                     // gets rid of comma on the last ingredient

        ep->handleRequest(ingredientVec);

        cout << name << " your " << shavedStr << " is ready. It will be $" << drink->getPrice() << ", please." << endl;
    }
    else {
        string shavedStr = orderDesc.substr(0, orderDesc.length() - 1);                                                                     // gets rid of comma on the last ingredient


        ep->handleRequest(ingredientVec);

        cout << name << " your " << shavedStr << " nothing is ready. It will be $" << drink->getPrice() << ", please." << endl;
    }
    /*for (char ingredient : ingredientVec) {
        cout << ingredient << endl;
    }*/
}