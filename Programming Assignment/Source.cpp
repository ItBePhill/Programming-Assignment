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
#include <functional>
#include <fstream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <vector>
#include <filesystem>
#include "./ConfHeader.h"
//reference 2: using json.hpp header to read and write json files.
#include "json.hpp"
using json = nlohmann::json;
//----------------------------------------------------------------

// got rid of (using namespace std;) as it was causing issues, mainly ambiguous function errors meaning
//there are two functions under the same name and the compiler doesnt know what to do with it.


// User class, gets passed around, contains information about the user.
class User {
public:
	std::string name = "";
	double credits = 0.00;
};
class Order {
public: 
	int time = -1;
	conf::Item potato;
	std::vector<conf::Item> toppings;
	std::vector<conf::Item> extras;
	double totalprice = -1;
};

//Update / Create JSON File, takes a user
void UpdateJSON(User user, Order order) {

	std::string filename = "users/" + user.name + "/user.json";
	json jsonf;
	std::ofstream f(filename);
	jsonf["name"] = user.name;
	//credits saved as string to keep the decimal points
	jsonf["credits"] = std::to_string(user.credits);
	f << jsonf;
}
//Read Json File, takes a filename
User ReadJson(std::string filename) {
	User user;
	std::ifstream f(filename);
	json data = json::parse(f);
	std::cout << data["name"];
	std::cout << std::setprecision(4) << data["credits"];
	user.name = data["name"];
	//the value that comes from the json isn't a double or string, so we convert it to a string and then c string, then convert that to a double.
	user.credits = strtod(to_string(data["credits"]).c_str(), NULL);
	return user;
}



