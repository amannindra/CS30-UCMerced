#include <iostream>
#include <IceCreamStore.h>

using namespace std;

void IceCreamStore::giveSample(Customer &c) {
        // Giving a sample to specified customer
        c.giveSample();
        // Everyone in the queue had to wait during this interaction
        totalWaitingTime += queue.size();
        // cout << "Total Wait time is increasing " << endl;
        // Printing a message
        cout << "Giving sample to " << c.getName() << endl;
    }

void IceCreamStore::completeService(Customer &c) {
    // Simply increase number of customers served
    customersServed++;
    cout << "Done with " << c.getName() << endl;
}

IceCreamStore::IceCreamStore(){
    // Default constructor
    customersServed = 0;
    totalWaitingTime = 0;
}

void IceCreamStore::addCustomer(std::string name, int samplesRequested) {
    // Add a customer to the queue, including their name,
    // and the number of samples requested
    queue.enqueue(Customer(name, samplesRequested));
}

void IceCreamStore::firstComeFirstServed() {
    // As long as there are still customers in line
    while (!queue.isEmpty()) {
        // Get the first customer
        Customer c = queue.dequeue();

        // As long as they still want a sample
        while (c.getRequestCount() > 0){
            // Give them a sample
            giveSample(c);
        }

        // At this point we have provided all the samples 
        // the customer wanted, so the service is complete
        completeService(c);
    }
}

void IceCreamStore::stats() {
    // Print out the number of customers served (completed orders)
    // The total waiting time for all customers and average per customer
    cout << "Customers served:  " << customersServed << endl;
    cout << "Total wait time:   " << totalWaitingTime << endl;
    cout << "Average wait time: " << ((float)totalWaitingTime / customersServed) << endl;
}