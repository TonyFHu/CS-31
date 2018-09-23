#include <iostream>
#include <string>
#include <cassert>
using namespace std;



int appendToAll(string a[], int n, string value)
{
	if (n < 0)
	{
		return -1;
	}

	//iterates through each element and adds value onto the end
	for (int i = 0; i < n; i++)
	{
		a[i] += value;
	}
	return n;
}

int lookup(const string a[], int n, string target)
{
	//iterates through each element
	for (int i = 0; i < n; i++)
	{
		//returns the first position where the target is equal to the element
		if (a[i] == target)
		{
			return i;
		}
	}
	//if the loop finishes without returning a value, then there is no value target in a
	return -1;
}

int positionOfMax(const string a[], int n)
{
	if (n <= 0)
	{
		return -1;
	}

	int currentMax = 0; //keeps track of the current maximum position
	for (int i = 1; i < n; i++)
	{
		//if the value at i is greater than the current maximum, set the current maximum position to i
		if (a[i] > a[currentMax])
		{
			currentMax = i;
		}
	}
	return currentMax;
}

int rotateLeft(string a[], int n, int pos)
{
	if (n < 0 || pos >= n || pos < 0)
	{
		return -1;
	}

	string temp = a[pos]; //stores the value at pos
	for (int i = pos; i < n - 1; i++) //starts at the position of the 'removed' element and ends one before the end
	{
		a[i] = a[i + 1]; //sets each value to the value of the one afterwards
	}
	a[n - 1] = temp; //sets the last value to the original value of a at pos
	return pos;
}

int countRuns(const string a[], int n)
{
	if (n < 0)
	{
		return -1;
	}

	//if there are no elements in the array, the amount of runs is zero
	if (n == 0)
	{
		return 0;
	}

	int run = 1; //if there are more than zero elements, then the minimum number of runs is 1
	for (int i = 1; i < n; i++) //starts at position 1 in order to compare to i-1
	{
		//if the value at i differs from the previous value, then run is incremented
		if (a[i] != a[i - 1])
		{
			run++;
		}
	}
	return run;
}

int flip(string a[], int n)
{
	if (n < 0)
	{
		return -1;
	}

	string swap = "";
	//iterates through half of the array, rounded up
	for (int i = 0; i < (n+1)/2; i++)
	{
		int index = (n-1) - i; //the 'mirrored' position of i. (if i is the first position, then index is the last. if i is the second, index is the second to last)
		//swaps the values in the positions i and index
		swap = a[i];
		a[i] = a[index];
		a[index] = swap;
	}
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)
	{
		return -1;
	}

	//finds the shorter of the two arrays
	int minElements = 0;
	if (n2 < n1)
	{
		minElements = n2;
	}
	else
	{
		minElements = n1;
	}

	//iterates through index values of the shorter array
	for (int i = 0; i < minElements; i++)
	{
		if (a1[i] != a2[i]) //at the first position where the arrays differ, returns the position
		{
			return i;
		}
	}
	//if there was no difference, return the size of the shorter array
	return minElements;
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
	if (n2 < 0)
	{
		return -1;
	}
	//a subsequence of zero elements is an element of any array
	if (n1 == 0 && n2 == 0)
	{
		return 0;
	}

	//iterates through a1
	for (int i = 0; i < n1-(n2-1); i++) //stops once the remaining elements in a1 are not enough to contain a2
	{
		bool match = true;
		//iterates through a2 and a1
		for (int j = 0; j < n2; j++)
		{
			//if all elements a2[j] are equal to elements a1[i+j], then match remains true
			if (a1[i+j] != a2[j]) //j is used to iterate through both a2 and a1, but a1 starts at position i instead of 0
			{
				match = false;
			}
		}
		if (match)
		{
			return i;
		}

	}
	return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
	//iterates through both arrays with a1 being 'first'/slower
	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			//checks a1[i] against all values of a2 and returns as soon as any match is found
			if (a1[i] == a2[j])
			{
				return i;
			}
		}
	}
	return -1;
}

int split(string a[], int n, string splitter)
{
	if (n < 0)
	{
		return -1;
	}
	//alphabetizes the array
	for (int i = 0; i < n; i++)
	{
		//each iteration, the maximum value is found using positionOfMax and placed on the end using rotateLeft
		//by passing an n value that decreases each iteration, the values that have been placed on the end are ignored and the max of the remaining elements are sorted
		rotateLeft(a, n - i, positionOfMax(a, n - i));
	}

	for (int i = 0; i < n; i++)
	{
		if (a[i] >= splitter) //finds the first position where the value is not less than splitter (greater than or equal to)
		{
			return i;
		}
	}
	return  n;
}


int main()
{
	string h[10] = { "selina", "reed", "diana", "tony", "", "logan", "peter", "que", "zzzz", "queue" };
	assert(lookup(h, 9, "que") == 7);
	assert(countRuns(h, -4) == -1);
	assert(lookup(h, 7, "queue") == -1);
	assert(lookup(h, 10, "") == 4);
	assert(positionOfMax(h, 0) == -1);

	string g[7] = { "selina", "reed", "diana", "tony", "", "logan", "pete" };
	assert(differ(h, 1, g, 0) == 0);
	assert(appendToAll(g, 7, "?") == 7 && g[0] == "selina?" && g[3] == "tony?");
	assert(rotateLeft(g, 0, 1) == -1 && g[1] == "reed?" && g[4] == "?");

	string e[4] = { "que", "zzzz", "queue", "logan" };
	assert(subsequence(h, 0, e, 2) == -1);

	string d[4] = { "reed", "reed", "test", "tony" };
	assert(countRuns(d, 3) == 2);

	string f[7] = { "zzzz", "selina", "steve", "jacob", "qqqqq", "bbbbb", "asdf" };
	assert(lookupAny(h, 10, f, 1) == 8);
	assert(flip(f, 7) == 7);
	assert(f[0] == "asdf");
	assert(f[1] == "bbbbb");
	assert(f[3] == "jacob");
	assert(f[6] == "zzzz");

	string alpha[9] = { "fb","hb","cb","eb","ab","db","gb","ib","bb" };
	for (int i = 0; i < 9; i++)
	{
		cout << alpha[i] << ", ";
	}
	cout << endl;
	assert(split(alpha, 9, "f") == 5);

	for (int i = 0; i < 9; i++)
	{
		cout << alpha[i] << ", ";
	}
	cout << "All tests succeeded" << endl;
}
