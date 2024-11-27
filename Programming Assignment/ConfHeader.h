#pragma once
//makes sure it cannot be declared twice in a source file.
//with ifndef which checks if the headerfile is already defined and return a blank file is so.
//otherwise just return the header file
#ifndef ConfHeader_H
#define ConfHeader_H
#include <string>
#include <iostream>


//Declare Stuff for Source.cpp to use from Config.cpp
namespace conf {
	class Item {
	public:
		std::string name;
		double price;
	};
	// enum for what type of item;
	const enum ItemType { topping, extra, potato };
	//add function adds an item to the menu e.g. creates a new json file for the item.
	int Add(Item item, ItemType type);
	//edit function edits an item
	inline int Edit(std::string name, ItemType type);
	//view function shows all items
	inline int View(ItemType type);
	
}

#endif

