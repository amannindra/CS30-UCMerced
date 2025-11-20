#include <igloo/igloo.h>
#include <unistd.h>
#include <ArrayList.h>
#include <SortedList.h>
#include <TimeSupport.h>

using namespace igloo;

Context(TestArrayList){
    int oldSTDOUT;
    int oldSTDERR;

    // Suppress outputs so that program being
    // tested does not pollute the console
    void SetUp() {
        oldSTDOUT = dup( 1 );
        oldSTDERR = dup( 2 );
        freopen( "/dev/null", "w", stdout );
        freopen( "/dev/null", "w", stderr );     
    }

    // Restore output ability after tests are complete
    void TearDown() {
        fflush( stdout );
        fflush( stderr );
        dup2( oldSTDOUT, 1 );
        dup2( oldSTDERR, 2 );
    }

    Spec(TestAppend){
        // std::cout << "TestAppend" << std::endl;
        SortedList<int> nums;
        nums.append(5);
        nums.append(3);
        nums.append(9);
        nums.append(7);
        nums.append(1);

        Assert::That(nums[0], Equals(1));
        Assert::That(nums[1], Equals(3));
        Assert::That(nums[2], Equals(5));
        Assert::That(nums[3], Equals(7));
        Assert::That(nums[4], Equals(9));

        Assert::That(nums.capacity, Equals(8));
        Assert::That(nums.count, Equals(5));

    }

    Spec(TestSearchSpeed){
            //    std::cout << "TestSearchSpeed" << std::endl;
        SortedList<int> nums;
        // We know the list will be sorted
        for (int i = 1; i <= 1000000; i++){
            nums.append(i);
        }

        Timestamp start;
        for (int i = 0; i < 1000; i++){
            nums.search(-1);
        }
        Timestamp end;

        int duration = end - start;

        Assert::That(duration, IsLessThan(100));

    }

    Spec(TestSearchCorrectness){
        //  std::cout << "TestSearchCorrectness" << std::endl;
        SortedList<int> nums;
        nums.append(5);
        nums.append(3);
        nums.append(9);
        nums.append(7);
        nums.append(1);

        Assert::That(nums.search(0), IsFalse());
        Assert::That(nums.search(1), IsTrue());
        Assert::That(nums.search(2), IsFalse());
        Assert::That(nums.search(3), IsTrue());
        Assert::That(nums.search(4), IsFalse());
        Assert::That(nums.search(5), IsTrue());
        Assert::That(nums.search(6), IsFalse());
        Assert::That(nums.search(7), IsTrue());
        Assert::That(nums.search(8), IsFalse());
        Assert::That(nums.search(9), IsTrue());
        Assert::That(nums.search(10), IsFalse());
    }

    Spec(TestMergeCorrectness){
        // std::cout << "TestMergeCorrectness" << std::endl;
        SortedList<int> one, two;

        one.append(1);
        one.append(2);
        one.append(5);
        one.append(6);

        two.append(3);
        two.append(4);

        one.merge(two);

        Assert::That(one.getSize(), Equals(6));
        Assert::That(one.capacity, Equals(8));
        Assert::That(one[0], Equals(1));
        Assert::That(one[1], Equals(2));
        Assert::That(one[2], Equals(3));
        Assert::That(one[3], Equals(4));
        Assert::That(one[4], Equals(5));
        Assert::That(one[5], Equals(6));
    }

    Spec(TestMergeCorrectnessAgain){
        // std::cout << "TestMergeCorrectnessAgain" << std::endl;
        SortedList<int> one, two;

        one.append(11);
        one.append(25);
        one.append(53);
        one.append(67);

        two.append(34);
        two.append(49);
        two.append(78);

        two.merge(one);

        Assert::That(two.getSize(), Equals(7));
        Assert::That(two.capacity, Equals(8));
        Assert::That(two[0], Equals(11));
        Assert::That(two[1], Equals(25));
        Assert::That(two[2], Equals(34));
        Assert::That(two[3], Equals(49));
        Assert::That(two[4], Equals(53));
        Assert::That(two[5], Equals(67));
        Assert::That(two[6], Equals(78));
    }

    Spec(TestMergeSpeed){
        // std::cout << "TestMergeSpeed" << std::endl;
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

        Assert::That(duration, IsLessThan(5));
    }
};


int main(int argc, const char** argv){
    return TestRunner::RunAllTests(argc, argv);
}