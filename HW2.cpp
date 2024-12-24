#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Light {
private:
    bool isOn;

public:
    Light() : isOn(false) {}

    void turnOn() { isOn = true; }
    void turnOff() { isOn = false; }
    string getStatus() const { return isOn ? "On" : "Off"; }
    bool getState() const { return isOn; }
    void setState(bool state) { isOn = state; }
};


class Thermostat {
private:
    int temperature;

public:
    Thermostat() : temperature(20) {}

    void setTemperature(int t) { temperature = t; }
    int getTemperature() const { return temperature; }
};

class SecuritySystem {
private:
    bool isArmed;

public:
    SecuritySystem() : isArmed(false) {}

    void arm() { isArmed = true; }
    void disarm() { isArmed = false; }
    string getStatus() const { return isArmed ? "Armed" : "Disarmed"; }
    bool getState() const { return isArmed; }
    void setState(bool state) { isArmed = state; }
};

class Curtains {
private:
    bool isUp;

public:
    Curtains() : isUp(false) {}

    void raise() { isUp = true; }
    void lower() { isUp = false; }
    string getStatus() const { return isUp ? "Raised" : "Lowered"; }
    bool getState() const { return isUp; }
    void setState(bool state) { isUp = state; }
};

class AirConditioner {
private:
    bool isOn;

public:
    AirConditioner() : isOn(false) {}

    void turnOn() { isOn = true; }
    void turnOff() { isOn = false; }
    string getStatus() const { return isOn ? "On" : "Off"; }
    bool getState() const { return isOn; }
    void setState(bool state) { isOn = state; }
};


class SmartHome {
private:
    Light light;
    Thermostat thermostat;
    SecuritySystem security;
    Curtains curtains;
    AirConditioner airConditioner;
    string stateFile;

public:
    SmartHome(const string& file = "home_state.txt") : stateFile(file) {
        loadState();
    }

    void controlLight(bool state) {
        if (state) light.turnOn();
        else light.turnOff();
    }

    void setTemperature(int temp) {
        thermostat.setTemperature(temp);
    }

    void controlSecurity(bool state) {
        if (state) security.arm();
        else security.disarm();
    }

    void controlCurtains(bool state) {
        if (state) curtains.raise();
        else curtains.lower();
    }

    void controlAirConditioner(bool state) {
        if (state) airConditioner.turnOn();
        else airConditioner.turnOff();
    }

    void displayStatus() {
        cout << "Light: " << light.getStatus() << endl;
        cout << "Temperature: " << thermostat.getTemperature() << "°C" << endl;
        cout << "Security System: " << security.getStatus() << endl;
        cout << "Curtains: " << curtains.getStatus() << endl;
        cout << "Air Conditioner: " << airConditioner.getStatus() << endl;
    }

    void saveState() {
        ofstream file(stateFile);
        if (file.is_open()) {
            file << light.getState() << endl;
            file << thermostat.getTemperature() << endl;
            file << security.getState() << endl;
            file << curtains.getState() << endl;
            file << airConditioner.getState() << endl;
            file.close();
        }
    }

    void loadState() {
        ifstream file(stateFile);
        if (file.is_open()) {
            bool lightState, securityState, curtainsState, airConditionerState;
            int temp;

            file >> lightState;
            file >> temp;
            file >> securityState;
            file >> curtainsState;
            file >> airConditionerState;

            light.setState(lightState);
            thermostat.setTemperature(temp);
            security.setState(securityState);
            curtains.setState(curtainsState);
            airConditioner.setState(airConditionerState);

            file.close();
        }
    }
};


int main() {
    SmartHome smartHome;

    while (true) {
        cout << "\nSmart Home Control System\n";
        cout << "1. Control Light\n";
        cout << "2. Set Temperature\n";
        cout << "3. Control Security System\n";
        cout << "4. Control Curtains\n";
        cout << "5. Control Air Conditioner\n";
        cout << "6. Display Status\n";
        cout << "7. Exit\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Enter 1 to turn on the light or 0 to turn off: ";
            bool state;
            cin >> state;
            smartHome.controlLight(state);
        }
        else if (choice == 2) {
            cout << "Enter desired temperature (°C): ";
            int temp;
            cin >> temp;
            smartHome.setTemperature(temp);
        }
        else if (choice == 3) {
            cout << "Enter 1 to arm the security system or 0 to disarm: ";
            bool state;
            cin >> state;
            smartHome.controlSecurity(state);
        }
        else if (choice == 4) {
            cout << "Enter 1 to raise curtains or 0 to lower: ";
            bool state;
            cin >> state;
            smartHome.controlCurtains(state);
        }
        else if (choice == 5) {
            cout << "Enter 1 to turn on air conditioner or 0 to turn off: ";
            bool state;
            cin >> state;
            smartHome.controlAirConditioner(state);
        }
        else if (choice == 6) {
            smartHome.displayStatus();
        }
        else if (choice == 7) {
            smartHome.saveState();
            cout << "Exiting... State saved.\n";
            break;
        }
        else {
            cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}