#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string toLowerCase(string str)
{
    for (char &c : str)
    {
        if (c >= 'A' && c <= 'Z')
        {
            c = c + 32;
        }
    }
    return str;
}

class ItemBase
{
protected:
    string id;
    string name;
    int quantity;
    double price;

public:
    ItemBase(string id, string name, int quantity, double price)
        : id(id), name(name), quantity(quantity), price(price) {}

    virtual string getID() = 0;
    virtual string getName() = 0;
    virtual int getQuantity() = 0;
    virtual double getPrice() = 0;
    virtual string getCategory() = 0;

    virtual void setQuantity(int newQuantity) = 0;
    virtual void setPrice(double newPrice) = 0;

    virtual ~ItemBase() {}
};

class ClothingItem : public ItemBase
{
public:
    ClothingItem(string id, string name, int quantity, double price)
        : ItemBase(id, name, quantity, price) {}

    string getID() override { return id; }
    string getName() override { return name; }
    int getQuantity() override { return quantity; }
    double getPrice() override { return price; }
    string getCategory() override { return "Clothing"; }

    void setQuantity(int newQuantity) override { quantity = newQuantity; }
    void setPrice(double newPrice) override { price = newPrice; }
};

class ElectronicsItem : public ItemBase
{
public:
    ElectronicsItem(string id, string name, int quantity, double price)
        : ItemBase(id, name, quantity, price) {}

    string getID() override { return id; }
    string getName() override { return name; }
    int getQuantity() override { return quantity; }
    double getPrice() override { return price; }
    string getCategory() override { return "Electronics"; }

    void setQuantity(int newQuantity) override { quantity = newQuantity; }
    void setPrice(double newPrice) override { price = newPrice; }
};

class EntertainmentItem : public ItemBase
{
public:
    EntertainmentItem(string id, string name, int quantity, double price)
        : ItemBase(id, name, quantity, price) {}

    string getID() override { return id; }
    string getName() override { return name; }
    int getQuantity() override { return quantity; }
    double getPrice() override { return price; }
    string getCategory() override { return "Entertainment"; }

    void setQuantity(int newQuantity) override { quantity = newQuantity; }
    void setPrice(double newPrice) override { price = newPrice; }
};

class Inventory
{
private:
    ItemBase *items[100];
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
                    ItemBase *temp = items[j];
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

        if (category == "clothing")
        {
            items[itemCount++] = new ClothingItem(id, name, quantity, price);
        }
        else if (category == "electronics")
        {
            items[itemCount++] = new ElectronicsItem(id, name, quantity, price);
        }
        else if (category == "entertainment")
        {
            items[itemCount++] = new EntertainmentItem(id, name, quantity, price);
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
                items[index]->setQuantity(newQuantity);
            }
            else
            {
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

        // Input validation for choice
        do
        {
            cout << "Enter choice (1-9): ";
            cin >> choice;
            if (cin.fail() || choice < 1 || choice > 9)
            {
                cin.clear();                   // clear the error state
                cin.ignore(10000, '\n');        // ignore invalid input
                cout << "Invalid choice! Please enter a number between 1 and 9." << endl;
            }
        } while (cin.fail() || choice < 1 || choice > 9);
        
        cin.ignore(); // Clear newline character from buffer

        system("cls");

        string id, name, category;
        int quantity;
        double price;
        bool updateQuantity, ascending;
        int newQuantity;
        double newPrice;

        switch (choice)
        {
        case 1:
            cout << "Enter ID: ";
            getline(cin, id);
            cout << "Enter Name: ";
            getline(cin, name);

            // Input validation for quantity
            do
            {
                cout << "Enter Quantity: ";
                cin >> quantity;
                if (cin.fail() || quantity < 0)
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid quantity! Please enter a non-negative integer." << endl;
                    quantity = -1;
                }
            } while (cin.fail() || quantity < 0);

            // Input validation for price
            do
            {
                cout << "Enter Price: ";
                cin >> price;
                if (cin.fail() || price < 0.0)
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid price! Please enter a non-negative number." << endl;
                    price = -1;
                }
            } while (cin.fail() || price < 0.0);

            cout << "Enter Category (Clothing/Electronics/Entertainment): ";
            cin >> category;
            inventory.addItem(id, name, quantity, price, category);
            break;

        case 2:
            cout << "Enter ID: ";
            getline(cin, id);

            // Input validation for updateQuantity (1 for Yes, 0 for No)
            do
            {
                cout << "Update Quantity? (1 for Yes, 0 for No): ";
                cin >> updateQuantity;
                if (cin.fail() || (updateQuantity != 0 && updateQuantity != 1))
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid input! Please enter 1 for Yes or 0 for No." << endl;
                }
            } while (cin.fail() || (updateQuantity != 0 && updateQuantity != 1));

            if (updateQuantity)
            {
                // Input validation for newQuantity
                do
                {
                    cout << "Enter New Quantity: ";
                    cin >> newQuantity;
                    if (cin.fail() || newQuantity < 0)
                    {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Invalid quantity! Please enter a non-negative integer." << endl;
                    }
                } while (cin.fail() || newQuantity < 0);

                inventory.updateItem(id, true, newQuantity);
            }
            else
            {
                // Input validation for newPrice
                do
                {
                    cout << "Enter New Price: ";
                    cin >> newPrice;
                    if (cin.fail() || newPrice < 0.0)
                    {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Invalid price! Please enter a non-negative number." << endl;
                    }
                } while (cin.fail() || newPrice < 0.0);

                inventory.updateItem(id, false, 0, newPrice);
            }
            break;

        case 3:
            cout << "Enter ID: ";
            getline(cin, id);
            inventory.removeItem(id);
            break;

        case 4:
            cout << "Enter Category (Clothing/Electronics/Entertainment): ";
            cin >> category;
            inventory.displayItemsByCategory(category);

            do
            {
                cout << "Sort by (1 for Quantity, 0 for Price): ";
                cin >> updateQuantity;
                if (cin.fail() || (updateQuantity != 0 && updateQuantity != 1))
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid input! Please enter 1 for Quantity or 0 for Price." << endl;
                }
            } while (cin.fail() || (updateQuantity != 0 && updateQuantity != 1));


            break;

        case 5:
            inventory.displayAllItems();
            break;

        case 6:
            cout << "Enter ID: ";
            getline(cin, id);
            inventory.searchItem(id);
            break;

        case 7:
            // Input validation for sorting byQuantity (1 for Quantity, 0 for Price)
            do
            {
                cout << "Sort by (1 for Quantity, 0 for Price): ";
                cin >> updateQuantity;
                if (cin.fail() || (updateQuantity != 0 && updateQuantity != 1))
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid input! Please enter 1 for Quantity or 0 for Price." << endl;
                }
            } while (cin.fail() || (updateQuantity != 0 && updateQuantity != 1));

            // Input validation for ascending order (1 for Yes, 0 for No)
            do
            {
                cout << "Sort in Ascending order? (1 for Yes, 0 for No): ";
                cin >> ascending;
                if (cin.fail() || (ascending != 0 && ascending != 1))
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid input! Please enter 1 for Yes or 0 for No." << endl;
                }
            } while (cin.fail() || (ascending != 0 && ascending != 1));

            inventory.sortItemsBy(updateQuantity, ascending);
            break;

        case 8:
            inventory.displayLowStockItems();
            break;

        case 9:
            cout << "Exiting program." << endl;
            break;

        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
        }

        system("pause");
        system("cls");

    } while (choice != 9);

    return 0;
}