/**********************************************************************
 * BillSystem.h - CSCI251 - Assignment4- BillSystem class declaration
 * Ethan Dsouza
 **********************************************************************/
#ifndef BILLSYS_H
#define BILLSYS_H

#include <iostream>
#include <vector>
#include "BillRecord.h"
using namespace std;


class BillSystem {
    public:
        ~BillSystem();

        bool ReadFile(char *fname);
        int GetNumRecs();
        void DisplayRec(int i); // prints ith record on screen
        void CalDiscounts();
        void CalBills();
        void PrintReport();

  private:
     vector<BillRecord*> BRecs; // vector of pointers to class BillRecord

     void printIfDiscount();
};


#endif

