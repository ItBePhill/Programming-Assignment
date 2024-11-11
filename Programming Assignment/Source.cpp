// Programming Assignment
//Brief: https://portal.uclan.ac.uk/ultra/courses/_177144_1/outline/file/_7529994_1
#include <iostream>
#include <map>
using namespace std;



/*
TODO:
- Research how to read and write to files, probably JSON or maybe an sqlite db for the potato / toppings / extras.
- Finish Add Credits Function
- Finish Create Order Function
- Finish View Recent Function
- 
*/


//Classes Not Done / Don't know if gonna use
//class Potato {
//public:
//	string name;
//	double price;
//};
//
//class Topping {
//public:
//	string name;
//	double price;
//};
//
//class Extra {
//public:
//	string name;
//	double price;
//};

void addCredits() {
	int creditAnswer;
	cout << endl << "-----Add Credits-----\nCurrent Credits: ";
	cout << endl << "";
}
void createOrder() {
	int orderAnswer;
	cout << endl << "----Create Order-----";
}
void viewRecent() {
	cout << endl << "----View Recent-----";
}

int main() {
	int welcomeAnswer;
	bool breakwhile = false;
	//loop forever until user types answer
	while (!breakwhile) {
		cout << "Welcome to Hot Potato!\nWhat would you like to do?\n1 - Add Credits\n2 - Create an Order\n3 - View Recent Orders\n- ";
		cin >> welcomeAnswer;

		//check if answer is valid
		switch (welcomeAnswer) {
			case 1:
				addCredits();
				breakwhile = true;
				break;
			case 2:
				createOrder();
				breakwhile = true;
				break;
			case 3:
				viewRecent();
				breakwhile = true;
				break;
			default:
				cout << "\nError: Invalid Option\n";
				break;
		}
	}

}

