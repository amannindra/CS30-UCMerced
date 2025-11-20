#include <Queue.h>
#include <Simulations.h>
#include <Student.h>
#include <iostream>

using namespace std;

int main() {

    Queue<Student> schedule;

    int maxAllowedSession = 5;

    schedule.enqueue(Student("Alice", 5, 0));
    schedule.enqueue(Student("Bob", 1, 0));
    schedule.enqueue(Student("Cathy", 2, 0));

    float actual = averageWaitingTimeRoundRobin(schedule, maxAllowedSession);

    cout << "Expected waiting time - First come first served: " << actual
         << endl;

    int expected = 5.3333;

    return 0;
}