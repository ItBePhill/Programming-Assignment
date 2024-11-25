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

- Create function for adding topping.
- Create function for adding extra.
- Create function for adding potato.
- Create other utility functions, e.g. Clear user folder.
- Create Function for viewing current config, e.g. toppings /  extras  / potatoes.
*/


#include <iostream>
#include "ConfHeader.h"
using namespace std;
//Take in a name and a type and save the new config.
int conf::Add(string name, conf::ConfType type) {
	cout << endl;
	switch (type) {
	case conf::topping:
		cout << "Topping";
		break;
	case conf::extra:
		cout << "Extra";
		break;
	case conf::potato:
		cout << "Potato";
		break;
	}
	return 0;
}
//Edit a config using the name and ConfType
int conf::Edit(string name, conf::ConfType type) {
	cout << "Edit";
	return 0;
}
int conf::View(conf::ConfType type) {
	cout << "View";
	return 0;
}
/*
References:

*/