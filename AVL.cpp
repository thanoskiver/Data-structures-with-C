#include "AVL.h"

#include <iostream>
/**
κενος κατασκεβαστης AVL
**/
   AVL::AVL()
   {

       less=NULL;
       more=NULL;
   }
/**
κατασκεβαστης AVL
@param value ειναι το ζευγος λεξεων καθε κομβου

**/
    AVL::AVL(string value)
    {
          this->added=0;
          this->value=value;
          less=NULL;
          more=NULL;
          moreD=0;
          lessD=0;
          count=1;

    }
/*
getters
*/
    AVL* AVL::getLessPath()
    {
        return less;
    }
    AVL* AVL::getMorePath()
    {
        return more;
    }
    string AVL::getValue()
    {
    return value;
    }

/**
πραξη προσθήκης μιας συμβολοσειρας στην δομη
@param nvalue συμβολοσειρα που προστιθεται στην δομη
**/
    AVL* AVL::add(string nvalue){
      AVL* temp=this;
        AVL* n=new AVL(nvalue);
       if(value.compare(n->getValue())>0)
       {

           if(this->getLessPath()!=NULL)
           {

          AVL* path=this->getLessPath();
          path= path->add(n->getValue());
          less=path;
              }
           else
           {
           less=n;
            }
       }
       else if(value.compare(n->getValue())<0)
       {
            if(this->getMorePath()!=NULL)
           {
            AVL* path=this->getMorePath();
           path=path->add(n->getValue());
          more=path;

           }
           else
            {
              more=n;
            }
       }
       else
       {delete n;
        this->isEqual();
         }


      lessD=findLessD(this);
      moreD=findMoreD(this);
int balance=lessD-moreD;
      if (balance > 1 && value.compare(this->getLessPath()->value)<0)
      {

          AVL *x=new AVL();
           x=this->getLessPath();
           	temp= x->getMorePath();



            x->more = this;
	          this->less = temp;
           temp=x;
        return x;
      }


    if (balance < -1 && value.compare(this->more->getValue())>0)
    {          AVL *x = this->getMorePath();
           temp = x->getLessPath();


             x->less = this;
	           this->more = temp;


         temp=x;
      return x;
}


    if (balance > 1 && value.compare( less->getValue())<0)
    {

           AVL *x = this->getMorePath();
           temp = x->getLessPath();


             x->less = this;
	           this->more = temp;


         temp=x;
        this->less = x;


         x=new AVL();
           x=this->getLessPath();
           	temp= x->getMorePath();



            x->more = this;
	          this->less = temp;
           temp=x;
    }


    if (balance < -1 && value.compare( this->more->getValue())>0)
    {
           AVL *x = this->getMorePath();
           temp = x->getLessPath();


             x->less = this;
	           this->more = temp;


         temp=x;
        this->more = x;

      x = this->getMorePath();
           temp = x->getLessPath();


             x->less = this;
	           this->more = temp;


         temp=x;
return x;
    }

      
      return temp;


    }

/**
εκτελειται οταν στην δομη προστιθεται μια συμβολοσειρα που ηδη υπαρχει σε αυτην ,αυξανει το αριθμο συχνοτητας κατα ενα .
  **/
    void AVL::isEqual(){
        count++;
    }




/**
αναζητηση μιας συμβολοσειρας
@param a η συμβολοσειρα που αναζητουμε
@return ο αριθμος συχνοτητας της συμβολοσειρας (αν υπαρχει)
**/

unsigned long long AVL:: search(string a)
{

    if(a.compare(value)==0)
    {
      return count;
    }

    if(a.compare(value)>0)
    {
        AVL* path=this->getMorePath();
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
       AVL* path=this->getLessPath();
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
/*
βρισκει το βαθος του αριστερου υποδενδρου
  */
int AVL::findLessD(AVL*root)
{
    int dl=1,dm=1;

if(this==root)
{

  if(this->getLessPath()!=NULL){

    dl+=this->getLessPath()->findLessD(root);
    }

    return dl;
}

if(this->getLessPath()!=NULL)
{
    dl+=this->getLessPath()->findLessD(root);
}

    if(this->getMorePath()!=NULL)
{
       dm+=this->getMorePath()->findMoreD(root);

}



if(dm>dl)
    return dm;
else
    return dl;



}
/*
βρισκει το βαθος του δεξιου υποδενδρου
  */
int AVL::findMoreD(AVL*root)
{
    int dl=1,dm=1;
if(this==root)
{
  if(this->getMorePath()!=NULL)
    {

    dm+=this->getMorePath()->findMoreD(root);
    }
    return dm;
}


if(this->getMorePath()!=NULL)
{
    dm+=this->getMorePath()->findMoreD(root);
}


  if(this->getLessPath()!=NULL)
{
       dl+=this->getLessPath()->findMoreD(root);

}

if(this->getLessPath()==NULL||this->getMorePath()==NULL)
    return 1;


if(dm>dl)
    return dm;
else
    return dm;

}





