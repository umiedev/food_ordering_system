

---

# Food Ordering System

A console-based Food Ordering System developed in C++ that allows both administrators to manage menu items and view sales, and customers to place, view, and manage their orders. The system utilizes fundamental data structures like linked lists and queues to handle menu items, customer orders, and order processing.

## Features

This system provides a comprehensive set of functionalities for managing a food ordering process:

### Administrator Features
* **View Total Sales:** Displays aggregated sales data, including total quantity and price for each sold item.
* **Manage Menu Items:**
    * Add new food items to the menu with unique serial numbers, names, and prices.
    * Delete existing food items by their serial number.
    * Update details (price, name, or serial number) of existing menu items.
* **Display Menu:** Shows the current food menu for administrators.
* **Sort Menu:** Allows sorting the menu by price or serial number in ascending order.
* **Search Menu Item:** Search for a specific menu item by its serial number and display its details.
* **Process Customer Orders:** Manages a queue of customer orders, processing them in a First-In, First-Out (FIFO) manner.

### Customer Features
* **Place Order:** Add selected food items and quantities to a personal order list.
* **View Ordered Items:** Display all items currently in the customer's order.
* **Delete Item from Order:** Remove specific items from the current order list.
* **Display Final Bill:** Calculates and presents the total bill for the customer's order, then adds it to the processing queue for the admin.

## Technologies Used
* **Language:** C++
* **Data Structures:**
    * **Linked Lists:** Used for managing menu items (AdminList), customer's current order (CustomerList), and aggregated sales records. The `Node` class forms the basic building block of these lists.
    * **Queues:** Implemented using a linked list (`OrderQueue`) to manage pending customer orders in a FIFO manner, ensuring orders are processed in the sequence they are placed.
* **Search Algorithm:** Linear search is employed for operations like searching, deleting, adding, and updating menu items.

## How to Compile and Run
To compile and run this program, you will need a C++ compiler (like g++).

1.  **Save the files:** Save `main.cpp`, `food_ordering_system.cpp`, and `food_ordering_system.h` in the same directory.
2.  **Compile:** Open your terminal or command prompt, navigate to the directory where you saved the files, and compile using the following command:
    ```bash
    g++ main.cpp food_ordering_system.cpp -o food_ordering_system
    ```
3.  **Run:** Execute the compiled program:
    ```bash
    ./food_ordering_system
    ```

## Project Structure
* `main.cpp`: Contains the `main` function, the entry point of the program. It initializes the `OrderQueue`, `AdminList`, and `CustomerList` objects and manages the main application loop, directing users to admin or customer sections.
* `food_ordering_system.h`: Header file containing class definitions (`Node`, `MenuItemData`, `QueueItem`, `QueueNode`, `OrderQueue`, `AdminList`, `CustomerList`) and function prototypes for the system's core logic.
* `food_ordering_system.cpp`: Source file containing the full implementations of the classes and functions declared in `food_ordering_system.h`, including all menu management, order processing, and display logic.

## Usage
Upon running the program, you will be presented with a main menu to choose between "Admin Section" and "Customer Section". Follow the on-screen prompts to interact with the system.

## Future Enhancements (Possible Ideas)
* **File I/O:** Implement saving and loading menu items and sales data to/from a file to persist data between program executions.
* **Graphical User Interface (GUI):** Develop a GUI version using libraries like Qt or SFML for a more intuitive user experience.
* **Error Handling:** Add more robust input validation and error handling.
* **More Sorting Options:** Implement sorting by food name.
* **Search Optimization:** For large menus, consider implementing more efficient search algorithms (e.g., binary search if data is sorted, or using hash tables).

---
