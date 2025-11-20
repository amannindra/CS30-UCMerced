#include "Simulations.h"
#include "Queue.h"
#include "Student.h"
#include <iostream>

using namespace std;

float averageWaitingTimeRoundRobin(Queue<Student> schedule,
                                   int maxAllowedSession) {
    float totalTime = 0;
    float currentTime = 0;
    int totalStudents = schedule.size();

    if (schedule.isEmpty()) {
        return 0;
    }

    Queue<Student> waitingQuene;

    int studentFinished = 0;

    while (studentFinished < totalStudents) {
        while (!schedule.isEmpty() &&
               schedule.peek().getArrivalTime() <= currentTime) {
            waitingQuene.enqueue(schedule.dequeue());
        }

        if (waitingQuene.isEmpty()) {
            if (!schedule.isEmpty()) {
                currentTime = schedule.peek().getArrivalTime();
            }
            continue;
        }

        Student cs = waitingQuene.dequeue();
        int timeP = maxAllowedSession;

        if (cs.getRemainingTime() < timeP) {
            timeP = cs.getRemainingTime();
        }
        // } else {

        //     timeP = maxAllowedSession;
        // }
        cs.talk(timeP);
        currentTime += timeP;

        while (!schedule.isEmpty() &&
               schedule.peek().getArrivalTime() <= currentTime) {
            waitingQuene.enqueue(schedule.dequeue());
        }
        if (cs.getRemainingTime() > 0) {
            waitingQuene.enqueue(cs);
        } else {
            int time =
                currentTime - (cs.getArrivalTime() + cs.getRequestedTime());
            totalTime += time;
            studentFinished++;

            cout << totalTime << endl;
        }
    }
    return (float)totalTime / totalStudents;

    // while (!schedule.isEmpty()) {
    //     Student s = schedule.dequeue();
    //     cout << s.getName() << " is requesting " << s.getRemainingTime()
    //          << ", and current time " << currentTime
    //          << " and timeWaiting: " << timeWaited << " and arrival time is "
    //          << s.getArrivalTime() << endl;
    //     string name = s.getName();

    //     if (s.getRemainingTime() > maxAllowedSession) {
    //         cout << s.getName() << " remaining time " << s.getRemainingTime()
    //              << " is more than the " << maxAllowedSession << endl;
    //         s.talk(maxAllowedSession);
    //         currentTime += maxAllowedSession;

    //         cout << s.getName() << " has " << s.getRemainingTime()
    //              << " time left. and current time is " << currentTime
    //              << ", and waiting time is " << timeWaited << endl;
    //         schedule.enqueue(s);

    //         // cout << "This is schedule.size(): " << schedule.size() <<
    //         endl;

    //     } else {
    //         if (currentTime < s.getArrivalTime()) {
    //             timeWaited += s.getArrivalTime() - currentTime;
    //             currentTime = s.getArrivalTime();
    //             s.talk(s.getRemainingTime());
    //         } else {
    //             timeWaited = currentTime - s.getArrivalTime();
    //             currentTime += s.getRemainingTime();
    //             s.talk(s.getRemainingTime());
    //         }
    //         // cout << "This is schedule.size(): " << schedule.size() <<
    //         endl;
    //         // schedule.enqueue(s);
    //         cout << s.getName() << " has " << s.getRemainingTime()
    //              << " time left. and current time is " << currentTime
    //              << ", and waiting time is " << timeWaited << endl;
    //     }

    //     // cout << "Returning this " << timeWaited/schedule.size() << " cuz "
    //     <<
    //     // timeWaited << "/" << schedule.size() << endl; cout << "It ran " <<
    //     // running << " cuz " << schedule.size() << endl;
    // }
    // return timeWaited / total;
}

float averageWaitingTimeFirstComeFirstServed(Queue<Student> schedule) {
    float currentTime = 0;
    float timeWaited = 0;

    for (int i = 0; i < schedule.size(); i++) {
        int timeRequested = schedule[i].getRequestedTime();
        int arrivalTime = schedule[i].getArrivalTime();

        if (currentTime > arrivalTime) {
            timeWaited += currentTime - arrivalTime;
            currentTime += timeRequested;
        } else {
            currentTime += timeRequested;
        }
    }

    cout << "average: " << timeWaited / schedule.size() << endl;
    return timeWaited / schedule.size();
}