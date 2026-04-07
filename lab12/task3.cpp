#include <iostream>
#include <string>
#include <random>

using namespace std;

class ITransport {
    public:
    virtual void deliver() = 0;
    virtual ~ITransport() = default;
};
class Truck : public ITransport {
private:
    string address;
public:
    Truck() : address("Innopolis University") {}

    void deliver() override {
        cout << "Truck delivers to address: " << address << endl;
    }
};

class Ship : public ITransport {
private:
    string country;
public:
    Ship() : country("Spain") {}

    void deliver() override {
        cout << "Ship delivers to country " << country << endl;
    }
};

class Plane : public ITransport {
private:
    string country;
public:
    Plane() : country("Germany") {}

    void deliver() override {
        cout << "Plane delivers to country " << country << endl;
    }
};

class TransportFactory {
    public:
    static ITransport *getTransport() {
        int c = rand() % 3;

        if (c == 0) {
            return new Truck();
        }
        if (c == 1) {
            return new Ship();
        } else {
            return new Plane();
        }
    }
};

int main() {
    TransportFactory t;

    for (int i = 0; i < 10; i++) {
        ITransport* transport = TransportFactory::getTransport();
        transport->deliver();
        delete transport;
    }
    return 0;
}
