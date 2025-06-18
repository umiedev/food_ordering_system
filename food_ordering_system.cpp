//food_ordering_system.cpp
#include "food_ordering_system.h"
#include <limits>    
#include <iomanip>
#include <utility>   
#include <string>    

using namespace std;
//this code use linear search, it checks every element one by one until a match is found function: AdminList::searchMenuItemBySerial() 
// AdminList::deleteAdminItem(),AdminList::addMenuItem(), AdminList::updateMenuItem(), and CustomerList::placeOrder()
// Node Implementations 
Node::Node(int data, string foodName, float price, int quantity)
    : data(data), foodName(std::move(foodName)), price(price), quantity(quantity), next(nullptr) {
} //LINKED LIST


// OrderQueue Implementations manages a queue of customer orders, processing them in a First-In, First-Out (FIFO) manner.
OrderQueue::OrderQueue() : front(nullptr), rear(nullptr), nextOrderId(1) {}

OrderQueue::~OrderQueue() {
    while (!isEmpty()) {
        dequeue(); // Dequeue 
    }
}
//LINKED LIST QUEUE NODE 
//Adds a new customer order to the rear of the queue.
void OrderQueue::enqueue(QueueItem item) {
    QueueNode* newNode = new QueueNode(std::move(item));
    if (isEmpty()) {
        front = newNode;
        rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }
    cout << "\n\t\t\t\t\t\tOrder #" << item.orderId << " has been added to the processing queue.\n";
}
// Removes and returns the order from the front of the queue.
QueueItem OrderQueue::dequeue() { 
    if (isEmpty()) {
        cout << "\n\t\t\t\t\t\tThe order queue is empty!\n";
        return QueueItem(); // Return a default/empty QueueItem
    }
    QueueNode* temp = front;
    QueueItem dequeuedItem = temp->data;
    front = front->next;
    if (front == nullptr) { // If queue becomes empty
        rear = nullptr;
    }
    delete temp;
    return dequeuedItem;
}
//Checks if the order queue is empty.
bool OrderQueue::isEmpty() const {
    return front == nullptr;
}
//Displays all orders currently waiting in the queue.
void OrderQueue::displayQueue() const {
    if (isEmpty()) {
        cout << "\n\t\t\t\t\t\tThe order queue is currently empty.\n";
        return;
    }
    cout << "\n\t\t\t\t\t\t--- Current Order Queue ---\n";
    QueueNode* current = front;
    while (current != nullptr) {
        cout << "\t\t\t\t\t\tOrder #" << current->data.orderId
            << " | Total: $" << fixed << setprecision(2) << current->data.totalAmount
            << " | Details: " << current->data.orderDetailsSummary << "\n";
        current = current->next;
    }
    cout << "\n";
}

int OrderQueue::getNextOrderIdAndIncrement() { // Provides a unique ID for a new order and increments the counter for the next one.
    return nextOrderId++;
}

// AdminList Implementations 
//tializes an empty menu list by setting head and tail to nullptr
AdminList::AdminList(OrderQueue& queue) : head(nullptr), tail(nullptr), orderQueueRef(queue) {}

AdminList::~AdminList() {
    clear();
}

void AdminList::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->getNext();
        delete current;
        current = nextNode;
    }
    head = nullptr;
    tail = nullptr;
}

void AdminList::adminMenu() {
    cout << "\n\t\t\t\t\t\t\t1. View total sales\n";
    cout << "\t\t\t\t\t\t\t2. Add new items in the order menu\n";
    cout << "\t\t\t\t\t\t\t3. Delete items from the order menu\n";
    cout << "\t\t\t\t\t\t\t4. Display order menu\n";
    cout << "\t\t\t\t\t\t\t5. Sort order menu (by price/serial number)\n";
    cout << "\t\t\t\t\t\t\t6. Update item in the order menu\n";
    cout << "\t\t\t\t\t\t\t7. Search menu item by serial number\n";
    cout << "\t\t\t\t\t\t\t8. Process next customer order\n\n";
    cout << "\t\t\t\t\t\t\t0. Back To Main Menu \n\n";
    cout << "\t\t\t\t\t\t\tEnter Your Choice --->";
}

