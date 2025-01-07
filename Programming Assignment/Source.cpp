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
- Finish Create Order Function //
- Clean up //
	- Add Comments to code //
- Fix create order letting answer beyond available //
- Fix Config //
- Add Orders to users //
- Finish View Recent Function //
- remove the previous menu when transitioning, so it doesn't fill the cmd //
*/

//includes
#include <iostream>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <vector>
#include <filesystem>
#include <ctime>
#include <random>
#include "./ConfHeader.h"
//reference 2: using json.hpp header to read and write json files.
#include "json.hpp"
using json = nlohmann::json;

//----------------------------------------------------------------

// got rid of (using namespace std;) as it was causing issues, mainly ambiguous function errors meaning
//there are two functions under the same name and the compiler doesnt know what to do with it.

//function declaration so I don't have to move them around
std::vector<conf::Item> ReadJsonItemMulti(std::string);
conf::Item ReadJsonItem(std::string);

// User class, gets passed around, contains information about the user.
class User {
public:
	std::string name = "";
	double credits = 0.00;
};
//Order class holds all the information for an order
class Order {
public:
	int time = -1;
	conf::Item potato;
	std::vector<conf::Item> toppings;
	std::vector<conf::Item> extras;
	double totalprice = -1;
};

/*Option Menu, show the user some options and check if the option they entered is correct and return the index of the answer, otherwise loop back and ask again;

Options:
Choices *Required* -  a Vector of std::strings that will be shown to the user (purely visual)
Message *Optional* - the message to show before asking, defaults to "What would you like to do?" if no message is set

Usage:
switch (Option(choices, message)) {
case 0:
	*Code*
case 1:
	*Code*
}
*/
int Option(std::vector<std::string> choices, std::string message = "What would you like to do?") {
	std::string answerString;
	int answerInt;
	while (true) {
		std::cout << message << std::endl;
		int x = 1;
		//loop over every choice and display it to the user;
		for (auto i : choices) {
			std::cout << x << " - " <<  i << std::endl;
			x++;
		}

		std::cout << "- ";
		//get users answer
		std::getline(std::cin, answerString);
		char* notnum;
		//convert string answer to an integer for comparison
		answerInt = strtol(answerString.c_str(), &notnum, 0);
		//check if the answer was allowed, otherwise return the answer
		if ((answerInt > choices.size()+1 || answerInt < 0) && &notnum) {
			std::cout << std::endl << "Sorry that's not an option!" << std::endl;
			continue;
		}
		else {
			return answerInt;
		}
	}
	return -1;
}


//CreateJsonFromOrder - create a json object for writing to a file from an Order object.
//Options:
//order *Required* - The order to turn into a json object
json CreateJsonFromOrder(Order order) {
	json jsono;
	jsono["totalprice"] = order.totalprice;
	//get current unix time e.g. seconds since midnight UTC on 1 January 1970
	const auto p1 = std::chrono::system_clock::now();
	jsono["time"] = std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();
	jsono["potato"] = ".\\config\\potatoes\\" + order.potato.name + ".json";
	
	int count = 0;
	//for every topping add its json file to the json object
	for (auto i : order.toppings) {
		jsono["toppings"][count] = ".\\config\\toppings\\" + i.name + ".json";
		count++;
	}

	//for every extra add its json file to the json object
	//std::cout << jsono["toppings"];
	count = 0;
	for (auto i : order.extras) {
		jsono["extras"][count] = ".\\config\\extras\\" + i.name + ".json";
		count++;
	}
	//return the created json object
	return jsono;

}
//CreateOrderFromJson - create an order object from a json object.
//Options:
//jsono *Required* - The Json object to convert to an order
Order CreateOrderFromJson(json jsono) {
	Order order;
	//set time and totalprice
	order.totalprice = jsono["totalprice"];
	order.time = jsono["time"];
	//set potato to the potato file that is referenced in the json file
	order.potato = ReadJsonItem(std::string(jsono["potato"]));
	conf::Item item;
	//add toppings
	for (auto i : jsono["toppings"]) {
		//get the information from the file
		item = ReadJsonItem(i);
		//add it to the array.
		order.toppings.push_back(item);
	}
	//add extras
	for (auto i : jsono["extras"]) {
		//get the information from the file
		item = ReadJsonItem(i);
		//add it to the array
		order.extras.push_back(item);
	}

	//return the resulting order
	return order;
}





