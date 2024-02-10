#ifndef ARRAY_H
#define ARRAY_H

#include <string>

using namespace std;

class UnsortedArray
{
  protected:
    string *pairs;
    long long *countsOfPairs;
    long long arraySize;
    long long countOfDiffPairs;

  public:
    UnsortedArray();
    ~UnsortedArray();

    long long getArraySize();
    long long getCountOfDiffPairs();
    string getPair(long long pos);

    long long searchPair(string pair);
    long long countOfPair(string pair);
    void add(string pair);
};

#endif