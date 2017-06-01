//This program asks a user for a number of test scores they would like to enter, then prompts them to enter the scores.
//The program then sorts the array of scores in ascending order, and calculates the average of the scores for the user.
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//Function prototypes
void getGrades(double*, int);
void sort(double*, int);
double average(double*, int);
void displayGrades(double*, int, double);

int main()
{
	char again;						//To ask user if they want to run the program again
	int numTestScores;				//Holds the number of test scores the user wants to enter (size of the dynamically allocated array)
	double *testScores = nullptr;	//To dynamically allocate an array to hold the test scores
	double scoreAverage;			//To hold the average of the test scores

	//const int numTestScores = 5;				//For testing purposes only
	//double testScores[numTestScores];			//For testing purposes only

	do {
		cout << "Test Score Program\n"
			<< "****************************************\n\n";
		
		cout << "How many test scores would you like to enter? ";
		cin >> numTestScores;
		while (numTestScores < 1)	//Input validation
		{
			cout << "\nError! You must enter a number greater than 0.  Please try again.\n\n";
			cout << "How many test scores would you like to enter? ";
			cin >> numTestScores;
		}

		//Dynamically allocate a new array based on the number of test scores the user wants to enter
		testScores = new double[numTestScores];
		
		//Get the grades from the user and validate them
		getGrades(testScores, numTestScores);

		//Sort the array of test scores
		sort(testScores, numTestScores);

		//Calculate the average of the test scores
		scoreAverage = average(testScores, numTestScores);

		//Display the information for the user
		displayGrades(testScores, numTestScores, scoreAverage);

		//Delete the dynamically allocated memory to free it for future use
		delete[] testScores;	

		cout << "Would you like to run the program again? (y/n): ";
		cin >> again;
		cin.ignore();

	} while (again == 'y' || again == 'Y');

	cout << "\nThank you for using this program!\n\n";
	char ch;
	ch = cin.get();

	return 0;
}

void getGrades(double* score, int size)
{
	cout << "\nPlease enter test scores now.\n\n";
	for (int count = 0; count < size; count++)
	{
		cout << "Score #" << (count + 1) << ": ";
		cin >> *(score + count);	//Add the value of count to the address of the score pointer, and store user's input in that location
		cin.ignore();

		//Input validation
		while (*(score + count) < 0)
		{
			cout << "\nError! You must enter a positive number.  Please try again.\n\n";
			cout << "Score #" << (count + 1) << ": ";
			cin >> *(score + count);
			cin.ignore();
		}
	}
}

void sort(double* score, int size)
{
	//Since the user might want to enter a lot of test scores, this function uses a selection sort to maximize efficiency.

	//Tools needed to perform the sorting operation
	int startScan, minIndex;
	double minValue;

	for (startScan = 0; startScan < (size - 1); startScan++)
	{
		minIndex = startScan;
		minValue = *(score + startScan);
		for (int index = (startScan + 1); index < size; index++)
		{
			if (*(score + index) < minValue)
			{
				minValue = *(score + index);
				minIndex = index;
			}
		}
		*(score + minIndex) = *(score + startScan);
		*(score + startScan) = minValue;
	}
	
	/*
	***********************************************************************************************************************
	Bubble sort code:

		bool swap;
		int temp;

		do
		{
			swap = false;
			for (int count = 0; count < (size - 1); count++)
			{
				if (*(score + count) > *(score + count + 1))
				{
					temp = *(score + count);
					*(score + count) = *(score + count + 1);
					*(score + count + 1) = temp;
					swap = true;
				}
			}
		} while (swap);

	***********************************************************************************************************************
	*/
}

double average(double* score, int numScores)
{
	double accumulator = 0;
	double calcAverage;

	for (int count = 0; count < numScores; count++)
	{
		accumulator += *(score + count);
	}

	calcAverage = accumulator / numScores;
	return calcAverage;
}

void displayGrades(double* score, int size, double avg)
{
	cout << "\nYour scores have been sorted in ascending order.\n\n";

	cout << "Score";
	cout << endl << endl;

	//Display the list of scores
	for (int count = 0; count < size; count++)
	{
		cout << fixed << showpoint << setprecision(2) << *(score + count);
		cout << endl << endl;
	}

	//Display the average score
	cout << "Average score: " << fixed << showpoint << setprecision(2) << avg << "\n\n";
}