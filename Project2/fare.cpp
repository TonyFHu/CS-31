#include <iostream>
#include <cmath>
#include <string>
//#include <iomanip>

using namespace std;

double fare(int age, bool isStudent, int numBoundaries);

int main()
{
	int age, numBoundaries;
	bool isStudent;
	string student, destination;

	cout << "Age of rider: ";
	cin >> age;

	cin.ignore(10000, '\n');

	if (age < 0)
	{
		cout << "---" << endl;
		cout << "The age must not be negative" << endl;
		return 0;
	}

	cout << "Student? (y/n): ";
	getline(cin, student);

	if (student == "y")
		isStudent = true;
	else if (student == "n")
		isStudent = false;
	else
	{
		cout << "---" << endl;
		cout << "You must enter y or n" << endl;
		return 0;
	}

	cout << "Destination: ";
	getline(cin, destination);

	if (destination == "")
	{
		cout << "---" << endl;
		cout << "You must enter a destination" << endl;
		return 0;
	}

	cout << "Number of zone boundaries crossed: ";
	cin >> numBoundaries;

	if (numBoundaries < 0)
	{
		cout << "---" << endl;
		cout << "The number of zone boundaries crossed must not be negative" << endl;
		return 0;
	}

	cout.precision(2);
	cout << "---" << endl;
	cout << "The fare to " << destination << " is $" << fixed << fare(age, isStudent, numBoundaries) << endl;
}

//calculates fare
double fare(int age, bool isStudent, int numBoundaries)
{
	bool senior = (age > 64);

	if (senior)
	{
		if (numBoundaries == 0)
		{
			return 0.45;
		}
		if (isStudent && numBoundaries == 1)
		{
			return 0.65;
		}
		return .55 + .25*numBoundaries;
	}

	if (numBoundaries <= 1)
	{
		if (age < 18 || isStudent)
		{
			return 0.65;
		}
	}
	return 1.35 + .55*numBoundaries;

}