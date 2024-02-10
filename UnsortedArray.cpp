#include "UnsortedArray.h"
#include <iostream>

using namespace std;

//Constructor
UnsortedArray::UnsortedArray()
{
  arraySize = 5;
  pairs = new string[arraySize];
  countsOfPairs = new long long[arraySize];
  countOfDiffPairs = 0;
}

//Destructor
UnsortedArray::~UnsortedArray()
{
  delete[] pairs;
  delete[] countsOfPairs;
}

//Getters

//Returns the size of the array
long long UnsortedArray::getArraySize()
{
  return arraySize;
}

//Returns the countOfDiffPairs of the array
long long UnsortedArray::getCountOfDiffPairs()
{
  return countOfDiffPairs;
}

/*@param pos is the position of the pair we want to get

Returns the pair, located at that position of the array
Returns the empty string "" if there is no pair at the given position  */
string UnsortedArray::getPair(long long pos)
{
  if(pos < countOfDiffPairs)
  {
    return pairs[pos];
  }
  return "";
}

/*@param pair is the pair we are searching for

Searches the array for the given pair.
If found, it returns its position.
If not, it returns -1  */
long long UnsortedArray::searchPair(string pair)
{
  for(long long i = 0; i < countOfDiffPairs; i++)
    {
      if(pairs[i] == pair)
      {
        return i;
      }
    }
  return -1;
}

/*@param pair is the pair whose count we want to get

Returns how many pairs of the given pair exist in the array  */
long long UnsortedArray::countOfPair(string pair)
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
void UnsortedArray::add(string pair)
{
  /*Checks if the given pair is already in the array
  If yes, it increases its count by 1  */
  long long posOfPair = searchPair(pair);
  if(posOfPair != -1)
  {
    countsOfPairs[posOfPair]++;
    return;
  }

  //If not and the array is full, it doubles the allocated memory
  if(countOfDiffPairs == arraySize)
  {
    arraySize *= 2;
    
    //Creates a temporary array and assigns the current one to it
    string *newPairs = pairs;
    
    //Allocates more memory and copies the pairs back
    pairs = new string[arraySize];
    for(long long i = 0; i < countOfDiffPairs; i++)
      {
        pairs[i] = newPairs[i];
      }
    delete[] newPairs;

  
    //Same process for the counts of the pairs
    long long *newCountsOfPairs = countsOfPairs;

    countsOfPairs = new long long[arraySize];
    for(long long i = 0; i < countOfDiffPairs; i++)
      {
        countsOfPairs[i] = newCountsOfPairs[i];
      }
    delete[] newCountsOfPairs;
  }
  
  //Finally, it adds the pair and sets its count to 1
  pairs[countOfDiffPairs] = pair;
  countsOfPairs[countOfDiffPairs] = 1;

  //Increases the countOfDiffPairs of the array by 1
  countOfDiffPairs++;
}