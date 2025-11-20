#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
    std::string name;   // Name of student
    int timeRequested;  // How much time they have requested
    int arrivalTime;    // What time they will arrive
    int remainingTime;  // How much of their requested time is still unfulfilled

public:
    // Default constructor
    Student(std::string name = "", int timeRequested = 0, int arrivalTime = 0);

    // Professor talks to student for a given time, reducing their remainingTime
    void talk(int time);

    // Simple getters for each property
    std::string getName() const;
    int getRequestedTime() const;    
    int getRemainingTime() const;
    int getArrivalTime() const;
};

#endif