/**********************************************************************
 * BillRecord.h - CSCI251 - Assignment4 - BillRecord class declaration
 * Ethan Dsouza
 **********************************************************************/
#ifndef BILLRECORD_H
#define BILLRECORD_H

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

enum billType {eElect, eGas, ePhone };

class BillRecord {
    public:
        BillRecord(string);
        virtual ~BillRecord();

        string getSupplier() const;
        string genID() const;

        void setBillAmount(double);
        bool readCustDetails(ifstream &fin);
        virtual bool readUsageInfo(ifstream &fin);
        void displayCustDetails();
        virtual void displayUsageInfo();
        void setDiscount(float);
        virtual void updateBalance()=0;
        bool hasDiscount();

    private:
        billType bType;
        string supplier; // Supplier's name
        string name, address; // Customer's name and address
        double billAmount;// Amount in dollars and cents of this bill

    protected:
        double accountBalance; // Customer's account balance
        int daysSinceLastReading; // Days since last reading
        float discount;
};


//derived classes...

class ElectBillRecord : public BillRecord
{
    public:
        ElectBillRecord(string);
        ~ElectBillRecord();

        bool readUsageInfo(ifstream&);
        void displayUsageInfo();
        void updateBalance();

    private:
        double prevReading, currReading, rate1, rate1Thresh, rate2, suppCharge;

};

class GasBillRecord : public BillRecord
{
    public:
        GasBillRecord(string);
        ~GasBillRecord();

        bool readUsageInfo(ifstream&);
        void displayUsageInfo();
        void updateBalance();

    private:
        double prevReading, currReading, heatingVal, rate, suppCharge;

};

class PhoneBillRecord : public BillRecord
{
    public:
        PhoneBillRecord(string);
        ~PhoneBillRecord();

        bool readUsageInfo(ifstream&);
        void displayUsageInfo();
        void updateBalance();

    private:
        double localCalls, localCallRate, longDistanceCallTime, longDistanceCallRate, lineRental;
};


#endif

