#include <string>
#include <vector>
#include <iostream>

using namespace std;

class SmartHouseMediator;

class Device {
public:
    virtual void sendMessage(const string& message) = 0;
    virtual void receiveMessage(const string& message) = 0;
    virtual void setMediator(SmartHouseMediator* mediator) = 0;
    virtual ~Device() = default;
};

class MotionSensor : public Device {
public:
    void sendMessage(const string& message) override;
    void receiveMessage(const string& message) override;
    void setMediator(SmartHouseMediator* med) override;

private:
    SmartHouseMediator* mediator = nullptr;
};

class TemperatureSensor : public Device {
public:
    void sendMessage(const string& message) override;
    void receiveMessage(const string& message) override;
    void setMediator(SmartHouseMediator* med) override;

private:
    SmartHouseMediator* mediator = nullptr;
};

class SmartHouseMediator {
public:
    void addDevice(Device* device) {
        devices.push_back(device);
        device->setMediator(this);
    }

    void mediate(Device* sender, const string& message) {
        for (Device* device : devices) {
            if (device != sender) {
                device->receiveMessage(message);
            }
        }
    }

private:
    vector<Device*> devices;
};

void MotionSensor::sendMessage(const string& message) {
    if (mediator != nullptr) {
        mediator->mediate(this, message);
    }
}

void MotionSensor::receiveMessage(const string& message) {
    cout << "MotionSensor received a " << message
         << ", the owner will be notified that they expect a visitor\n";
}

void MotionSensor::setMediator(SmartHouseMediator* med) {
    mediator = med;
}

void TemperatureSensor::sendMessage(const string& message) {
    if (mediator != nullptr) {
        mediator->mediate(this, message);
    }
}

void TemperatureSensor::receiveMessage(const string& message) {
    cout << "TemperatureSensor received a " << message
         << ", the room temperature will be adjusted\n";
}

void TemperatureSensor::setMediator(SmartHouseMediator* med) {
    mediator = med;
}

int main() {
    SmartHouseMediator mediator;
    MotionSensor motion;
    TemperatureSensor temp;

    mediator.addDevice(&motion);
    mediator.addDevice(&temp);

    motion.sendMessage("Motion detected");

    return 0;
}