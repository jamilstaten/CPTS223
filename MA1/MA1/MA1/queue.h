#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <climits>

#define SIZE 10

class queue
{
private:
    int* arr;
    int capacity;
    int front;
    int rear;
    int count;

public:
    queue(int size = SIZE);
    ~queue();
    bool dequeue();
    bool enqueue(int x);
    int peek();
    int size();
    bool isEmpty();
    bool isFull();
};

#endif 

