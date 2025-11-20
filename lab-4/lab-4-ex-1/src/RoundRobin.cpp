#include <IceCreamStore.h>

void IceCreamStore::roundRobin() {
    std::cout << "RoundRobin" << std::endl;
    while (!queue.isEmpty()){
        Customer C = queue.dequeue();
        giveSample(C);
        if (C.getRequestCount() > 0) {
            queue.enqueue(C);
        }else{
            completeService(C);
        }
    }

}