void AdminList::addMenuItem(int data, const string& foodName, float price) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->getData() == data) {
            cout << "\n\t\t\t\t\t\tFood item with given serial number already exists!!\n\n";
            return;
        }
        temp = temp->getNext();
    }
    Node* newNode = new Node(data, foodName, price, 0);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->setNext(newNode);
        tail = newNode;
    }
    cout << "\n\t\t\t\t\t\tNew food item added to the list!!\n\n";
}
//Deletes a food item from the admin menu by its serial number
bool AdminList::deleteAdminItem() {
    cout << "\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ";
    int num;
    cin >> num;

    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->getData() == num) {
            if (current == head) {
                head = current->getNext();
            }
            else {
                prev->setNext(current->getNext());
            }
            if (current == tail) {
                tail = prev;
            }
            delete current;
            cout << "\n\t\t\t\t\t\t### Updated list of food items menu ###\n";
            displayAdminMenu();
            return true;
        }
        prev = current;
        current = current->getNext();
    }
    cout << "\n\t\t\t\t\t\tFood item with given serial number doesn't exist!\n\n";
    return false;
}

//  Displays the current food menu for administrators.
void AdminList::displayAdminMenu() {
    Node* temp1 = head;
    if (temp1 == nullptr) {
        cout << "\n\t\t\t\t\t\t\t\tMenu is empty!!\n\n";
    }
    else {
        cout << "\n";
        size_t maxFoodNameLen = 0;
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->getFoodName().length() > maxFoodNameLen) {
                maxFoodNameLen = temp->getFoodName().length();
            }
            temp = temp->getNext();
        }
        
        maxFoodNameLen = max(maxFoodNameLen, string("Name").length());
        if (maxFoodNameLen < 8) maxFoodNameLen = 8;

        
        const int serialWidth = 10;
        const int priceWidth = 10; 

        
        cout << "\t\t\t\t\t\t\t";
        cout << left << setw(serialWidth) << "Serial No";
        cout << left << setw(static_cast<int>(maxFoodNameLen + 4)) << "Name";
        cout << left << setw(priceWidth) << "Price";
        cout << "\n";
        cout << "\t\t\t\t\t\t\t";
        cout << setfill('-') << setw(serialWidth) << "-";
        cout << setfill('-') << setw(static_cast<int>(maxFoodNameLen + 4)) << "-";
        cout << setfill('-') << setw(priceWidth) << "-";
        cout << setfill(' ') << "\n"; 
  
        while (temp1 != nullptr) {
            cout << "\t\t\t\t\t\t\t" << left << setw(serialWidth) << temp1->getData();
            cout << left << setw(static_cast<int>(maxFoodNameLen + 4)) << temp1->getFoodName();
            cout << fixed << setprecision(2) << right << setw(priceWidth) << temp1->getPrice() << "\n";
            temp1 = temp1->getNext();
        }
        cout << "\n";
    }
}
//Displays aggregated sales data (total quantity and price for each sold item).
void AdminList::viewTotalSales(Node* salesHead) { //salesHead as argument
    Node* temp1 = salesHead;
    if (temp1 == nullptr) {
        cout << "\n\t\t\t\t\t\t\t\tNo sales yet!!\n\n";
    }
    else {
        cout << "\n\t\t\t\t\t\t\t--- Total Sales ---\n";
        size_t maxFoodNameLen = 0;
        Node* temp = salesHead;
        while (temp != nullptr) {
            if (temp->getFoodName().length() > maxFoodNameLen) {
                maxFoodNameLen = temp->getFoodName().length();
            }
            temp = temp->getNext();
        }
        if (maxFoodNameLen < 8) maxFoodNameLen = 8; 

        
        const int serialWidth = 10;
        const int quantityWidth = 10;
        const int priceWidth = 10;

     
        cout << "\t\t\t\t\t\t\t";
        cout << left << setw(serialWidth) << "Serial No";
        cout << left << setw(static_cast<int>(maxFoodNameLen + 4)) << "Name";
        cout << left << setw(quantityWidth) << "Quantity";
        cout << left << setw(priceWidth) << "Total Price";
        cout << "\n";

        
        cout << "\t\t\t\t\t\t\t";
        cout << setfill('-') << setw(serialWidth) << "-";
        cout << setfill('-') << setw(static_cast<int>(maxFoodNameLen + 4)) << "-";
        cout << setfill('-') << setw(quantityWidth) << "-";
        cout << setfill('-') << setw(priceWidth) << "-";
        cout << setfill(' ') << "\n"; 


        while (temp1 != nullptr) {
            cout << "\t\t\t\t\t\t\t" << left << setw(serialWidth) << temp1->getData();
            cout << left << setw(static_cast<int>(maxFoodNameLen + 4)) << temp1->getFoodName();
            cout << left << setw(quantityWidth) << temp1->getQuantity();
            cout << fixed << setprecision(2) << right << setw(priceWidth) << temp1->getPrice() << "\n";
            temp1 = temp1->getNext();
        }
        cout << "\n";
    }
}
//Sorts the admin menu either by price or by serial number.
void AdminList::sortMenu(const string& sortBy) {
    if (head == nullptr || head->getNext() == nullptr) {
        cout << "\n\t\t\t\t\t\t\tMenu is empty or has only one item. Nothing to sort.\n";
        return;
    }

    Node* current;
    Node* index;
    int temp_data;
    string temp_foodName;
    float temp_price;

    for (current = head; current->getNext() != nullptr; current = current->getNext()) {
        for (index = current->getNext(); index != nullptr; index = index->getNext()) {
            bool swapNeeded = false;
            if (sortBy == "price") {
                if (current->getPrice() > index->getPrice()) {
                    swapNeeded = true;
                }
            }
            else if (sortBy == "serial") {
                if (current->getData() > index->getData()) {
                    swapNeeded = true;
                }
            }
            else {
                cout << "\n\t\t\t\t\t\t\tInvalid sort option.\n";
                return;
            }

            if (swapNeeded) {
                temp_data = current->getData();
                temp_foodName = current->getFoodName();
                temp_price = current->getPrice();

                current->setData(index->getData());
                current->setFoodName(index->getFoodName());
                current->setPrice(index->getPrice());

                index->setData(temp_data);
                index->setFoodName(temp_foodName);
                index->setPrice(temp_price);
            }
        }
    }

    if (sortBy == "price") {
        cout << "\n\t\t\t\t\t\t\tMenu sorted by price (ascending).\n";
    }
    else if (sortBy == "serial") {
        cout << "\n\t\t\t\t\t\t\tMenu sorted by serial number (ascending).\n";
    }
    cout << "\n\t\t\t\t\t\t\tDisplaying sorted menu:\n";
    displayAdminMenu();
}
//Allows modifying details (price, name, or serial number) of an existing menu item.
void AdminList::updateMenuItem() {
    if (head == nullptr) {
        cout << "\n\t\t\t\t\t\t\tMenu is empty. Nothing to update.\n";
        return;
    }

    cout << "\n\t\t\t\t\t\t\t### Current Order Menu ###\n";
    displayAdminMenu();

    cout << "\n\t\t\t\t\t\tEnter serial number of the item to update: ";
    int serialToUpdate;
    cin >> serialToUpdate;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Node* itemToUpdate = nullptr;
    Node* current = head;
    while (current != nullptr) {
        if (current->getData() == serialToUpdate) {
            itemToUpdate = current;
            break;
        }
        current = current->getNext();
    }

    if (itemToUpdate == nullptr) {
        cout << "\n\t\t\t\t\t\t\tItem with serial number " << serialToUpdate << " not found.\n";
        return;
    }

    cout << "\n\t\t\t\t\t\t\tItem found: " << itemToUpdate->getFoodName() << " (Serial: " << itemToUpdate->getData() << ", Price: $" << fixed << setprecision(2) << itemToUpdate->getPrice() << ")\n";
    cout << "\n\t\t\t\t\t\t\tWhat do you want to update?\n";
    cout << "\t\t\t\t\t\t\t1. Price\n";
    cout << "\t\t\t\t\t\t\t2. Name\n";
    cout << "\t\t\t\t\t\t\t3. Serial Number\n";
    cout << "\t\t\t\t\t\t\tEnter your choice (1-3) --->";
    int updateChoice;
    cin >> updateChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (updateChoice) {
    case 1: {
        float newPrice;
        cout << "\t\t\t\t\t\t\tEnter new price: $";
        cin >> newPrice;
        itemToUpdate->setPrice(newPrice);
        cout << "\n\t\t\t\t\t\t\tPrice updated successfully!\n";
        break;
    }
    case 2: {
        string newName;
        cout << "\t\t\t\t\t\t\tEnter new name: ";
        getline(cin, newName);
        itemToUpdate->setFoodName(newName);
        cout << "\n\t\t\t\t\t\t\tName updated successfully!\n";
        break;
    }
    case 3: {
        int newSerial;
        cout << "\t\t\t\t\t\t\tEnter new serial number: ";
        cin >> newSerial;

        Node* checkNode = head;
        bool serialExists = false;
        while (checkNode != nullptr) {
            if (checkNode->getData() == newSerial && checkNode != itemToUpdate) {
                serialExists = true;
                break;
            }
            checkNode = checkNode->getNext();
        }

        if (serialExists) {
            cout << "\n\t\t\t\t\t\t\tError: Serial number " << newSerial << " already exists. Update failed.\n";
        }
        else {
            itemToUpdate->setData(newSerial);
            cout << "\n\t\t\t\t\t\t\tSerial number updated successfully!\n";
        }
        break;
    }
    default:
        cout << "\n\t\t\t\t\t\t\tInvalid update choice.\n";
        break;
    }
    cout << "\n\t\t\t\t\t\t\t### Updated Order Menu ###\n";
    displayAdminMenu();
}
//Searches for a menu item by its serial number and displays its details.
void AdminList::searchMenuItemBySerial() {
    if (head == nullptr) {
        cout << "\n\t\t\t\t\t\t\tMenu is empty. Nothing to search.\n";
        return;
    }

    cout << "\n\t\t\t\t\t\t\t### Current Order Menu ###\n";
    displayAdminMenu();

    cout << "\n\t\t\t\t\t\tEnter serial number of the item to search: ";
    int serialToSearch;
    cin >> serialToSearch;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Node* current = head;
    bool found = false;
    while (current != nullptr) {
        if (current->getData() == serialToSearch) {
            cout << "\n\t\t\t\t\t\t\t--- Item Found ---\n";
            cout << "\t\t\t\t\t\t\tSerial Number: " << current->getData() << "\n";
            cout << "\t\t\t\t\t\t\tFood Name:       " << current->getFoodName() << "\n";
            cout << "\t\t\t\t\t\t\tPrice:           $" << fixed << setprecision(2) << current->getPrice() << "\n\n";
            found = true;
            break;
        }
        current = current->getNext();
    }

    if (!found) {
        cout << "\n\t\t\t\t\t\t\tItem with serial number " << serialToSearch << " not found.\n";
    }
}
// Processes the next pending customer order from the OrderQueue.
void AdminList::processNextOrder() {
    if (orderQueueRef.isEmpty()) {
        cout << "\n\t\t\t\t\t\tNo orders in the queue to process.\n";
        return;
    }

    cout << "\n\t\t\t\t\t\t--- Processing Next Order ---\n";
    QueueItem processedOrder = orderQueueRef.dequeue(); //dequeue

    cout << "\t\t\t\t\t\tOrder #" << processedOrder.orderId << " processed.\n";
    cout << "\t\t\t\t\t\tDetails: " << processedOrder.orderDetailsSummary << "\n";
    cout << "\t\t\t\t\t\tTotal Amount: $" << fixed << setprecision(2) << processedOrder.totalAmount << "\n\n";
    cout << "\t\t\t\t\t\tOrder has been moved from the active queue.\n";
}


