#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

int encodeSong(string song, string& instructions, int& badBeat);
bool hasCorrectSyntax(string song);
bool isPlayable(string beat);
char encodeNote(int octave, char noteLetter, char accidentalSign);
vector<string> divideIntoBeats(string song);
vector<string> divideIntoNotes(string song);


int main()
{
	string UNJUST_LIFE = "F5D3//A4A3//F4D4//A4//E5C3//A4A3//F4C4//A4//D5B2//A4F3//D4Bb3//A4//C5A2//G4G3//C4//G3A2//D5G2//F4F3//D4B3//F4//E5A2//G4G3//E4C4//C5//D5Bb2//D4F3//A4A3//D4F3//E5C3//G3//C4E4////F5D3//A4A3//F4D4//F5//E5C3//A4A3//E4C4//A4A3//D5Bb2//A4F3//D4A3//D5//C5A2//C4G3//G4E3//A2//D5G2//F3//Bb3D4//F4//G4A2//G3//C4E4//E4//D4D3//A3//D4//G4//F#4D4////////F4D4D3//G4A3//A4D4//A3//C3//F5A3//E5C4//A4//G4D4Bb2//A4A3//F3//F4D3//G4C4A2//A4F3//A3//D4/E4/F4Bb3G2//F3//E4Bb3//F4F3//G4C4A2//G3//C4//F4G3//G4D4B2//G3//D4//A4G3//A4E4C#3//A3//E4C#4////F4D4D3//G4E4A3//A4F4D4//A3//C3//F5//E5C4//A4A3//G4D4Bb2//A4F3//D4//F4F3//G4C4A2//A4G3//C4//D4/E4/F4Bb3D3//F3//E4Bb3//F4F3//G4C4A2//E3//C4//E4//D4A3D2//A2//G3D3//A3//F#3//D3//D2//D3/";
	string CYGNUS_GARDEN = "Eb3Eb2//D4Bb3G3//D4Bb3G3//D4Bb3G3////D3D2//C4A3F3//C4A3F3//C4A3F3////G3G2//C4A3//Bb3G3//G3G2//A3F3//Bb3G3//A4A3F3//Bb4Bb3G3G2//C5C4A3//D5D4Bb3G3G2//Eb5C5Eb4F3F2//F5F4D4Bb3//G5G4Eb3Eb2//D4Bb3G3//D4Bb3G3//D5D4Bb3G3////G5//C6D3D2//F4C4A3F3//F4C4A3F3//F4C4A3F3//A5//F5//G5G2//D4Bb3/Eb4C4/D4Bb3//G3G2//C4A3/D4Bb3/C4A3//Bb3G3G2//C4A3//D4Bb3//G4Bb3G3G2//////G4Eb3Eb2//D4Bb3G3//D4Bb3G3//G4Eb3Eb2/D5/C5D4Bb3G3/Bb4/A4/G4/A4F3F2//C4A3F3//C4A3F3//F4F3F2//C4A3F3//Bb4//G4G3G2//D4Bb3G3//D4Bb3G3/C4/D4G3G2//C4A3F3//F4C4A3F3//D4G3G2//D4Bb3G3//D4Bb3G3//Bb3F3F2//C4A3//D4Bb3//G4Eb3Eb2//D4Bb3G3//D4Bb3G3//G4Eb3Eb2/D5/C5D4Bb3G3/Bb4/A4/G4/A4F3F2//C4A3F3//C4A3F3//F4F3F2/G4/A4C4A3F3/Bb4/A4//G4G3G2//D4Bb3G3D3//Bb3G3D3/C4/D4G3G2//C4A3F3//F4C3A3F3//D4G3G2//Bb3G3D3//G3D3//Bb3Bb2//C4C3/D4/G4D4D3/D5/G5Eb3Eb2//G4Eb4Bb3//G4Eb4Bb3//C5Eb3Eb2//Eb4Bb3G3//Eb4Bb3G3/Bb4/C5F3F2//F4C4A3//F4C4A3//F5F3F2//F4C4A3//Eb5F4C4A3//D5Bb3Bb2//D5F4D4Bb3/Eb5/D5D4Bb3//A3A2//C5F4D4Bb3/D5/C5F4D4Bb3//Bb4G3G2//A4D4Bb3G3//C5Eb4Bb3G3//Bb4F3F2//F4Bb3G3//A4F4Bb3G3//G4C3C2//Eb4C4G3//Eb4C4G3//Eb4C3C2//Eb4C4G3/F4/G4Eb4C4G3/C5/A4D3D2//C4A3F3//C4A3F3//F4D3D2//C4A3F3//D4C4A3F3//G4G3G2//Bb3G3/C4A3/D4Bb3//";
	string SUMMER = "B2//F#3//B3//F#3//G2//D3//G3//D3//A2//E3//A3//E3//D3//A3//D4//A3//B2//F#3//B3//F#3//G2//D3//G3//D3//A2//E3//A3//E3//D3//A3//D4A4/D5/A3E5/F#5/E5B2//D5F#3/D5/B3//F#3//G2//D3//A4G3/D5/E5D3/F#5/E5A2//D5E3/E5/A3/F#5/E3/F#5/D3//A3//A4D4/D5/E5A3/F#5/E5B2//D5F#3/D5/B3//F#3//G2//D3//A4G3/D5/E5D3/F#5/E5A2//D5E3/E5/A3/A5/E3/F#5/D3//A3//F#5F#4D4//G5G4A3//A5C#5A4A2//A5C#5A4E3/A5C#5A4/A3//A5C#5A4E3//A5B4G2//F#5B4D3/D5B4/G3//F#5D3/G5/A5C#5A4F#2//A5C#5A4C#3/A5C#5A4/F#3//A5C#5A4C#3//A5D5B4B2//F#5B3F#3/D5B4/B3//D5F#3/E5/F#5B4G#4E2//F#5B4G#4B2/F#5B4G#4/E3//F#5B4G#4B2//F#5B4G4G2//B5D3//B5G3/E5/D5D3//E5A2//E3//E5B4G4A3//E5B4G4E3/E5B4G4/E5B4G4A2//C#5E3//A4A3/D5/E5E3/F#5/E5B2//D5F#3/D5/B3//F#3//G2//D3//A4G3/D5/E5D3/F#5/E5A2//D5E3/E5/A3/F#5/E3/F#5/D3//A3//A4D4/D5/E5A3/F#5/E5B2//D5F#3/D5/B3//F#3//G2//D3//A4G3/D5/E5D3/F#5/E5A2//D5E3/E5/A3/A5/E3/F#5/D3//A3//F#5F#4D4//G5G4A3//A5C#5A4A2//A5C#5A4E3/A5C#5A4/A3//A5C#5A4E3//A5B4G2//F#5B4D3/D5B4/G3//F#5D3/G5/A5C#5A4F#2//A5C#5A4C#3/A5C#5A4/F#3//A5C#5A4C#3//A5D5B4B2//F#5B3F#3/D5B4/B3//D5F#3/E5/F#5D5G#4E2//F#5D5G#4B2/F#5D5G#4/E3//F#5D5G#4B2//F#5C#5G4A3A2//B5E5/F#5/E5/D5/B4/D5D3//A3//D4//A3//B2//F#3//B3//F#3/";
	string HOWLS_MOVING_CASTLE = "D4D2//G4D4Bb3G3//Bb4D4Bb3G3//D5C3C2//G4Eb4C4G3//D5G4Eb4C4G3//C5D3D2//Bb4Gb4Eb4C4A3//A4Gb4Eb4C4A3//Bb4G3G2//F4Bb3A3//F4Bb3A3//G4G3G2//Bb4F4D4Bb3//D5F4D4Bb3//G5C3C2//G4D4Bb3//G5G4D4Bb3//G5F3F2//F5F4Eb4A3//Eb5F4Eb4A3//F5Bb2//F4D4A3//F4D4A3//A4F3F2//D5F4D4A3//F5F4D4A3//A5E3E2//A4D4Bb3//G5G4D4Bb3//F5A3A2//E5C#4A3G3//F5C#4A3G3//G5D3D2//G4D4A3//F5F4D4A3//E5C3C2//E4A3F3//D5D4A3F3//C5Bb2//Bb4D4A3F3//C5D4A3F3//D5A2//C5E4D4A3//G4E4D4A3//A4D3D2//G4D4A3//G4D4A3//D4D3D2//G4D4Bb3G3//Bb4F#4D4Bb3G3//D5Eb4G4C3C2//G4Eb4C4G3//D5G4Eb4C4G3//C5A4F#4D3D2//Bb4Gb4Eb4C4A3//A4Gb4Eb4C4A3//Bb4F4D4Bb3G3G2//F4Bb3A3//F4Bb3A3//G4Bb3Eb4Ab3F3//Bb4/D4Ab3F3/D5//G5Bb4Eb3Eb2//G4D4Bb3//G5G4D4Bb3//G5Bb4Eb3Eb2//A5F4Eb4A3//F5F4Eb4A3/Eb5/F5A4D3D2//F4D4A3//F4D4A3//A4G3G2//D5F4D4A3//F5F4D4A3//A5E3E2//A4D4Bb3//G5G4D4Bb3//A2//F5C#4A3G3/E5/D#5C#4A3G3/E5/G5D3D2//A4D4A3//F5F4D4A3//C3C2//E5E4A3F3/D5/C#5D4A3F3/D5/D5Bb2//C5D4A3F3/D5/C5D4A3F3/Bb4/A4A2//C#4A3G3/B4/C#5C#4A3G3//D5D3D2//";
	
	string song = ""; 
	string instructions;
	int badBeat;

	for (;;)
	{
		song = "";
		instructions = "?????";
		badBeat = -888;
		cout << "Enter song: " << endl;
		getline(cin, song);
		cerr << encodeSong(song, instructions, badBeat) << endl << "------------" << endl;
		cerr << badBeat << endl;
		cerr << instructions << endl << endl;
	}
}

