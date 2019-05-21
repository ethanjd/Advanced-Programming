/***************************************************************************
 * main.cpp - CSCI251/851 - Ass3 - main() driver for testing WordStats class
 * Ethan Dsouza ejd881 5811831 4th December 2018
 ***************************************************************************/

#include <iostream>
#include <cstdlib>
#include "wordstats.h"
using namespace std;


int main(){

   WordStats ws;
   cout << "Begin Text File Analyser Tests\n";

   cout << "\nStep-1 Reading and displaying dictionary\n\n";
   ws.ReadDictionary();
   ws.DisplayDictionary();
   system("pause");

   cout << "\nStep-2 Reading words from text file\n\n";
   ws.ReadTxtFile();
   system("pause");

   cout << "\nStep-3 Displaying known words:\n\n";
   ws.DisplayKnownWordStats();
   system("pause");

   cout << "\nStep-4 Displaying unknown words:\n\n";
   ws.DisplayUnknownWordStats();
   system("pause");

   cout << "\nStep-5 Displaying most frequent known words\n\n";
   ws.DisplayMostFreqKnownWords();
   system("pause");

   cout << "\nStep-6 Displaying most frequent unknown words\n\n";
   ws.DisplayMostFreqUnknownWords();
   system("pause");

   cout << "\nStep-7 Displaying original text\n\n";
   ws.DisplayOriginalText();

   cout << "\nEnd Text File Analyser Tests\n\n";

   return 0;
}

