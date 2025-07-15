#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>
#include <limits>

using namespace std;

void cls() {
    system("cls");
}

void centerText(const string& text) {
    const int consoleWidth = 150; 
    int spaces = (consoleWidth - text.length()) / 2;
    for (int i = 0; i < spaces; i++) cout << " ";
    cout << text << endl;
}

struct Furniture {
    int id;
    string name;
    string category;
    double price;
    int quantity;
};

struct OrderItem {
    int furnitureId;
    string furnitureName;
    string category;
    int quantity;
    double price;
};

struct Order {
    int orderId;
    OrderItem items[100]; 
    int itemCount;
    double totalAmount;
};

Furniture inventory[100] = {  
    // Bedroom Category
    {1, "Amber Wardrobe", "Bedroom",  215000, 20},
    {2, "Ornate Bed", "Bedroom", 70775, 10},
    {3, "Dressing Table", "Bedroom", 21500, 12},
    {4, "Regent Dressing Table", "Bedroom", 25975, 15},
    {5, "Ardly Bed", "Bedroom", 65000, 20},
    
    // Dining Category
    {6, "Wooden Dining Tables", "Dining", 30000, 15},
    {7, "MELODY Dining Table", "Dining", 33234, 10},
    {8, "NOVA New Dining Table", "Dining", 58649, 8},
    {9, "Caplin Dining Chair", "Dining", 13875, 7},
    {10, "Round Dining Table", "Dining", 25000, 25},
    
    // Office Furniture Category
    {11, "Fabric Typist Chair", "Office", 15929, 10},
    {12, "Iron Leg Table", "Office", 25469, 18},
    {13, "L-Shape Table ", "Office", 50749, 15},
    {14, "Nero Table", "Office", 22500, 12},
    {15, "Walnut Executive Desk", "Office", 113975, 14},
    
    // Sofa Category
    {16, "Rily Sofa", "Sofa", 92000, 8},
    {17, "Louie Sofa", "Sofa", 227500, 10},
    {18, "Tiana Sofa", "Sofa", 92000, 6},
    {19, "Leyard Sofa", "Sofa", 87500, 12},
    {20, "Vivian Sofa", "Sofa", 90000, 7}
};

int INVENTORY_SIZE = 20; 
const int MAX_INVENTORY = 100;  
Order currentOrder;
int nextOrderId = 1001;
string username;
bool isAdmin = false;  

void LoadingScreen() {
    cls();
    cout << "\n\n\n\n\n\n\n\n\n";
    centerText("       *************************************************     ");
    centerText("      *                                                 *    ");
    centerText("     *                FURNITURE VILLAGE                  *   ");
    centerText("    *                                                     *  ");
    centerText("   *           ---------------------------------           * ");
    centerText("    *                                                     *  ");
    centerText("     *   Bringing Comfort & Style to Your Small Space    *   ");
    centerText("      *                                                *     ");
    centerText("       ************************************************      ");
    cout << endl;
    
    centerText("Loading Your Space...");


    time_t start = time(0); 
    while (time(0) - start < 5) {  
    }

    cls();  
}

void displayMenu();
void displayAdminMenu();  
void addFurniture();  
void addNewFurniture();  
void listFurniture();
void searchFurniture();
void placeOrder();
void displayHelp();

