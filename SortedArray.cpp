#include "SortedArray.h"
#include <iostream>

using namespace std;

/*@param pair is the pair we are searching for

Searches the array for the given pair using binary search.
If found, it returns its position.
If not, it returns -1  */
long long SortedArray::searchPair(string pair)
{
  long long low = 0, high = countOfDiffPairs - 1;
  while(low <= high)
    {
      long long mid = (low + high) / 2;
      
      if(pairs[mid] > pair)
      {
        high = mid - 1;
      }
      else if(pairs[mid] < pair)
      {
        low = mid + 1;
      }
      else
      {
        return mid;
      }
    }
  return -1;
}

/*@param pair is the pair whose count we want to get

Returns how many pairs of the given pair exist in the array  */
long long SortedArray::countOfPair(string pair)
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
void SortedArray::add(string pair)
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

  /*Searches binarily for the correct position of the pair.
  "low" will become greater than "high" and the correct 
  position will always be equal to "low" when that happens  */
  long long low = 0, high = countOfDiffPairs - 1;
  while(low <= high)
    {
      long long mid = (low + high) / 2;
      
      if(pairs[mid] > pair)
      {
        high = mid - 1;
      }
      else if(pairs[mid] < pair)
      {
        low = mid + 1;
      }
    }
  long long correctPos = low;
  
  /*It shifts all the pairs from the correct position, that the
  pair will be added at, to the right, by 1 position  */
  for(long long k = countOfDiffPairs - 1; k >= correctPos; k--)
    {
      pairs[k + 1] = pairs[k];
      countsOfPairs[k + 1] = countsOfPairs[k];
    }
  //Finally, it adds the pair and sets its count to 1
  pairs[correctPos] = pair;
  countsOfPairs[correctPos] = 1;

  //Increases the countOfDiffPairs of the array by 1
  countOfDiffPairs++;
}