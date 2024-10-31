#pragma once
#include <iostream>

using namespace std;

/**
* @class QueueException
* Prints if queue exception has occured.
*/
class QueueException
{
    public:
    void print()
    {
        cout << "Queue Exception Occurred" << endl;
    }
};

/**
* @class Queue
* Queue with resizing array.
* 
* Queue with resizing array that halves if quarter full and doubles when full.
*/
template <typename T> class Queue 
{
    private:
    /**
    * data is the array that holds the objects in the queue
    * capacity is the number of objects able to fit in the array
    * head is the object at the beginning of the queue
    * tail is the object at the end of the queue
    * size is the number of objects in the array
    */
    T* data;
    int capacity;    
    int head;    
    int tail;         
    int size;         

    public:
    /**
    * Queue constructor.
    *
    * Constructs the queue class by setting the capacity value along with the capacity 
    * of the data array, setting head and tail to -1 and the size to 0.
    * @param _capacity Initial capacity of queue, with the default capacity set to 10.
    */
    Queue(int _capacity = 10)
    {
        capacity = _capacity;
        data = new T[capacity];
        head = tail = -1;
        size = 0;
    }

    /**
    * Queue doubling function.
    *
    * Function that doubles the queue's array if the queue is full.
    */
    void grow()
    {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];

        // Copy elements to the new array
        for (int i = 0; i < size; ++i)
        {
            newData[i] = data[(head + i) % capacity];
        }

        head = 0;
        tail = size - 1;

        delete[] data;

        capacity = newCapacity;
        data = newData;

        //cout << "<Queue> Array doubled to capacity " << capacity << endl;
    }

    /**
    * Queue halving function.
    *
    * Function that halves the queue's array if the queue is a quarter full.
    */
    void shrink()
    {
        if (size <= capacity / 4)
        {
            int newCapacity = capacity / 2;
            T* newData = new T[newCapacity];

            // Copy elements to the new array
            for (int i = 0; i < size; ++i)
            {
                newData[i] = data[(head + i) % capacity];
            }

            head = 0;
            tail = size - 1;

            delete[] data;

            capacity = newCapacity;
            data = newData;

            //cout << "<Queue> Array halved to capacity " << capacity << endl;
        }
    }

    /**
    * Queue class deconstructor.
    */
    ~Queue()
    {
        delete[] data;
    }

    /**
    * @return true if stack is empty or false if the stack is not empty.
    */
    bool isEmpty() const
    {
        return size == 0;
    }

    /**
    * @return size the current size of the queue.
    */
    int getSize() const
    {
        return size;
    }

    /**
    * @return capacity the current capacity of the stack.
    */
    int getCapacity() const
    {
        return capacity;
    }

    /**
    * Queue push function.
    *
    * Takes in a value and adds it to the tail of the queue.
    * @param item Takes in a value.
    */
    void enqueue(const T& item)
    {
        if (size == capacity) 
        {
            grow();
        }

        if (isEmpty()) 
        {
            head = tail = 0;
        } else 
        {
            tail = (tail + 1) % capacity;
        }

        data[tail] = item;
        size++;
    }

    /**
    * Queue pop function.
    *
    * Takes the head value off the queue and returns it as long as the queue is not empty.
    * @return value at the beginning of the queue.
    */
    T dequeue()
    {
        if (isEmpty())
        {
            throw QueueException();
        }

        T item = data[head];
        head = (head + 1) % capacity;
        size--;

        shrink();

        return item;
    }

    /**
    * @return the value at the beginning of the queue.
    */
    T peekhead() const
    {
        if (isEmpty())
        {
            throw QueueException();
        }
        return data[head];
    }
};

void callQueue(int);