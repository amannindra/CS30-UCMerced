#ifndef ICE_CREAM_STORE_H
#define ICE_CREAM_STORE_H

#include <Queue.h>
#include <Customer.h>

class IceCreamStore {
    Queue<Customer> queue;
    int customersServed;
    int totalWaitingTime;

    void giveSample(Customer &c);
    void completeService(Customer &c);

public:
    IceCreamStore();

    void addCustomer(std::string name, int samplesRequested);

    void roundRobin();

    void firstComeFirstServed();

    void stats();

    friend struct TestIceCreamStore;
};

#endif