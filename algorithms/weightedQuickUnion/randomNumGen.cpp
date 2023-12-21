/** Linear Congruential Generator
 * 
 *  Generates random numbers using the formula
 *      X_n+1 = (aX_n + c) mod m
 *  Using the values
 *      mod m = 9, multiplier a = 7, increment c = 4, and seed x0 = 3.
 */

#include <iostream>

using namespace std;

/**
* Generates a random set of numbers.
*
* Uses a linear congruential function to generate a random list of numbers with a given max value and stores them in an array.
* @param randNum Array that holds the set of random numbers.
* @param m Maximum number that the generator can produce and also the amount of numbers that it generates.
*/
void randomGenerator(int* randNum, int m)
{
    int num;
    int a = 7;
    int c = 4;
    int max = 2 * m;

    for(int x = 0; x < max; x++)
    {
        num = ((a * x) + c) % m;
        randNum[x] = num;
        if(x == (m - 1))
        {
            a = num + 1;
            c += 2;
        }
    }
    cout << endl;
}