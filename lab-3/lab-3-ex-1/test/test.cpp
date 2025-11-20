#include <LinkedList.h>
#include <igloo/igloo.h>
#include <unistd.h>

using namespace igloo;

Context(TestLinkedList) {
    int oldSTDOUT;
    int oldSTDERR;

    // Suppress outputs so that program being
    // tested does not pollute the console
    void SetUp() {
        oldSTDOUT = dup(1);
        oldSTDERR = dup(2);
        freopen("/dev/null", "w", stdout);
        freopen("/dev/null", "w", stderr);
    }

    // Restore output ability after tests are complete
    void TearDown() {
        fflush(stdout);
        fflush(stderr);
        dup2(oldSTDOUT, 1);
        dup2(oldSTDERR, 2);
    }

    Spec(TestWithInt) {
        LinkedList<int> numbers;
        numbers.append(5);
        numbers.append(7);
        numbers.append(2);

        Assert::That(numbers.front->data, Equals(5));
        Assert::That(numbers.front->next->data, Equals(7));
        Assert::That(numbers.front->next->next->data, Equals(2));
    }

    Spec(TestWithString) {
        LinkedList<std::string> names;
        names.append("Alice");
        names.append("Trudy");
        names.append("Bob");

        Assert::That(names.front->data, Equals("Alice"));
        Assert::That(names.front->next->data, Equals("Trudy"));
        Assert::That(names.front->next->next->data, Equals("Bob"));
    }

    Spec(TestRemoveFirstGeneral) {
        LinkedList<int> nums;
        nums.append(5);
        nums.append(7);
        nums.append(2);

        int x = nums.removeFirst();
        Assert::That(x, Equals(5));
        Assert::That(nums.front->data, Equals(7));
        Assert::That(nums.front->next->data, Equals(2));
    }

    Spec(TestRemoveFirstFromOne) {
        LinkedList<int> nums;
        nums.append(9);

        int x = nums.removeFirst();
        Assert::That(x, Equals(9));
        Assert::That(nums.front == nullptr, IsTrue());
        Assert::That(nums.back == nullptr, IsTrue());
    }

    Spec(TestRemoveFirstFromEmpty) {
        LinkedList<int> nums;

        AssertThrows(std::logic_error, nums.removeFirst());
    }

    Spec(TestRemoveLastGeneral) {
        LinkedList<int> nums;
        nums.append(5);
        nums.append(7);
        nums.append(2);

        int x = nums.removeLast();
        Assert::That(x, Equals(2));
        Assert::That(nums.front->data, Equals(5));
        Assert::That(nums.front->next->data, Equals(7));
    }

    Spec(TestRemoveLastFromOne) {
        LinkedList<int> nums;
        nums.append(9);

        int x = nums.removeLast();
        Assert::That(x, Equals(9));
        Assert::That(nums.front == nullptr, IsTrue());
        Assert::That(nums.back == nullptr, IsTrue());
    }

    Spec(TestRemoveLastFromEmpty) {
        LinkedList<int> nums;

        AssertThrows(std::logic_error, nums.removeLast());
    }

    Spec(TestReverse) {
        LinkedList<int> nums;
        nums.append(1);
        nums.append(2);
        nums.append(3);
        nums.append(4);
        nums.append(5);

        Link<int> *first = nums.front;
        Link<int> *second = nums.front->next;
        Link<int> *third = nums.front->next->next;
        Link<int> *fourth = nums.front->next->next->next;
        Link<int> *fifth = nums.front->next->next->next->next;

        nums.reverse();

        Assert::That(first->data, Equals(1));
        Assert::That(second->data, Equals(2));
        Assert::That(third->data, Equals(3));
        Assert::That(fourth->data, Equals(4));
        Assert::That(fifth->data, Equals(5));

        Link<int> *one = nums.front;
        Link<int> *two = nums.front->next;
        Link<int> *three = nums.front->next->next;
        Link<int> *four = nums.front->next->next->next;
        Link<int> *five = nums.front->next->next->next->next;

        Assert::That(one->data, Equals(5));
        Assert::That(two->data, Equals(4));
        Assert::That(three->data, Equals(3));
        Assert::That(four->data, Equals(2));
        Assert::That(five->data, Equals(1));

        Assert::That(first, Equals(five));
        Assert::That(second, Equals(four));
        Assert::That(third, Equals(three));
        Assert::That(fourth, Equals(two));
        Assert::That(fifth, Equals(one));
    }

    Spec(TestCopyConstructor) {
        std::cout << "TestCopyConstructor" << std::endl;
        LinkedList<int> original;
        original.append(10);
        original.append(20);
        original.append(30);

        // Create a copy using the copy constructor
        LinkedList<int> copy = original;

        // Assert that the copy has the same elements as the original
        Assert::That(copy.getSize(), Equals(3));
        Assert::That(copy.front->data, Equals(10));
        Assert::That(copy.front->next->data, Equals(20));
        Assert::That(copy.front->next->next->data, Equals(30));

        // Ensure that the copy is independent of the original
        copy.removeFirst();
        Assert::That(copy.getSize(), Equals(2));
        Assert::That(original.getSize(),
                     Equals(3)); // Original list should remain unchanged
    }

    Spec(TestAssignmentOperator) {
        LinkedList<int> original;
        original.append(10);
        original.append(20);
        original.append(30);

        // Create a copy using the copy constructor
        LinkedList<int> copy;
        copy.append(100);
        copy = original;

        // Assert that the copy has the same elements as the original
        Assert::That(copy.getSize(), Equals(3));
        Assert::That(copy.front->data, Equals(10));
        Assert::That(copy.front->next->data, Equals(20));
        Assert::That(copy.front->next->next->data, Equals(30));

        // Ensure that the copy is independent of the original
        copy.removeFirst();
        Assert::That(copy.getSize(), Equals(2));
        Assert::That(original.getSize(),
                     Equals(3)); // Original list should remain unchanged
    }

    Spec(TestAccessByIndex) {
        LinkedList<int> nums;
        nums.append(5);
        nums.append(10);
        nums.append(15);

        // Assert that elements are accessible by index
        Assert::That(nums[0], Equals(5));
        Assert::That(nums[1], Equals(10));
        Assert::That(nums[2], Equals(15));
    }

    Spec(TestAccessByIndexOutOfBounds) {
        LinkedList<int> nums;
        nums.append(100);
        nums.append(200);

        // Ensure accessing out of bounds throws an exception
        AssertThrows(std::logic_error, nums[3]);
    }

    Spec(TestAccessByIndexOutOfBoundsNegative) {
        LinkedList<int> nums;
        nums.append(100);
        nums.append(200);

        // Ensure accessing out of bounds throws an exception
        AssertThrows(std::logic_error, nums[-1]);
    }

    Spec(TestInsertFront) {
        LinkedList<int> list;
        list.append(2);
        list.append(3);

        list.insert(1, 0); // Insert at the front

        Assert::That(list[0], Equals(1));
        Assert::That(list[1], Equals(2));
        Assert::That(list[2], Equals(3));
        Assert::That(list.getSize(), Equals(3));
    }

    Spec(TestInsertMiddle) {
        LinkedList<int> list;
        list.append(1);
        list.append(3);

        list.insert(2, 1); // Insert between 1 and 3

        Assert::That(list[0], Equals(1));
        Assert::That(list[1], Equals(2));
        Assert::That(list[2], Equals(3));
    }

    Spec(TestInsertEnd) {
        LinkedList<int> list;
        list.append(1);
        list.append(2);

        list.insert(3, 2); // Insert at the end

        Assert::That(list[2], Equals(3));
        Assert::That(list.getSize(), Equals(3));
    }

    Spec(TestInsertInvalidIndex) {
        LinkedList<int> list;
        list.append(1);

        AssertThrows(std::logic_error, list.insert(5, -1));
        AssertThrows(std::logic_error, list.insert(5, 3)); // size is 1
    }

    Spec(TestRemoveFront) {
        
        LinkedList<int> list;
        list.append(10);
        list.append(20);
        list.append(30);

        int val = list.remove(0);

        Assert::That(val, Equals(10));
        Assert::That(list[0], Equals(20));
        Assert::That(list.getSize(), Equals(2));
    }

    Spec(TestRemoveMiddle) {
        LinkedList<int> list;
        list.append(10);
        list.append(20);
        list.append(30);

        int val = list.remove(1);

        Assert::That(val, Equals(20));
        Assert::That(list[1], Equals(30));
        Assert::That(list.getSize(), Equals(2));
    }

    Spec(TestRemoveEnd) {
        LinkedList<int> list;
        list.append(10);
        list.append(20);
        list.append(30);

        int val = list.remove(2);

        Assert::That(val, Equals(30));
        Assert::That(list.getSize(), Equals(2));
    }

    Spec(TestRemoveInvalidIndex) {
        LinkedList<int> list;
        list.append(10);

        AssertThrows(std::logic_error, list.remove(-1));
        AssertThrows(std::logic_error, list.remove(1)); // size is 1
    }
};

int main(int argc, const char **argv) {
    return TestRunner::RunAllTests(argc, argv);
}