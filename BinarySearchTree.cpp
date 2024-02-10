#include "BinarySearchTree.h"
#include <stack>
#include <iostream>
   node::node()
   {
       less=NULL;
       more=NULL;
   }
/*
class constractor
@param value
when a node is created , the constractor sets the value of string and the pointers are set to point to null
*/
    node::node(string value)
    {

      count=1;
        this->value=value;
         less=NULL;
       more=NULL;

    }
/*
returns the pointer that points to a node of less value that this
  */
    node* node::getLessPath()
    {
        return less;
    }
/*
returns the pointer that points to a node of bigger value that this
  */
    node* node::getMorePath()
    {
        return more;
    }
/**
returns the string of this node
  **/
    string node::getValue()
    {
    return value;
    }

/**
@param nvalue is the string of the new node

this function add a new node to the tree with the correct placement according to the value of the string
  **/
    void node::add(string nvalue){

        node* n=new node(nvalue);
       if(value.compare(n->getValue())>0)
       {
           if(this->getLessPath()!=NULL)
           {
            node* path=this->getLessPath();
           path->add(n->getValue());
           }
           else
           {
                 less=n;
            }
       }
       else 
         if(value.compare(n->getValue())<0)
       {
            if(this->getMorePath()!=NULL)
           {
            node* path=this->getMorePath();
           path->add(n->getValue());
           }
           else
             more=n;
       }else
       {
         delete n;
         this->isEqual();
         }


    }
/**
counts how many times a specific string is being added to the tree
  **/
    void node::isEqual(){
        count++;
    }
    void node::setLess(){}
    void  node::setMore(){}

    void node::print()
    {
cout<<value<<" and "<<this->less->getValue()<<less->getLessPath()->getValue();
                }


/*
this function searches in the tree for a specific string
  */
unsigned long long node:: search(string a)
{

    if(a.compare(value)==0)
    {
     return count;
      }
    if(a.compare(value)>0)
    {
        node* path=this->getMorePath();
        if(path!=NULL)
        {

            return path->search(a);
        }
        else{
            cout<<"The thing you searched is not here "<<endl;
          return 0;
        }

    }


    if(a.compare(value)<0)
    {
       node* path=this->getLessPath();
           if(path!=NULL)
        {

            return path->search(a);
        }
        else
        {
            cout<<"The thing you searched is not here "<<endl;
          return 0;
        }
    }
  return 0;
}
