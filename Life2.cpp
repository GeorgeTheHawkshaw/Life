//Name: Harold Foster
//NetID: HAF180001

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
using namespace std;

void determineSize(ifstream& input, int& rows, int& columns) {
	string line;
	while (getline(input, line)) {
		rows++;
		if (rows == 1) { //Run this code only once
			columns = line.length(); //Count the # of characters in one row
		}
	}
	input.clear(); //Clear eof flag
	input.seekg(0, ios::beg);
}

int countNeighbors(char* in, int index, int rows, int columns) {
	bool left = false;
	bool right = false;
	bool top = false;
	bool bottom = false;
	int size = rows * columns;
	int neighbors = 0;

	//Corner Checking
	if (index == 0) { //If at top left, evaluate the 3 neighboring cells
		if (*(in + index + 1) == '*') { neighbors++; }
		if (*(in + index + columns) == '*') { neighbors++; }
		if (*(in + index + columns + 1) == '*') { neighbors++; }
		return neighbors;
	}
	if (index == columns - 1) {  //If at top right, evaluate the 3 neighboring cells
		if (*(in + index - 1) == '*') { neighbors++; }
		if (*(in + index + columns) == '*') { neighbors++; }
		if (*(in + index + columns - 1) == '*') { neighbors++; }
		return neighbors;
	}
	if (index == size - columns) { //If at bottom left, evaluate the 3 neighboring cells
		if (*(in + index + 1) == '*') { neighbors++; }
		if (*(in + index - columns) == '*') { neighbors++; }
		if (*(in + index - columns + 1) == '*') { neighbors++; }
		return neighbors;
	}
	if (index == size - 1) { //If at bottom right, evaluate the 3 neighboring cells
		if (*(in + index - 1) == '*') { neighbors++; }
		if (*(in + index - columns) == '*') { neighbors++; }
		if (*(in + index - columns - 1) == '*') { neighbors++; }
		return neighbors;
	}

	//EDGE CHECKING
	if (index < columns) { //Top Edge Checking
		top = true;
	}
	if (index >= size-columns) { //Bottom Edge Checking
		bottom = true;
	}
	if (index % columns == 0) { //Left Edge Checking
		left = true;
	}
	if (index % columns == columns-1) { //Right Edge Checking
		right = true;
	}

	//Evaluate Neighbors For Edges
	if (top) {//If at top or bottom edge, there will be 5 neighboring cells
		if (*(in + index - 1) == '*') { neighbors++; }
		if (*(in + index + 1) == '*') { neighbors++; }
		if (*(in + index +columns) == '*') { neighbors++; }
		if (*(in + index + (columns - 1)) == '*') { neighbors++; }
		if (*(in + index + (columns + 1)) == '*') { neighbors++; }
		return neighbors;
	}
	if (bottom) {
		if (*(in + index - 1) == '*') { neighbors++; }
		if (*(in + index + 1) == '*') { neighbors++; }
		if (*(in + index - columns) == '*') { neighbors++; }
		if (*(in + index - columns - 1) == '*') { neighbors++; }
		if (*(in + index - columns + 1) == '*') { neighbors++; }
		return neighbors;
	}
	if (left) { //Left and right edges will have 5 Neighbors
		if (*(in + index + 1) == '*') { neighbors++; }
		if (*(in + index - columns) == '*') { neighbors++; }
		if (*(in + index - columns + 1) == '*') { neighbors++; }
		if (*(in + index + columns) == '*') { neighbors++; }
		if (*(in + index + columns + 1) == '*') { neighbors++; }
		return neighbors;
	}
	if (right) {
		if (*(in + index - 1) == '*') { neighbors++; }
		if (*(in + index - columns) == '*') { neighbors++; }
		if (*(in + index - columns - 1) == '*') { neighbors++; }
		if (*(in + index + columns) == '*') { neighbors++; }
		if (*(in + index + columns - 1) == '*') { neighbors++; }
		return neighbors;
	}

	//Evaluate Everything else (8 Neighbors)
	if (*(in + index - 1) == '*') { neighbors++; }
	if (*(in + index + 1) == '*') { neighbors++; }
	if (*(in + index - columns) == '*') { neighbors++; }
	if (*(in + index + columns) == '*') { neighbors++; }
	if (*(in + index - columns + 1) == '*') { neighbors++; }
	if (*(in + index - columns - 1) == '*') { neighbors++; }
	if (*(in + index + columns + 1) == '*') { neighbors++; }
	if (*(in + index + columns - 1) == '*') { neighbors++; }
	return neighbors;

}

