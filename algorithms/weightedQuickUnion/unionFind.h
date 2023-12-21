#pragma once
#include <iostream>

using namespace std;

class UnionFind
{
    int *id, *size;

    public:

    UnionFind(const int &);

    ~UnionFind();

    int quickFind(const int &);

    int find(const int &);

    int findConnection(int, int);

    bool connected(const int &, const int &);

    void makeUnion(const int &, const int &);
    
    int query(const int &);
};