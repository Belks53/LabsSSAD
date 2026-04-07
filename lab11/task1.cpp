#include <iostream>
#include <string>

using namespace std;

class Light {
public:
    void on() {
        cout << "Light is turned on." << endl;
    }

    void off() {
        cout << "Light is turned off." << endl;
    }
};

class Thermostat {
public:
    void setTemperature(const string& mode) {
        cout << "Thermostat set to " << mode << "." << endl;
    }
};

class SecurityCamera {
public:
    void activate() {
        cout << "Security camera activated." << endl;
    }

    void deactivate() {
        cout << "Security camera deactivated." << endl;
    }
};

class SmartHomeFacade {
private:
    Light light;
    Thermostat thermostat;
    SecurityCamera camera;

public:
    void LeavingHome() {
        cout << "\nLeaving home scenario:" << endl;
        light.off();
        thermostat.setTemperature("eco mode");
        camera.activate();
    }

    void ArrivingHome() {
        cout << "\nArriving home scenario:" << endl;
        light.on();
        thermostat.setTemperature("comfortable temperature");
        camera.deactivate();
    }
};

int main() {
    SmartHomeFacade home;

    home.ArrivingHome();
    home.LeavingHome();

    return 0;
}