bool hasCorrectSyntax(string song)
{
	//checks the last character; must be a / to end the beat
	//avoids a negative index
	if (song != "" && song[song.size() - 1] != '/')
	{
		return false;
	}

	int index = 0;
	while (index < song.size())
	{
		switch (song[index])
		{
		//any of these are valid on their own
		case '/':
			index++;
			break;
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
			index++;
			//b and # must follow a letter
			if (song[index] == 'b' || song[index] == '#')
				index++;
			//the digit follows the accidental if it exists, the letter if not
			if (isdigit(song[index]))
				index++;
			break;
		default:
			return false;
		}
	}
	return true;
}

//checks if all notes are within the playable range
bool isPlayable(string song)
{
	vector<string> notes = divideIntoNotes(song);
	for (int i = 0; i < notes.size(); i++)
	{
		//default if not specified
		int octave = 4;
		char accidental = ' ';

		//get the first and last character of the note
		string note = notes[i];
		char firstCharacter = note[0];
		char lastCharacter = note[notes[i].size() - 1];

		if (isdigit(lastCharacter))
			octave = lastCharacter - '0'; //character to int
		if (note.size() > 1 && (note[1] == 'b' || note[1] == '#')) //the accidental is always the 2nd character in a note
			accidental = note[1];


		//creates an integer score representing the note
		int score = 0;
		switch (firstCharacter)
		{
		case 'C':  score = 0; break;
		case 'D':  score = 2; break;
		case 'E':  score = 4; break;
		case 'F':  score = 5; break;
		case 'G':  score = 7; break;
		case 'A':  score = 9; break;
		case 'B':  score = 11; break;
		default:   
			return false;
		}
		switch (accidental)
		{
		case '#':  score++; break;
		case 'b':  score--; break;
		case ' ':  break;
		}


		//anything lower than B#1 and higher than C6 is unplayable
		score += 12*octave;
		if (score < 24 || score > 72) //24 is equivalent B#1(C2) and 72 is equivalent to C6
		{
			return false;
		}
	}
	return true;
}


