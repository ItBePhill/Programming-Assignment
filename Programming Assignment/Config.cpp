/*
Programming Assignment - Config.cpp configure the program,
e.g. edit / add / remove extras, toppings and potatoes from the menu
additionally control other config options like clearing user folder.
Each reference will be at bottom of the file and will be numbered 
*/

/*
TODO:		Key:
			 // done
			 / doing

- Create function for adding item. /
- Create function for editing an item
- Create Function for viewing current config, e.g. toppings /  extras  / potatoes.
*/


#include <iostream>
#include "ConfHeader.h"
#include "json.hpp"
#include <fstream>
using json = nlohmann::json;
using namespace std;
using namespace conf;

//Take in an item (name and price) and a type and save the new item.
int conf::Add(Item item, conf::ItemType type) {
	std::ofstream jsonf;
	json jsond;
	cout << endl;
	switch (type) {
	case conf::topping:
		cout << "Topping";
		jsonf = std::ofstream("config/toppings/"+item.name+".json");
		break;
	case conf::extra:
		cout << "Extra";
		jsonf = std::ofstream("config/extras/" + item.name + ".json");
		break;
	case conf::potato:
		jsonf = std::ofstream("config/potatoes/" + item.name + ".json");
		cout << "Potato";
		break;
	}
	jsond["name"] = item.name;
	jsond["price"] = item.price;
	jsonf << jsond;
	return 0;
}
//Edit or remove an item using the name and ItemType.
int conf::Edit(string name, conf::ItemType type) {
	cout << "Edit";

	return 0;
}
//view all menu items
int conf::View(conf::ItemType type) {
	cout << "View";
	return 0;
}
/*
References:

*/