//Update / Create JSON File, takes a user and order
//Options:
//User *Required* - the user to save.
//Order *Optional* - the order to save.
void UpdateJSON(User user, Order order) {
	json jsondu;
	json jsondo;
	//filename for users folder
	std::string filename = "users\\" + user.name;
	//file stream for user file
	std::ofstream fu(filename + "\\user.json");
	jsondu["name"] = user.name;
	jsondu["credits"] = user.credits;
	//check if the user already has an order file if not set the count to 0 as they haven't ordered anything,
	if (!std::filesystem::exists(filename + "\\orders.json")) {
		jsondo["count"] = 0;
	}
	else {
		//file stream for reading
		std::ifstream foread(filename + "\\orders.json");
		//open file
		jsondo = json::parse(foread);
		foread.close();
	}
	int count = jsondo["count"];
	//Increment the count(amount of orders saved) by 1
	count++;
	jsondo["count"] = count;
	//create a json object from the order given
	jsondo[std::to_string(count)] = CreateJsonFromOrder(order);
	//write to orders file
	std::ofstream fowrite(filename + "\\orders.json");
	fowrite << jsondo;
	fowrite.close();
	//write to user file
	fu << jsondu;
	fu.close();
}
//overload without order
void UpdateJSON(User user) {
	json jsondu;
	json jsondo;
	//filename for users folder
	std::string filename = "users\\" + user.name;
	//file stream for user file
	std::ofstream fu(filename + "\\user.json");
	jsondu["name"] = user.name;
	jsondu["credits"] = user.credits;
	//write to user file
	fu << jsondu;
	fu.close();
}