void print(char* arr, int rows, int columns) {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			cout << *(arr + (r * columns + c));
		}
		cout << endl;
	}
}

void writeOutput(ofstream& output, char* arr, int rows, int columns) {
	int size = rows * columns;
	int counter = 0;
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			output << *(arr + counter);
			counter++;
		}
		if (counter != size) {
			output << endl;
		}
	}
	output.close();
}

void generateMap(ofstream& output) {

	output.open("simbac.txt");
	if (!output) {
		cout << "There was an error opening the output file" << endl;
		exit(0);
	}

	srand(time(0));
	int rows = rand() % 20 + 10;
	int columns = rows;
	int size = rows * columns;
	char* randoarray = new char[size];
	int i = 0;
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			if ((rand() % 10 + 1) > 8) {
				*(randoarray + i) = '*';
			}
			else {
				*(randoarray + i) = ' ';
			}
			output << *(randoarray + i);
			i++;
		}
		output << endl;
	}
	delete[] randoarray;
	output.close();
}

int main() {
	int rows = 0;
	int columns = 0;
	int neighbors = 0;
	ifstream input;
	ofstream output;

	//generateMap(output);

	//Open File, Exit if File is unable to open
	input.open("simbac.txt");
	if (!input) {
		cout << "There was an error opening the file" << endl;
		exit(0);
	}

	//Determine the number of rows anc columns from the file input
	determineSize(input, rows, columns);
	int size = rows * columns;
	char* arr = new char[size]; //arr[i][j] = arr[i*columns+j] = *(arr + (i*columns+j))
	string line;

	//Populate Array with contents of the file
	int counter = 0;
	while (getline(input, line)) {
		for (char c : line) {
			*(arr + counter) = c;
			counter++;
		}
	}
	input.close(); //Close Input File

	//Print 1st Generation
	cout << "Generation 1" << endl;
	print(arr, rows, columns);

	//Ask user for the number of generations to generate
	int numGenerations = 0;
	cout << "Enter the number of generations to simulate (Must be between 1-500): ";
	cin >> numGenerations;
	while (numGenerations < 1 || numGenerations > 500) { //Validate Input
		cout << endl << "You must enter a number between 1-10: ";
		cin >> numGenerations;
	}

	//Create 2nd array, to which the program will populate with the next iteration
	char* arr2 = new char[size];
	
	//Repeat for the number of generations entered
	for (int gen = 0; gen < numGenerations; gen++) {
		for (int i = 0; i < size; i++) {
			//Populate the new array with empty spaces
			*(arr2 + i) = ' ';
			neighbors = countNeighbors(arr, i, rows, columns);

			if (*(arr + i) == '*') { //Checks if cell is occupied
				if (neighbors < 2 || neighbors > 3) {
					*(arr2 + i) = ' ';
				}
				else { //If it's not 2 or 3 neighbors, Keep organism alive
					*(arr2 + i) = '*';
				}
			}
			else { //If cell is empty
				if (neighbors == 3) {
					*(arr2 + i) = '*';
				}
			}
			neighbors = 0;
		}

		//Print Next Generation
		cout << endl << "Generation " << gen+2 << endl;
		print(arr2, rows, columns);

		//Copy second array back into first;
		for (int i = 0; i < size; i++) {
			*(arr + i) = *(arr2 + i);
		}
		Sleep(10);
		system("CLS");
	}

	output.open("simbac.txt");
	if (!output) {
		cout << "There was an error opening the file to write" << endl;
		exit(0);
	}
	writeOutput(output, arr, rows, columns);

	//Deallocate
	delete[] arr; 
	delete[] arr2;
	return 0;
}