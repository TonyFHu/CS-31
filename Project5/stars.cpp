#include <iostream>
#include <ctime>
#include <cstdlib>
#include "utilities.h"
#include <iomanip>
#include <cstring>
using namespace std;

const int MAX_NUM_WORDS = 10000;
const int MAX_WORD_LENGTH = 6;

int runOneRound(const char wordList[][MAX_WORD_LENGTH + 1], int numWords, int wordnum);
void generateClue(const char wordList[], const char probe[], int& stars, int& planets);
bool isRealWord(const char wordList[][MAX_WORD_LENGTH + 1], int numWords, const char probe[]);
void print(const char word[]);

int main() 
{
	//
	//srand(time(NULL));
	//

	int numWords = 0;

	const char WORDFILENAME[] = "D:/Users/Tony/source/repos/Project5/words.txt";
	char wordList[MAX_NUM_WORDS][MAX_WORD_LENGTH + 1];

	//populates the array of cstrings
	numWords = getWords(wordList, MAX_NUM_WORDS, WORDFILENAME);
	if (numWords < 1)
	{
		cout << "No words were loaded, so I can't play the game." << endl;
		exit(0);
	}
	
	//takes user input
	int rounds;
	cout << "How many rounds do you want to play? ";
	cin >> rounds;

	//ignore the newline after cin on an int
	cin.ignore(10000, '\n');

	if (rounds < 1)
	{
		cout << "The number of rounds must be positive." << endl;
		exit(0);
	}

	int minimum = 2147483647;
	int maximum = -2147483647;
	double totalTries = 0;

	//iterates the number of times the user indicates
	for (int i = 0; i < rounds; i++)
	{
		//generates a random numeber, which is an index
		int wordNum = randInt(0, numWords - 1);

		cout << endl << "Round " << i + 1 << endl;
		cout << "The secret word is " << strlen(wordList[wordNum]) << " letters long." << endl;
	//	cerr << "the secret word is "; print(wordList[wordNum]);

		int tries = runOneRound(wordList, numWords, wordNum);
		if (tries == 1)
		{
			cout << "You got it in 1 try." << endl;
		}
		else
		{
			cout << "You got it in " << tries << " tries." << endl;
		}
		

		if (tries < minimum) //if tries is below the previous minimum, set minimum to tries
		{
			minimum = tries;
		}
		if (tries > maximum) //if tries is above the previous maximum, set maximum to tries
		{
			maximum = tries;
		}
		totalTries += tries;

		cout << "Average: " << fixed << setprecision(2) << ((totalTries) / (i + 1)) << ", minimum: " << minimum << ", maximum: " << maximum << endl;
	}
}

int runOneRound(const char wordList[][MAX_WORD_LENGTH + 1], int numWords, int wordNum)
{
	//checks some initial conditions that must be met
	if (numWords < 1 || wordNum < 0 || wordNum >= numWords)
	{
		return -1;
	}

	char probe[100 /*MAX_WORD_LENGTH + 1*/];
	int stars = 0;
	int planets = 0;

	int tries = 0;

	for(;;) //infinite loop
	{	
		bool valid = true;

		cout << "Probe word: ";
		cin.getline(probe, 100);
		//string must be between 4 and 6 characters, inclusive
		if (strlen(probe) < 4 || strlen(probe) > 6)
		{
			cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
			continue;
		}
		else
		{
			//checks if all the characters are lowercase letters
			for (int i = 0; probe[i] != '\0'; i++)
			{
				//if any of the characters are not lowercase letters, the validity is marked as false
				if (!islower(probe[i]))
				{
					cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
					valid = false;
					break;
				}
			}		
		}
		
		/*
		if ( !cin.getline(probe, MAX_WORD_LENGTH + 1) )
		{
			cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
			cerr << "too long" << endl;		
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		bool valid = true;
		for (int i = 0; probe[i] != '\0'; i++)
		{
			
			if ( ! islower(probe[i]))
			{
				cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
				cerr << "not lowercase letters" << endl;
				valid = false;
				break;
			}
		}
		if (strlen(probe) < 4)
		{
			cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
			cerr << "too short" << endl;
			valid = false;
		}
		*/
		
		if (valid) //ensures the contained code is not run if the input fails to meet the requirements
		{
			//checks if the word is in the list of words
			if (!isRealWord(wordList, numWords, probe))
			{
				cout << "I don't know that word." << endl;
				continue;
			}

			//if the probe matches the word, return the number of tries it took
			tries++;
			if (strcmp(wordList[wordNum], probe) == 0)
			{
				return tries;
			}

			//otherwise, reset values and generate a clue
			stars = 0;
			planets = 0;
			generateClue(wordList[wordNum], probe, stars, planets); //calls the function to calculate stars and planets

			cout << "Stars: " << stars << ", ";
			cout << "Planets: " << planets << endl;
		}
	}
}

void generateClue(const char wordList[], const char probe[], int& stars, int& planets)
{
	//stars and planets essentially 'pair' certain positions in the words; these two arrays are used to keep track of which indices are paired
	int wordUsedPositions[6] = { -1, -1, -1, -1, -1, -1 }; //keeps track of used positions in the secret word
	int usedPositions[6] = { -1, -1, -1, -1, -1, -1 }; //keeps track of positions in probe that have been counted as either a star or planet
	int index = 0;

	for (int i = 0; probe[i] != '\0'; i++)
	{
		//for every letter in probe, if the same letter is in the same position, stars is incremented
		if (probe[i] == wordList[i])
		{
			stars++;
			usedPositions[index] = i; //the position that was 'used' is stored
			wordUsedPositions[index] = i; //for stars, the position in both words are the same
			index++;
		}
	}

	for (int i = 0; probe[i] != '\0'; i++)
	{
		//every letter in probe is compared against every letter in the correct word
		for (int j = 0; wordList[j] != '\0'; j++)
		{
			if (probe[i] == wordList[j] && i != j) //if they're equal and NOT stars
			{
				bool available = true;
				//checks if the position has been counted as either a star or planet
				for (int k = 0; k < 6; k++)
				{
					//if any of the positions have been paired already, they are not available to count again
					if (usedPositions[k] == i || wordUsedPositions[k] == j)
					{
						available = false;
						break;
					}
				}
				//if the position has not been used already, increment planets and mark the position as used
				if (available)
				{
					planets++;
					usedPositions[index] = i; //i is used to iterate through probe's characters
					wordUsedPositions[index] = j; //j i used to iterate through the secret word's characters
					index++;
					break;
				}
			}
		}
	}
}

bool isRealWord(const char wordList[][MAX_WORD_LENGTH + 1], int numWords, const char probe[])
{
	//compares the probe word against every word in wordList to see if the word is part of the wordList
	for (int i = 0; i < numWords; i++)
	{
		if (strcmp(wordList[i], probe) == 0)
		{
			return true;
		}
	}
	return false;
}

//prints out an array of characters
void print(const char word[])
{
	for (int i = 0; word[i] != '\0'; i++)
	{
		cerr << word[i];
	}
	cerr << endl;
}