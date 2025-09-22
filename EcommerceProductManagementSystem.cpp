#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream> // dùng d? tách chu?i nh?p nhi?u ID
using namespace std;

// Abstract interface
class Discountable {
public:
    virtual double applyDiscount(double rate) = 0;
    virtual ~Discountable() {}
};

// Base class
class Product : public Discountable {
protected:
    string id, name;
    double price;
    int stock;
public:
    Product(string id, string name, double price, int stock)
        : id(id), name(name), price(price), stock(stock) {}

    virtual void updateStock(int amount) {
        stock += amount;
    }

    string getId() const { return id; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }

    virtual void display() const {
        cout << "Product: " << name << " | ID: " << id
             << " | Price: $" << price << " | Stock: " << stock << endl;
    }

    bool operator==(const Product& other) const {
        return id == other.id;
    }

    double applyDiscount(double rate) override {
        return price * (1 - rate);
    }

    virtual ~Product() {}
};

// Derived class
class Electronics : public Product {
    int warrantyMonths;
public:
    Electronics(string id, string name, double price, int stock, int warranty)
        : Product(id, name, price, stock), warrantyMonths(warranty) {}

    void updateStock(int amount) override {
        stock += amount;
        price += 10; // phí thêm cho hàng di?n t?
    }

    void display() const override {
        Product::display();
        cout << "Warranty: " << warrantyMonths << " months" << endl;
    }
};

// Template class
template <typename T>
class InventoryList {
    vector<T> items;
public:
    void addItem(T item) {
        items.push_back(item);
    }

    void removeItem(string id) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if ((*it)->getId() == id) {
                items.erase(it);
                return;
            }
        }
        cout << "Item not found.\n";
    }

    T searchItem(string id) {
        for (auto& item : items) {
            if (item->getId() == id) return item;
        }
        return nullptr;
    }

    void displayAll() const {
        for (auto& item : items) {
            item->display();
        }
    }

    vector<T>& getItems() { return items; }
};

// Shopping cart
class ShoppingCart : public Discountable {
    map<string, pair<Product*, int>> cart;
public:
    void operator+=(Product* p) {
        if (p->getStock() <= 0) {
            cout << "Cannot add. Product out of stock.\n";
            return;
        }
        cart[p->getId()].first = p;
        cart[p->getId()].second++;
        p->updateStock(-1);
    }

    double applyDiscount(double rate) override {
        double total = 0;
        for (auto& entry : cart) {
            Product* product = entry.second.first;
            int quantity = entry.second.second;
            total += product->applyDiscount(rate) * quantity;
        }
        return total;
    }

    void displayCart() const {
        cout << "=== Shopping Cart ===\n";
        for (auto& entry : cart) {
            Product* product = entry.second.first;
            int quantity = entry.second.second;
            cout << product->getId() << " x" << quantity
                 << " ? $" << product->getPrice() * quantity << endl;
        }
    }

    void checkout() {
        if (cart.empty()) {
            cout << "Cart is empty. Cannot checkout.\n";
            return;
        }

        double rate;
        cout << "Enter discount rate (e.g., 0.1 for 10%): ";
        cin >> rate;
        double total = applyDiscount(rate);
        cout << "Total after discount: $" << total << endl;

        int method;
        cout << "Choose payment method:\n";
        cout << "1. Cash\n";
        cout << "2. Card\n";
        cout << "Your choice: ";
        cin >> method;

        if (method == 1) {
            cout << "Payment successful via Cash.\n";
        } else if (method == 2) {
            cout << "Payment successful via Card.\n";
        } else {
            cout << "Invalid payment method.\n";
        }

        cout << "Thank you for your purchase!\n";
        cart.clear();
    }
};

// Main menu
int main() {
    InventoryList<Product*> inventory;
    ShoppingCart cart;

    int choice;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Add Product\n";
        cout << "2. Add Electronics\n";
        cout << "3. Show Inventory\n";
        cout << "4. Add Items to Cart\n";
        cout << "5. Show Cart\n";
        cout << "6. Apply Discount\n";
        cout << "7. Checkout\n";
        cout << "8. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1) {
            string id, name;
            double price;
            int stock;
            cout << "Enter ID: "; cin >> id;
            cout << "Enter Name: "; cin.ignore(); getline(cin, name);
            cout << "Enter Price: "; cin >> price;
            cout << "Enter Stock: "; cin >> stock;
            inventory.addItem(new Product(id, name, price, stock));
        }
        else if (choice == 2) {
            string id, name;
            double price;
            int stock, warranty;
            cout << "Enter ID: "; cin >> id;
            cout << "Enter Name: "; cin.ignore(); getline(cin, name);
            cout << "Enter Price: "; cin >> price;
            cout << "Enter Stock: "; cin >> stock;
            cout << "Enter Warranty (months): "; cin >> warranty;
            inventory.addItem(new Electronics(id, name, price, stock, warranty));
        }
        else if (choice == 3) {
            inventory.displayAll();
        }
        else if (choice == 4) {
            cin.ignore();
            cout << "Enter Product IDs to add to cart (separated by space): ";
            string line;
            getline(cin, line);
            istringstream iss(line);
            string id;
            while (iss >> id) {
                Product* p = inventory.searchItem(id);
                if (p) cart += p;
                else cout << "Product ID '" << id << "' not found.\n";
            }
        }
        else if (choice == 5) {
            cart.displayCart();
        }
        else if (choice == 6) {
            double rate;
            cout << "Enter discount rate (e.g., 0.1 for 10%): ";
            cin >> rate;
            double total = cart.applyDiscount(rate);
            cout << "Total after discount: $" << total << endl;
        }
        else if (choice == 7) {
            cart.checkout();
        }

    } while (choice != 8);

    // Cleanup
    for (auto p : inventory.getItems()) delete p;
    return 0;
}

