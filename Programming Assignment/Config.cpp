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
using namespace std;

//enum containing topping, extra, potato, will tell functions which you are using.
enum confType {topping, extra, potato};


//Take in a name and a type and save the new config.
void Add(string name, confType type) {
	switch (type) {
	case topping:
		cout << "Topping";
		break;
	case extra:
		cout << "Extra";
		break;
	case potato:
		cout << "Potato";
		break;
	}
}
//Edit a config using the name and ConfType
void Edit(string name, confType type) {
	return;
}


int main() {
	return 0;
}



/*
References:

*/