int encodeSong(string song, string& instructions, int& badBeat)
{
	if (hasCorrectSyntax(song))
	{
		//checks each beat for playability, setting badBeat equal to the firet beat with an unplayable note
		int beat = 1;
		vector<string> beats = divideIntoBeats(song); //gets each individual beat as an entry in a vector
		for (int i = 0; i < beats.size(); i++)
		{
			if (!isPlayable(beats[i]))
			{
				badBeat = beat;
				return 2;
			}
			beat++;
		}

		instructions = ""; //clears whatever was in instructions before

		//goes through every beat
		for (int i = 0; i < beats.size(); i++)
		{
			vector<string> notes = divideIntoNotes(beats[i]); //gets every note in a beat as an entry in a vector

			if (notes.size() > 1) //if the beat has more than one note, use brackets
				instructions += "[";

			if (beats[i] == "/") //if the beat is just a slash, add a space
			{
				instructions += " ";
			}

			//goes through each note and retrieves the note letter, octave, and accidental
			//then passes them to encodeNote
			for (int j = 0; j < notes.size(); j++)
			{
				//default if nothing attached to the letter
				int octave = 4;
				char accidental = ' ';

				string note = notes[j];
				char firstCharacter = note[0];
				char lastCharacter = note[notes[j].size() - 1];

				if (isdigit(lastCharacter)) //if there's a number, set that as the octave number; if not, use default
					octave = lastCharacter - '0'; //convert to int
				if (note.size() > 1 && (note[1] == 'b' || note[1] == '#')) //if there's an accidental, store it
					accidental = note[1];

				instructions += encodeNote(octave, firstCharacter, accidental);
			}
			if (notes.size() > 1)
				instructions += "]";
		}
		return 0;
	}
	else
	{
		return 1;
	}
	
}


