/********************************************************************
 * CSCI251 - Assignment1
 * <Ethan Joseph Dsouza>
 * recordFunctions.cpp - Contains function definitions for student records database
 ********************************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>

using namespace std;

// ============== Constants ==========================================

const char cTextFileName[] = "studentDatafile.txt";
const char cBinaryFileName[] = "studentDatafile.dat";
const int cMaxRecs = 100;
const int cMaxChars = 30;
const int cMaxSubjects = 8;

// ============= User Defined types ==================================

enum StatusType{eEnrolled,eProvisional,eWithdrawn};
struct SubjectType{ char Code[8]; StatusType Status; int Mark;};

struct StudentRecord{
	long StudentNo;
	char FirstName[cMaxChars];
	char LastName[cMaxChars];
	int NumSubjects;
	SubjectType Subjects[cMaxSubjects];
};


// ============= Global Data =========================================

StudentRecord gRecs[cMaxRecs];
int gNumRecs=0;


// ============= Private Function Prototypes =========================

void PrintRecord(int i);
int FindRecord(long StudentNum);
bool ReadTextFile(const char Filename[]); //reads text data from file to gRecs[] array
bool WriteTextFile(const char Filename[]); //writes text data from gRecs[] to file
bool ReadBinaryFile(const char Filename[]); //reads binary data from file to gRecs[] array
bool WriteBinaryFile(const char Filename[]); //writes binary data from gRecs[] to file
void WriteBinaryRecord(const char Filename[], int pos);

// ============= Public Function Definitions =========================


void ReadFile()
{// Reads data file into array

    if (ReadBinaryFile(cBinaryFileName))
        cout << "read binary file executed\n";
    else if(ReadTextFile(cTextFileName))
    {
        cout << "read text file executed\n";
        WriteBinaryFile(cBinaryFileName);
    }
    else
    {
        cerr << "Cant find text data file!\n";
        exit(1);
    }

    cout << gNumRecs << " record(s) read\n";
}

void DisplayRecord()
{// Displays specified record on screen

    int num;
    cout << "Enter student number: ";
    cin >> num;
    int res = FindRecord(num);

    if (res == -1)
    {
        cerr << "Record not found\n";
        exit(1);
    }
    PrintRecord(res);
}

void SaveFile()
{// Writes array to text data file

    if (WriteBinaryFile(cBinaryFileName))
    {
        cout << "Saved to binary file\n";
    }
    else if (WriteTextFile(cTextFileName))
    {
        cout << "Saved to text file\n";
    }
    else
    {
        cerr << "Can't open output file\n";
        exit(1);
    }

    cout << gNumRecs << " records saved\n";
}

void UpdateRecord()
{// updates status or mark of specified subject of specified student number

    int res;
    cout << "Enter student number: ";
    cin >> res;
    res = FindRecord(res);

    if (res == -1)
    {
        cerr << "Record not found\n";
        exit(1);
    }

    PrintRecord(res);

    char subCode[8];
    cout << "Which subject would you like to update? ";
    cin >> subCode;

    for (int i = 0; i < 8; i++)
    {
        subCode[i] = toupper(subCode[i]);
    }

    bool found = false;

    for (int i = 0; i < gRecs[res].NumSubjects; i++)
    {
        if (!strcmp(subCode, gRecs[res].Subjects[i].Code))
        {
            char choice;
            cout << "Would you like to update status or mark? (s/m): ";
            cin >> choice;

            if (tolower(choice) == 's')
            {
                found = true;
                char newStatus;
                cout << "Select a new status\n   e: Enrolled\n   p: Provisionally enrolled\n   w: Withdrawn\nStatus: ";
                cin >> newStatus;

                while(tolower(newStatus) != 'e' && tolower(newStatus) != 'p' && tolower(newStatus) != 'w' )
                {
                    cerr << "Invalid choice\n";
                    cout << "Select a new status\n   e: Enrolled\n   p: Provisionally enrolled\n   w: Withdrawn\nStatus: ";
                    cin >> newStatus;
                }

                switch (newStatus)
                {
                    case 'e':
                        gRecs[res].Subjects[i].Status = eEnrolled;
                    case 'p':
                        gRecs[res].Subjects[i].Status = eProvisional;
                    case 'w':
                        gRecs[res].Subjects[i].Status = eWithdrawn;
                }
                break;
            }
            else if(tolower(choice) == 'm')
            {
                found = true;
                int nMark;
                cout << "Enter a new " << gRecs[res].Subjects[i].Code << " mark for " << gRecs[res].FirstName << ": ";
                cin >> nMark;

                gRecs[res].Subjects[i].Mark = nMark;
                break;
            }
            else
            {
                cerr << "You have entered an invalid response";
                return;
            }
        }
    }
    if (!found)
    {
        cerr << "Subject code not found!";
        exit(1);
    }

    cout << "Record updated\n";

    WriteBinaryRecord(cBinaryFileName, res);
    WriteTextFile(cTextFileName);
}

// ============= Private Function Definitions =========================

void PrintRecord(int i)
{ // Prints record i on screen

    cout << "Student number: " << gRecs[i].StudentNo << endl;
    cout << "First Name: " << gRecs[i].FirstName << endl;
    cout << "Last name: " << gRecs[i].LastName << endl;
    cout << "Subjects:" << endl;
    for(int j = 0; j < gRecs[i].NumSubjects; j++)
    {
        int intStatus = gRecs[i].Subjects[j].Status;
        switch(intStatus)
            {
                case 0:
                    cout << "   " << gRecs[i].Subjects[j].Code << "  Enrolled     " <<  gRecs[i].Subjects[j].Mark << endl;
                    break;
                case 1:
                    cout << "   " << gRecs[i].Subjects[j].Code << "  Provisional  " <<  gRecs[i].Subjects[j].Mark << endl;
                    break;
                case 2:
                    cout << "   " << gRecs[i].Subjects[j].Code << "  Withdrawn    " <<  gRecs[i].Subjects[j].Mark << endl;
                    break;
            }
    }
}

int FindRecord(long StudentNo)
{// returns index of matching record or -1 if not found

    for(int i = 0; i < gNumRecs; i++)
    {
        if (gRecs[i].StudentNo == StudentNo)
            return i;
    }
	return -1;

}

bool ReadTextFile(const char Filename[])
{//returns true if the text file is read properly or false if the file isn't found
    ifstream input;
    input.open(Filename);

    if (!input.is_open())
    {
        cerr << "Cant find text data file!\n";
        return false;
    }

    int i = 0, intStatus;
    long numTemp;

    while (!input.eof())
    {
        numTemp = 0;
        input >> numTemp;
        if (numTemp == 0)
            continue;

        gRecs[i].StudentNo = numTemp;
        input >> gRecs[i].FirstName;
        input >> gRecs[i].LastName;
        input >> gRecs[i].NumSubjects;

        for (int j = 0; j < gRecs[i].NumSubjects; j++)
        {
            input >> gRecs[i].Subjects[j].Code;
            input >> intStatus;
            switch(intStatus)
            {
                case 0:
                    gRecs[i].Subjects[j].Status = eEnrolled;
                    break;
                case 1:
                    gRecs[i].Subjects[j].Status = eProvisional;
                    break;
                case 2:
                    gRecs[i].Subjects[j].Status = eWithdrawn;
                    break;
            }
            input >> gRecs[i].Subjects[j].Mark;
        }
        i++;
    }
    gNumRecs = i;

    input.close();
    return true;
}

bool WriteTextFile(const char Filename[])
{//returns true if records are written to the text file properly or false if not
    ofstream output;
    output.open(Filename);

    if (!output.is_open())
    {
        cerr << "Can't open output data file!\n";
        exit(1);
    }

    for (int i = 0; i < gNumRecs; i++)
    {
        output << gRecs[i].StudentNo << endl;
        output << gRecs[i].FirstName << " ";
        output << gRecs[i].LastName << endl;
        output << gRecs[i].NumSubjects << endl;

        for (int j = 0; j < gRecs[i].NumSubjects; j++)
        {
            output << gRecs[i].Subjects[j].Code << " ";
            output << gRecs[i].Subjects[j].Status << " ";
            output << gRecs[i].Subjects[j].Mark << endl;
        }
        output << endl;
    }

    output.close();
    return true;
}

bool ReadBinaryFile(const char Filename[])
{//returns true if the binary file is read properly or false if the file isn't found
    ifstream input;
    input.open(Filename, ios::binary);

    if (!input.is_open())
    {
        cerr << "Cant find binary data file!\n";
        return false;
    }

    input.read(reinterpret_cast<char *> (&gNumRecs), sizeof(gNumRecs));

    int intStatus;
    StudentRecord stud;

    for (int i = 0; i < gNumRecs; i++)
    {
        input.read(reinterpret_cast<char *> (&stud), sizeof(stud));

        gRecs[i].StudentNo = stud.StudentNo;
        strcpy(gRecs[i].FirstName, stud.FirstName);
        strcpy(gRecs[i].LastName, stud.LastName);
        gRecs[i].NumSubjects = stud.NumSubjects;

        for (int j = 0; j < gRecs[i].NumSubjects; j++)
        {
            strcpy (gRecs[i].Subjects[j].Code, stud.Subjects[j].Code);
            intStatus = stud.Subjects[j].Status;
            switch(intStatus)
            {
                case 0:
                    gRecs[i].Subjects[j].Status = eEnrolled;
                    break;
                case 1:
                    gRecs[i].Subjects[j].Status = eProvisional;
                    break;
                case 2:
                    gRecs[i].Subjects[j].Status = eWithdrawn;
                    break;
            }
            gRecs[i].Subjects[j].Mark = stud.Subjects[j].Mark;
        }
    }

    input.close();
    return true;
}

bool WriteBinaryFile(const char Filename[])
{//returns true if records are written to the binary file properly or false if not
    ofstream output;
    output.open(Filename, ios::binary);

    if (!output.is_open())
    {
        cerr << "Can't open output binary file!\n";
        exit(1);
    }

    output.write(reinterpret_cast<const char *> (&gNumRecs), sizeof(gNumRecs));

    StudentRecord stud;

    for (int i = 0; i < gNumRecs; i++)
    {
        stud.StudentNo = gRecs[i].StudentNo;
        strcpy (stud.FirstName, gRecs[i].FirstName);
        strcpy (stud.LastName, gRecs[i].LastName);
        stud.NumSubjects = gRecs[i].NumSubjects;

        for (int j = 0; j < gRecs[i].NumSubjects; j++)
        {
            strcpy (stud.Subjects[j].Code, gRecs[i].Subjects[j].Code);
            stud.Subjects[j].Status = gRecs[i].Subjects[j].Status;
            stud.Subjects[j].Mark = gRecs[i].Subjects[j].Mark;
        }
        output.write(reinterpret_cast<const char*> (&stud), sizeof(StudentRecord));
    }

    output.close();
    return true;
}

void WriteBinaryRecord(const char Filename[], int pos)
{//Updates single record in binary file at position pos
    ofstream output;
    output.open(Filename,ios::binary);

    if (!output.is_open())
    {
        cerr << "Cant find binary data file!\n";
        return;
    }
    output.seekp(sizeof(gNumRecs), ios::beg);
    output.seekp(pos * sizeof(StudentRecord), ios::cur);
    output.write(reinterpret_cast<const char*> (&gRecs[pos]), sizeof(StudentRecord));

    output.close();
}