//ReadJson - Read User Json File, takes a filename
//Options:
//filename *Required* - the path to the file
User ReadJson(std::string filename) {
	User user;
	//file stream for reading the json file
	std::ifstream f(filename);
	//get the information form the file
	json data = json::parse(f);
	std::cout << data["name"];
	std::cout << std::fixed << std::setprecision(2) << data["credits"];
	//set the values for the reurned user
	user.name = data["name"];
	//the value that comes from the json isn't a double so we convert it
	user.credits = double(data["credits"]);
	f.close();
	return user;
}
//ReadJsonItemMulti - Loop over a directory and read each item json
//Options:
//filename *Required* - The path to the folder
std::vector<conf::Item> ReadJsonItemMulti(std::string filename) {
	std::vector<conf::Item> items;
	conf::Item item;
	//loop over every file in the folder
	for (const auto& entry : std::filesystem::directory_iterator(filename)) {
		//open the file
		std::ifstream f(entry.path().string());
		json data = json::parse(f);

		//set the values and add it to the items array
		item.name = data["name"];
		item.price = data["price"];
		items.push_back(item);
		f.close();
	}
	return items;
}
//ReadJsonItem - Read a single item json file
//Options:
//filename *Required* - The path to the item file
conf::Item ReadJsonItem(std::string filename) {
	conf::Item item;
	//open the file
	std::ifstream f(filename);
	json data = json::parse(f);
	//set values
	item.name = data["name"];
	item.price = data["price"];
	f.close();
	return item;
}
//addCredits - Allow the user to add credits
//Options:
//user *Required* - the user to add the credits to
void addCredits(User &user) {
	system("cls");
	// Set Variables
	const double minAnswer = 0.01;
	const double maxAnswer = 999999999999999999.0;

	std::string creditAnswerS;
	double creditAnswerD;
	std::string sure = "n";
	char* notnum;
	double credits = user.credits;

	std::cout << "--------- Add Credits ---------\nCurrent Credits: " << std::fixed << std::setprecision(2) << credits;
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
					return;
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
			
			std::cout << std::endl << "Are you Sure?\nNew amount will be: " << std::fixed << std::setprecision(2) << credits + creditAnswerD << "\n(y / n)\n- ";
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
	}

}
//createOrder - Create and Order
//Options:
//user *Required* - The User that is creating the order
//Create Order doesn't use Option as it uses different formatting for displaying options
void createOrder(User &user) {
	//All options are dynamic and are assigned automatically when function is called, options are assigned by looping through the directory and filling a vector with Items from ConfHeader.h
	//Questions are then asked based on this vector and checked based on this vector
	//Asks User what size potato they want to order
	//ask if they want any toppings by looping over and over checking if they want to move on
	//also ask for extras using the same approach
	double totalprice = 0;
	conf::Item potato;
	Order order;
	std::vector<conf::Item> toppings;
	std::vector<conf::Item> extras;

	std::string answerString;
	int answerInt = -1;
	//get the items to show
	std::vector<conf::Item> toppingsItems = ReadJsonItemMulti("./config/toppings");
	std::vector<conf::Item> extrasItems = ReadJsonItemMulti("./config/extras");
	std::vector<conf::Item> potatoesItems = ReadJsonItemMulti("./config/potatoes");

	system("cls");
	std::cout << "--------- Create A New Order ----------";

	//loop until the user picks a potato
	while (true) {
		std::cout << std::endl << "What potato would you like to order? or type -1 to go back\n(Enter Number)" << std::endl;
		int x = 0; //used for number above item as we are using a foreach loop
		for (auto i : potatoesItems) {
			std::cout << "----------------- " << x << " ------------------" << std::endl;
			std::cout << "Name: " << i.name << std::endl;
			std::cout << "Price: " << std::fixed << std::setprecision(2) << i.price;
			std::cout << std::endl << "-------------------------------------" << std::endl;
			x++;
		}
		std::cout << "\n- ";
		std::getline(std::cin, answerString);
		char* notnum;
		//convert the answer the user gave to an integer
		answerInt = strtol(answerString.c_str(), &notnum, 0);
		//notnum is a pointer the last character after strtol is finished 
		//if it got through without encountering a letter 
		//then it will return nothing as there is no character after the last
		if (!&notnum) {
			std::cout << "Error: Not an Option!" << std::endl;
			continue;
		}//check if the answer is higher than the highest option or lower than the first
		if (answerInt < 0 || answerInt > potatoesItems.size()-1) {
			if (answerInt == -1) {
				return;
			}
			std::cout << "Error: Not an Option!" << std::endl;
			continue;
		}
		else {
			//set the values
			order.totalprice += potatoesItems[answerInt].price;
			order.potato = potatoesItems[answerInt];

			break;
		}
	}
	//loop until the user picks a topping
	while (true) {
		system("cls");
		std::cout << std::endl << "Would you like to add any toppings? or type -1 to add no toppings\n(Enter Number)" << std::endl;
		int x = 0;
		for (auto i : toppingsItems) {
			std::cout << "----------------- " << x << " ------------------" << std::endl;
			std::cout << "Name: " << i.name << std::endl;
			std::cout << "Price: " << std::fixed << std::setprecision(2) << i.price;
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
		if (answerInt < 0 || answerInt > toppingsItems.size()-1) {
			if (answerInt == -1) {
				break;
			}
			std::cout << "Error: Not an Option!" << std::endl;
			continue;
		}
		else {
			
			order.totalprice += toppingsItems[answerInt].price;
			order.toppings.push_back(toppingsItems[answerInt]);
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
					std::cout << std::endl << "Error: not an option!" << std::endl;
					continue;
				}
				
			}
			if (stop) break;
			else continue;
		}
		

	}
	//loop until user picks an extra
	while (true) {
		system("cls");
		std::cout << std::endl << "Would you like to add any Extras? or type -1 to add no extras\n(Enter Number)" << std::endl;
		int x = 0; //number above order
		for (auto i : extrasItems) {
			std::cout << "----------------- " << x << " ------------------" << std::endl;
			std::cout << "Name: " << i.name << std::endl;
			std::cout << "Price: " << std::fixed << std::setprecision(2) << i.price;
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
		//check if answer is too low or high
		if (answerInt < 0 || answerInt > extrasItems.size()-1) {
			if (answerInt == -1) {
				break;
			}
			std::cout << "Error: Not an Option!" << std::endl;
			continue;
		}
		else {

			order.totalprice += extrasItems[answerInt].price;
			order.extras.push_back(extrasItems[answerInt]);
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



	//show the user what they ordered and how much it cost
	system("cls");
	std::cout << "--------------- Reciept ----------------" << std::endl; 

	std::cout << std::endl << "-------- Potato --------" << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	std::cout << "Name: " << order.potato.name << std::endl;
	std::cout << "Price: " << std::fixed << std::setprecision(2) << order.potato.price;
	std::cout << std::endl << "-----------------------------------" << std::endl;


	std::cout << std::endl << "--------- Toppings ---------" << std::endl;
	for (auto i : order.toppings) {
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "Name: " << i.name << std::endl;
		std::cout << "Price: " << std::fixed << std::setprecision(2) << i.price;
		std::cout << std::endl << "-----------------------------------" << std::endl;
	}


	std::cout << std::endl << "-------- Extras --------" << std::endl;
	for (auto i : order.extras) {
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "Name: " << i.name << std::endl;
		std::cout << "Price: " << std::fixed << std::setprecision(2) << i.price;
		std::cout << std::endl << "-----------------------------------" << std::endl;
	}
	std::cout << std::endl << "Total Price: " << std::fixed << std::setprecision(2) << order.totalprice;
	std::cout << std::endl << "----------------------------------------" << std::endl;

	//user doesnt have enough credits so boot them back to the welcome menu
	if (order.totalprice > user.credits) {
		std::cout << "Sorry you don't have enough credits" << std::endl;
		system("pause");
		return;
	}
	else {
		//take credits from the user
		user.credits -= order.totalprice;
		std::cout << order.totalprice << " credits taken from your account\nNew Balance: " << std::fixed << std::setprecision(2) << user.credits << std::endl;
	}
	UpdateJSON(user, order);

	system("pause");

}

//View Recent Function - view all recent orders from the currently used account;
//Options:
//user *Required* - The user currently using the system;
void viewRecent(User &user) {
	system("cls");
	std::cout << "-------- View Recent Orders ---------" << std::endl;
	json jsond;
	//open orders file for current user
	if (std::filesystem::exists("users\\" + user.name + "\\orders.json")) {
		std::ifstream foread("users\\" + user.name + "\\orders.json");
		Order order;
		jsond = json::parse(foread);
		for (auto i : jsond) {
			if (i.type_name() != "number") {
				order = CreateOrderFromJson(i);
				//show the time the order was made, and use the same format as the reciept at the end of create order
				std::cout << std:: endl << "---------------" << std::chrono::sys_seconds(std::chrono::seconds(order.time)) << "---------------" << std::endl;

				std::cout << std::endl << "-------- Potato --------" << std::endl;
				std::cout << "-----------------------------------" << std::endl;
				std::cout << "Name: " << order.potato.name << std::endl;
				std::cout << "Price: " << std::fixed << std::setprecision(2) << order.potato.price;
				std::cout << std::endl << "-----------------------------------" << std::endl;


				std::cout << std::endl << "--------- Toppings ---------" << std::endl;
				for (auto j : order.toppings) {
					std::cout << "-----------------------------------" << std::endl;
					std::cout << "Name: " << j.name << std::endl;
					std::cout << "Price: " << std::fixed << std::setprecision(2) << j.price;
					std::cout << std::endl << "-----------------------------------" << std::endl;
				}


				std::cout << std::endl << "-------- Extras --------" << std::endl;
				for (auto j : order.extras) {
					std::cout << "-----------------------------------" << std::endl;
					std::cout << "Name: " << j.name << std::endl;
					std::cout << "Price: " << std::fixed << std::setprecision(2) << j.price;
					std::cout << std::endl << "-----------------------------------" << std::endl;
				}
				std::cout << std::endl <<  "Total Price: " << std::fixed << std::setprecision(2) << order.totalprice;
				std::cout << std::endl << "--------------------------------------------------";
			}
			else {
				std::cout << std::endl << "Amount of orders = " << i << std::endl;
			}
		}
		system("pause");
	}
	else {
		std::cout << "You haven't created any orders yet!";
		system("pause");
		return;
	}
}

//createuser - Create a User and return it
//Options:
//name *Required* - The name of the user
//credits *Optional* - The Amount of credits to give the user.
User createuser(std::string name, double credits = 0.00) {
	system("cls");
	//User not initialized so create a new User variable
	User user = User();
	user.credits = credits; 
	user.name = name;
	//Also save to folder and json file
	std::filesystem::create_directory("./users/"+name+"");
	UpdateJSON(user);
	return user;
}

//welcome - the welcome function gives the user the welcome menu and calls the other functions
//Options:
//user *Required* - The current logged in user
void welcome(User user) {
	system("cls");
	std::vector <std::string> messages = {"Welcome!", "Hello!", "Live Long and Prosper\nWelcome!", "Hey you you're finally awake\nWelcome!", "Keep the change, ya filthy animal!\nWelcome!", "Also try Minecraft!\nWelcome!", "Han didn't shoot first!\nWelcome!", "I guess you guys aren't ready for that yet. But your kids are gonna love it\nWelcome!", "When you get to Hell, Tell 'em Viper sent you\nWelcome!", "If my grandmother had wheels she would have been a bike\nWelcome!", "Well excuse me, princess\nWelcome!"};
	//Reference 3 ---------------------------------------------
	//Generates a random number to be used to show a welcome message
	int min = 0;
	int max = 10;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);
	//---------------------------------------------------------

	std::string message = "-------- Hot Potato! ---------\n{randommsg} " + user.name +"\n";

	//Reference 4 ---------------------------------------------
	//replace {randommsg} with a random message chosen by random number generator above
	message.replace(message.find("{randommsg}"), sizeof("{randommsg}") - 1, messages[distrib(gen)]);
	//---------------------------------------------------------
	
	//show the main welcome menu
	switch (Option({"Add Credits", "Create Order", "View Recent Orders", "Quit"}, message)) {
				//add credits
			case 1:
				//set the user variable to what the function return as this contains the updated credits.
				addCredits(user);
				break;
				//create an order
			case 2:
				createOrder(user);
				break;
				//view recent orders
			case 3:
				viewRecent(user);
				break;
				// quit
			case 4:
				std::cout << std::endl << "Bye! " << user.name << ", Come Back Soon!" << std::endl;
				quick_exit(0);
			case -1:
				std::cout << "Something Went Wrong!";
				break;
	}
	// call the function again to return the user to the welcome screen after choosing an option
	welcome(user);
	
}
//Config - Config options e.g. adding a new item, or viewing items
void Config() {
	system("cls");
	std::cout << "----Config----" << std::endl;
	conf::Item item;
	std::string price = "";
	std::string type;
	conf::ItemType itemtype;
	std::vector<std::filesystem::path> paths;

	//show options for add or editing or viewing items
	switch (Option({ "Add or Edit an Item", "View Items" })) {
	// add / edit
	case 1:
		system("cls");
		switch (Option({"Topping", "Extra", "Potato"}, "What is the type of item you want to add or edit?")) {
		// Topping
		case 1:
			itemtype = conf::topping;
			//ask for name
			std::cout << "What is the name of the item you would like to add or edit?\n- ";
			getline(std::cin, item.name);

			while (price == "" && !std::cin.fail()) {
				//ask for price
				std::cout << "What is the price of the item you would like to add or edit?\n- ";
				getline(std::cin, price);

			}
			//convert the string given from getline into a double
			item.price = strtod(price.c_str(), NULL);

			//add the new item
			conf::Add(item, itemtype);
			std::cout << std::endl << "Successfully Added / Edited Item" << std::endl;
			break;


		
		case 2:
			itemtype = conf::extra;
			//ask for name
			std::cout << "What is the name of the item you would like to add or edit?\n- ";
			getline(std::cin, item.name);

			while (price == "" && !std::cin.fail()) {
				//ask for price
				std::cout << "What is the price of the item you would like to add or edit?\n- ";
				getline(std::cin, price);

			}
			//convert the string given from getline into a double
			item.price = strtod(price.c_str(), NULL);

			//add the new item
			conf::Add(item, itemtype);
			std::cout << std::endl << "Successfully Added / Edited Item" << std::endl;
			break;
		case 3:
			itemtype = conf::potato;
			//ask for name
			std::cout << "What is the name of the item you would like to add or edit?\n- ";
			getline(std::cin, item.name);

			while (price == "" && !std::cin.fail()) {
				//ask for price
				std::cout << "What is the price of the item you would like to add or edit?\n- ";
				getline(std::cin, price);

			}
			//convert the string given from getline into a double
			item.price = strtod(price.c_str(), NULL);

			//add the new item
			conf::Add(item, itemtype);
			std::cout << std::endl << "Successfully Added / Edited Item" << std::endl;
			break;
		case -1:
			std::cout << "Something Went Wrong!";
			break;
		}
		break;
		


	//view
	case 2:
		system("cls");
		//ask user which they want to view
		switch (Option({ "Topping", "Extra", "Potato" }, "What type of items do you want to view?")) {
		//topping
		case 1:
			itemtype = conf::topping;
			//get list of file paths
			paths = conf::View(itemtype);
			std::cout << std::endl << "--Toppings--" << std::endl;
			//for each file path
			for (auto i : paths) {
				//open the file and show it's contents
				std::cout << "-----------------------------------" << std::endl;
				conf::Item item;
				std::ifstream f(i);
				json data = json::parse(f);
				std::cout << "Name: " << data["name"] << std::endl;
				std::cout << "Price: " << std::fixed << std::setprecision(2) << data["price"];
				std::cout << std::endl << "-----------------------------------" << std::endl;
				f.close();
			}
			break;
		//extra
		case 2:
			itemtype = conf::extra;
			//get list of file paths
			paths = conf::View(itemtype);
			std::cout << std::endl << "--Extras--" << std::endl;
			//for each file path
			for (auto i : paths) {
				//open the file and show it's contents
				std::cout << "-----------------------------------" << std::endl;
				conf::Item item;
				std::ifstream f(i);
				json data = json::parse(f);
				std::cout << "Name: " << data["name"] << std::endl;
				std::cout << "Price: " << std::fixed << std::setprecision(2) << data["price"];
				std::cout << std::endl << "-----------------------------------" << std::endl;
				f.close();
			}
			break;
		//potato
		case 3:
			itemtype = conf::potato;
			//get list of file paths
			paths = conf::View(itemtype);
			std::cout << std::endl << "--Potatoes--" << std::endl;
			//for each file path
			for (auto i : paths) {
				//open the file and show it's contents
				std::cout << "-----------------------------------" << std::endl;
				conf::Item item;
				std::ifstream f(i);
				json data = json::parse(f);
				std::cout << "Name: " << data["name"] << std::endl;
				std::cout << "Price: " << std::fixed << std::setprecision(2) << data["price"];
				std::cout << std::endl << "-----------------------------------" << std::endl;
				f.close();
			}
			break;
		}
		
	

}
	system("pause");


	//ask user if they want to return to the config menu to choose add/edit or view
	switch (Option({"Return to Config Menu", "Quit"}, "Would you like to return to the config menu or quit?")) {
		case 1:
			Config();
			break;
		case 2:
			quick_exit(0);
	}
}


//clearUser - Delete the user directory
void clearUser() {
	std::cout << std::endl << "Removing users directory";
	std::filesystem::remove_all("./users");
	std::cout << std::endl << "Successfully Removed users";
	quick_exit(0);
}
//clearItem - Delete the config directory
void clearItem() {
	std::cout << std::endl << "Removing Items directory";
	std::filesystem::remove_all("./config");
	std::cout << std::endl << "Successfully Removed Items";
	quick_exit(0);
}

//main - The function that starts when the program starts, makes sure everything is in order,
//for example checks if all folders exist
//also creates and check for user then finally calls welcome
int main() {
	// Initialize an empty user
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
	std::cout << "------------ Startup ------------\n";
	std::string title = "enter /command to use commands\n\nEnter your name\n- ";
	//commands controls if the user is using commands
	bool commands = false;
	while (name == "") {
		std::cout << std::endl << title;
		getline(std::cin, name);

		filename = "./users/" + name + "/user.json";
		system("pause");
		//enable command mode and show available commands
		if (name == "/command") {
			title = "Enter a Command\n- ";
			std::cout << "Commands are CASE SENSITIVE\n----Commands----\nconfig - add or remove items from the menu\nclearUser - clear user data\nclearItems - clear all items\nreturn - return to the name menu";
			name = "";
			commands = true;
			continue;
		}

		//commands
		if (name == "config" && commands) {
			Config();
			name = ""; 
			commands = false;
			continue;
		}
		else if (name == "clearUser" && commands) {
			clearUser();
			name = ""; 
			commands = false;
			continue;
		}
		else if (name == "clearItems" && commands) {
			clearItem();
			name = ""; 
			commands = false;
			continue;
		}
		else if (name == "return" && commands) {
			name = ""; 
			commands = false;
			title = "enter / command to use commands\n\nEnter your name\n- ";
			continue;
		}
		else if (name == "hello" || name == "hi") {
			std::cout << "Hi!";
			name = ""; 
			commands = true;
			continue;
		}
		else if (commands){
			std::cout << "Error: command doesn't exist" << std::endl;
			name = ""; commands = true;
			continue;
		}
	}
	//check if the user exists
	if (!std::filesystem::exists(filename)) {
		//user doesnt exist so create one
		std::cout << std::endl << "User doesn't exist";
		system("pause");
		user = createuser(name);

	}
	else {
		//user exists so just read the json file
		user = ReadJson(filename);
	}


	// start the welcome screen
	welcome(user);

}











/*
References:

1 - https://stackoverflow.com/questions/4654636/how-to-determine-if-a-std::string-is-a-number-with-c
2 - Lohmann, N. (2023). JSON for Modern C++ (Version 3.11.3) [Computer software]. https://github.com/nlohmann
3 - https://stackoverflow.com/questions/3418231/replace-part-of-a-string-with-another-string
4 - https://www.geeksforgeeks.org/how-to-generate-random-number-in-range-in-cpp/


*/