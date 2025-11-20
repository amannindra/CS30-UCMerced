#include <IceCreamStore.h>
#include <Queue.h>
#include <iostream>
#include <sstream>

using namespace std;

int main() {

    IceCreamStore store;

    string line;
    // while (getline(cin, line)){
    //     stringstream ss(line);

    //     string name;
    //     getline(ss, name, ',');
    //     string samplesRequested;
    //     getline(ss, samplesRequested);
    //     store.addCustomer(name, stoi(samplesRequested));
    // }

    store.addCustomer("Alice", 5);
    store.addCustomer("Bob", 1);
    store.roundRobin();
    // Do only one of the two below
    store.averageWaitingTimeFirstComeFirstServed(store);
    // store.roundRobin();

    store.stats();

    return 0;
}