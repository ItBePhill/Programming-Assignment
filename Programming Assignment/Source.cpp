// Programming Assignment
// Each reference will be at bottom of file and will be numbered
//Brief: https://portal.uclan.ac.uk/ultra/courses/_177144_1/outline/file/_7529994_1


#include <iostream>
#include <string>
#include <functional>
#include <map>
using namespace std;

/*
TODO:		Key: 
			 // fully done
			 / doing
			 
- Research how to read and write to files, probably JSON or maybe an sqlite db
- Research Constant Variables
- Finish Add Credits Function /
- Create new Welcome function so the main function is just calling other functions
- Finish Create Order Function
- Finish View Recent Function
- change to cin.fail()
*/


// User class, gets passed around, contains information about the user.
//credits are passed in as a string for easier storage;
class User {
public:
	string name;
	string credits;
};



//reference 1 
User addCredits(User user) {
	// Set Variables
	string creditAnswerS;
	double creditAnswerD;
	string sure = "n";
	double credits = 0.0;
	char* p;

	cout << endl << "-----Add Credits-----\nCurrent Credits: " << credits;
	//ask user to input an amount of credits then ask if they're sure and check if answer is valid by looping until the answer is yes.
	while (sure != "y") {
		while (true) {
			cout << endl << "Hello! " << user.name << " How many credits would you like to add?\n- ";
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
			else if (creditAnswerD > 999999999999999999.0) {
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
		user.credits = to_string(credits);
		cout << endl << "New Amount: " << credits << endl << endl;
		return user;
	}

}
void createOrder() {
	cout << endl << "----Create A New Order-----";

}
void viewRecent() {
	cout << endl << "----View Recent Orders-----";
}

User createuser(string name, string credits) {
	//User not initialized so create a new user
	User user = User();
	user.credits = credits; 
	user.name = name;
	return user;
}


int main(User user) {
	int welcomeAnswer;
	bool breakwhile = false;
	string name;
	//check if the user is initialized or not (will be changed in the future, will read from file)
	if (true) {
		cout << "What is your name?\n- ";
		getline(cin, name);
		user = createuser(name, "0");
	}
	//loop forever until user types a correct answer answer
	//Sets breakwhile to true when a correct answer is entered
	while (!breakwhile) {
		cout << "----Welcome to Hot Potato!----\n" << user.name << " What would you like to do?\n1 - Add Credits\n2 - Create an Order\n3 - View Recent Orders\n4 - Quit\n- ";
		cin >> welcomeAnswer;
		//check if answer is valid
		switch (welcomeAnswer) {
			case 1:
				user = addCredits(user);
				breakwhile = true;
				break;
			case 2:
				createOrder();
				breakwhile = true;
				break;
			case 3:
				viewRecent();
				breakwhile = true;
				break;
			case 4:
				cout << endl << "Bye! " << user.name <<  ", Come Back Soon!" << endl;
				quick_exit(0);
	
			default:
				cout << "\nError: Invalid Option\n";
				break;
		}
	}
	main(user);
}





/*
References:

1 - https://www.quora.com/How-do-you-pass-a-function-to-another-function-in-C-and-what-is-its-use
2 - https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c

*/