// Napon Krassner
// CSC 2430, Homework 1
// 01-08-2015
// Due: Friday, 1/16/2015
// Name: Password Strength Deteminer
// Description: This program reads in a file that contains a list of SSN, User Name, and Password in that order each line.
// Then it outputs a txt file that contains a list of masked SSN (except for the last 4 digits), User Name, masked Password,
// and Password Strength in that order each line.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

string maskSSorPW(string);
int detStrengthPW (string);

int main()
{
	ifstream fileLinesIn;
	ofstream fileLinesOut;
	string ssNumber;
	string userName;
	string password;
	string maskedSS;
	string maskedPW;
	int strengthPW;

	// Associate file loc with var
	fileLinesIn.open("..\\data.txt");
	fileLinesOut.open("..\\output.txt");

	// Test if able to open file
	if (fileLinesIn.fail())
	{
		cout << "Error, failed to open file!" << endl;
		exit(1); // 1 = error, 0 = no error
	}

	// Out put header and formatting
	fileLinesOut << left;
	fileLinesOut << setw(20) << "SSN";
	fileLinesOut << setw(15) << "User Name";
	fileLinesOut << setw(20) << "Password";
	fileLinesOut << "Password Strength" << endl;
	
	// Prime read and write
	fileLinesIn >> ssNumber >> userName >> password;

	// Pime Work on SS
	maskedSS = maskSSorPW(ssNumber);
	fileLinesOut << setw(20) << maskedSS;

	// Prime Work on username
	fileLinesOut << setw(15) << userName;

	// Prime Work on PW
	maskedPW = maskSSorPW(password);
	strengthPW = detStrengthPW(password);
	fileLinesOut << setw(20) << maskedPW;
	fileLinesOut << strengthPW << endl;

	while (fileLinesIn.good())  // While not at the end of file
	{
		fileLinesIn >> ssNumber >> userName >> password;  // get the line from file

		// Work on SS
		maskedSS = maskSSorPW(ssNumber);
		fileLinesOut << setw(20) << maskedSS;

		// Work on username
		fileLinesOut << setw(15) << userName;

		// Work on PW
		maskedPW = maskSSorPW(password);
		strengthPW = detStrengthPW(password);
		fileLinesOut << setw(20) << maskedPW;
		fileLinesOut << strengthPW << endl;
	}

	// Close the file stream
	fileLinesIn.close();
	fileLinesOut.close();

	return 0;
}

// Parameters: string of SS or PW
// Returns: string of masked SS with last 4 digits displayd or masked PW with all chars to x
// Description: Takes a string and determines if it is SS or PW and masks it
string maskSSorPW (string strSSorPW)
{
	string maskedString;

	if (strSSorPW.find('-') == 3)  // SS test 1
	{
		if (strSSorPW.find('-', 6) == 6)  // This is a SS
		{
			maskedString = "xxx-xx-" + strSSorPW.substr(7, 10);
		} 
		else  // This is a PW
		{
			int pwLen = strSSorPW.length();
			for (int i = 0; i < pwLen; i++)
			{
				maskedString = maskedString + "x";
			}
		}
	}
	else  // This is a PW
	{
		int pwLen = strSSorPW.length();
			for (int i = 0; i < pwLen; i++)
			{
				maskedString = maskedString + "x";
			}
	}
	return maskedString;
}

// Parameters: string of PW
// Returns: then strength of the PW (int)
// Description: Takes a PW string and determines its strength
int detStrengthPW (string strPW)
{
	int totalPT = 0;
	int pwLen = strPW.length();

	if (pwLen > 7)  // 1 point for length > 7 char
	{
		totalPT += 1;
	}
	
	if (strPW.find_first_of("0123456789", 0) >= 0 && strPW.find_first_of("0123456789", 0) != string::npos)  // 1 point for 1 number
	{
		totalPT += 1;
	}

	if (strPW.find_first_of("!@#$%^&*()_+", 0) >= 0 && strPW.find_first_of("!@#$%^&*()_+", 0) != string::npos)  // 1 point for 1 symbol
	{
		totalPT += 1;
	}

	return totalPT;
}