#pragma once
#include <iostream>

using namespace std;

/**
* @class StackException
* Prints if a stack exception has occured.
*/
class StackException
{
    public:
    void print()
    {
        cout << "Stack Exception Occurred" << endl;
    }
};

/**
* @class Stack
* Stack with resizing array.
*
* Templated stack with resizing array that halves if quarter full and doubles when full.
*/
template <typename T> class Stack
{
    /**
    * values is the array that holds the objects in the stack
    * capacity is the number of objects able to fit in the array
    * position is the number in the array a certain object is at
    */
    T * values;
    int capacity;
    int position;

    public:
    /**
    * Stack constructor.
    *
    * Constructs the stack class by setting the capacity and position value along with the capacity of the values array.
    * @param _capacity Sets the default capacity to 10.
    * @param _position Sets the default position to -1.
    */
    Stack(int _capacity = 10, int _position = -1)
    {
        values = new T[_capacity];
        capacity = _capacity;
        position = _position;
    }

    /**
    * Stack class deconstructor.
    */
    ~Stack()
    {
        delete[] values;
    }

    /**
    * @return capacity the current capacity of the stack.
    */
    int getCapacity() const
    {
        return capacity;
    }

    /**
    * Stack push function with resizing.
    *
    * Function that takes in a value and places it on the top of the stack,
    * also doubles if the array is full and halves when a quarter full.
    * @param newValue Takes in a value to place on top of the stack.
    */
    void push(T newValue)
    {
        // Doubling
        if (isFull())
        {
            int newCapacity = capacity * 2;
            T *newValues = new T[newCapacity];
            
            // Copy existing elements to the new array.
            for (int i = 0; i < capacity; i++)
            {
                newValues[i] = values[i];
            }

            delete[] values;
            values = newValues;
            capacity = newCapacity;

            //cout << "<Stack> Array doubled to capacity " << capacity << endl;
        }

        position++;
        values[position] = newValue;
    }

    /**
    * Stack pop function.
    *
    * Removes the value on the top of the stack and returns it.
    * @return value at the top of the stack.
    */
    T pop()
    {
        // Halving
        if (position < capacity / 4)
        {
            int newCapacity = capacity / 2;
            T* newValues = new T[newCapacity];

            // Copy existing elements to the new array.
            for (int i = 0; i <= position; i++)
            {
                newValues[i] = values[i];
            }

            delete[] values;
            values = newValues;
            capacity = newCapacity;

            //cout << "<Stack> Array halved to capacity " << capacity << endl;
        }

        if (!isEmpty())
        {
            T poppedValue = values[position];
            position--;

            return poppedValue;
        }
        throw StackException();
    }

    /**
    * Stack top returns the value at the top of the stack.
    * @return value at the top of the stack.
    */
    T top() const
    {
        if (!isEmpty())
            return values[position];
        throw StackException();
    }

    /**
    * @return true if stack is empty or false if the stack not empty.
    */
    bool isEmpty() const
    {
        return (position == -1); 
    }

    /**
    * @return true if the stack is full and false if the stack is not full.
    */
    bool isFull() const
    {
        return (position == capacity - 1); 
    }
};

void callStack(int);