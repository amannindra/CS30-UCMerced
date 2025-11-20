#include <igloo/igloo.h>
#include <stdexcept>
#include <unistd.h>
#include <Queue.h>
#include <Student.h>
#include <Simulations.h>

using namespace igloo;

Context(TestOfficeHoursSimulator){
    Spec(Test1_FCFS_Arrive_Together){
        Queue<Student> schedule;
        schedule.enqueue(Student("Alice", 5, 0));
        schedule.enqueue(Student("Bob", 1, 0));
        schedule.enqueue(Student("Cathy", 2, 0));

        float actual = averageWaitingTimeFirstComeFirstServed(schedule);
        float expected = 3.667;

        Assert::That(actual, EqualsWithDelta(expected, 0.001));
    }

    Spec(Test2_RR_Arrive_Together){
        Queue<Student> schedule;
        schedule.enqueue(Student("Alice", 5, 0));
        schedule.enqueue(Student("Bob", 1, 0));
        schedule.enqueue(Student("Cathy", 2, 0));

        float actual = averageWaitingTimeRoundRobin(schedule, 5);
        float expected = 3.667;

        Assert::That(actual, EqualsWithDelta(expected, 0.001));
    }

    Spec(Test3_FCFS_Abuser_Arrive_Together){
        Queue<Student> schedule;
        schedule.enqueue(Student("Alice", 59, 0));
        schedule.enqueue(Student("Bob", 2, 0));
        schedule.enqueue(Student("Cathy", 2, 0));

        float actual = averageWaitingTimeFirstComeFirstServed(schedule);
        float expected = 40;

        Assert::That(actual, EqualsWithDelta(expected, 0.001));
    }

    Spec(Test4_RR_Abuser_Arrive_Together){
        Queue<Student> schedule;
        schedule.enqueue(Student("Alice", 59, 0));
        schedule.enqueue(Student("Bob", 2, 0));
        schedule.enqueue(Student("Cathy", 2, 0));

        float actual = averageWaitingTimeRoundRobin(schedule, 5);
        float expected = 5.333;

        Assert::That(actual, EqualsWithDelta(expected, 0.001));
    }

    Spec(Test5_FCFS_Spread_Arrivals){
        Queue<Student> schedule;
        schedule.enqueue(Student("Alice", 10, 0));
        schedule.enqueue(Student("Bob", 4, 5));
        schedule.enqueue(Student("Cathy", 2, 7));

        float actual = averageWaitingTimeFirstComeFirstServed(schedule);
        float expected = 4;

        Assert::That(actual, EqualsWithDelta(expected, 0.001));
    }

    Spec(Test6_RR_Spread_Arrivals){
        Queue<Student> schedule;
        schedule.enqueue(Student("Alice", 10, 0));
        schedule.enqueue(Student("Bob", 4, 5));
        schedule.enqueue(Student("Cathy", 2, 7));

        float actual = averageWaitingTimeRoundRobin(schedule, 5);
        float expected = 3.667;

        Assert::That(actual, EqualsWithDelta(expected, 0.001));
    }

    Spec(Test7_FCFS_Abuser_Spread_Arrivals){
        Queue<Student> schedule;
        schedule.enqueue(Student("Alice", 59, 0));
        schedule.enqueue(Student("Bob", 4, 5));
        schedule.enqueue(Student("Cathy", 2, 7));

        float actual = averageWaitingTimeFirstComeFirstServed(schedule);
        float expected = 36.667;

        Assert::That(actual, EqualsWithDelta(expected, 0.001));
    }

    Spec(Test8_RR_Abuser_Spread_Arrivals){
        Queue<Student> schedule;
        schedule.enqueue(Student("Alice", 59, 0));
        schedule.enqueue(Student("Bob", 4, 5));
        schedule.enqueue(Student("Cathy", 2, 7));

        float actual = averageWaitingTimeRoundRobin(schedule, 5);
        float expected = 4.333;

        Assert::That(actual, EqualsWithDelta(expected, 0.001));
    }
};

int main(int argc, const char* argv[]){
    TestRunner::RunAllTests(argc, argv);
}