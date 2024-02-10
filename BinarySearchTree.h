#include <string>
#include <fstream>
#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED

using namespace std;
class node{
private :
    node* less;
    node* more;
    string value;
  //  int FrequencyCount;
unsigned long long count;
public:
    node();
    node(string value);

    node* getLessPath();
    node* getMorePath();
    string getValue();

    unsigned long long search(string A);
    void print();
    void add(string);
    void isEqual();
    void setLess();
    void  setMore();







};


#endif // BINARYSEARCHTREE_H_INCLUDED
