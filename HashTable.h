#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

using namespace std;

class HashTable
{
  private:
    long long tableSize;
    long long countOfDiffPairs;
    string *table;
    long long *countsOfPairs;

  public:
    HashTable();
    ~HashTable();

    long long getTableSize();
    long long getCountOfDiffPairs();
    string getPair(long long pos);

    long long stringToInt(string pair);
    long long hashFunc1(long long x);
    long long hashFunc2(long long x);
    long long doubleHashFunc(long long x, long long i);
    bool isPrime(long long num);
    long long nextTableSize();
    long long searchPair(string pair);
    long long countOfPair(string pair);
    void add(string pair);
};

#endif