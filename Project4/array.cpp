#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value); //Append a string to the end of every element in an array
int lookup(const string a[], int n, string target); //Find the earliest position of string target and return that position
int positionOfMax(const string a[], int n); //Return position of the string >= every other string in an array
int rotateLeft(string a[], int n, int pos); //Move the string at int position to the end of the array and move all elements following it to the left 
int countRuns(const string a[], int n); //Return number of sequences for one or more consecutive identical element in the array
int flip(string a[], int n); //Reverse order of elements in an array
int differ(const string a1[], int n1, const string a2[], int n2); //Return the first position where elements are a1 and a2 are different 
int subsequence(const string a1[], int n1, const string a2[], int n2); //Check if a1 contains the elements of a2 in the same consecutive order, return position of a1 where sequence began
int lookupAny(const string a1[], int n1, const string a2[], int n2); //Return the smallest position in a1 of an element that is equal to any of the n2 elements in a2
int separate(string a[], int n, string separator); //Move all values less than separator to the beginning of array and all values greater than separator to the end of array 
int separate(string a[], int n, string separator); //Move all values less than separator to the beginning of array and all values greater than separator to the end of array 

int main()
{
	string h[7] = { "mick", "marie", "fiona", "rudy", "", "gordon", "lindsey" };
	assert(lookup(h, 7, "gordon") == 5);
	assert(lookup(h, 7, "fiona") == 2);
	assert(lookup(h, 2, "fiona") == -1);
	assert(positionOfMax(h, 7) == 3);

	string g[4] = { "mick", "marie", "lindsey", "nancy" };
	assert(differ(h, 4, g, 4) == 2);
	assert(appendToAll(g, 4, "?") == 4 && g[0] == "mick?" && g[3] == "nancy?");
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "lindsey?" && g[3] == "marie?");

	string e[4] = { "fiona", "rudy", "", "gordon" };
	assert(subsequence(h, 7, e, 4) == 2);

	string d[5] = { "marie", "marie", "marie", "rudy", "rudy" };
	assert(countRuns(d, 5) == 2);

	string f[3] = { "lindsey", "fiona", "mike" };
	assert(lookupAny(h, 7, f, 3) == 2);
	assert(flip(f, 3) == 3 && f[0] == "mike" && f[2] == "lindsey");

	assert(separate(h, 7, "lindsey") == 3);
	
	cout << "All tests succeeded" << endl;
}

int appendToAll(string a[], int n, string value)
{
	if (n < 0) //returns -1 if n is a negative number
		return -1;

	for (int e = 0; e != n; e++)
	{
		a[e] += value; //adds string, value to the end of a[e]
	}
	return n;
}
int lookup(const string a[], int n, string target)
{
	if (n < 0) //returns -1 if n is a negative number
		return -1;

	for (int e = 0; e != n; e++)
	{
		if (target == a[e]) //check if array a at position e is equalivent to target
			return e;
	}
	return -1; //if no values in the array match target, return -1
}
int positionOfMax(const string a[], int n)
{
	if (n < 0) //returns -1 if n is a negative number
		return -1;

	string max = a[0];
	int position = -1;

	for (int e = 0; e != n; e++)
	{
		for (int e2 = 1; e2 != n; e2++)
		{
			if (a[e] >= a[e2]) //compares two elements of an array to see which is greater
			{
				if (a[e] > max) //compares the greatest element to an element of the array
				{
					max = a[e];
					position = e;
				}
			}
		}
	}
	return position;
} //question
int rotateLeft(string a[], int n, int pos)
{
	if (n < 0) //returns -1 if n is a negative number
		return -1;
	if (pos >= n || pos < 0) //return -1 if position is greater than or equal to array size or less than 0
		return -1;

	string element = a[pos]; //store value at position pos
	for (int e = 0; e != n; e++)
	{
		if (e == pos)
		{
			for (int l = e; l != n - 1; l++)
			{
				a[l] = a[l + 1];
			}
			a[n - 1] = element;
			break;
		}
	}
	return pos;
}
int countRuns(const string a[], int n)
{
	if (n < 0) //returns -1 if n is a negative number
		return -1;

	int sequences = 0;
	if (n > 0) //continue only if array has an element
	{
		sequences++;
		for (int e = 1; e != n; e++)
		{
			if (a[e] == a[e - 1])
				continue;
			else
				sequences++;
		}
		return sequences;
	}
	return sequences;
}
int flip(string a[], int n)
{
	if (n < 0)
		return -1;

	string copy;
	for (int e = 0; e != n / 2; e++)
	{
		copy = a[e]; //stores a copy of the outer element
		a[e] = a[n - 1 - e];
		a[n - 1 - e] = copy;
	}
	return n;
}
int differ(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0) //returns -1 if n1 or n2 is a negative number
		return -1;


	for (int a = 0; a != n1 || a != n2; a++)
	{
		if (a1[a] == a2[a])
		{
			continue;
		}
		else
			return a;
	}
	if (n1 < n2) //If the arrays are equal up to the point where one or both runs out, return the smaller n1 or n2
		return n1;
	else
		return n2;
}
int subsequence(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 <= 0 || n2 < 0) //returns -1 if n1 or n2 is a negative number
		return -1;
	if (n2 == 0) //returns 0 if there is nothing to evaluate
		return 0;

	int b = 0;
	int position = 0;
	for (int a = 0; a != n1; a++)
	{
		if (a1[a] == a2[b])
		{
			position = a; //sets position to the first location where array a and b are equal
			while (a1[a] == a2[b])
			{
				if (a1[a] == a2[b] && (b + 1) == n2)
				{
					return position; //once every element of a2 is evaluated true, return position
				}
				else
				{
					a++;
					b++;
				}
			}
			a--;
			b = 0;
		}
	}
	return -1;
}
int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0) //returns -1 if n1 or n2 is a negative number
		return -1;
	if (n2 == 0) //returns 0 if there is nothing to evaluate
		return 0;

	for (int a = 0; a != n1; a++)
	{
		for (int b = 0; b != n2; b++)
		{
			if (a1[a] == a2[b])
			{
				return a;
			}
		}
	}
	return -1;
}
int separate(string a[], int n, string separator)
{
	if (n < 0) //returns -1 if n is a negative number
		return -1;

	string store;
	string equal;
	int f = 0;
	int b = 0;
	for (int l = 0; l != n; l++) //moves all the values less than separator to beginning of array
	{
		if (a[l] < separator)
		{
			store = a[f];
			a[f] = a[l];
			a[l] = store;
			f++;
		}
	}

	for (int g = 0; g != n; g++) //moves all values greater than separator to end of array 
	{
		if (a[g] > separator)
		{
			store = a[n - 1 - b];
			a[n - 1 - b] = a[g];
			a[g] = store;
			b++;
		}
	}

	for (int e = 0; e != n; e++) //places all values equal to separator in between those that are less than or greater than the separator
	{
		if (a[e] == separator)
		{
			for (int e2 = 0; e2 != n; e2++)
			{
				if (a[e2] > separator)
				{
					equal = a[e];
					a[e] = a[e2];
					a[e2] = equal;
					break;
				}
			}
		}
	}

	for (int pos = 0; pos != n; pos++) //returns position of first value greater than or equal to separator
	{
		if (a[pos] >= separator)
		{
			return pos;
		}
	}
	return n; //if no elements > separator, return n
}