User addCredits(User user) {
	system("cls");
	// Set Variables
	const double minAnswer = 0.01;
	const double maxAnswer = 999999999999999999.0;

	std::string creditAnswerS;
	double creditAnswerD;
	std::string sure = "n";
	char* notnum;
	double credits = user.credits;

	std::cout << "--------- Add Credits ---------\nCurrent Credits: " << std::setprecision(4) << credits;
	//ask user to input an amount of credits then ask if they're sure and check if answer is valid by looping until the answer is yes.
	while (sure != "y") {
		while (true) {
			std::cout << std::endl << "How many credits would you like to add? or type -1 to return to the menu\n- ";
			std::getline(std::cin, creditAnswerS);
			// convert std::string to a double
			creditAnswerD = strtod(creditAnswerS.c_str(), &notnum));
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
			
			std::cout << std::endl << "Are you Sure?\nNew amount will be: " << std::setprecision(4) << credits + creditAnswerD << "\n(y / n)\n- ";
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
		Order order;
		UpdateJSON(user, order);
		return user;
	}
	return user;

}
User createOrder(User user) {
	//All options are dynamic and are assigned automatically when function is called, options are assigned by looping through the directory and filling a vector with Items from ConfHeader.h
	//Questions are then asked based on this vector and checked based on this vector
	//Asks User what size potato they want to order
	//ask if they want any toppings by looping over and over checking if they want to move on
	//also ask for extras using the same approach
	double totalprice = 0;
	conf::Item potato;
	std::vector<conf::Item> toppings;
	std::vector<conf::Item> extras;

	std::string answerString;
	int answerInt = -1;

	std::vector<conf::Item> toppingsItems;
	std::vector<conf::Item> extrasItems;
	std::vector<conf::Item> potatoesItems;
	
	
	conf::Item item;
	for (const auto& entry : std::filesystem::directory_iterator("./config/toppings")) {
		std::ifstream f(entry.path().string());
		json data = json::parse(f);
		item.name = data["name"];
		item.price = data["price"];

		toppingsItems.push_back(item);
	}
	for (const auto& entry : std::filesystem::directory_iterator("./config/extras")) {
		std::ifstream f(entry.path().string());
		json data = json::parse(f);
		item.name = data["name"];
		item.price = data["price"];

		extrasItems.push_back(item);
	}
	for (const auto& entry : std::filesystem::directory_iterator("./config/potatoes")) {
		std::ifstream f(entry.path().string());
		json data = json::parse(f);
		item.name = data["name"];
		item.price = data["price"];

		potatoesItems.push_back(item);
	}


	system("cls");
	std::cout << "--------- Create A New Order ----------";


	while (true) {
		std::cout << std::endl << "What potato would you like to order?\n(Enter Number)" << std::endl;
		int x = 0;
		for (auto i : potatoesItems) {
			std::cout << "----------------- " << x << " ------------------" << std::endl;
			std::cout << "Name: " << i.name << std::endl;
			std::cout << "Price: " << std::setprecision(4) << i.price;
			std::cout << std::endl << "-------------------------------------" << std::endl;
			x++;
		}
		std::cout << "\n- ";
		std::getline(std::cin, answerString);
		char* notnum;
		answerInt = strtol(answerString.c_str(), &notnum, 0);
		if (!&notnum) {
			std::cout << "Error: Not an Option!" << std::endl;
			continue;
		}
		if (answerInt < 0 || answerInt > potatoesItems.size()) {
			std::cout << "Error: Not an Option!" << std::endl;
			continue;
		}
		else {
			totalprice += potatoesItems[answerInt].price;
			potato = potatoesItems[answerInt];

			break;
		}
	}


	while (true) {
		system("cls");
		std::cout << std::endl << "Would you like to add any toppings?\n(Enter Number)" << std::endl;
		int x = 0;
		for (auto i : toppingsItems) {
			std::cout << "----------------- " << x << " ------------------" << std::endl;
			std::cout << "Name: " << i.name << std::endl;
			std::cout << "Price: " << std::setprecision(4) << i.price;
			std::cout << std::endl << "-------------------------------------" << std::endl;
			x++;
		}
		std::cout << "\n- ";
		std::getline(std::cin, answerString);
		char* notnum;
		answerInt = strtol(answerString.c_str(), NULL, 0);
		if (!&notnum) {
			std::cout << "Error: Not an Option!" << std::endl;
			continue;
		}
		if (answerInt < 0 || answerInt > toppingsItems.size()) {
			std::cout << "Error: Not an Option!" << std::endl;
			continue;
		}
		else {
			
			totalprice += toppingsItems[answerInt].price;
			toppings.push_back(toppingsItems[answerInt]);
			std::string cont;
			bool stop;
			while (true) {
				std::cout << std::endl << "Continue?\n1 - Continue to extras\n2 - Add more toppings\n- ";
				std::getline(std::cin, cont);
				if (cont == "1") {
					stop = true;
					break;
				}
				else if (cont == "2") {
					stop = false;
					break;
				}
				else {
					std::cout << std::endl << "Error: not an option!";
					continue;
				}
				
			}
			if (stop) break;
			else continue;
		}
		

	}

	while (true) {
		system("cls");
		std::cout << std::endl << "Would you like to add any Extras?\n(Enter Number)" << std::endl;
		int x = 0;
		for (auto i : extrasItems) {
			std::cout << "----------------- " << x << " ------------------" << std::endl;
			std::cout << "Name: " << i.name << std::endl;
			std::cout << "Price: " << std::setprecision(4) << i.price;
			std::cout << std::endl << "-------------------------------------" << std::endl;
			x++;
		}
		std::cout << "\n- ";
		std::getline(std::cin, answerString);
		char* notnum;
		answerInt = strtol(answerString.c_str(), &notnum, 0);
		if (!&notnum) {
			std::cout << "Error: Not an Option!" << std::endl;
			continue;
		}
		if (answerInt < 0 || answerInt > extrasItems.size()) {
			std::cout << "Error: Not an Option!" << std::endl;
			continue;
		}
		else {

			totalprice += extrasItems[answerInt].price;
			extras.push_back(extrasItems[answerInt]);
			std::string cont;
			bool stop;
			while (true) {
				std::cout << std::endl << "Continue?\n1 - Continue to payment\n2 - Add more extras\n- ";
				std::getline(std::cin, cont);

				if (cont == "1") {
					stop = true;
					break;
				}
				else if (cont == "2") {
					stop = false;
					break;
				}
				else {
					std::cout << std::endl << "Error: not an option!";
					continue;
				}

			}
			if (stop) break;
			else continue;
		}

	}

	system("cls");
	std::cout << "Total Price: " << totalprice << std::endl;
	std::cout << "--------------- Items ----------------" << std::endl; 


	std::cout << std::endl << "-------- Potato --------" << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	std::cout << "Name: " << potato.name << std::endl;
	std::cout << "Price: " << std::setprecision(4) << potato.price;
	std::cout << std::endl << "-----------------------------------" << std::endl;


	std::cout << std::endl << "--------- Toppings ---------" << std::endl;
	for (auto i : toppings) {
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "Name: " << i.name << std::endl;
		std::cout << "Price: " << std::setprecision(4) << i.price;
		std::cout << std::endl << "-----------------------------------" << std::endl;
	}


	std::cout << std::endl << "-------- Extras --------" << std::endl;
	for (auto i : extras) {
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "Name: " << i.name << std::endl;
		std::cout << "Price: " << std::setprecision(4) << i.price;
		std::cout << std::endl << "-----------------------------------" << std::endl;
	}


	if (totalprice > user.credits) {
		std::cout << "Sorry you don't have enough credits";
		system("pause");
		quick_exit(0);
	}
	else {
		user.credits -= totalprice;
		std::cout << totalprice << " credits taken from your account\nNew Balance: " << std::setprecision(4) << user.credits << std::endl;
	}
	


	Order order;
	UpdateJSON(user, order);

	system("pause");
	quick_exit(0);
	return user;
}
User viewRecent(User user) {
	system("cls");
	std::cout << "-------- View Recent Orders ---------";
	return user;

}