int main() {
    LoadingScreen();
    
    cout << "\n\n\n";
    centerText("===================================================");
    centerText("WELCOME TO FURNITURE VILLAGE SYSTEM");
    centerText("===================================================");
    cout << endl;

    bool loginSuccess = false;
    while (!loginSuccess) {
        centerText("Please Enter your credentials to Login");
        centerText("Login with your Admin or Customer account\n");
        string inputUsername, password;
        cout << "  Username: ";
        getline(cin, inputUsername);
        cout << "  Password: ";
        getline(cin, password);


        if (inputUsername == "shanuka" && password == "shanuka123") {
            username = inputUsername;
            isAdmin = false;  // Regular user
            loginSuccess = true;
        }
        else if (inputUsername == "admin" && password == "admin123") {
            username = inputUsername;
            isAdmin = true;  // Admin user
            loginSuccess = true;
        }
        else {
            cout << "  Invalid username or password. Please try again.\n\n";
        }
    }

    cout << "\n  Login successful!";
    if (isAdmin) {
        cout << " (Admin Mode)";
    }
    cout << "\n";
    cout << "  Press Enter to continue...";
    cin.get();
    cls();

    int choice;
    do {
        if (isAdmin) {
            displayAdminMenu();  
        } else {
            displayMenu(); 
        }
        
        cout << "  Enter your choice: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Invalid input. Please enter a number.\n";
            cout << "  Press Enter to return to Menu...";
            cin.get();
            cls();
            continue;
        }
        cin.ignore();
        cls();

        if (isAdmin) {
            switch (choice) {
                case 1: listFurniture(); break;
                case 2: searchFurniture(); break;
                case 3: addNewFurniture(); break; 
                case 4: centerText("Exiting program. Thank you for using FURNITURE VILLAGE Admin System!"); break;
                default: cout << "  Invalid choice. Please enter a number from 1-4\n";
            }
            
            if (choice != 4) {
                cout << "\n  Press Enter to return to Menu...";
                cin.get();
                cls();
            }
        } else {
        	
            switch (choice) {
                case 1: addFurniture(); break;
                case 2: listFurniture(); break;
                case 3: searchFurniture(); break;
                case 4: placeOrder(); break;
                case 5: displayHelp(); break;
                case 6: centerText("Exiting program. Thank you for using FURNITURE VILLAGE Ordering System!"); break;
                default: cout << "  Invalid choice. Please enter a number from 1-6\n";
            }
            
            if (choice != 6) {
                cout << "\n  Press Enter to return to Menu...";
                cin.get();
                cls();
            }
        }
    } while ((isAdmin && choice != 4) || (!isAdmin && choice != 6));

    return 0;
}

void displayMenu() {
    cout << "\n\n\n";
    centerText("===================================================");
    centerText("FURNITURE VILLAGE Ordering System");
    centerText("===================================================\n");
    cout << " ------------- MAIN MENU --------------\n";
    cout << " |                                    |\n";
    cout << " |  1. Add Furniture                  |\n";
    cout << " |  2. List Of Available Furniture    |\n";
    cout << " |  3. Search Furniture               |\n";
    cout << " |  4. Place Order                    |\n";
    cout << " |  5. Help                           |\n";
    cout << " |  6. Exit                           |\n";
    cout << " |                                    |\n";
    cout << " --------------------------------------\n";
}


void displayAdminMenu() {
    cout << "\n\n\n";
    centerText("===================================================");
    centerText("FURNITURE VILLAGE Admin System");
    centerText("===================================================\n");
    cout << " ------------- ADMIN MENU -------------\n";
    cout << " |                                    |\n";
    cout << " |  1. List Of Available Furniture    |\n";
    cout << " |  2. Search Furniture               |\n";
    cout << " |  3. Add New Furniture              |\n";  
    cout << " |  4. Exit                           |\n";
    cout << " |                                    |\n";
    cout << " --------------------------------------\n";
}

