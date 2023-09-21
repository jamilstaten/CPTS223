#include "queue.h"

queue::queue(int size)
{
    arr = new int[size];
    capacity = size;
    front = 0;
    rear = -1;
    count = 0;
}

queue::~queue()
{
    delete[] arr;
}

bool queue::dequeue()
{
    if (isEmpty())
    {
        return false;
    }
    front = (front + 1) % capacity;
    count--;
    return true;
}

bool queue::enqueue(int item)
{
    if (isFull())
    {
        return false;
    }
    rear = (rear + 1) % capacity;
    arr[rear] = item;
    count++;
    return true;
}

int queue::peek()
{
    if (isEmpty())
    {
        return INT_MIN;
    }
    return arr[front];
}

int queue::size()
{
    return count;
}

bool queue::isEmpty()
{
    return (size() == 0);
}

bool queue::isFull()
{
    return (size() == capacity);
}


