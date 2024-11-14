// Programming Assignment
// Each reference will be at bottom of file and will be numbered
//Brief: https://portal.uclan.ac.uk/ultra/courses/_177144_1/outline/file/_7529994_1


#include <iostream>
#include <string>
#include <functional>
using namespace std;

/*
TODO:		Key: 
			 // fully done
			 / doing
			 
- Research how to read and write to files, probably JSON or maybe an sqlite db
- Research Constant Variables
- Finish Add Credits Function /
	fix too big check 
- Finish Create Order Function
- Finish View Recent Function
*/


//Classes Not Done / Don't know if gonna use
//class Potato {
//public:
//	string name;
//	double price;
//};
//
//class Topping {
//public:
//	string name;
//	double price;
//};
//
//class Extra {
//public:
//	string name;
//	double price;


// Reference 2
// Function loops over every character in the string until it reaches a letter and stops and returns false otherwise true.


//reference 1 
void addCredits(std::function<void()> ptr) {
	// Set Variables
	string creditAnswerS;
	double creditAnswerD;
	string sure = "n";
	double credits = 0;
	char* p;

	cout << endl << "-----Add Credits-----\nCurrent Credits: " << credits;
	//ask user to input an amount of credits then ask if they're sure and check if answer is valid by looping until the answer is yes.
	while (sure != "y") {
		while (true) {
			cout << endl << "How many credits would you like to add?\n- ";
			cin >> creditAnswerS;
			// convert string to a double
			creditAnswerD = strtod(creditAnswerS.c_str(), &p);
			
			if (*p) {
				cout << "Error: NAN";
				continue;
			}
			//make sure it's not too small
			//I think this is fine for a magic number as there's no way it's gonna change.
			if (creditAnswerD < 1.0) {
				cout << endl << "Entry too small";
				continue;
			}
			//make sure it's not too big, this feels wrong but idk
			else if (creditAnswerD > 999999999999999999) {
				cout << endl << "Entry too large";
				continue;
			}
			
			cout << endl << "Are you Sure? (y/n)";
			cin >> sure;
			if (sure == "y") {
				break;
			}
			else if (sure == "n") {
				sure = "n";
				continue;
			}
			else {
				cout << "Error: Invalid Option";
			}

			
		}
		credits += creditAnswerD;
		cout << endl << "New Amount: " << credits << endl << endl;
		ptr();
	}

}
void createOrder(std::function<void()> ptr) {
	cout << endl << "----Create A New Order-----";

}
void viewRecent(std::function<void()> ptr) {
	cout << endl << "----View Recent Orders-----";
}

int main() {
	int welcomeAnswer;
	bool breakwhile = false;
	//loop forever until user types a correct answer answer
	//Sets breakwhile to true when a correct answer is entered
	while (!breakwhile) {
		cout << "----Welcome to Hot Potato!----\nWhat would you like to do?\n1 - Add Credits\n2 - Create an Order\n3 - View Recent Orders\n4 - Quit\n- ";
		cin >> welcomeAnswer;

		//check if answer is valid
		switch (welcomeAnswer) {
			case 1:
				addCredits(main);
				breakwhile = true;
				break;
			case 2:
				createOrder(main);
				breakwhile = true;
				break;
			case 3:
				viewRecent(main);
				breakwhile = true;
				break;
			case 4:
				cout << endl << "Bye!, Come Back Soon!" << endl;
				quick_exit(0);
	
			default:
				cout << "\nError: Invalid Option\n";
				break;
		}
	}

}







/*
References:

1 - https://www.quora.com/How-do-you-pass-a-function-to-another-function-in-C-and-what-is-its-use
2 - https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c

*/