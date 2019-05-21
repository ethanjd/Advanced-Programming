/**********************************************************************
 * wordstats.cpp - CSCI251 - Ass3 - Contains WordsStats class definition
 * Ethan Dsouza ejd881 5811831 4th December 2018
 **********************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include "wordstats.h"
using namespace std;

WordStats::WordStats(){
	strcpy(Filename,"textFile.txt");
}

// Reads dictionary.txt into Dictionary
void WordStats::ReadDictionary(){
    ifstream input;
    input.open("dictionary.txt");

    if(!input.is_open())
    {
        cerr << "The file was not found";
        exit(1);
    }

    string word;

    while(input >> word) //this loop iterates through each word in the Dictionary file
    {
        for(unsigned int i = 0; i < word.length(); i++) //this loop iterates through each character in the word and makes it lowercase and inserts it to the private data member Dictionary
            word[i] = tolower(word[i]);
        Dictionary.insert(word);
    }
    cout << Dictionary.size() << " words read from dictionary.\n";

    input.close();
}

// Displays Dictwords 20 at a time
void WordStats::DisplayDictionary(){

    char choice = 'y';
    string word;
    set<string>::iterator dictIter = Dictionary.begin();

    for(int i = 0; i < 20; i++) //this loop displays the first 20 values int the dictionary
        cout << *dictIter++ << endl;

    do //an infinite loop that only stops when a valid input is entered
    {
        cout << "Do you want to continue?(y/n) ";
        cin >> choice;
        cin.clear();
        cin.ignore();
        cout << endl;
        switch(tolower(choice)) //this switch case accepts y or n otherwise it asks the user to reenter a choice
        {
            case 'y':
                for(int i = 0; i < 20; i++) //this loop displays the next 20 values in the dictionary
                    cout << *dictIter++ << endl;
                break;
            case 'n':
                return;
            default:
                cout << "You have entered an invalid choice please try again\n\n";
                cout << "Do you want to continue?(y/n) ";
                cin >> choice;
                cin.clear();
                cin.ignore();
                cout << endl;
                break;
        }
    }while(true);
}

// Reads the text file into KnownWords and UnknownWords
void WordStats::ReadTxtFile(){
    ifstream input;
    input.open(Filename);

    if(!input.is_open())
    {
        cerr << "The file was not found";
        exit(1);
    }

    string inWord, word;
    set<string>::iterator dictIter;
    int pos = 1, kwCount = 0, ukwCount = 0;

    while(input >> inWord) //this loop iterates through every word in the file which has the name stored in the Filename variable
    {
        word = "";
        for(unsigned int i = 0; i < inWord.length(); i++) //this loop iterates through each character in the word and removes all the unwanted characters
        {
            if(isalpha(inWord[i]) || inWord[i] == '-' || inWord[i] == '\'')
                word += tolower(inWord[i]);
        }

        dictIter = Dictionary.find(word);
        if(dictIter != Dictionary.end()) //checks whether The word exists in the dictionary and calls the respective function
            kwCount += addWord(word, pos, KnownWords);
        else
            ukwCount += addWord(word, pos, UnknownWords);
        pos++;
    }
    cout << kwCount << " known words read.\n";
    cout << ukwCount << " unknown words read.\n";
}
// Displays stats of words in KnownWords by calling the printMap private function on the KnownWords map
void WordStats::DisplayKnownWordStats(){
    cout << right << setw(15) << "Word" << setw(9) << "Count"<< setw(15) << "Position(s)" << endl;
    printMap(KnownWords);
}

// Displays stats of words in Unknownwords by calling the printMap private function on the UnknownWords map
void WordStats::DisplayUnknownWordStats(){
    cout << right << setw(15) << "Word" << setw(9) << "Count"<< setw(15) << "Position(s)" << endl;
    printMap(UnknownWords);
}

// Displays th 10 most frequent words in KnownWords by calling the displayMostFreqWords function on KnownWords
void WordStats::DisplayMostFreqKnownWords(){
    cout << right << setw(15) << "Word" << setw(9) << "Count" << endl;
    displayMostFreqWords(KnownWords);
}

// Displays 10 most frequent words in UnknownWords by calling the displayMostFreqWords function on UnknownWords
void WordStats::DisplayMostFreqUnknownWords(){
    cout << right << setw(15) << "Word" << setw(9) << "Count" << endl;
    displayMostFreqWords(UnknownWords);
}

// Displays original text from KnownWords & UnknownWords to the console
void WordStats::DisplayOriginalText(){

    map<int, string> originalText;
    map<int, string>::iterator otIt;
    WordMapIter it;

    for(it = KnownWords.begin(); it != KnownWords.end(); it++) //this loop iterates through each pair in the KnownWords map and inserts it into the originalText map with the position as the key
    {
        for(unsigned int i = 0; i < it->second.size(); i++)
            originalText.insert(pair <int, string> (it->second.at(i),it->first));
    }
    for(it = UnknownWords.begin(); it != UnknownWords.end(); it++)//this loop iterates through each pair in the UnknownWords map and inserts it into the originalText map with the position as the key
    {
        for(unsigned int i = 0; i < it->second.size(); i++)
            originalText.insert(pair<int, string>(it->second.at(i),it->first));
    }
    for(otIt = originalText.begin(); otIt != originalText.end(); otIt++) //this loop iterates through the originalText map and prints each word in its original order
    {
        cout << otIt->second << " ";
    }
}

// ============ Private Fns ========================

// this private function adds a word to the map that is passed by reference and returns
// 1 if the word doesn't already exist in the map and 0 if it does.
int WordStats::addWord(string word, int pos, WordMap& wm)
{
    WordMapIter it;
    it = wm.find(word);
    if(it != wm.end())
    {
        it->second.push_back(pos);
        return 0;
    }
    else
    {
        vector<int> temp(1,pos);
        wm.insert(pair<string, vector<int>> (word, temp));
        return 1;
    }
}

// this function prints the entire WordMap including a count of the number of elements in the vector
void WordStats::printMap(WordMap wm)
{
    WordMapIter it;
    for(it = wm.begin();it != wm.end(); it++) // this loop iterates through the passed WordMap and prints the variables in column form
    {
        cout << right <<  setw(15) << it->first << setw(7) << it->second.size()<< "      ";
        for(int x : it->second)
            cout << left << x << " ";
        cout << endl;
    }
}

// this function prints the top 10 most frequently used words in the supplied text file
void WordStats::displayMostFreqWords(WordMap wm)
{
    multimap<int,string> freqMap;
    multimap<int,string>::iterator it;
    WordMapIter wmi;

    for(wmi = wm.begin(); wmi != wm.end(); wmi++) // this loop iterated through the passed WordMap and adds it to a multimap that sorts the words by frequency
    {
        freqMap.insert(pair<int, string>(wmi->second.size(), wmi->first));
    }

    it = freqMap.end();

    for(int i = 0; i < 10; i++) // this loop prints the last 10 pairs in the multimap which are the most frequently used words in the text file
    {
        it--;
        cout << setw(15) << it->second << setw(7)<< it->first << endl;
    }
}
