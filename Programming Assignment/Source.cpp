// Programming Assignment
// Each reference will be at bottom of file and will be numbered
//Brief: https://portal.uclan.ac.uk/ultra/courses/_177144_1/outline/file/_7529994_1


#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <filesystem>
//reference 2
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

/*
TODO:		Key: 
			 // done
			 / doing
			 
- Research how to read and write to files //
- Create ReadJson Function //
- Create UpdateJson Function //
- Finish Add Credits Function //
- Create new Welcome function so the main function is just calling other functions //
- Finish Create Order Function /
- Finish View Recent Function
- change to cin.fail() /
- remove the previous menu when transitioning, so it doesn't fill the cmd //
*/


// User class, gets passed around, contains information about the user.
//credits are passed in as a string for easier storage and reading from json file;
class User {
public:
	string name = "";
	string credits = "0.0";
};


//Update / Create JSON File, takes a user
void UpdateJSON(User user) {
	string filename = "users/" + user.name + ".json";
	json jsonf;
	std::ofstream f(filename);
	jsonf["name"] = user.name;
	jsonf["credits"] = user.credits;
	f << jsonf;
}
//Read Json File, takes a filename
User ReadJson(string filename) {
	User user;
	std::ifstream f(filename);
	json data = json::parse(f);
	cout << data["name"];
	cout << data["credits"];
	user.name = data["name"];
	//this is horrible and I hate it but idk how else to do 
	user.credits = to_string(data["credits"]);
	return user;
}



User addCredits(User user) {
	system("cls");
	// Set Variables
	double minAnswer = 1.0;
	double maxAnswer = 999999999999999999.0;
	string creditAnswerS;
	double creditAnswerD;
	string sure = "n";
	char* notnum;
	double credits = strtod(user.credits.c_str(), NULL);

	cout <<  "-----Add Credits-----\nCurrent Credits: " << credits;
	//ask user to input an amount of credits then ask if they're sure and check if answer is valid by looping until the answer is yes.
	while (sure != "y") {
		while (true) {
			cout << endl << "How many credits would you like to add? or type -1 to return to the menu\n- ";
			cin >> creditAnswerS;
			// convert string to a double
			creditAnswerD = strtod(creditAnswerS.c_str(), &notnum);
			// make sure it's a number. reference 1
			if (*notnum) {
				cout << "Error: NAN";
				continue;
			} 
			//make sure it's not too small
			if (creditAnswerD < minAnswer) {
				if (creditAnswerD == -1) {
					return user;
				}
				else {
					cout << endl << "Entry too small";
					continue;
				}
				
			}
			//make sure it's not too big
			else if (creditAnswerD > maxAnswer) {
				cout << endl << "Entry too large";
				continue;
			}
			
			cout << endl << "Are you Sure?\nNew amount will be: " << credits + creditAnswerD << "\n(y / n)\n- ";
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
		user.credits = credits;
		UpdateJSON(user);
		return user;
	}
	return user;

}
User createOrder(User user) {
	system("cls");
	cout << "----Create A New Order-----";
	return user;
}
User viewRecent(User user) {
	system("cls");
	cout << "----View Recent Orders-----";
	return user;

}


User createuser(string name,  double credits) {
	system("cls");
	//User not initialized so create a new User variable
	User user = User();
	user.credits = credits; 
	user.name = name;
	//Also save to corresponding json file
	UpdateJSON(user);
	return user;
}


void welcome(User user) {
	system("cls");
	int welcomeAnswer;
	bool breakwhile = false;
	//loop forever until user types a correct answer
	//Sets breakwhile to true when a correct answer is entered
	while (!breakwhile) {
		cout << "----Welcome to Hot Potato!----\nHello! " << user.name << "\nWhat would you like to do?\n1 - Add Credits\n2 - Create an Order\n3 - View Recent Orders\n4 - Quit\n- ";
		cin >> welcomeAnswer;
		//check if answer is valid
		switch (welcomeAnswer) {
			//add credits
		case 1:
			//set the user variable to what the fucntion return as this contains the updated credits.
			user = addCredits(user);
			breakwhile = true;
			break;
			//create an order
		case 2:
			user = createOrder(user);
			breakwhile = true;
			break;
			//view recent orders
		case 3:
			user = viewRecent(user);
			breakwhile = true;
			break;
			// quit
		case 4:
			cout << endl << "Bye! " << user.name << ", Come Back Soon!" << endl;
			quick_exit(0);
			// not an option
		default:
			cout << "\nError: Invalid Option\n";
			break;
		}
	}
	// call the function again to return the user to the welcome screen after choosing an option
	welcome(user);
}


int main() {
	// Initialize an empty user to avoid a memory error.
	User user = User();
	string name;
	string filename;
	// check if folders exist that will hold settings if not create them

	//check if config folder exists
	if (!filesystem::exists("config")) {
		filesystem::create_directory("./config");
	}
	//check if potatoes folder exists
	if (!filesystem::exists("config/potatoes")) {
		filesystem::create_directory("./config/potatoes");
	}
	//check if toppings folder exists
	if (!filesystem::exists("config/toppings")) {
		filesystem::create_directory("./config/toppings");
	}
	//check if extras folder exists
	if (!filesystem::exists("config/extras")) {
		filesystem::create_directory("./config/extras");
	}
	//check if users folder exists
	if (!filesystem::exists("users")) {
		filesystem::create_directory("./users");
	}


	//check if the user is initialized or not (if the json file exists)
	cout << "----Startup----\n";
	cout << "What is your name?\n- ";
	getline(cin, name);

	filename = "users/" + name + ".json";
	cout << endl << filename << endl;
	system("pause");
	if (!filesystem::exists(filename)) {
		cout << "User doesn't exist";
		system("pause");
		user = createuser(name, 0.0);

	}
	else {
		user = ReadJson(filename);
	}
	
	
	// start the welcome screen
	welcome(user);
}





/*
References:

1 - https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
2 - Lohmann, N. (2023). JSON for Modern C++ (Version 3.11.3) [Computer software]. https://github.com/nlohmann

*/