// CustomerList Implementations 

CustomerList::CustomerList(AdminList& adminList, OrderQueue& queue)
    : head(nullptr), tail(nullptr), salesHead(nullptr), adminMenuRef(adminList), orderQueueRef(queue) {
}

CustomerList::~CustomerList() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->getNext();
        delete current;
        current = nextNode;
    }
    head = nullptr;
    tail = nullptr;

    current = salesHead;
    while (current != nullptr) {
        Node* nextNode = current->getNext();
        delete current;
        current = nextNode;
    }
    salesHead = nullptr;
}
//Displays the customer's main menu options.
void CustomerList::customerMenu() {
    cout << "\n\t\t\t\t\t\t\t1. Place your order\n";
    cout << "\t\t\t\t\t\t\t2. View your ordered items\n";
    cout << "\t\t\t\t\t\t\t3. Delete an item from order\n";
    cout << "\t\t\t\t\t\t\t4. Display final bill\n";
    cout << "\t\t\t\t\t\t\t5. Back To Main Menu \n\n";
    cout << "\t\t\t\t\t\t\tEnter Your Choice --->";
}
//Adds a selected food item to the customer's current order.
void CustomerList::placeOrder(int itemData, int quantity) {
    Node* tempAdmin = adminMenuRef.getHead();
    bool found = false;

    while (tempAdmin != nullptr) {
        if (tempAdmin->getData() == itemData) {
            found = true;
            break;
        }
        tempAdmin = tempAdmin->getNext();
    }

    if (found) {
        Node* newNode = new Node(itemData, tempAdmin->getFoodName(), quantity * tempAdmin->getPrice(), quantity);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->setNext(newNode);
            tail = newNode;
        }
        cout << "\n\t\t\t\t\t\tItem added to your order!\n";
    }
    else {
        cout << "\n\t\t\t\t\t\t\tThis item is not present in the menu!\n";
    }
}
//Removes an item from the customer's current order list.
bool CustomerList::deleteCustomerItem() {
    cout << "\n\t\t\t\t\t\t### Your Current Ordered Items ###\n";
    viewOrderedItems();

    cout << "\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ";
    int num;
    cin >> num;

    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->getData() == num) {
            if (current == head) {
                head = current->getNext();
            }
            else {
                prev->setNext(current->getNext());
            }
            if (current == tail) {
                tail = prev;
            }
            delete current;
            cout << "\n\t\t\t\t\t\t### Updated list of your ordered food items ###\n";
            viewOrderedItems();
            return true;
        }
        prev = current;
        current = current->getNext();
    }
    cout << "\n\t\t\t\t\t\tFood item with given serial number doesn't exist!!\n";
    return false;
}
//Displays the items currently in the customer's order.
void CustomerList::viewOrderedItems() {
    displayList(head);
}
//Calculates and displays the total bill for the customer's current order, then enqueues the order.
void CustomerList::displayFinalBill() {
    displayList(head);
    float total_price = 0;
    Node* temp = head;

    string orderDetailsSummary = "Items: "; 
    bool firstItem = true;

    while (temp != nullptr) {
        total_price += temp->getPrice();
        if (!firstItem) {
            orderDetailsSummary += ", ";
        }
        orderDetailsSummary += temp->getFoodName();
        orderDetailsSummary += " (x";
        orderDetailsSummary += to_string(temp->getQuantity()); 
        orderDetailsSummary += ")";
        firstItem = false;
        temp = temp->getNext();
    }
    cout << "\t\t\t\t\t\t\tTotal price: $" << fixed << setprecision(2) << total_price << "\n";

    if (total_price > 0) {
        int orderId = orderQueueRef.getNextOrderIdAndIncrement();
        QueueItem newOrder(orderId, total_price, orderDetailsSummary);
        orderQueueRef.enqueue(newOrder);
    }
}
//Aggregates sales data from the current customer's order into the salesHead linked list.
void CustomerList::calculateTotalSales() {
    Node* temp = head;
    while (temp != nullptr) {
        salesHead = addSalesNode(temp->getData(), temp->getQuantity(), temp->getFoodName(), temp->getPrice());
        temp = temp->getNext();
    }
}
//A helper function to add or update sales records in the salesHead list.
Node* CustomerList::addSalesNode(int data, int quantity, const string& foodName, float price) {
    Node* tempSales = salesHead;
    bool found = false;
    while (tempSales != nullptr) {
        if (tempSales->getData() == data) {
            tempSales->setQuantity(tempSales->getQuantity() + quantity);
            tempSales->setPrice(tempSales->getPrice() + price);
            found = true;
            break;
        }
        tempSales = tempSales->getNext();
    }

    if (!found) {
        Node* newNode = new Node(data, foodName, price, quantity);
        if (salesHead == nullptr) {
            salesHead = newNode;
        }
        else {
            tempSales = salesHead;
            while (tempSales->getNext() != nullptr) {
                tempSales = tempSales->getNext();
            }
            tempSales->setNext(newNode);
        }
    }
    return salesHead;
}
// Clears the customer's temporary order list after an order is finalized.
void CustomerList::deleteCustomerOrderList() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->getNext();
        delete current;
        current = nextNode;
    }
    head = nullptr;
    tail = nullptr;
}

