/*
Programming Assignment - Config.cpp configure the program,
e.g. edit / add / remove extras, toppings and potatoes from the menu
Each reference will be at bottom of the file and will be numbered 
*/

/*
TODO:		Key:
			 // done
			 / doing

- Create function for adding item. //
- Create Function for viewing current config, e.g. toppings /  extras  / potatoes. //
*/


#include <iostream>
#include "ConfHeader.h"
#include "json.hpp"
#include <fstream>
#include <filesystem>
#include <vector>
using json = nlohmann::json;
using namespace std;

//Take in an item (name and price) and a type and save the new item.
int conf::Add(Item item, conf::ItemType type) {
	std::ofstream jsonf;
	json jsond;
	cout << endl;
	switch (type) {
	case conf::topping:
		jsonf = std::ofstream("config/toppings/"+item.name+".json");
		break;

	case conf::extra:
		jsonf = std::ofstream("config/extras/" + item.name + ".json");
		break;

	case conf::potato:
		jsonf = std::ofstream("config/potatoes/" + item.name + ".json");
		break;
	}
	jsond["name"] = item.name;
	jsond["price"] = item.price;
	jsonf << jsond;
	return 0;
}
//view all menu items
std::vector<filesystem::path> conf::View(conf::ItemType type) {
	cout << endl << "View" << endl;
	vector<filesystem::path> paths;
	string path = "";
	
	switch (type) {
	case conf::topping:
		path = "./config/toppings";
		break;
	case conf::extra:
		path = "./config/extras";
		break;
	case conf::potato:
		path = "./config/potatoes";
		break;
	}
	//reference 1--------------------------------------------------------
	for (const auto& entry : filesystem::directory_iterator(path))
		paths.push_back(entry.path());
	//-------------------------------------------------------------------
	return paths;
}
/*
References:
1 - https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c

*/