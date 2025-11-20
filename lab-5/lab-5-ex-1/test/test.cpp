#include <igloo/igloo.h>
#include <TimeSupport.h>
#include <RandomSupport.h>
#include <HashTable.h>

using namespace igloo;

Context(TestProgram){
    Spec(Test1_Insert_Search_Simple){
        HashTable ht(10);

        ht.insert(1);
        ht.insert(2);
        ht.insert(3);
        ht.insert(4);
        ht.insert(5);

        bool foundFour = ht.search(4);
        bool foundSeven = ht.search(7);

        Assert::That(foundFour, IsTrue());
        Assert::That(foundSeven, IsFalse());
        Assert::That(ht.size, Equals(5));  
    }

    Spec(Test2_Speed){
        const int N = 1000000;

        RNG rng(1, N * 100);

        HashTable hashTable(N / 10);

        Timestamp insertStart;

        for (int i = 0; i < N; i++){
            hashTable.insert(rng.get());
        }

        Timestamp insertEnd;

        int insertDuration = insertEnd - insertStart;

        Timestamp searchStart;

        for (int i = 0; i < N; i++){
            hashTable.search(-rng.get());
        }

        Timestamp searchEnd;

        int searchDuration = searchEnd - searchStart;

        Assert::That(insertDuration, IsLessThan(1000));
        Assert::That(searchDuration, IsLessThan(1000));
        Assert::That(hashTable.size, Equals(1000000));
    }
    
    Spec(Test3_Copy){
        HashTable ht;

        ht.insert(5);
        ht.insert(15);
        ht.insert(3);
        ht.insert(17);

        HashTable copy = ht;

        ht.insert(23);

        bool foundInFirst = false;
        for (int i = 0; i < ht.capacity; i++){
            if (ht.table[i].search(23)){
                foundInFirst = true;
                break;
            }
        }

        bool foundInSecond = false;
        for (int i = 0; i < copy.capacity; i++){
            if (copy.table[i].search(23)){
                foundInSecond = true;
                break;
            }
        }

        Assert::That(foundInFirst, IsTrue());
        Assert::That(ht.size, Equals(5));
        Assert::That(foundInSecond, IsFalse());
        Assert::That(copy.size, Equals(4));
    }

    Spec(Test4_Assign){
        HashTable ht;

        ht.insert(5);
        ht.insert(15);
        ht.insert(3);
        ht.insert(17);

        HashTable copy;
        copy = ht;

        ht.insert(23);

        bool foundInFirst = false;
        for (int i = 0; i < ht.capacity; i++){
            if (ht.table[i].search(23)){
                foundInFirst = true;
                break;
            }
        }

        bool foundInSecond = false;
        for (int i = 0; i < copy.capacity; i++){
            if (copy.table[i].search(23)){
                foundInSecond = true;
                break;
            }
        }

        Assert::That(foundInFirst, IsTrue());
        Assert::That(ht.size, Equals(5));
        Assert::That(foundInSecond, IsFalse());
        Assert::That(copy.size, Equals(4));
    }

    Spec(Test5_LoadFactor){
        const int N = 10000;

        RNG rng(1, N * 100);

        HashTable ht(N / 10);

        for (int i = 0; i < N; i++){
            ht.insert(rng.get());
        }

        float loadFactor = (float) ht.size / ht.capacity;

        
        Assert::That(loadFactor, IsLessThan(3));
        Assert::That(ht.size, Equals(10000));
        Assert::That(ht.capacity, Equals(4000));
    }
};

int main(int argc, const char* argv[]){
    TestRunner::RunAllTests(argc, argv);
}