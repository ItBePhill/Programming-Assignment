#pragma once
#include <string>
#include <iostream>

//Declare Functions for Source.cpp to use funtions from Config.cpp
//Also declare enum ConfType
namespace conf {
	const enum ConfType {topping, extra, potato};
	inline int Add(std::string name, ConfType type);
	inline int Edit(std::string name, ConfType type);
	inline int View(ConfType type);

}

