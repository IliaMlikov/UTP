#include <iostream>
#include <list>
#include <string>
#include <iterator>

class ElDevice {
protected:
    std::string brand;
    std::string model;

public:
    ElDevice(const std::string& brand, const std::string& model)
        : brand(brand), model(model) {}

    virtual void display() const {
        std::cout << "Device - Brand: " << brand << ", Model: " << model << std::endl;
    }

    virtual ~ElDevice() {}
};

class Smartphone : public ElDevice {
private:
    std::string operatingSystem;

public:
    Smartphone(const std::string& brand, const std::string& model, const std::string& os)
        : ElDevice(brand, model), operatingSystem(os) {}

    void display() const override {
        std::cout << "Smartphone - Brand: " << brand << ", Model: " << model
                  << ", OS: " << operatingSystem << std::endl;
    }
};

class Laptop : public ElDevice {
private:
    double screenSize;

public:

    Laptop(const std::string& brand, const std::string& model, double screenSize)
        : ElDevice(brand, model), screenSize(screenSize) {}

    void display() const override {
        std::cout << "Laptop - Brand: " << brand << ", Model: " << model
                  << ", Screen Size: " << screenSize << " inches" << std::endl;
    }
};


void modifyDevice(ElDevice* device) {
    if (Smartphone* phone = dynamic_cast<Smartphone*>(device)) {
        std::cout << "Modifying Smartphone..." << std::endl;
        phone->display();
        phone = new Smartphone(phone->brand, phone->model, "Updated OS");
        phone->display();
    } 
    else if (Laptop* laptop = dynamic_cast<Laptop*>(device)) {
        std::cout << "Modifying Laptop..." << std::endl;
        laptop->display();
        laptop = new Laptop(laptop->brand, laptop->model, 17.3);
        laptop->display();
    }
}


int main() {
    Smartphone* smartphone1 = new Smartphone("Apple", "iPhone 14", "iOS");
    Laptop* laptop1 = new Laptop("Dell", "XPS 13", 13.3);
    Smartphone* smartphone2 = new Smartphone("Samsung", "Galaxy S21", "Android");
    Laptop* laptop2 = new Laptop("HP", "Spectre x360", 15.6);

    std::list<ElDevice*> devices;
    devices.push_back(smartphone1);
    devices.push_back(laptop1);
    devices.push_back(smartphone2);
    devices.push_back(laptop2);

    std::cout << "Displaying all devices:\n";
    for (auto it = devices.begin(); it != devices.end(); ++it) {
        (*it)->display();
    }

    std::cout << "\nModifying devices:\n";
    for (auto it = devices.begin(); it != devices.end(); ++it) {
        modifyDevice(*it);
    }


    for (auto it = devices.begin(); it != devices.end(); ++it) {
        delete *it;
    }

    return 0;
}
