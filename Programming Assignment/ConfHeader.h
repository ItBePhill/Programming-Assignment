//makes sure it cannot be declared twice in a source file.
//with ifndef it checks if the header file is already defined and return a blank file is so.
//otherwise just return the header file
#ifndef ConfHeader_H
#define ConfHeader_H
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>


//Declare Stuff for Source.cpp to use from Config.cpp
namespace conf {
	class Item {
	public:
		std::string name = "";
		double price = 0.00;
	};
	// enum for what type of item;
	const enum ItemType { topping, extra, potato };
	//add function adds an item to the menu e.g. creates a new json file for the item.
	int Add(Item item, ItemType type);
	//view function shows all items
	std::vector<std::filesystem::path> View(ItemType type);
	
}

#endif

