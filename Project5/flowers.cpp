#define _CRT_SECURE_NO_DEPRECATE

#include "utilities.h"
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

const char WORDFILENAME[] = "mywordfile.txt";
const int MAXWORD = 9000;

int playOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum); //when function is called a round of the Flowers and Bees Game will be played
int flowers(char word[], char trial[]); //calculate number of flowers 
int bees(char word[], char trial[]); //calculate number of bees
bool lowerCase(char trial[]); //evaluates trial word for all lowercase letters, returns false if trial word has a non-lowercase letter
bool wordLength(char trial[]); //evaluates length of trial word to be between 4 to 6 characters, returns false if word length is under 4 or over 6 chars
bool match(const char words[][MAXWORDLEN + 1], char trial[], int nWords); //Checks to see if trial word matches a word from mywordfile.txt


int main()
{
	char w[MAXWORD][MAXWORDLEN + 1];
	int n = getWords(w, 9000, WORDFILENAME); //get the total number of words contained in smallwords.txt

	if (n < 1) //if getWords returns no words, terminate the program
	{
		cout << "No words were loaded, so I can't play the game.";
		return -1;
	}

	double average = 0;
	int min = 1000000000;
	int max = 0;
	int numberOfRounds;
	cout << "How many rounds do you want to play? ";
	cin >> numberOfRounds;
	cin.ignore(10000, '\n');

	if (numberOfRounds <= 0) //if the user enters a negative number for rounds,terminate the program
	{
		cout << "The number of rounds must be positive.";
		return -1;
	}

	for (int r = 1; r <= numberOfRounds; r++)
	{
		cout << endl;
		cout << "Round " << r << endl;
		int randWord = randInt(0, n - 1); //generates a random number between 0 and 1 less than the total number of words in file
		cout << "The mystery word is " << strlen(w[randWord]) << " letters long." << endl; //write length of mystery word

		int tries = playOneRound(w, n, randWord);
		if (tries > 1)
			cout << "You got it in " << tries << " tries." << endl;
		else
			cout << "You got it in " << tries << " try." << endl;

		cout.setf(ios::fixed);
		cout.precision(2); //two decimal point
		average += tries; //calculates the total tries between rounds
		average /= r; //calculates average using totals
		if (tries > max) //alter max if tries is greater than the current maximum
			max = tries;
		if (tries < min) //alter min if tries is less than the current minimum
			min = tries;

		cout << "Average: " << average << ", minimum: " << min << ", maximum: " << max << endl; //prints player's statistics
	}
}

int playOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum)
{
	if (nWords <= 0 || wordnum < 0 || wordnum >= nWords) //potential errors
		return -1;

	int numOfTries = 0;

	for (;;)
	{
		char store[MAXWORDLEN + 1];
		strcpy(store, words[wordnum]); //set cstring store to words[wordnum] with a zero byte at the end
		cout << "Trial word: ";
		char tWord[101];
		cin.getline(tWord, 101); //user inputs trial word

		if (!lowerCase(tWord) || !wordLength(tWord)) //checks for lowercase and word length
		{
			cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
			continue;
		}

		else if (!match(words, tWord, nWords)) //checks if word matches textfile
		{
			cout << "I don't know that word." << endl;
			continue;
		}

		else if (strcmp(words[wordnum], tWord) == 0) //return number of tries when trial word matches mystery word
		{
			numOfTries++;
			return numOfTries;
		}

		int nFlowers = flowers(store, tWord); //calculates number of flowers
		cout << "Flowers: " << nFlowers;
		int nBees = bees(store, tWord); //calculates number of bees
		cout << ", Bees: " << nBees << endl;
		numOfTries++;
	}
}

int flowers(char word[], char trial[])
{
	int numFlowers = 0;
	for (int l = 0; trial[l] != '\0' && word[l] != '\0'; l++)
	{
		if (word[l] == trial[l]) //if mystery word and trial have the same character at the same position, add a flower
		{
			word[l] = '.';
			trial[l] = '/';
			numFlowers++;
		}
	}
	return numFlowers;
}

int bees(char word[], char trial[])
{
	int numBees = 0;
	for (int l1 = 0; word[l1] != '\0'; l1++)
	{
		for (int l2 = 0; trial[l2] != '\0'; l2++)
		{
			if (word[l1] == trial[l2]) //if mystery word and trial word have the same character at different positions, add a bee
			{
				word[l1] = '-';
				trial[l2] = '_';
				numBees++;
				break;
			}
		}
	}
	return numBees;
}

bool lowerCase(char trial[])
{
	int lowerCheck = 0;
	while (trial[lowerCheck] != '\0') //checks if trial word contains only lowercase characters
	{
		if (islower(trial[lowerCheck]))
			lowerCheck++;
		else
		{
			return false;
		}
	}
	return true;
}

bool wordLength(char trial[])
{
	if (strlen(trial) < MINWORDLEN || strlen(trial) > MAXWORDLEN) //checks if trial word is within 4 to 6 characters
	{
		return false;
	}
	else
		return true;
}

bool match(const char words[][MAXWORDLEN + 1], char trial[], int nWords)
{
	for (int m = 0; m != nWords; m++) //checks if trial word matches a potential mystery word
	{
		if (strcmp(words[m], trial) == 0)
			return true;
	}
	return false;
}