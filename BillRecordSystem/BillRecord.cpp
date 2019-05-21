/**********************************************************************
 * BillRecord.cpp - CSCI251 - Assignment4 - BillRecord class definition
 * Ethan Dsouza
 **********************************************************************/
#include "BillRecord.h"

// ========== class BillRecord function definitions ==========

// Default constructor
BillRecord::BillRecord(string type)
{
    if(type == "Phone")
        bType = ePhone;
    else if (type == "Gas")
        bType = eGas;
    else
        bType = eElect;

    discount = 1;
}

BillRecord::~BillRecord()
{

}

string BillRecord::getSupplier() const
{
    return supplier;
}

string BillRecord::genID() const
{
    return name + "/" + address;
}

void BillRecord::setBillAmount(double amt)
{
    billAmount = amt;
}

// Reads customer details part of record from file
bool BillRecord::readCustDetails(ifstream &fin)
{
    getline(fin, supplier);
    getline(fin, name);
    getline(fin, address);
    fin >> accountBalance;
    fin >> daysSinceLastReading;
//    fin.ignore();

	//put code here for reading the customer details part of file record only into the private data members
	return true;
}

// Displays customer details part of record on screen
void BillRecord::displayCustDetails()
{
    switch(bType)
    {
        case 0:
            cout << setw(13) << "Electricity";
            break;
        case 1:
            cout << setw(13) << "    Gas";
            break;
        case 2:
            cout << setw(13) << "   Phone";
            break;
    }
    cout << setw(10) << supplier;
    cout << setw(15) << name;
    cout << setw(25) << address;
    cout << setw(9) << accountBalance;
    cout << setw(05) << daysSinceLastReading;
    cout << endl;
}

// Virtual fn for reading usage info part of record from file in derived classes
bool BillRecord::readUsageInfo(ifstream &fin)
{
	return true;
}


// virtual fn for displays usage info part of record in derived classes
void BillRecord::displayUsageInfo()
{
	// does nothing - later we will override this fn to display the appropriate billing info in the derived classes
}

void BillRecord::setDiscount(float d)
{
    discount = 1 - d;
}

bool BillRecord::hasDiscount()
{
    return(discount < 1);
}


// ========== Derived Class function definitions ==========


// =============== Subclass for Electricity bill records ====================
ElectBillRecord::ElectBillRecord(string type) : BillRecord(type)
{

}

ElectBillRecord::~ElectBillRecord()
{

}

bool ElectBillRecord::readUsageInfo(ifstream& fin)
{
    if(fin >> prevReading >> currReading >> rate1 >> rate1Thresh >> rate2 >> suppCharge)
        return true;
    return false;
}

void ElectBillRecord::displayUsageInfo()
{
    cout << "(Readings: " << prevReading << ", "<< currReading;
    cout << "\tR1: " << rate1;
    cout << "  R1Th: " << rate1Thresh;
    cout << "  R2: " << rate2;
    cout << "\tSuppC: " << suppCharge << ")" << endl;
}

void ElectBillRecord::updateBalance()
{
    double C, P;
    C = currReading - prevReading;
    P = suppCharge * daysSinceLastReading;

    if(C <= rate1Thresh)
        setBillAmount((C * rate1 + P) * discount - accountBalance);
    else
        setBillAmount((rate1Thresh * rate1 + (C - rate1Thresh) * rate2 + P) * discount - accountBalance);
    accountBalance = 0;
}


// ================== Subclass for Gas bill records =========================
GasBillRecord::GasBillRecord(string type) : BillRecord(type)
{

}

GasBillRecord::~GasBillRecord()
{

}

bool GasBillRecord::readUsageInfo(ifstream& fin)
{
    if (fin >> prevReading >> currReading >> heatingVal >> rate >> suppCharge)
        return true;
    return false;
}

void GasBillRecord::displayUsageInfo()
{
    cout << "(Readings: " << prevReading << ", " << currReading;
    cout << "\tHV: " << heatingVal;
    cout << "\tRate: " << rate;
    cout << "\tSuppC: " << suppCharge << ")" <<endl;
}

void GasBillRecord::updateBalance()
{
    double C, P;

    C = currReading - prevReading;
    P = suppCharge * daysSinceLastReading;
    setBillAmount((C * heatingVal * rate) * discount - accountBalance);
    accountBalance = 0;
}


// ================= Subclass for phone bill records ========================
PhoneBillRecord::PhoneBillRecord(string type) : BillRecord(type)
{

}

PhoneBillRecord::~PhoneBillRecord()
{

}

bool PhoneBillRecord::readUsageInfo(ifstream& fin)
{
    if (fin >> localCalls >> localCallRate >> longDistanceCallTime >> longDistanceCallRate >> lineRental)
        return true;
    return false;
}

void PhoneBillRecord::displayUsageInfo()
{
    cout << "(LCalls: " << localCalls << ", " << localCallRate;
    cout << "\tDCalls: " << longDistanceCallTime << ", " << longDistanceCallRate;
    cout << "\tRental: " << lineRental << ")" << endl;
}

void PhoneBillRecord::updateBalance()
{
    double L, D, P;

    L = localCallRate * localCalls;
    D = longDistanceCallRate * longDistanceCallTime;
    P = lineRental * daysSinceLastReading;
    setBillAmount((L + D + P) * discount - accountBalance);
    accountBalance = 0;
}
