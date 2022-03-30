/*************************************************************************
    > File Name: design-circular-queue.cpp
    > Author: tiankonguse
    > Mail: i@tiankonguse.com
    > Created Time: Mon Apr  1 23:05:37 2019
 ************************************************************************/

#include "../../include/base.h"

class MyCircularQueue {
    vector<int> data;
    int head;
    int tail;
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) {
        data.resize(k);
        head = -1;
        tail = -1;
    }

    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if (isFull())
            return false;
        if (isEmpty())
            head = 0;
        tail = (tail + 1) % data.size();
        data[tail] = value;
        return true;
    }

    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if (isEmpty())
            return false;
        if (head == tail) {
            head = -1;
            tail = -1;
            return true;
        }
        head = (head + 1) % data.size();
        return true;
    }

    /** Get the front item from the queue. */
    int Front() {
        if (isEmpty())
            return -1;
        return data[head];
    }

    /** Get the last item from the queue. */
    int Rear() {
        if (isEmpty())
            return -1;
        return data[tail];
    }

    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        return head == -1;
    }

    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        return (tail + 1) % data.size() == head;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */

/*
    TEST_SMP1(ClassName, FunNAme, expectAns, firstData)
    TEST_SMP2(ClassName, FunNAme, expectAns, firstData, secondData)

    int first;
    int expectAns;


    first = 1;
    expectAns = 1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);
*/
int main() {
    int first;
    int expectAns;

    first = 113;
    expectAns = 112;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);

    first = 2;
    expectAns = -1;
    TEST_SMP1(Solution, smallestRepunitDivByK, expectAns, first);

    return 0;
}
