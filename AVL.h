#include <string>

#ifndef AVL_H
#define AVL_H

using namespace std;
class AVL{
private :
    AVL* less;
    AVL* more;
    string value;
    int lessD,moreD;
    unsigned long long count;
    int added;
//AVL* root;
public:
    AVL();
    AVL(string value);

    AVL* getLessPath();
    AVL* getMorePath();
    string getValue();

int getCount(){return count;}
    int findLessD(AVL*);
    int findMoreD(AVL*);

void setLessD(int a){lessD=a;}
void setMoreD(int a){moreD=a;}
int getLessD(){return lessD;}
int getMoreD(){return moreD;}
  unsigned long long search(string A);
    void print();
    AVL* add(string);
    void isEqual();
    void setLess(AVL*a){this->less=a;};
    void  setMore(AVL*a){this->more=a;};








};


#endif // BINARYSEARCHTREE_H_INCLUDED
