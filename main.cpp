#include "AVL.h"
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "SortedArray.h"
#include "UnsortedArray.h"
#include <algorithm>
#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
using namespace std;
/**
η συναρτηση δεχεται μια ακατεργαστη συμβολοσειρα διαβασμενη απο το αρχειο και
εφαρμοζει τις καταλληλες λειτουργιες ωστε να εχει μονο μικρα γραμματα και κανενα
σημειο στιξης.
**/

string hereIsWhereMagicHappens(string word) {
  int i = 0, j;
  while (word[i] != 0) {

    if (word[i] >= 'A' && word[i] <= 'Z') {

      word[i] += 32;
    }

    i++;
  }

  /*
ο κώδικας που χρησιμοποιήθηκε
https://www.techiedelight.com/remove-punctuation-from-string-in-cpp/
    */
  auto it = remove_if(word.begin(), word.end(),
                      [](char const &c) { return ispunct(c); });

  word.erase(it, word.end());

  return word;
}

int main() {
  srand(time(NULL));
  float  sum=0;
  ofstream out;
  out.open("output.txt", ios::trunc | ios::out);
  int Q = rand() % 10000 + 5000;
  unsigned long int searchin = 0;
  string toBeSearched[Q];
  AVL *balance = new AVL();
  node *bst = new node();
  UnsortedArray *array = new UnsortedArray();
  SortedArray *super = new SortedArray();
  HashTable *hash = new HashTable();

  bool flag = true;
  string test;

  unsigned long long count = 0,res;

  int enalagi = 0; // 0->ειναι η πρωτη λεξη ,1->ειναι η δευτερη λεξη που
                   // προσθετουμε στο ζευγος
  
  string word, pairS = "",
               save; // word->μια λεξη που διαβαζουμε απο το αρχειο
                     // κειμενου,pairS->το ζευγαρι συνεχομενων
                     // λεξεων,save->αποθηκευει την τελευταια λεξη του ζευγαριου.
  ifstream file("small-file(1).txt");

  if (file.is_open()) {
    file >> word;
    pairS += hereIsWhereMagicHappens(word);
    enalagi++; //εφοσον μπηκε η πρωτη λεξη αυξανω την μεταβλητη στο 1.

    while (file >> word) {
      if (enalagi == 0 &&
          (save.compare(""))) //η περιπτωση που κατασκευαζω το νεο ζευγος
      {
        enalagi++; //εφοσον μπηκε η πρωτη λεξη αυξανω την μεταβλητη στο 1.
        pairS = save; //η πρωτη λεξη του νεου ζευγους ειναι η τελευταια λεξη του
                      //προηγουμενου ζευγους.
      }
      if (enalagi == 1) //η περιπτωση που προσθετω την δευτερη λεξη
      {

        save =
            hereIsWhereMagicHappens(word); //κραταω την δευτερη λεξη στην save
        if (save.compare("")) {
          pairS += " " + save; //προσθετω την save το ζευγος

          if (flag) {
            balance = new AVL(pairS);
            bst = new node(pairS);
            flag = !flag;
          } else {
            balance=balance->add(pairS);
           bst->add(pairS);
          }
          array->add(pairS);
          super->add(pairS);
         hash->add(pairS);

          count++;
          if (rand() % 2 && Q > searchin) {
            toBeSearched[searchin++] = pairS;
          }

          enalagi = 0; //εφοσον το ζευγος συμπληρωθηκε επαναφερω την μεταβλητη
                       //στο μηδεν
        }
      }
    }
  } else {
    cout << "mistakes were made oops";
    return -2;
  }
   auto start = chrono::steady_clock::now();
   auto end = chrono::steady_clock::now();
  if (out.is_open()) {
    out << "Structure: BST. "<<endl<<endl;
    
    for (int i = 0; i < searchin; i++) {
       start = chrono::steady_clock::now();
     res= bst->search(toBeSearched[i]);
       end = chrono::steady_clock::now();
  sum+= (chrono::duration_cast<chrono::milliseconds>(end - start) .count());
      
       out<<"The pair \""<<toBeSearched[i]<<"\" was inserted in the binary search tree "<<res<< " times."<<endl ;
      
    }
  

    out << "Search algorithm completed in "
        <<   sum/1000.0<< " sec, searching " << searchin << " values among " << count << " values." << endl << endl;

    out << "Structure: AVL. "<<endl<<endl;

    for (int i = 0; i < searchin; i++) {

       start = chrono::steady_clock::now();
       res=  balance->search(toBeSearched[i]);
       end = chrono::steady_clock::now();
       out<<"The pair \""<<toBeSearched[i]<<"\" was inserted in the AVL tree "<<res<<" times."<<endl ;
   sum+= (chrono::duration_cast<chrono::milliseconds>(end - start) .count());

    }
    out << "Search algorithm completed in "
        <<sum/1000.0 << " sec searching " << searchin << " values among " << count
        << " values." << endl<<endl;
    out << "Structure: Unsorted Array. "<<endl<<endl;
   
sum=0;
    for (int i = 0; i < searchin; i++) {
       start = chrono::steady_clock::now();
       res = array->countOfPair(toBeSearched[i]);
    
         end = chrono::steady_clock::now();
   sum+= (chrono::duration_cast<chrono::milliseconds>(end - start) .count());
      out << "The pair \"" << toBeSearched[i] << "\"" << " was inserted in the unsorted array " << res << " times." << endl;
    }
 
    out << "Search algorithm completed in "
        <<sum/1000.0<< " sec searching " << searchin << " values among " << count
        << " values" << endl<<endl;

    out << "Structure: Sorted Array. " << endl<<endl;
   
sum=0;
    for (int i = 0; i < searchin; i++) {
       start = chrono::steady_clock::now();
       res = super->countOfPair(toBeSearched[i]);
       end = chrono::steady_clock::now();

      sum+= (chrono::duration_cast<chrono::milliseconds>(end - start) .count());
      
      out << "The pair \"" << toBeSearched[i] << "\"" << " was inserted in the sorted array " << res << " times." << endl;
    }
   
    out << "Search algorithm completed in "
        <<sum/1000.0<< " sec searching " << searchin << " values among " << count<< " values" <<endl<<endl;

    out << "Structure: Hash Table. " << endl<<endl;
    
sum=0;
    for (int i = 0; i < searchin; i++) {
       start = chrono::steady_clock::now();
       res = hash->countOfPair(toBeSearched[i]);
       end = chrono::steady_clock::now();
      sum+= (chrono::duration_cast<chrono::milliseconds>(end - start) .count());
      
      out << "The pair \"" << toBeSearched[i] << "\"" << " was inserted in the hash table " << res << " times." << endl;
      
    }
 
    out << "Search algorithm completed in "
        << sum/1000.0 << " seconds searching " << searchin << " values among " << count << " values" <<endl<<endl;
  }
  return 0;
}