//display function used by both viewOrderedItems and displayFinalBill to present linked list data (customer orders).
void CustomerList::displayList(Node* currentHead) {
    Node* temp1 = currentHead;
    if (temp1 == nullptr) {
        cout << "\n\t\t\t\t\t\t\t\tList is empty!!\n\n";
    }
    else {
        cout << "\n";
        size_t maxFoodNameLen = 0;
        Node* temp = currentHead;
        while (temp != nullptr) {
            if (temp->getFoodName().length() > maxFoodNameLen) {
                maxFoodNameLen = temp->getFoodName().length();
            }
            temp = temp->getNext();
        }
        // Ensure minimum width and account for headers
        maxFoodNameLen = max(maxFoodNameLen, string("Name").length());
        if (maxFoodNameLen < 8) maxFoodNameLen = 8;


        // Define fixed widths for headers
        const int serialWidth = 10;
        const int quantityWidth = 10; // For quantity column
        const int priceWidth = 10;    // For price column

        // Print header row
        cout << "\t\t\t\t\t\t\t";
        cout << left << setw(serialWidth) << "Serial No";
        cout << left << setw(static_cast<int>(maxFoodNameLen + 4)) << "Name";

        // Conditionally print Quantity header if it's a customer order list (not admin menu)
        if (currentHead != nullptr && currentHead->getQuantity() != 0) {
            cout << left << setw(quantityWidth) << "Quantity";
        }

        cout << left << setw(priceWidth) << "Price";
        cout << "\n";

        // Print separator line
        cout << "\t\t\t\t\t\t\t";
        cout << setfill('-') << setw(serialWidth) << "-";
        cout << setfill('-') << setw(static_cast<int>(maxFoodNameLen + 4)) << "-";
        if (currentHead != nullptr && currentHead->getQuantity() != 0) {
            cout << setfill('-') << setw(quantityWidth) << "-";
        }
        cout << setfill('-') << setw(priceWidth) << "-";
        cout << setfill(' ') << "\n"; // Reset fill character


        while (temp1 != nullptr) {
            if (temp1->getQuantity() == 0) { // For admin menu display (no quantity column)
                cout << "\t\t\t\t\t\t\t" << left << setw(serialWidth) << temp1->getData();
                cout << left << setw(static_cast<int>(maxFoodNameLen + 4)) << temp1->getFoodName();
                cout << fixed << setprecision(2) << right << setw(priceWidth) << temp1->getPrice() << "\n";
            }
            else { // For customer order display (with quantity column)
                cout << "\t\t\t\t\t\t\t" << left << setw(serialWidth) << temp1->getData();
                cout << left << setw(static_cast<int>(maxFoodNameLen + 4)) << temp1->getFoodName();
                cout << left << setw(quantityWidth) << temp1->getQuantity();
                cout << fixed << setprecision(2) << right << setw(priceWidth) << temp1->getPrice() << "\n";
            }
            temp1 = temp1->getNext();
        }
        cout << "\n";
    }
}

