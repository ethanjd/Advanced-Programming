/**********************************************************************
 * BillSystem.cpp - CSCI251 - Assignment4 - BillSystem class definition
 * Ethan Dsouza
 **********************************************************************/
#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>
#include "BillSystem.h"
using namespace std;


// ========== class BillSystem Public Function definitions ==========

// Destructor
BillSystem::~BillSystem()
{
    for (vector<BillRecord*>::iterator it = BRecs.begin(); it != BRecs.end(); it++)
        delete (*it);
    BRecs.clear();
}

// Reads data in "usage.txt" into BRecs vector
bool BillSystem::ReadFile(char *fname)
{
    ifstream input;
    input.open(fname);
    if(!input.is_open())
        return false;

    BillRecord *temp;
    string type;

    while(!input.eof())
    {
        type = "";
        getline(input >> ws, type);

        if (type == "Phone")
            temp = new PhoneBillRecord(type);
        else if (type == "Gas")
            temp = new GasBillRecord(type);
        else if (type == "Elect")
            temp = new ElectBillRecord(type);
        else
            continue;

        if (!temp->readCustDetails(input))
            system("pause");
        if (!temp->readUsageInfo(input))
            system("pause");
        BRecs.push_back(temp);
    }
    input.close();
    return true;
}

// Returns the number of records in BRecs
int BillSystem::GetNumRecs()
{
	return BRecs.size();
}

 // Displays ith record on screen
void BillSystem::DisplayRec(int i)
{
    cout << setw(5) << left << i + 1;
	BRecs[i]->displayCustDetails();
	BRecs[i]->displayUsageInfo();
	cout << endl;
}

void BillSystem::CalDiscounts()
{
    map<string, float> suppDiscounts;
    map<string, float>::iterator itDisc;
    suppDiscounts.insert(pair<string, float>("Dodo", 0.15));
    suppDiscounts.insert(pair<string, float>("Alinta", 0.20));

    map<string, int> customerCount;
    map<string, int>::iterator itCust;

    for(vector<BillRecord*>::iterator it = BRecs.begin(); it != BRecs.end(); it++)
    {
        itDisc = suppDiscounts.find((*it)->getSupplier());
        if (itDisc != suppDiscounts.end())
        {
            itCust = customerCount.find((*it)->genID());
            if (itCust != customerCount.end())
            {
                if (++itCust->second == 3)
                    (*it)->setDiscount(itDisc->second);
            }
            else
                customerCount.insert(pair<string, int> ((*it)->genID(), 1));
        }
    }
}

void BillSystem::CalBills()
{
    for(vector<BillRecord*>::iterator it = BRecs.begin(); it != BRecs.end(); it ++)
        (*it)->updateBalance();
}

void BillSystem::PrintReport()
{
    for(int i = 0; i < 5; i++)
    {
        DisplayRec(i);
    }

    cout << "============= Customers with discount ===========\n";
    printIfDiscount();
}
// ========== class BillSystem Private Function definitions ==========

void BillSystem::printIfDiscount()
{
    for(unsigned int i = 0; i < BRecs.size() ; i++)
        if (BRecs[i]->hasDiscount())
            DisplayRec(i);
}
