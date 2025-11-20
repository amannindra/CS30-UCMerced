#ifndef SIMULATIONS_H
#define SIMULATIONS_H

#include <Queue.h>
#include <Student.h>

float averageWaitingTimeFirstComeFirstServed(Queue<Student> schedule);

float averageWaitingTimeRoundRobin(Queue<Student> schedule, int maxAllowedSession);

#endif