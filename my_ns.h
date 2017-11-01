#pragma once
#include <string>

namespace utilns{
	
	std::string inputGetlineString();

	// overloaded getline function to handle setInitial balance
	std::string inputGetlineString(std::string str);
	
	int inputNumber();

	double inputDouble();
}