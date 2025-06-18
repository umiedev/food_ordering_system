#include "food_ordering_system.h"
#include <limits> 
#include <utility> 
using namespace std; 

int main() {
    OrderQueue orderQueue; 
    AdminList adminMenu(orderQueue);
    CustomerList customerOrder(adminMenu, orderQueue); 
    adminMenu.addMenuItem(1, "Burger", 12.50);
    adminMenu.addMenuItem(2, "Pizza", 25.00);
    adminMenu.addMenuItem(3, "Fries", 5.00);
    adminMenu.addMenuItem(4, "Soda", 3.00); 

    while (true) {
        mainMenu();
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            adminSection(adminMenu, customerOrder, orderQueue); 
            break;
        case 2:
            customerSection(adminMenu, customerOrder, orderQueue); 
            break;
        case 3:
            cout << "\n\t\t\t\t\t\tThank You For Using Our System!\n";
            return 0;
        default:
            cout << "\n\t\t\t\t\t\tInvalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}