//divides the song string into individual beats
vector<string> divideIntoBeats(string song)
{
	vector<string> beats;
	int index = 0;

	while (index < song.size())
	{
		int lengthOfBeat = song.find('/', index) - (index - 1); //searching for a slash starting at index; sets lengthOfBeat equal to the number of characters searched to find the slash (including the slash)
		beats.push_back( song.substr(index, lengthOfBeat) ); //takes the substring, which will always end in a slash, and adds it to the vector
		index += lengthOfBeat; //moves the index to the character after the slash
	}

	return beats;
}

//divides a song string into individual notes in a vector
vector<string> divideIntoNotes(string song)
{
	vector<string> notes;

	//*remove all slashes*
	while (song.find('/') != string::npos)
		song = song.erase(song.find('/'), 1);
	
	//iterates through each character
	//Each capital A-G is the start of a new note; checks for an accidental and digit
	//adds each note to a vector
	string note = "";
	for (int i = 0; i < song.size(); i++)
	{
		switch (song[i])
		{
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
			note += song[i]; //takes the letter and adds it to note
			i++; //moves on to the next character
			break;
		default:
			cerr << "Not a valid song string" << endl;
		}
	
		//apparently, the grading script doesn't like an index equal to the size. Even though it works with both compilers.
		if (i < song.size())
		{

			//if the next character is an accidental, add it to note
			if (song[i] == 'b' || song[i] == '#')
			{
				note += song[i];
				i++; //move on to the next character
			}
			//if the next character is a digit, add it to note
			if (isdigit(song[i]))
			{
				note += song[i];
				//no need to increment since the for loop already does that
			}
			else
				i--; //if there was no digit, then the character is the start of a new note, but since the for loop will increment i, i needs to be decremented to avoid skipping the next letter
		}
		notes.push_back(note); //adds the note to the vector
		note = "";
	}
	return notes;

}


//*************************************
//  encodeNote
//*************************************

// Given an octave number, a note letter, and an accidental sign, return
// the character that the indicated note is encoded as if it is playable.
// Return a space character if it is not playable.
//
// First parameter:   the octave number (the integer 4 is the number of the
//                    octave that starts with middle C, for example).
// Second parameter:  an upper case note letter, 'A' through 'G'
// Third parameter:   '#', 'b', or ' ' (meaning no accidental sign)
//
// Examples:  encodeNote(4, 'A', ' ') returns 'Q'
//            encodeNote(4, 'A', '#') returns '%'
//            encodeNote(4, 'H', ' ') returns ' '

char encodeNote(int octave, char noteLetter, char accidentalSign)
{
	// This check is here solely to report a common CS 31 student error.
	if (octave > 9)
	{
		cerr << "********** encodeNote was called with first argument = "
			<< octave << endl;
	}

	// Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
	//      to -1, 0,   1,   2,   3, ...,  11, 12

	int note;
	switch (noteLetter)
	{
	case 'C':  note = 0; break;
	case 'D':  note = 2; break;
	case 'E':  note = 4; break;
	case 'F':  note = 5; break;
	case 'G':  note = 7; break;
	case 'A':  note = 9; break;
	case 'B':  note = 11; break;
	default:   return ' ';
	}
	switch (accidentalSign)
	{
	case '#':  note++; break;
	case 'b':  note--; break;
	case ' ':  break;
	default:   return ' ';
	}

	// Convert ..., A#1, B1, C2, C#2, D2, ... to
	//         ..., -2,  -1, 0,   1,  2, ...

	int sequenceNumber = 12 * (octave - 2) + note;

	string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
	if (sequenceNumber < 0 || sequenceNumber >= keymap.size())
		return ' ';
	return keymap[sequenceNumber];
}