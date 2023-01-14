#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class IDGenerator {
    static int nextID;
public:
    static int getNextID() { return nextID++; }
};
int IDGenerator::nextID = 0;

template<typename T>
class Agency {
    std::vector<T> items;
    std::string name;
    int id;

public:
    Agency(std::string name) : name(name), id(IDGenerator::getNextID()) {}
    virtual ~Agency() {}

    T* clone(T* item) {
        return new T(*item);
    }
    void addItem(T* item) {
        items.push_back(*item);
    }
    void removeItem(T* item) {
        auto it = std::find(items.begin(), items.end(), *item);
        if (it != items.end()) {
            items.erase(it);
        }
    }
    void display() const {
        std::cout << "Agency: " << name << ", ID: " << id << std::endl;
        for (auto& item : items) {
            item.display();
        }
    }


    friend std::ostream& operator<<(std::ostream& os, const Agency<T>& agency) {
        agency.display();
        return os;
    }
};

class Tour {
public:
    std::string destination;
    double price;
    Tour(std::string destination, double price) : destination(destination), price(price) {}
    virtual ~Tour() {}
    virtual void display() const {
        std::cout << "Tour: " << destination << ", Price: " << price << std::endl;
    }
    bool operator==(const Tour& rhs) const {
        return destination == rhs.destination && price == rhs.price;
    }
};

class SpecialTour : public Tour {
    std::string package;
public:
    SpecialTour(std::string destination, double price, std::string package) :
            Tour(destination, price), package(package) {}
    virtual void display() const {
        std::cout << "Special Tour: " << destination << ", Price: " << price << ", Package: " << package << std::endl;
    }

};



int main() {
    Agency<Tour> agency("Travel Agency");
    Tour* tour1 = new Tour("France", 1000);
    agency.addItem(tour1);
    Tour* tour2 = new Tour("Italy", 2000);
    agency.addItem(tour2);
    SpecialTour* specialTour1 = new SpecialTour("Spain", 1500, "Beach");
    agency.addItem(specialTour1);
    std::cout << agency << std::endl;

    Tour* tour3 = agency.clone(tour1);
    agency.removeItem(tour1);
    std::cout << agency << std::endl;

    delete tour1;
    delete tour2;
    delete specialTour1;
    delete tour3;
    return 0;
}
