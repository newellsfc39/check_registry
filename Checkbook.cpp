#include "Checkbook.h"
#include <iostream>
#include <vector>
using namespace std;


int Checkbook::checkNumber = 0;
vector<int> Checkbook::duplicateVector;


// default constructor definition
Checkbook::Checkbook(){
	transactionType = "";
	transactionDate = "";
	transactionDescription = "";
	payment = "";
	deposit = "";
	balance = "";
}

// constructor definition
Checkbook::Checkbook(string selection, string date, string desc, string pay, string dep, string bal){
	setTransactionType(selection);
	setDate(date);
	setDescription(desc);
	setPayment(pay);
	setDeposit(dep);
	setBalance(bal);
}

// destructor definition
/*
Checkbook::~Checkbook(){

}
*/

void Checkbook::setBalance(string bal){
	balance = bal;
}

string Checkbook::getBalance() const{
	return balance;
}

void Checkbook::setDate(string date){
	transactionDate = date;
}

string Checkbook::getDate()const{
	return transactionDate;
}

void Checkbook::setDescription(string desc){
	transactionDescription = desc;
}

string Checkbook::getDescription() const{
	return transactionDescription;
}

void Checkbook::setPayment(string pay){
	payment = pay;
}

string Checkbook::getPayment() const{
	return payment;
}

void Checkbook::setDeposit(string dep){
	deposit = dep;
}

string Checkbook::getDeposit() const{
	return deposit;
}

int Checkbook::getCheckNumber(){
	return checkNumber;
}

void Checkbook::setCheckNumber(int check_Num){
	checkNumber = check_Num;
}

// this function passes (static variable checkNumber + 1) on to set Check Number ()
int Checkbook::getNextCheck(){  
	int check = checkNumber + 1;
	bool noMatch = true;
	do{
			noMatch = isMatchingCheckNumber(check, "N");
			noMatch = false;
	} while (noMatch);
	setCheckNumber(check);
	return check;
}

void Checkbook::setTransactionType(string selection){
	transactionType = selection;
}

string Checkbook::getTransactionType()const{
	return transactionType;
}

// compares to previous entered check numbers, called by setCheckNumber() isValidCheckNumber()
bool Checkbook::isMatchingCheckNumber(int check, string str = ""){
	static vector<int> duplicateVector = { 0 };

	//for (int number : duplicateVector){
	//	cout << number << " ";
	//}
	bool match = false;
	int i;
	for (i = 0; i < duplicateVector.size(); i++){
//		cout << "\nLine: " << LN << "  , " << duplicateVector[i] << " ";
		if (duplicateVector[i] == check){
//			cout << "\n--------------Found a match.------------  " << check << endl;
			if (str == "C"){
				throw Checkbook::FoundMatchException(check);
			}
			else if (str == "N"){
				throw Checkbook::NextCheckException(check);
			}
			else
				continue;
		} 
	}
	duplicateVector.push_back(check);  // add checkNumber to vector for later comparison to additional checks by user
	return match;
}