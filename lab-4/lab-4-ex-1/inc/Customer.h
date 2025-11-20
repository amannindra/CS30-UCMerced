#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer {
    std::string name;
    int samplesRequested;

public:
    Customer(std::string n = "", int s = 1) {
        name = n;
        samplesRequested = s;
    }

    void giveSample(){
        samplesRequested--;
    }

    std::string getName() const {
        return name;
    }

    int getRequestCount() const {
        return samplesRequested;
    }

};

#endif