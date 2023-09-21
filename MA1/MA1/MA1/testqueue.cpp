#include "queue.h"
#include <iostream>

/*
Test Case: testSize
Description: Verifies the size method of the queue class and correctly reports the size of a newly created queue.
Expected Outcome: The test should pass showing that the size method is working correctly for a new queue.
 */
void testSize() {
    queue q;
    if (q.size() == 0) {
        std::cout << "testSize passed\n";
    }
    else {
        std::cout << "testSize failed\n";
    }
}

/*
 Test Case: testIsEmpty
 Description: Verifies the isEmpty method of the queue class correctly identifies a newly created queue as empty.
 Expected Outcome: The test should pass indicating that the isEmpty method is working correctly for a new queue.
 */
void testIsEmpty() {
    queue q;
    if (q.isEmpty()) {
        std::cout << "testIsEmpty passed\n";
    }
    else {
        std::cout << "testIsEmpty failed\n";
    }
}

/*
Test Case: testIsFull
Description: Verifies that the isFull method of the queue class correctly identifies when the queue is full.
 * Expected Outcome: The test should pass indicating that the isFull method is working correctly.
 */
void testIsFull() {
    queue q;
    for (int i = 0; i < 10; ++i) {
        q.enqueue(i);
    }
    if (q.isFull()) {
        std::cout << "testIsFull passed\n";
    }
    else {
        std::cout << "testIsFull failed\n";
    }
}

/*
 Test Case: testDequeue1
 Description: Verifies that the dequeue method of the queue class correctly removes an element from a non-empty queue.
 Expected Outcome: The test should pass indicating that the dequeue method is working correctly for a non-empty queue.
 */
void testDequeue1() {
    queue q;
    q.enqueue(1);
    q.dequeue();
    if (q.size() == 0) {
        std::cout << "testDequeue1 passed\n";
    }
    else {
        std::cout << "testDequeue1 failed\n";
    }
}

/*
 Test Case: testDequeue2
 Description: Verifies that the dequeue method of the queue class correctly identifies an underflow condition.
 Expected Outcome: The test should pass, indicating that the dequeue method correctly handles underflow conditions.
 */
void testDequeue2() {
    queue q;
    if (!q.dequeue()) {
        std::cout << "testDeque2 passed\n";
    }
    else {
        std::cout << "testDequeue2 failed\n";
    }
}

/*
 Test Case: testEnqueue1
 Description: Verifies that the enqueue method of the queue class correctly adds an element to a non-full queue.
 Expected Outcome: The test should pass indicating that the enqueue method is working correctly for a non-full queue.
 */
void testEnqueue1() {
    queue q;
    q.enqueue(5);
    if (q.peek() == 5) {
        std::cout << "testEnqueue1 passed\n";
    }
    else {
        std::cout << "testEnqueue1 failed\n";
    }
}

/*
 Test Case: testEnqueue2
 Description: Verifies that the enqueue method of the queue class correctly identifies an overflow condition.
 Expected Outcome: The test should pass indicating that the enqueue method correctly handles overflow conditions.
 */
void testEnqueue2() {
    queue q;
    for (int i = 0; i < 10; ++i) {
        q.enqueue(i);
    }
    if (!q.enqueue(10)) {
        std::cout << "testEnqueue2 passed\n";
    }
    else {
        std::cout << "testEnqueue2 failed\n";
    }
}

/*
 Test Case: testPeek1
 Description: Verifies that the peek method of the queue class correctly returns the front element from a non-empty queue.
 Expected Outcome: The test should pass indicating that the peek method is working correctly for a non-empty queue.
 */
void testPeek1() {
    queue q;
    q.enqueue(1);
    if (q.peek() == 1) {
        std::cout << "testPeek1 passed\n";
    }
    else {
        std::cout << "testPeek1 failed\n";
    }
}

/*
 Test Case: testPeek2
 Description: Verifies that the peek method of the queue class correctly identifies an underflow condition when trying to peek into an empty queue.
 Expected Outcome: The test should pass, indicating that the peek method correctly handles underflow conditions.
 */
void testPeek2() {
    queue q;
    if (q.peek() == INT_MIN) {
        std::cout << "testPeek2 passed\n";
    }
    else {
        std::cout << "testPeek2 failed\n";
    }
}
