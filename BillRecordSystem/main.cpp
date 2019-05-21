/**********************************************************************
 * main.cpp - CSCI251 - Assignment4- main() tester for class BillSystem
 * Ethan Dsouza
 **********************************************************************/
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "BillSystem.h"
using namespace std;

char Menu();

int main(){

	BillSystem BS;

	cout << "Begin tests for BillSystem\n\n";

	if(!BS.ReadFile("usage.txt")){
		cout << "File not found!\n\n";
		exit(1);
	}
	int n = BS.GetNumRecs();

	cout << "Num records read: " << n << endl << endl;

    cout << setw(05) << left << "#";
    cout << setw(13) << "  Service";
    cout << setw(10) << "Supplier";
    cout << setw(15) << "   Customer";
    cout << setw(25) << "       Address";
    cout << setw(8) << "AccBal";
    cout << setw(05) << "Days\n\n";

	for(int i=0; i<n && i<10; i++){
		BS.DisplayRec(i);
	}

	BS.CalDiscounts(); // uncoment when step 3 complete

	BS.CalBills();     // uncoment when step 4 complete

	cout << "========== Print Report ==========\n";
    BS.PrintReport();  // uncoment when step 4 complete

	cout << endl << "End tests for BillSystem\n";

	return 0;
}

