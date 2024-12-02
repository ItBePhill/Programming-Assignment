/*
Programming Assignment - Source.cpp the main command line program.
e.g. Create users, add credits, create orders and view orders.
Each reference will be at bottom of the file and will be numbered
Brief: https://portal.uclan.ac.uk/ultra/courses/_177144_1/outline/file/_7529994_1
requires C++17 or above.
*/



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
- remove the previous menu when transitioning, so it doesn't fill the cmd //
*/

//includes
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>
#include <filesystem>
#include "./ConfHeader.h"
//reference 2: using json.hpp header to read and write json files.
#include "json.hpp"
using json = nlohmann::json;
//----------------------------------------------------------------
void Config() {
	system("cls");
	std::cout << "----Config----" << std::endl;
	bool breakwhile = false;
	//this isn't great naming but it works for now.
	bool breakwhile2 = false;
	int welcomeAnswer;
	std::string welcomeAnswerString;
	conf::Item item;
	std::string price = "";
	std::string type;
	conf::ItemType itemtype;
	std::vector<std::filesystem::path> paths;

	while (!breakwhile && !std::cin.fail()) {
		std::cout << "What would you like to do?\n1 - Add an Item\n2 - View Items\n- ";
		getline(std::cin, welcomeAnswerString);
		welcomeAnswer = atoi(welcomeAnswerString.c_str());
		//check if answer is valid
		switch (welcomeAnswer) {

		case 1:
			system("cls");
			while (!breakwhile2 && !std::cin.fail()) {
				std::cout << "What is the type of Item you want to add?\n1 - Topping\n2 - Extra\n3 - Potato\n- ";
				getline(std::cin, type);
				switch (atoi(type.c_str())) {
				case 1:
					itemtype = conf::topping;
					breakwhile2 = true;
					break;
				case 2:
					itemtype = conf::extra;
					breakwhile2 = true;
					break;
				case 3:
					itemtype = conf::potato;
					breakwhile2 = true;
					break;
				default:
					std::cout << std::endl << "Error: Not an Option" << std::endl;
					break;
				}

			}
		
		std::cout << "What is the name of the item you would like to add?\n- ";
		getline(std::cin, item.name);

		while (price == "" && !std::cin.fail()) {
			std::cout << "What is the price of the item you would like to add?\n- ";
			getline(std::cin, price);

		}
		item.price = strtod(price.c_str(), NULL);


		conf::Add(item, itemtype);
		std::cout << std::endl << "Successfully Added Item";
		breakwhile = true;
		break;
		
		case 2:
			system("cls");
			while (!breakwhile2 && !std::cin.fail()) {
				std::cout << "What type of items do you want to view?\n1 - Topping\n2 - Extra\n3 - Potato\n- ";
				getline(std::cin, type);
				switch (atoi(type.c_str())) {
				case 1:
					itemtype = conf::topping;
					breakwhile2 = true;
					break;
				case 2:
					itemtype = conf::extra;
					breakwhile2 = true;
					break;
				case 3:
					itemtype = conf::potato;
					breakwhile2 = true;
					break;
				default:
					std::cout << std::endl << "Error: Not an Option" << std::endl;
					break;
				}
			}
			paths = conf::View(itemtype);
			
			switch (itemtype) {
			case conf::topping:
				std::cout << std::endl << "--Toppings--" << std::endl;
				break;
			case conf::extra:
				std::cout << std::endl << "--Extras--" << std::endl;
				break;
			case conf::potato:
				std::cout << std::endl << "--Potatoes--" << std::endl;
				break;

			}
			for (auto i : paths) {
				std::cout << "-----------------------------------" << std::endl;
				conf::Item item;
				std::ifstream f(i);
				json data = json::parse(f);
				std::cout << "Name: " << data["name"] << std::endl;
				std::cout << "Price: " << data["price"];
				std::cout << std::endl << "-----------------------------------" << std::endl;

			}
			breakwhile = true;
			break;

		default:
			std::cout << "\nError: Invalid Option\n";
			break;

		}	
	}
	system("pause");
	bool breakwhile3 = false;

	while (!breakwhile3 && !std::cin.fail()) {
		std::cout << "Would you like to return to the config menu or quit?\n1 - return to config menu\n2 - Quit\n- ";
		std::getline(std::cin, welcomeAnswerString);
		welcomeAnswer = atoi(welcomeAnswerString.c_str());
		//check if answer is valid
		switch (welcomeAnswer) {
			//add credits
		case 1:
			Config();
			break;
			//create an order
		case 2:
			quick_exit(0);
		default:
			std::cout << "\nError: Invalid Option\n";
			break;
		}
	}
}


// User class, gets passed around, contains information about the user.
class User {
public:
	std::string name = "";
	double credits = 0.00;
};

//Update / Create JSON File, takes a user
void UpdateJSON(User user) {
	std::string filename = "users/" + user.name + ".json";
	json jsonf;
	std::ofstream f(filename);
	jsonf["name"] = user.name;
	jsonf["credits"] = user.credits;
	f << jsonf;
}
//Read Json File, takes a filename
User ReadJson(std::string filename) {
	User user;
	std::ifstream f(filename);
	json data = json::parse(f);
	std::cout << data["name"];
	std::cout << data["credits"];
	user.name = data["name"];
	//this is horrible and I hate it but idk how else to do 
	user.credits = strtod(to_string(data["credits"]).c_str(), NULL);
	return user;
}



