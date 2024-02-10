#ifndef SORTEDARRAY_H
#define SORTEDARRAY_H

#include "UnsortedArray.h"
#include <iostream>

using namespace std;

class SortedArray : public UnsortedArray
{
  public:
    long long searchPair(string pair);
    long long countOfPair(string pair);
    void add(string pair);
};

#endif