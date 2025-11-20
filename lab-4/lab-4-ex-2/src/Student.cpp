#include <Student.h>

using namespace std;

// Custom constructor
Student::Student(string name, int timeRequested, int arrivalTime) {
    this->name = name;
    this->timeRequested = timeRequested;
    // Initially remainingTime is set to the full timeRequested
    this->remainingTime = timeRequested;
    this->arrivalTime = arrivalTime;
}

void Student::talk(int time) {
    // Professor talks to student for a given time
    // The time is subtracted from the remainingTime counter

    // When professor has talked to student for the entire timeRequested
    // then remainingTime will be 0
    remainingTime -= time;
}

// Simple getters for each of the properties
int Student::getRequestedTime() const {
    return timeRequested;
}

string Student::getName() const {
    return name;
}

int Student::getRemainingTime() const {
    return remainingTime;
}

int Student::getArrivalTime() const {
    return arrivalTime;
}