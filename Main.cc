#include <iostream>
#include <string>
#include <algorithm> 

using namespace std;

string toLowerCase(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

class Item
{
private:
    string id;
    string name;
    int quantity;
    double price;
    string category;

public:
    Item(string id, string name, int quantity, double price, string category)
        : id(id), name(name), quantity(quantity), price(price), category(category) {}

    string getID() { return id; }
    string getName() { return name; }
    int getQuantity() { return quantity; }
    double getPrice() { return price; }
    string getCategory() { return category; }

    void setQuantity(int newQuantity) { quantity = newQuantity; }
    void setPrice(double newPrice) { price = newPrice; }
};

class Inventory
{
private:
    Item *items[100];
    int itemCount;

    int findItemByID(string id)
    {
        id = toLowerCase(id); 
        for (int i = 0; i < itemCount; ++i)
        {
            if (toLowerCase(items[i]->getID()) == id)
                return i;
        }
        return -1;
    }

    void sortItems(bool byQuantity, bool ascending)
    {
        for (int i = 0; i < itemCount - 1; ++i)
        {
            for (int j = 0; j < itemCount - i - 1; ++j)
            {
                bool condition = byQuantity
                                     ? (ascending ? (items[j]->getQuantity() > items[j + 1]->getQuantity())
                                                  : (items[j]->getQuantity() < items[j + 1]->getQuantity()))
                                     : (ascending ? (items[j]->getPrice() > items[j + 1]->getPrice())
                                                  : (items[j]->getPrice() < items[j + 1]->getPrice()));
                if (condition)
                {
                    Item *temp = items[j];
                    items[j] = items[j + 1];
                    items[j + 1] = temp;
                }
            }
        }
    }

public:
    Inventory() : itemCount(0) {}

    void addItem(string id, string name, int quantity, double price, string category)
    {
        category = toLowerCase(category);
        
        if (findItemByID(id) != -1) 
        {
            cout << "Item with ID " << id << " already exists!" << endl;
            return;
        }

        if (category == "clothing" || category == "electronics" || category == "entertainment")
        {
            items[itemCount++] = new Item(id, name, quantity, price, category);
            cout << "Item added successfully!" << endl;
        }
        else
        {
            cout << "Category " << category << " does not exist!" << endl;
        }
    }

    void updateItem(string id, bool updateQuantity, int newQuantity = 0, double newPrice = 0.0)
    {
        int index = findItemByID(id);
        if (index != -1)
        {
            if (updateQuantity)
            {
                cout << "Quantity of Item " << items[index]->getName() << " is updated from "
                     << items[index]->getQuantity() << " to " << newQuantity << endl;
                items[index]->setQuantity(newQuantity);
            }
            else
            {
                cout << "Price of Item " << items[index]->getName() << " is updated from "
                     << items[index]->getPrice() << " to " << newPrice << endl;
                items[index]->setPrice(newPrice);
            }
        }
        else
        {
            cout << "Item not found!" << endl;
        }
    }

    void removeItem(string id)
    {
        int index = findItemByID(id);
        if (index != -1)
        {
            cout << "Item " << items[index]->getName() << " has been removed from the inventory" << endl;
            for (int i = index; i < itemCount - 1; ++i)
            {
                items[i] = items[i + 1];
            }
            --itemCount;
        }
        else
        {
            cout << "Item not found!" << endl;
        }
    }

    void displayItemsByCategory(string category)
    {
        category = toLowerCase(category);
        if (category == "clothing" || category == "electronics" || category == "entertainment")
        {
            cout << "ID\tName\t\tQuantity\tPrice" << endl;
            bool found = false;
            for (int i = 0; i < itemCount; ++i)
            {
                if (toLowerCase(items[i]->getCategory()) == category)
                {
                    cout << items[i]->getID() << "\t" << items[i]->getName() << "\t\t"
                         << items[i]->getQuantity() << "\t\t" << items[i]->getPrice() << endl;
                    found = true;
                }
            }
            if (!found)
                cout << "No items found in this category." << endl;
        }
        else
        {
            cout << "Category " << category << " does not exist!" << endl;
        }
    }

    void displayAllItems()
    {
        if (itemCount == 0)
        {
            cout << "No items in inventory." << endl;
        }
        else
        {
            cout << "ID\tName\t\tQuantity\tPrice\tCategory" << endl;
            for (int i = 0; i < itemCount; ++i)
            {
                cout << items[i]->getID() << "\t" << items[i]->getName() << "\t\t"
                     << items[i]->getQuantity() << "\t\t" << items[i]->getPrice() << "\t"
                     << items[i]->getCategory() << endl;
            }
        }
    }

    void searchItem(string id)
    {
        int index = findItemByID(id);
        if (index != -1)
        {
            cout << "ID: " << items[index]->getID() << "\nName: " << items[index]->getName()
                 << "\nQuantity: " << items[index]->getQuantity() << "\nPrice: "
                 << items[index]->getPrice() << "\nCategory: " << items[index]->getCategory() << endl;
        }
        else
        {
            cout << "Item not found!" << endl;
        }
    }

    void sortItemsBy(bool byQuantity, bool ascending)
    {
        sortItems(byQuantity, ascending);
        displayAllItems();
    }

    void displayLowStockItems()
    {
        cout << "ID\tName\t\tQuantity\tPrice\tCategory" << endl;
        bool found = false;
        for (int i = 0; i < itemCount; ++i)
        {
            if (items[i]->getQuantity() <= 5)
            {
                cout << items[i]->getID() << "\t" << items[i]->getName() << "\t\t"
                     << items[i]->getQuantity() << "\t\t" << items[i]->getPrice() << "\t"
                     << items[i]->getCategory() << endl;
                found = true;
            }
        }
        if (!found)
            cout << "No low stock items found." << endl;
    }
};

int main()
{
    Inventory inventory;
    int choice;

    do
    {
        cout << "Menu\n1 - Add Item\n2 - Update Item\n3 - Remove Item\n4 - Display Items by Category\n"
             << "5 - Display All Items\n6 - Search Item\n7 - Sort Items\n8 - Display Low Stock Items\n9 - Exit\n";
        cin >> choice;
        cin.ignore();

        system("cls");

        switch (choice)
        {
        case 1:
        {
            string id, name, category;
            int quantity;
            double price;
            cout << "Enter ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name); 
            cout << "Enter Quantity: ";
            cin >> quantity;
            cout << "Enter Price: ";
            cin >> price;
            cout << "Enter Category (Clothing/Electronics/Entertainment): ";
            cin >> category;
            inventory.addItem(id, name, quantity, price, category);
            break;
        }
        case 2:
        {
            string id;
            int type;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Update (1 - Quantity, 2 - Price): ";
            cin >> type;
            if (type == 1)
            {
                int newQuantity;
                cout << "Enter new Quantity: ";
                cin >> newQuantity;
                inventory.updateItem(id, true, newQuantity);
            }
            else
            {
                double newPrice;
                cout << "Enter new Price: ";
                cin >> newPrice;
                inventory.updateItem(id, false, 0, newPrice);
            }
            break;
        }
        case 3:
        {
            string id;
            cout << "Enter ID: ";
            cin >> id;
            inventory.removeItem(id);
            break;
        }
        case 4:
        {
            string category;
            cout << "Enter Category: ";
            cin >> category;
            inventory.displayItemsByCategory(category);
            break;
        }
        case 5:
            inventory.displayAllItems();
            break;
        case 6:
        {
            string id;
            cout << "Enter ID: ";
            cin >> id;
            inventory.searchItem(id);
            break;
        }
        case 7:
        {
            int type, order;
            cout << "Sort by (1 - Quantity, 2 - Price): ";
            cin >> type;
            cout << "Order (1 - Ascending, 2 - Descending): ";
            cin >> order;
            inventory.sortItemsBy(type == 1, order == 1);
            break;
        }
        case 8:
            inventory.displayLowStockItems();
            break;
        }
    } while (choice != 9);

    return 0;
}
