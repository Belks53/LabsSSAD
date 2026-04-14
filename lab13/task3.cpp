#include <iostream>
#include <vector>
#include <string>

using namespace std;

class IStoreVisitor;
// IStoreItem interface (intended for Visitor pattern)
// Note: In the starter code, none of the concrete classes use this.
class IStoreItem {
public:
    virtual double accept(IStoreVisitor* visitor) = 0;
    virtual ~IStoreItem() = default;
};

// IStoreVisitor interface (intended for Visitor pattern)
// Note: In the starter code, this is just provided for future use.
class IStoreVisitor {
public:
    virtual double visit(class Book &book) = 0;
    virtual double visit(class Tea &tea) = 0;
    virtual double visit(class Coffee &coffee) = 0;
    virtual ~IStoreVisitor() = default;
};

class Book: public IStoreItem{
private:
    string isbn;
    double price;
    double tax;
public:
    Book(const string& isbn, double price, double tax)
        : isbn(isbn), price(price), tax(tax) {}

    string getIsbn() const { return isbn; }
    double getPrice() const { return price; }
    double getTax() const { return tax; }
    double accept(IStoreVisitor* visitor) override {
        return visitor->visit(*this);
    }
};

class Coffee : public IStoreItem{
private:
    string brand;
    double price;
    double tax;
    bool discount;
public:
    Coffee(const string& brand, double price, double tax, bool discount)
        : brand(brand), price(price), tax(tax), discount(discount) {}

    string getBrand() const { return brand; }
    double getPrice() const { return price; }
    double getTax() const { return tax; }
    bool isDiscount() const { return discount; }
    double accept(IStoreVisitor* visitor) override {
        return visitor->visit(*this);
    }
};

class Tea : public IStoreItem{
private:
    string brand;
    double price;
    double tax;
    bool discount;
public:
    Tea(const string& brand, double price, double tax, bool discount)
        : brand(brand), price(price), tax(tax), discount(discount) {}

    string getBrand() const { return brand; }
    double getPrice() const { return price; }
    double getTax() const { return tax; }
    bool isDiscount() const { return discount; }

    double accept(IStoreVisitor* visitor) override {
        return visitor->visit(*this);
    }
};

// StoreVisitor class with independent cost-calculation methods
// (No Visitor pattern “accept” calls here – todo: change that)
class StoreVisitor : public IStoreVisitor{
public:
    double visit(Book& book) override {
        return book.getPrice() + book.getTax() * book.getPrice();
    }

    double visit(Tea& tea) override {
        double cost = tea.getPrice() + tea.getTax() * tea.getPrice();
        if (tea.isDiscount())
            cost -= cost * 0.1;
        return cost;
    }

    double visit(Coffee& coffee) override {
        double cost = coffee.getPrice() + coffee.getTax() * coffee.getPrice();
        if (coffee.isDiscount())
            cost -= cost * 0.15;
        return cost;
    }
};


int main() {
    vector<IStoreItem*> items;
    items.push_back(new Book("1234", 20.01, 0.08));
    items.push_back(new Book("5678", 345, 0.08));
    items.push_back(new Coffee("Espresso", 300, 0.092, false));
    items.push_back(new Coffee("Starbucks", 400, 0.099, true));
    items.push_back(new Tea("Curtis", 50, 0.003, true));

    IStoreVisitor* visitor = new StoreVisitor(); // Future implementation
    double totalCost = 0;
    for (auto item : items) {
        totalCost += item->accept(visitor); // Method to be implemented by students
    }

    cout << "Total cost = " << totalCost << endl;
    return 0;
}