User createuser(std::string name,  double credits) {
	system("cls");
	//User not initialized so create a new User variable
	User user = User();
	user.credits = credits; 
	user.name = name;
	//Also save to corresponding json file
	Order order;
	std::filesystem::create_directory("./users/"+name+"");
	UpdateJSON(user, order);
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
		std::cout << "-------- Welcome to Hot Potato! --------\nHello! " << user.name << "\nWhat would you like to do?\n1 - Add Credits\n2 - Create an Order\n3 - View Recent Orders\n4 - Quit\n- ";
		std::getline(std::cin, welcomeAnswerString);
		welcomeAnswer = strtol(welcomeAnswerString.c_str(), NULL, 0);
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
		std::cout << "What would you like to do?\n1 - Add or edit an item\n2 - View Items\n- ";
		getline(std::cin, welcomeAnswerString);
		welcomeAnswer = strtol(welcomeAnswerString.c_str(), NULL, 0);
		//check if answer is valid
		switch (welcomeAnswer) {

		case 1:
			system("cls");
			while (!breakwhile2 && !std::cin.fail()) {
				std::cout << "What is the type of item you want to add or edit?\n1 - Topping\n2 - Extra\n3 - Potato\n- ";
				getline(std::cin, type);
				switch (strtol(type.c_str(), NULL, 0)) {
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

			std::cout << "What is the name of the item you would like to add or edit?\n- ";
			getline(std::cin, item.name);

			while (price == "" && !std::cin.fail()) {
				std::cout << "What is the price of the item you would like to add or edit?\n- ";
				getline(std::cin, price);

			}
			item.price = strtod(price.c_str(), NULL);


			conf::Add(item, itemtype);
			std::cout << std::endl << "Successfully Added / Edited Item";
			breakwhile = true;
			break;

		case 2:
			system("cls");
			while (!breakwhile2 && !std::cin.fail()) {
				std::cout << "What type of items do you want to view?\n1 - Topping\n2 - Extra\n3 - Potato\n- ";
				getline(std::cin, type);
				switch (strtol(type.c_str(), NULL, 0)) {
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
				std::cout << "Price: " << std::setprecision(4) << data["price"];
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
	//also not great naming but also fine for now
	bool breakwhile3 = false;

	while (!breakwhile3 && !std::cin.fail()) {
		std::cout << "Would you like to return to the config menu or quit?\n1 - return to config menu\n2 - Quit\n- ";
		std::getline(std::cin, welcomeAnswerString);
		welcomeAnswer = strtol(welcomeAnswerString.c_str(), NULL, 0);
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



void clearUser() {
	std::cout << std::endl << "Removing users directory";
	std::filesystem::remove_all("./users");
	std::cout << std::endl << "Successfully Removed users";
	quick_exit(0);
}
void clearItem() {
	std::cout << std::endl << "Removing Items directory";
	std::filesystem::remove_all("./config");
	std::cout << std::endl << "Successfully Removed Items";
	quick_exit(0);
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

		filename = "./users/" + name + "/user.json";
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
				clearUser();
			}
			else if (name.contains("clearItems")) {
				clearItem();
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