#include "my_ns.h"
#include <iostream>
#include<iomanip>

namespace utilns{
	
	std::string inputGetlineString(){
		std::string str;
		std::getline(std::cin, str);
		return str;
	}

	// overloaded getline function to handle setInitial balance
	std::string inputGetlineString(std::string str){
		return str;
	}

	int inputNumber(){
		int num;
		while (!(std::cin >> num)){
			std::cin.clear();
			std::cin.ignore(80, '\n');
			std::cout << "\nThis was not a whole number, enter again. ";
		}
		std::cin.ignore(80, '\n');
		return num;
	}

	double inputDouble(){
		double num;
		bool useIgnore = true;
		while (!(std::cin >> num >> std::fixed >> std::setprecision(2))){
			std::cin.clear();
			std::cin.ignore(80, '\n');
			std::cout << "\nThis was not a number, enter again. ";
			useIgnore = false;
		}
		std::cin.ignore(80, '\n');
		return num;
	}
	
}