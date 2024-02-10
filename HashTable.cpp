#include <iostream>
#include "HashTable.h"

using namespace std;

//Constructor
HashTable::HashTable()
{
  tableSize = 5;
  table = new string[tableSize];
  countsOfPairs = new long long[tableSize];
  countOfDiffPairs = 0;
}

//Destructor
HashTable::~HashTable()
{
  delete[] table;
  delete[] countsOfPairs;
}

//Getters

//Returns the size of the table
long long HashTable::getTableSize()
{
  return tableSize;
}

//Returns the count of different pairs
long long HashTable::getCountOfDiffPairs()
{
  return countOfDiffPairs;
}

/*@param pos is the position of the pair we want to get

Returns the pair, located at that position of the table
Returns the empty string "" if there is no pair at the given position  */
string HashTable::getPair(long long pos)
{
  if(pos < tableSize)
  {
    return table[pos];
  }
  return "";
}

/*@param pair is the pair whose value we want

Returns a value for each string
Same strings will have the same value
Different strings can have the same value
That is not an issue, it just increases the amount of collisions */
long long HashTable::stringToInt(string pair)
{
  long long stringValue = 0;
  long long power = 1;
  const long long max = 1000000000003;
  const int base = 29;
    
  /*Multiplies each element with a base to the  
  power of its index and adds them all together.
  It makes sure the value does not surpass a 
  max  number by using the modulo operation %  */
  for(int i = 0; i < pair.length(); i++)
    {
      /*Characters outside of the ascii table can return negative numbers as 
      their value which can lead to the stringValue becoming negative
      and throwing an error.
      In that case, it uses 255 as its value to avoid that.  */
      if(pair[i] <= 0)
      {
        stringValue = (stringValue + 255 * power) % max;
        power = (power * base) % max;
      }
      else
      {
        stringValue = (stringValue + pair[i] * power) % max;
        power = (power * base) % max;
      }
    }
  return stringValue;
}

/*@param x is the given value of a pair from stringToInt()

First simple hash function  */
long long HashTable::hashFunc1(long long x)
{
  return x % tableSize;
}

/*@param x is the given value of a pair from stringToInt()

Second simple hash function  */
long long HashTable::hashFunc2(long long x)
{
  /*If the result is 0 and that position is occupied,
  then it will keep trying to add it to that position 
  until it runs out of attempts  */
  if((x / tableSize) % tableSize == 0)
  {
    return 1;
  }
  else
  {
    return (x / tableSize) % tableSize;
  }
}

/*@param x is the given value of a pair from stringToInt()
@param i is the index of failed attempts to find a free position

Double hashing
Complex hash function using two simple hash functions  */
long long HashTable::doubleHashFunc(long long x, long long i)
{
  return (hashFunc1(x) + i*hashFunc2(x)) % tableSize;
}

/*@param num is the number we want to check if it's prime or not

Returns true if the number is prime, if not, return false  */
bool HashTable::isPrime(long long num)
{
  if(num <= 1)
  {
    return false;
  }
  else
  {
    for(long long i = 2; i <= num/2; i++)
      {
        if(num % i == 0)
        {
          return false;
        }
      }
  }
  return true;
}

/*The size of the table needs to be a prime number so 
that the pairs can be added as effectively as possible
It returns the next prime number 
after the double size of the table  */
long long HashTable::nextTableSize()
{
  long long nextPrime = 2 * tableSize;
  while(true)
    {
      if(isPrime(nextPrime))
      {
        return nextPrime;
      }
      else
      {
        nextPrime++;
      }
    }
}

/*@param pair is the pair we are searching for

Searches the array for the given pair.
If found, it returns its position.
If not, it returns -1  */
long long HashTable::searchPair(string pair)
{
  //Calculates the string's value
  long long pairValue = stringToInt(pair);

  //Checks each possbile position until it finds it
  for(long long i = 0; i < tableSize; i++)
    {
      long long possiblePos = doubleHashFunc(pairValue, i);
      
      if(table[possiblePos] == pair)
      {
        return possiblePos;
      }
      /*If it finds an empty position, it means the pair does not 
      exist since it should have been placed in that empty position  */
      else if(table[possiblePos] == "")
      {
        return -1;
      }
    }
  return -1;
}

/*@param pair is the pair whose count we want to get

Returns how many pairs of the given pair exist in the array  */
long long HashTable::countOfPair(string pair)
{
  long long posOfPair = searchPair(pair);

  if(posOfPair != -1)
  {
    return countsOfPairs[posOfPair];
  }
  return 0;
}

/*@param pair is the pair we want to add to the array

Adds a pair to the array  */
void HashTable::add(string pair)
{
  /*Checks if the given pair is already in the array
  If yes, it increases its count by 1  */
  long long posOfPair = searchPair(pair);
  if(posOfPair != -1)
  {
    countsOfPairs[posOfPair]++;
    return;
  }

  /*If not, and the empty positions are less 
  than half the table size it doubles it   */
  if(countOfDiffPairs > tableSize/2)
  {
    //Creates a temporary object and copies the current one to it
    HashTable tempTable = *this;

    //Increases the size and resets the rest member variables
    tableSize = nextTableSize();
    table = new string[tableSize];
    countsOfPairs = new long long[tableSize];
    countOfDiffPairs = 0;

    //Adds all the pairs from the temporary object back to the current one
    for(long long i = 0; i < tempTable.tableSize; i++)
      {
        if(tempTable.table[i] != "")
        {
          for(long long j = 0; j < tempTable.countsOfPairs[i]; j++)
            {
              add(tempTable.table[i]);
            }
        }
      }
  }

  //Calculates the string's value
  long long pairValue = stringToInt(pair);

  //Searches possible positions until it finds an empty one
  for(long long i = 0; i < tableSize; i++)
    {
      long long possiblePos = doubleHashFunc(pairValue, i);
      if(table[possiblePos] == "")
      {
        //Finally, it adds the pair and sets its count to 1
        table[possiblePos] = pair;
        countsOfPairs[possiblePos] = 1;
        countOfDiffPairs++;
        return;
      }
    }
}