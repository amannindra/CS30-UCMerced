#include <SortedList.h>
#include <iostream>
#include <TimeSupport.h>

using namespace std;

int main() {
    const int N = 10000;

        SortedList<int> even, odd;

        for (int i = 0; i < N*2; i++){
            if (i % 2 == 0){
                even.append(i);
            }
            else{
                odd.append(i);
            }
        }

        Timestamp start; 

        even.merge(odd);

        Timestamp end;

        int duration = end - start;

    std::cout << "Even: " << even << std::endl;
    std::cout << "Duration: " << duration << std::endl;

    // two.merge(one);

    // std::cout << "Done: " << two << std::endl;

    return 0;
}