void addNewFurniture() {
    cout << "\n\n\n";
    centerText("===================================================");
    centerText("ADD NEW FURNITURE (ADMIN ONLY)");
    centerText("===================================================");
    cout << endl;

    if (INVENTORY_SIZE >= MAX_INVENTORY) {
        cout << "  Error: Inventory is full. Cannot add more items.\n";
        return;
    }

    int newId;
    string newName, newCategory;
    double newPrice;
    int newQuantity;
    
    cout << "  Enter furniture details:\n";
    
    bool validId = false;
    while (!validId) {
        cout << "  ID: ";
        if (!(cin >> newId)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Error: Please enter a valid number.\n";
            continue;
        }
        cin.ignore();
        
        bool idExists = false;
        for (int i = 0; i < INVENTORY_SIZE; i++) {
            if (inventory[i].id == newId) {
                idExists = true;
                break;
            }
        }
        
        if (idExists) {
            cout << "  Error: ID already exists. Please enter a unique ID.\n";
        } else {
            validId = true;
        }
    }
    
    cout << "  Name: ";
    getline(cin, newName);
    
    cout << "  Category (Bedroom, Dining, Office, Sofa): ";
    getline(cin, newCategory);

    bool validPrice = false;
    while (!validPrice) {
        cout << "  Price: ";
        if (!(cin >> newPrice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Error: Please enter a valid price.\n";
            continue;
        }
        cin.ignore();
        
        if (newPrice <= 0) {
            cout << "  Error: Price must be greater than 0.\n";
        } else {
            validPrice = true;
        }
    }
    
    bool validQuantity = false;
    while (!validQuantity) {
        cout << "  Quantity: ";
        if (!(cin >> newQuantity)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Error: Please enter a valid quantity.\n";
            continue;
        }
        cin.ignore();
        
        if (newQuantity <= 0) {
            cout << "  Error: Quantity must be greater than 0.\n";
        } else {
            validQuantity = true;
        }
    }
    
    inventory[INVENTORY_SIZE].id = newId;
    inventory[INVENTORY_SIZE].name = newName;
    inventory[INVENTORY_SIZE].category = newCategory;
    inventory[INVENTORY_SIZE].price = newPrice;
    inventory[INVENTORY_SIZE].quantity = newQuantity;
    
    INVENTORY_SIZE++;
    
    cout << "\n  New furniture item added successfully!\n";

    cout << "\n  Added item details:\n";
    cout << "  " << left << setw(5) << "ID" 
              << setw(30) << "Name" 
              << setw(20) << "Category" 
              << setw(15) << "Price" 
              << setw(15) << "Quantity" << endl;
    cout << string(80, '-') << endl;
    
    cout << "  " << left << setw(5) << newId 
              << setw(30) << newName 
              << setw(20) << newCategory 
              << "Rs." << setw(14) << fixed << setprecision(2) << newPrice 
              << setw(15) << newQuantity << endl;
}

void addFurniture() {
    char addMore;
    do {
        cout << "\n\n\n";
        centerText("===================================================");
        centerText("ADD FURNITURE TO ORDER");
        centerText("===================================================");
        cout << endl;

        cout << "  " << left << setw(5) << "ID" 
                  << setw(30) << "Name" 
                  << setw(20) << "Category" 
                  << setw(15) << "Price" 
                  << setw(15) << "Quantity" << endl;
        cout << string(80, '-') << endl;

        for (int i = 0; i < INVENTORY_SIZE; i++) {
            cout << "  " << left << setw(5) << inventory[i].id 
                      << setw(30) << inventory[i].name 
                      << setw(20) << inventory[i].category 
                      << "Rs." << setw(14) << fixed << setprecision(2) << inventory[i].price 
                      << setw(15) << inventory[i].quantity << endl;
        }

        int furnitureId;
        bool validId = false;
        
        while (!validId) {
            cout << "\n  Enter furniture ID to add to your order: ";
            if (!(cin >> furnitureId)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "  Error: Please enter a valid number.\n";
                continue;
            }
            cin.ignore();
            
            bool idExists = false;
            for (int i = 0; i < INVENTORY_SIZE; i++) {
                if (inventory[i].id == furnitureId) {
                    idExists = true;
                    break;
                }
            }
            
            if (idExists) {
                validId = true;
            } else {
                cout << "  Error: Please enter a valid furniture ID.\n";
            }
        }

        Furniture* selectedFurniture = nullptr;
        for (int i = 0; i < INVENTORY_SIZE; i++) {
            if (inventory[i].id == furnitureId) {
                selectedFurniture = &inventory[i];
                break;
            }
        }

        if (!selectedFurniture) {
            cout << "  Error: Furniture with ID " << furnitureId << " not found.\n";
            continue;
        }

        int quantity;
        bool validQuantity = false;
        
        while (!validQuantity) {
            cout << "  Enter quantity: ";
            if (!(cin >> quantity)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "  Error: Please enter a valid number.\n";
                continue;
            }
            cin.ignore();
            
            if (quantity <= 0) {
                cout << "  Error: Quantity must be greater than 0.\n";
                continue;
            }

            if (quantity > selectedFurniture->quantity) {
                cout << "  Error: Requested quantity exceeds available stock. Maximum available: " 
                     << selectedFurniture->quantity << "\n";
                continue;
            }
            
            validQuantity = true;
        }

        OrderItem newItem;
        newItem.furnitureId = selectedFurniture->id;
        newItem.furnitureName = selectedFurniture->name;
        newItem.category = selectedFurniture->category;
        newItem.quantity = quantity;
        newItem.price = selectedFurniture->price;

        currentOrder.items[currentOrder.itemCount++] = newItem;
        cout << "  Item added to your order.\n";

        bool validInput = false;
        while (!validInput) {
            cout << "\n  Add more items? (Y/N): ";
            cin >> addMore;
            cin.ignore();
            
            addMore = toupper(addMore);
            if (addMore == 'Y' || addMore == 'N') {
                validInput = true;
            } else {
                cout << "  Error: Invalid input. Please enter Y for Yes or N for No.\n";
            }
        }
    } while (addMore == 'Y');
}

void listFurniture() {
    cout << "\n\n\n";
    centerText("===================================================");
    centerText("AVAILABLE FURNITURES");
    centerText("===================================================");
    cout << endl;

    cout << "  " << left << setw(5) << "ID" 
              << setw(30) << "Name" 
              << setw(20) << "Category" 
              << setw(15) << "Price" 
              << setw(15) << "Quantity" << endl;
    cout << string(80, '-') << endl;

    for (int i = 0; i < INVENTORY_SIZE; i++) {
        cout << "  " << left << setw(5) << inventory[i].id 
                  << setw(30) << inventory[i].name 
                  << setw(20) << inventory[i].category 
                  << "Rs." << setw(14) << fixed << setprecision(2) << inventory[i].price 
                  << setw(15) << inventory[i].quantity << endl;
    }
}

void searchFurniture() {
    cout << "\n\n\n";
    centerText("===================================================");
    centerText("SEARCH FURNITURE");
    centerText("===================================================");
    cout << endl;

    cout << "  Available categories: Bedroom, Dining, Office, Sofa\n\n";
    string searchCategory;
    cout << "  Enter category to search: ";
    getline(cin, searchCategory);
    

    cout << "\n";
    cout << "  " << left << setw(5) << "ID" 
              << setw(30) << "Name" 
              << setw(20) << "Category" 
              << setw(15) << "Price" 
              << setw(15) << "Quantity" << endl;
    cout << string(80, '-') << endl;

    bool found = false;  
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (inventory[i].category == searchCategory) {
            cout << "  " << left << setw(5) << inventory[i].id 
                      << setw(30) << inventory[i].name 
                      << setw(20) << inventory[i].category 
                      << "Rs." << setw(14) << fixed << setprecision(2) << inventory[i].price 
                      << setw(15) << inventory[i].quantity << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "  No matching furniture found.\n";
    }
}

void placeOrder() {
    cout << "\n\n\n";
    centerText("===================================================");
    centerText("PLACE ORDER");
    centerText("===================================================\n");

    if (currentOrder.itemCount == 0) {
        cout << "  Your order is empty. Please add furniture items first.\n";
        return;
    }

    currentOrder.totalAmount = 0.0;
    for (int i = 0; i < currentOrder.itemCount; i++) {
        const auto& item = currentOrder.items[i];
        currentOrder.totalAmount += (item.price * item.quantity);
    }
    
    currentOrder.orderId = nextOrderId++;
    
    for (int i = 0; i < currentOrder.itemCount; i++) {
        const auto& orderItem = currentOrder.items[i];
        for (int j = 0; j < INVENTORY_SIZE; j++) {
            if (inventory[j].id == orderItem.furnitureId) {
                inventory[j].quantity -= orderItem.quantity;
                break;
            }
        }
    }

    ofstream orderFile("order_bill_" + to_string(currentOrder.orderId) + ".txt");
    if (orderFile.is_open()) {
        orderFile << "                   |---------------------------------------- |\n";
        orderFile << "                   |       FURNITURE VILLAGE ORDER BILL      |\n";
        orderFile << "                   |-----------------------------------------|\n\n";
        orderFile << "  Order ID: " << currentOrder.orderId << "\n\n";
        orderFile << "  Items:\n";
        orderFile << "  " << left << setw(30) << "Name" 
                  << setw(20) << "Category"
                  << setw(10) << "Quantity" 
                  << setw(15) << "Price" 
                  << setw(15) << "Subtotal" << endl;
        orderFile << string(90, '-') << endl;

        for (int i = 0; i < currentOrder.itemCount; i++) {
            const auto& item = currentOrder.items[i];
            double subtotal = item.price * item.quantity;
            orderFile << "  " << left << setw(30) << item.furnitureName 
                      << setw(20) << item.category
                      << setw(10) << item.quantity 
                      << "Rs." << setw(14) << fixed << setprecision(2) << item.price 
                      << "Rs." << setw(14) << fixed << setprecision(2) << subtotal << endl;
        }

        orderFile << string(90, '-') << endl;
        orderFile << "  Total Amount: Rs." << fixed << setprecision(2) << currentOrder.totalAmount << endl;
        orderFile << "\n  Thank you for shopping at FURNITURE VILLAGE!\n";
        orderFile << "  Free delivery will be arranged within the country.\n";
        orderFile.close();

        centerText("Order placed successfully! Order ID: " + to_string(currentOrder.orderId));

        currentOrder.itemCount = 0; 
        centerText("Thank you for your order! Below is your Order Bill.\n");
        cout << endl;

        ifstream orderBill("order_bill_" + to_string(currentOrder.orderId) + ".txt");
        if (orderBill.is_open()) {
            string line;
            while (getline(orderBill, line)) {
                cout << line << endl;
            }
            orderBill.close();
        } else {
            cout << "Error: Unable to read the order summary file.\n";
        }
    } else {
        cout << "\n  Error: Unable to save order summary to file.\n";
    }
}

void displayHelp() {
    cout << "\n\n\n";
    centerText("===================================================");
    centerText("HELP CENTER");
    centerText("===================================================");
    cout << endl;
    cout << "  1. Add Furniture:\n";
    cout << "     - Browse our furniture list across several categories\n";
    cout << "     - Select items by ID and specify the quantity you wish to purchase\n";
    cout << "     - Add multiple items to your order with the convenient 'Add more items?' option\n";
    cout << "     - System automatically checks stock availability to ensure your order can be fulfilled\n\n";
    
    cout << "  2. List Available Furniture:\n";
    cout << "     - View our complete furniture inventory with detailed information\n";
    cout << "     - See item IDs, names, categories, prices, and stock levels\n\n";
    
    cout << "  3. Search Furniture:\n";
    cout << "     - Find furniture by specific category (Bedroom, Dining, Office Furniture, Sofa)\n";
    cout << "     - View detailed information about items in your chosen category\n\n";
    
    cout << "  4. Place Order:\n";
    cout << "     - System automatically calculates the total cost of your order\n";
    cout << "     - Receive a unique order ID for easy tracking\n";
    cout << "     - Order summary is saved as a text file for your records\n\n";
    
    cout << "  5. Help:\n";
    cout << "     - Access this comprehensive help section for assistance\n";
    cout << "     - Find detailed information about all system features\n\n";
    
    cout << "  6. Exit:\n";
    cout << "     - Safely exit the FURNITURE VILLAGE Ordering System\n\n";
}
