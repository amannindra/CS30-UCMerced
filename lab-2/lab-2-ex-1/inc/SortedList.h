#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <ArrayList.h>
#include <sys/types.h>

template <typename T> class SortedList : public ArrayList<T> {
private:
    int lower_bound_index(const T &value) const {
        int lo = 0;
        int hi = this->count - 1;
        int ans = this->count; // default to end (insert at end)
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (this->data[mid] >= value) {
                ans = mid;
                hi = mid - 1;

            } else {
                lo = mid + 1;
            }
        }
        return ans;
    }

public:
    void append(T value) {
        int idx = lower_bound_index(value);

        for (int i = this->count; i > idx; --i) {
            this->data[i] = this->data[i - 1];
        }

        this->data[idx] = value;

            this->count++;
        if (this->count == this->capacity) {
            this->inflate();
        }
    }

    bool search(T value) const {

        int left = 0;
        int right = this->count - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2; // avoid overflow
            if (this->data[mid] == value) {
                return true; // found target
            } else if (this->data[mid] < value) {
                left = mid + 1; // search right half

            } else {
                right = mid - 1; // search left half
            }
        }
        return false;

        // for(int i = 0; i < this->count;i++){
        //     if(value == this->data[i]){
        //         return true;
        //     }
        // }
        // return false;
    }


	void merge(const SortedList<T> &other) {

        int cou = this->count + other.count;

        int newCapacity = 1;

        while (newCapacity < cou)
            newCapacity *= 2;

        T *newData = new T[newCapacity];

        int i = 0;

        int j = 0;
        int k = 0;
        while (i < this->count && j < other.count) {
            if (this->data[i] <= other.data[j])
                newData[k++] = this->data[i++];
            else
                newData[k++] = other.data[j++];
        }
        while (i < this->count)
            newData[k++] = this->data[i++];
        while (j < other.count)
            newData[k++] = other.data[j++];
        
        delete[] this->data;

        this->data = newData;
        this->count = cou;
        this->capacity = newCapacity;
    }
    // Friendship declaration for unit testing (we want access to everything
    // when testing).
    friend struct TestSortedList;
};

#endif