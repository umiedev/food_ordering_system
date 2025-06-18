
#ifndef FOOD_ORDERING_SYSTEM_H
#define FOOD_ORDERING_SYSTEM_H

#include <iostream>
#include <string>
#include <iomanip>
#include <utility> 

using namespace std; 


class AdminList;
class CustomerList;
class OrderQueue; 

// Node structure for the linked list
class Node {
private:
    string foodName;
    int quantity;
    float price;
    int data; 
    Node* next; //A pointer to the next Node in the linked list

public:
  
    Node(int data, string foodName, float price, int quantity = 0);

    int getData() const { return data; }
    string getFoodName() const { return foodName; }
    float getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    Node* getNext() const { return next; }
    void setQuantity(int qty) { quantity = qty; }
    void setPrice(float p) { price = p; }
    void setNext(Node* n) { next = n; }
    void setFoodName(const string& newName) { foodName = newName; }
    void setData(int newData) { data = newData; } 
};

struct MenuItemData {
    int serialNumber;
    string name;
    float price;
    MenuItemData() : serialNumber(0), name(""), price(0.0f) {}
    MenuItemData(int sn, const string& n, float p) : serialNumber(sn), name(n), price(p) {}
};

//  to hold a customer's entire order 
struct QueueItem {
    int orderId;
    float totalAmount;
    string orderDetailsSummary; 

    QueueItem() : orderId(0), totalAmount(0.0f), orderDetailsSummary("") {}
    QueueItem(int id, float amount, string details)
        : orderId(id), totalAmount(amount), orderDetailsSummary(std::move(details)) {
    }
};

class QueueNode {
public:
    QueueItem data;
    QueueNode* next;

    QueueNode(QueueItem item) : data(std::move(item)), next(nullptr) {}
};

class OrderQueue {
private:
    QueueNode* front;
    QueueNode* rear;
    int nextOrderId;

public:
    OrderQueue();
    ~OrderQueue();

    void enqueue(QueueItem item);
    QueueItem dequeue();
    bool isEmpty() const;
    void displayQueue() const;
    int getNextOrderIdAndIncrement();
};


class AdminList {
private:
    Node* head;
    Node* tail;
    OrderQueue& orderQueueRef; 

public:
    AdminList(OrderQueue& queue); 
    ~AdminList();

    void adminMenu();
    void addMenuItem(int data, const string& foodName, float price);
    bool deleteAdminItem();
    void displayAdminMenu(); 
    void viewTotalSales(Node* salesHead);

    void sortMenu(const string& sortBy);
    void clear();

    void updateMenuItem();
    void searchMenuItemBySerial();

    void processNextOrder();

    Node* getHead() const { return head; }
    Node* getTail() const { return tail; }
};


class CustomerList {
private:
    Node* head;
    Node* tail;
    Node* salesHead; //for total sales list
    AdminList& adminMenuRef; // admin's menu for item lookup
    OrderQueue& orderQueueRef; //order queue

    Node* addSalesNode(int data, int quantity, const string& foodName, float price);

public:
    //AdminList AND OrderQueue reference
    CustomerList(AdminList& adminList, OrderQueue& queue);
    ~CustomerList();

    void customerMenu();
    void placeOrder(int itemData, int quantity);
    bool deleteCustomerItem();
    void viewOrderedItems();
    void displayFinalBill(); //enqueue the order
    void calculateTotalSales();
    void deleteCustomerOrderList();
    void displayList(Node* currentHead); 

    Node* getSalesHead() const { return salesHead; }
};

void mainMenu();
void adminSection(AdminList& adminList, CustomerList& customerList, OrderQueue& orderQueue);
void customerSection(AdminList& adminList, CustomerList& customerList, OrderQueue& orderQueue);

#endif