// Main Menu that control the flow of the application
// Displays the initial main menu of the Food Ordering System.
void mainMenu() {
    cout << "\n\t\t\t\t\t\t\t########################################\n";
    cout << "\t\t\t\t\t\t\t#       FOOD ORDERING SYSTEM           #\n";
    cout << "\t\t\t\t\t\t\t########################################\n";
    cout << "\n\t\t\t\t\t\t\t1. Admin Section\n";
    cout << "\t\t\t\t\t\t\t2. Customer Section\n";
    cout << "\t\t\t\t\t\t\t3. Exit\n\n";
    cout << "\t\t\t\t\t\t\tEnter Your Choice --->";
}
//Manages the interactions within the Admin section.
void adminSection(AdminList& adminList, CustomerList& customerList, OrderQueue& orderQueue) {
    cout << "\n\t\t\t\t\t\t\t-----\n";
    cout << "\t\t\t\t\t\t\tADMIN SECTION\n";
    cout << "\t\t\t\t\t\t\t-----\n";

    while (true) {
        adminList.adminMenu();
        int opt;
        cin >> opt;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opt == 0) {
            break;
        }

        switch (opt) {
        case 1:
            adminList.viewTotalSales(customerList.getSalesHead());
            break;
        case 2: {
            cout << "\n\t\t\t\t\t\t\t### Current Order Menu ###\n";
            adminList.displayAdminMenu();

            int num;
            string name;
            float price;
            cout << "\n\t\t\t\t\t\t\tEnter serial no. of the food item: ";
            cin >> num;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\t\t\t\t\t\tEnter food item name: ";
            getline(cin, name);
            cout << "\t\t\t\t\t\t\tEnter price: ";
            cin >> price;
            adminList.addMenuItem(num, name, price);
            break;
        }
        case 3:
            adminList.deleteAdminItem();
            break;
        case 4:
            cout << "\n\t\t\t\t\t\t\t### Order menu ###\n";
            adminList.displayAdminMenu();
            break;
        case 5: {
            cout << "\n\t\t\t\t\t\t\tSort by:\n";
            cout << "\t\t\t\t\t\t\t1. Price (ascending)\n";
            cout << "\t\t\t\t\t\t\t2. Serial Number (ascending)\n";
            cout << "\t\t\t\t\t\t\tEnter your choice (1 or 2) --->";
            int sortChoice;
            cin >> sortChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (sortChoice == 1) {
                adminList.sortMenu("price");
            }
            else if (sortChoice == 2) {
                adminList.sortMenu("serial");
            }
            else {
                cout << "\n\t\t\t\t\t\t\tInvalid sort choice. Please try again.\n";
            }
            break;
        }
        case 6: {
            adminList.updateMenuItem();
            break;
        }
        case 7: {
            adminList.searchMenuItemBySerial();
            break;
        }
        case 8: {
            adminList.processNextOrder();
            break;
        }
        default:
            cout << "\n\t\t\t\t\t\tWrong Input !! Please choose a valid option\n";
            break;
        }
    }
}
// Manages the interactions within the Customer section.
void customerSection(AdminList& adminList, CustomerList& customerList, OrderQueue& orderQueue) {
    cout << "\n\t\t\t\t\t\t\t-----\n";
    cout << "\t\t\t\t\t\t\tCUSTOMER SECTION\n";
    cout << "\t\t\t\t\t\t\t-----\n";

    while (true) {
        customerList.customerMenu();
        int opt;
        cin >> opt;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opt == 5) {
            break;
        }

        switch (opt) {
        case 1: {
            char addMore;
            do {
                adminList.displayAdminMenu(); // Display menu before each order
                cout << "\n\t\t\t\t\t\tEnter number corresponding to the item you want to order: ";
                int n;
                // Input validation for item number
                while (!(cin >> n)) {
                    cout << "\t\t\t\t\t\tInvalid input. Please enter a number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cout << "\t\t\t\t\t\tEnter quantity: ";
                int quantity;
                // Input validation for quantity
                while (!(cin >> quantity) || quantity <= 0) {
                    cout << "\t\t\t\t\t\tInvalid quantity. Please enter a positive number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer after quantity input

                customerList.placeOrder(n, quantity);

                cout << "\n\t\t\t\t\t\tDo you want to add more items? (y/n): ";
                cin >> addMore;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer after char input
            } while (addMore == 'y' || addMore == 'Y');
            break;
        }
        case 2:
            cout << "\n\t\t\t\t\t\t\t### List of ordered items ###\n";
            customerList.viewOrderedItems();
            break;
        case 3:
            cout << "\n\t\t\t\t\t\t\t### Your Current Order ###\n";
            customerList.viewOrderedItems();
            customerList.deleteCustomerItem();
            break;
        case 4: {
            customerList.calculateTotalSales();
            cout << "\n\t\t\t\t\t\t\t### Final Bill ###\n";
            customerList.displayFinalBill();
            customerList.deleteCustomerOrderList();
            cout << "\n\t\t\t\t\t\tPress any key to return to main menu:\n\t\t\t\t\t\t";
            string dummy;
            getline(cin, dummy);
            break;
        }
        default:
            cout << "\n\t\t\t\t\t\tWrong Input !! Please choose a valid option\n";
            break;
        }
    }
}