User addCredits(User user) {
	system("cls");
	// Set Variables
	const double minAnswer = 1.0;
	const double maxAnswer = 999999999999999999.0;
	std::string creditAnswerS;
	double creditAnswerD;
	std::string sure = "n";
	char* notnum;
	double credits = user.credits;

	std::cout <<  "-----Add Credits-----\nCurrent Credits: " << credits;
	//ask user to input an amount of credits then ask if they're sure and check if answer is valid by looping until the answer is yes.
	while (sure != "y") {
		while (true) {
			std::cout << std::endl << "How many credits would you like to add? or type -1 to return to the menu\n- ";
			std::getline(std::cin, creditAnswerS);
			// convert std::string to a double
			creditAnswerD = strtod(creditAnswerS.c_str(), &notnum);
			// make sure it's a number. reference 1
			if (*notnum) {
				std::cout << "Error: NAN";
				continue;
			} 
			//make sure it's not too small
			if (creditAnswerD < minAnswer) {
				if (creditAnswerD == -1) {
					return user;
				}
				else {
					std::cout << std::endl << "Entry too small";
					continue;
				}
				
			}
			//make sure it's not too big
			else if (creditAnswerD > maxAnswer) {
				std::cout << std::endl << "Entry too large";
				continue;
			}
			
			std::cout << std::endl << "Are you Sure?\nNew amount will be: " << credits + creditAnswerD << "\n(y / n)\n- ";
			std::getline(std::cin, sure);
			if (sure == "y") {
				break;
			}
			else if (sure == "n") {
				sure = "n";
				continue;
			}
			else {
				std::cout << "Error: Invalid Option";
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
	std::cout << "----Create A New Order-----";
	return user;
}
User viewRecent(User user) {
	system("cls");
	std::cout << "----View Recent Orders-----";
	return user;

}


User createuser(std::string name,  double credits) {
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
	std::string welcomeAnswerString;
	bool breakwhile = false;
	//loop forever until user types a correct answer
	//Sets breakwhile to true when a correct answer is entered
	while (!breakwhile && !std::cin.fail()) {
		std::cout << "----Welcome to Hot Potato!----\nHello! " << user.name << "\nWhat would you like to do?\n1 - Add Credits\n2 - Create an Order\n3 - View Recent Orders\n4 - Quit\n- ";
		std::getline(std::cin, welcomeAnswerString);
		welcomeAnswer = atoi(welcomeAnswerString.c_str());
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
			std::cout << std::endl << "Bye! " << user.name << ", Come Back Soon!" << std::endl;
			quick_exit(0);
			// not an option
		default:
			std::cout << "\nError: Invalid Option\n";
			break;
		}
	}
	// call the function again to return the user to the welcome screen after choosing an option
	welcome(user);
	
}


int main() {
	// Initialize an empty user to avoid a memory error.
	User user = User();
	std::string name = "";
	std::string filename;
	// check if folders exist that will hold settings if not create them

	//check if config folder exists
	if (!std::filesystem::exists("config")) {
		std::filesystem::create_directory("./config");
	}
	//check if potatoes folder exists
	if (!std::filesystem::exists("config/potatoes")) {
		std::filesystem::create_directory("./config/potatoes");
	}
	//check if toppings folder exists
	if (!std::filesystem::exists("config/toppings")) {
		std::filesystem::create_directory("./config/toppings");
	}
	//check if extras folder exists
	if (!std::filesystem::exists("config/extras")) {
		std::filesystem::create_directory("./config/extras");
	}
	//check if users folder exists
	if (!std::filesystem::exists("users")) {
		std::filesystem::create_directory("./users");
	}


	//check if the user is initialized or not (if the json file exists)
	std::cout << "----Startup----\n";
	while (name == "") {
		std::cout << std::endl << "use /help for a list of commands\n\nWhat is your name?\n- ";
		getline(std::cin, name);

		filename = "users/" + name + ".json";
		system("pause");
		if (name.contains("/")) {
			if (name.contains("help")) {
				std::cout << "Commands are CASE SENSITIVE\n----Commands----\nconfig - add or remove items from the menu\nclearUser - clear user data\nclearItems - clear all items";
				name = "";
				continue;
			}
			if (name.contains("config")) {
				Config();
			}
			else if (name.contains("clearUser")) {
				quick_exit(0);
			}
			else if (name.contains("clearItems")) {
				quick_exit(0);
			}
			else {
				std::cout << "Error: command doesn't exist" << std::endl;
				name = "";
				continue;
			}
		}
	}


	if (!std::filesystem::exists(filename)) {
		std::cout << std::endl << "User doesn't exist";
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

1 - https://stackoverflow.com/questions/4654636/how-to-determine-if-a-std::string-is-a-number-with-c
2 - Lohmann, N. (2023). JSON for Modern C++ (Version 3.11.3) [Computer software]. https://github.com/nlohmann

*/