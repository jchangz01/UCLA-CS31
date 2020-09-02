#include <iostream>
#include <string>
using namespace std;

int main ()
{
	cout << "Defendant: ";
	string defendantName;
	getline(cin, defendantName);

	if (defendantName == "" ) //empty string test case
	{
		cout << "---" << endl;
		cout << "You must enter a defendant name." << endl;
		return 1;
	}
	
	cout << "Amount paid (in thousands): ";
	double amountPaid;
	cin >> amountPaid;
	cin.ignore(10000, '\n');

	if (amountPaid < 0) //negative amount paid test case
	{
		cout << "---" << endl;
		cout << "The amount paid must not be negative." << endl;
		return 1;
	}

	cout << "Fake athlete? (y/n): ";
	string fakeAthlete;
	getline(cin, fakeAthlete);

	if (fakeAthlete != "y" && fakeAthlete != "n") //response not "y" or "n" test case
	{
		cout << "---" << endl;
		cout << "You must enter y or n." << endl;
		return 1;
	}

	double baseFine = 20; //base amount
	double firstFine = 0;
	double secondFine = 0;
	double thirdFine = 0;

	
	if (amountPaid >= 40) //First Fine Calculations
	{
		firstFine = 40 * 0.66;
		if (amountPaid >= 250) //Second Fine & Third Fine Calculations
		{
			if (fakeAthlete == "y")
			{
				secondFine = (210) * 0.22;
			}
			else if (fakeAthlete == "n")
			{
				secondFine = 210 * 0.10;
			}
			thirdFine = (amountPaid - 250) * 0.14;
		}
		
		else if (amountPaid >= 40 && amountPaid < 250) //Second Fine Calculations
		{
			if (fakeAthlete == "y")
			{
				secondFine = (amountPaid - 40) * 0.22;
			}
			else if (fakeAthlete == "n")
			{
				secondFine = (amountPaid - 40) * 0.10;
			}
		}
	}
	else
	{
		firstFine = amountPaid * 0.66;
		secondFine = 0;
		thirdFine = 0;
	}

	double totalFine;
	totalFine = baseFine + firstFine + secondFine + thirdFine; //Calculate the suggested fine
	cout.setf(ios::fixed);
	cout.precision(1); //one decimal point

	cout << "---" << endl;
	cout << "The suggested fine for " << defendantName << " is $" << totalFine << " thousand." << endl;
}