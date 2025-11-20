#include <igloo/igloo.h>
#include <stdexcept>
#include <unistd.h>
#include <IceCreamStore.h>

using namespace igloo;

Context(TestIceCreamStore){
    Spec(Test1_Initial){
        IceCreamStore store;

        Assert::That(store.totalWaitingTime, Equals(0));
        Assert::That(store.customersServed, Equals(0));
    }

    Spec(Test2_One_Customer_FCFS){
        IceCreamStore store;
        store.addCustomer("Alice", 5);
        store.firstComeFirstServed();
        Assert::That(store.customersServed, Equals(1));
        Assert::That(store.totalWaitingTime, Equals(0));
    }

    Spec(Test3_One_Customer_RR){
        IceCreamStore store;
        store.addCustomer("Alice", 5);
        store.roundRobin();
        Assert::That(store.customersServed, Equals(1));
        Assert::That(store.totalWaitingTime, Equals(0));
    }

    Spec(Test4_Two_Customers_FCFS){
        IceCreamStore store;
        store.addCustomer("Alice", 5);
        store.addCustomer("Bob", 1);

        store.firstComeFirstServed();

        Assert::That(store.customersServed, Equals(2));
        Assert::That(store.totalWaitingTime, Equals(5));
    }

    Spec(Test5_Two_Customers_RR){
        IceCreamStore store;
        store.addCustomer("Alice", 5);
        store.addCustomer("Bob", 1);

        store.roundRobin();

        Assert::That(store.customersServed, Equals(2));
        Assert::That(store.totalWaitingTime, Equals(2));
    }

    Spec(Test6_Three_Customers_FCFS){
        IceCreamStore store;
        store.addCustomer("Alice", 5);
        store.addCustomer("Bob", 1);
        store.addCustomer("Cathy", 2);

        store.firstComeFirstServed();

        Assert::That(store.customersServed, Equals(3));
        Assert::That(store.totalWaitingTime, Equals(11));
    }

    Spec(Test7_Three_Customers_RR){
        IceCreamStore store;
        store.addCustomer("Alice", 5);
        store.addCustomer("Bob", 1);
        store.addCustomer("Cathy", 2);

        store.roundRobin();

        Assert::That(store.customersServed, Equals(3));
        Assert::That(store.totalWaitingTime, Equals(7));
    }
};

int main(int argc, const char* argv[]){
    TestRunner::RunAllTests(argc, argv);
}