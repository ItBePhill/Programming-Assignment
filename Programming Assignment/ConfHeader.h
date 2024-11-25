#pragma once
#include <string>
#include <iostream>
using namespace std;

//Declare Functions for Source.cpp to use funtions from Config.cpp
//Also declare enum ConfType
namespace conf {
	enum ConfType {topping, extra, potato};
	int Add(string name, ConfType type);
	int Edit(string name, ConfType type);
	int View(ConfType type);

}

