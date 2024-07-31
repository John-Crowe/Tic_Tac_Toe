#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

// Define our functions for this game
string getGoodNumber(string array[3][3]);
string getNewArray(string array[3][3]);
void outputGrid(string array[3][3]);
bool isWinner(string array[3][3], string symbol);

int main() {
	// Output introduction
	cout << "Let's Play Tic-Tac-Toe! You will be 'X'\n";

	// Create our starting game grid, which we will use throughout the program
	string array[3][3] = {
		{"1", "2", "3"},
		{"4", "5", "6"},
		{"7", "8", "9"}
	};
	outputGrid(array);

	for (int steps = 0; steps < 9; steps++) {

		// User goes
		if (steps % 2 == 0) {

			// Declare our variables
			string userPick;
			userPick = getGoodNumber(array);
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (array[i][j] == userPick) {
						array[i][j] = "X";
					}
				}
			}

			if (isWinner(array, "X") == true) {
				cout << "Player Wins!!" << endl;
				outputGrid(array);
				break;

			}
		}

		// Computer goes
		else {
			// Initialize vector to store our available options
			vector<vector<int>> availableOptions;

			// Loop through array to find which items have not been selected
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {

					// If spot is available, add to our available options vector
					if ((array[i][j] != "O") && (array[i][j] != "X")) {
						vector<int> availableSpot;
						availableSpot.push_back(i);
						availableSpot.push_back(j);
						availableOptions.push_back(availableSpot);
					}
				}
			}

			// Define parameters we need for options A through C
			bool didPick = false;
			int finalRow;
			int finalCol;

			// Option A: Check for Computer win if they play any available tile and play if yes
			for (int i = 0; i < availableOptions.size(); i++) {

				int row = availableOptions[i][0];
				int col = availableOptions[i][1];

				// Create copy of array
				string copyArray[3][3];
				for (int i = 0; i < 3; ++i) {
					for (int j = 0; j < 3; ++j) {
						copyArray[i][j] = array[i][j];
					}
				}

				copyArray[row][col] = "O";
				if (isWinner(copyArray, "O") == true) {
					array[row][col] = "O";
					didPick = true;
					finalRow = row;
					finalCol = col;
					break;
				}
			}

			// Option B: Only executed if no tile selected, check if player wins if they play any available tile and block if yes
			if (didPick == false) {
				for (int i = 0; i < availableOptions.size(); i++) {

					int row = availableOptions[i][0];
					int col = availableOptions[i][1];

					// Create copy of array
					string copyArray[3][3];
					for (int i = 0; i < 3; ++i) {
						for (int j = 0; j < 3; ++j) {
							copyArray[i][j] = array[i][j];
						}
					}

					copyArray[row][col] = "X";
					if (isWinner(copyArray, "X") == true) {
						array[row][col] = "O";
						didPick = true;
						finalRow = row;
						finalCol = col;
						break;
					}
				}
			}

			// Option C: Pick randomly is nothing selected
			if (didPick == false) {
				srand(time(0));

				int element = rand() % availableOptions.size();
				int row = availableOptions[element][0];
				int col = availableOptions[element][1];
				array[row][col] = "O";
				finalRow = row;
				finalCol = col;
			}

			if (isWinner(array, "O") == true) {
				cout << "Computer took square " << 3 * finalRow + finalCol + 1 << "\n";
				cout << "Computer Wins!!" << endl;
				outputGrid(array);
				break;
			}
			// Row and column given by i and j
			cout << "Computer took square " << 3 * finalRow + finalCol + 1 << "\n";
			outputGrid(array);
		}

		if (steps == 8) {
			cout << "It's a tie!" << endl;
		}
	}
	return 0;
}

string getGoodNumber(string array[3][3])
{
	string num;
	cout << "Pick your tile: \n";
	cin >> num;
	bool isInArray = false;

	while (isInArray == false) // repeat until a positive number is entered
	{
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (array[i][j] == num) {
					isInArray = true;
				}
			}
		}

		if (isInArray == false) {
			cout << "Invalid! Tile is not available\n";
			cout << "Enter another number: ";
			cin >> num;
		}
	}

	return num;
}

void outputGrid(string array[3][3]) {
	for (int i = 0; i < 3; ++i) {
		cout << "_____________\n";
		cout << "| ";
		for (int j = 0; j < 3; ++j) {
			cout << array[i][j] << " | ";
		}
		cout << "\n";
	}
}

// Check if the symbol of choice won and return true/false
bool isWinner(string array[3][3], string symbol) {

	bool winner = false;

	// Conditions for horizontal or vertical tiles
	for (int i = 0; i < 3; i++) {
		bool condition1 = (array[i][0] == symbol) && (array[i][1] == symbol) && (array[i][2] == symbol);
		bool condition2 = (array[0][i] == symbol) && (array[1][i] == symbol) && (array[2][i] == symbol);
		if ((condition1 == true) || (condition2 == true)) {
			winner = true;
		}
	}

	// Conditions for winning diagonal tiles
	bool condition3 = (array[0][0] == symbol) && (array[1][1] == symbol) && (array[2][2] == symbol);
	bool condition4 = (array[0][2] == symbol) && (array[1][1] == symbol) && (array[2][0] == symbol);
	if ((condition3 == true) || (condition4 == true)) {
		winner = true;
	}

	return winner;
}