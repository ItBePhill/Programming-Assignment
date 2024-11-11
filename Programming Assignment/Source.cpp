// Programming Assignment 
#include <iostream>
#include <map>
using namespace std;


//Classes
class Potato {
public:
	string name;
	double price;
};

class Topping {
public:
	string name;
	double price;
};

class Extra {
public:
	string name;
	double price;
};


int main() {
	Extra extra;
	extra.name = "Salad Box";
	extra.price = 1.50;
	cout << "Welcome to Hot Potato!\nWhat woudl you like to do?\n1 - Add Credits\n2 - Create an Order\n3 - View Recent Orders";
	cout << endl << extra.name << " " << extra.price;
}