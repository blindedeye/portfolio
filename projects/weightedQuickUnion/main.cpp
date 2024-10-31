/** Weighted Quick-Union Algorithm with Path Compression
 * 
 *  @author Jake Peterson
 *  @author Michael A. Nuttall
 *  @author Ellena Schmitt
 *  
 *  The program tests our weighted quick-union algorithm with path compression. First, the number of elements
 *  is taken as input. Then, a series of random union operations is generated.  Finally, the size of the tree
 *  for each node is output.
 * 
 *  For organizational purposes, all header files used are listed in a single "headers.h" header file.
 */

#include <iostream>
#include "headers.h"

using namespace std;

int main()
{
    int num, p, q;

    cout << "Enter the number of elements: ";
    cin >> num;
    UnionFind newUnion(num);

    // Generate random numbers and save them to an array
    int size = num * 2;
    int randNum[size];
    randomGenerator(randNum, num);

    // Output list of random numbers generated
    cout << "Numbers generated: ";
    for(int i = 0; i < size; i++)
    {
        cout << randNum[i] << " ";
    }
    cout << endl;

    // Completes a union operation for each pair of randomly generated numbers
    for(int i = 1; i < size; i += 2)
    {
        p = randNum[i - 1];
        q = randNum[i];
        cout << "Current query for p & q: " << newUnion.query(p) << " & " << newUnion.query(q) << endl;
        newUnion.makeUnion(p, q);
        cout << "makeUnion(" << p << "," << q << ")" << endl;
    }

    // Queries each node in the array
    for(int j = 0; j < size; j++)
    {
        p = randNum[j];
        cout << "Query for p: " << newUnion.query(p) << endl;
    }

    return 0;
}