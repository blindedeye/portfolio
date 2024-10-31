#include <iostream>
#include "unionFind.h"

using namespace std;

/** Constructor. 
 * @param N Number of nodes.
 */
UnionFind::UnionFind(const int &N)
{
    id = new int[N];
    size = new int[N];

    // Initialize id and size arrays
    for (int i = 0; i < N; i++) 
    {
        id[i] = i;
        size[i] = 1;
    }
}

/** Deconstructor. */
UnionFind::~UnionFind()
{
    delete[] id;
    delete[] size;
}

/** Finds the parent of a node without compressing the path.
 *  @param node Node to be found.
 *  @return grandparent Least common ancestor for node.
 */
int UnionFind::quickFind(const int &node)
{
    int grandparent = node;
    
    // Find least common ancestor
    while (grandparent != id[grandparent])
    {
        grandparent = id[grandparent];
    }

    return grandparent;
}

/** Finds the parent of a node while compressing the path.
 *  @param node Node to be found.
 *  @return grandparent Least common ancestor for node.
 */
int UnionFind::find(const int &node)
{
    int parent = node;
    int grandparent = quickFind(node);

    // Compress path
    while (parent != grandparent)
    {
        int newParent = id[parent];
        id[parent] = grandparent;
        parent = newParent;
    }

    return grandparent;
}

/** Returns two nodes' least common ancestor, or returns -1 if no connection exists.
 *  @param p First node to be found.
 *  @param q Second node to be found.
 *  @return Least common ancestor if nodes are connected, or -1 if nodes are not connected.
*/
int UnionFind::findConnection(int p, int q)
{
    p = find(p);
    q = find(q);

    if (p == q)
        return p;
    return -1;
}

/** Determines whether a connection exists between two nodes.
 *  @param p First node to be found.
 *  @param q Second node to be found.
 *  @return true if nodes are connected, or false if nodes are not connected.
 */
bool UnionFind::connected(const int &p, const int &q)
{
    return (findConnection(p,q) > -1);
    return false;
}

/** Unifies disjoint sets for two given nodes.
 *  @param p First node to be connected.
 *  @param q Second node to be connected.
 */
void UnionFind::makeUnion(const int &p, const int &q)
{
    // Find least common ancestors and compress path
    int i = find(p);
    int j = find(q);

    if (i != j) 
    {
        // If size of p is smaller than q, then append p to q
        if (size[i] < size[j])
        {
            id[i] = j;
            size[j] += size[i];
        }
        else // Else append q to p
        {
            id[j] = i;
            size[i] += size[j];
        }

        // Complete residual path compression
        find(p);
        find(q);
    }
}

/** Returns the number of nodes in the parent tree.
 *  @param node Node to be queried.
 *  @return size Size of tree.
 */
int UnionFind::query(const int &node)
{
    return size[find(node)];
}