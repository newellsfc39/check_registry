#ifndef CHECKBOOK_H
#define CHECKBOOK_H
#include <string>
#include <vector>
#define LN __LINE__
#define FN __FILE__
using namespace std;

class Checkbook{

private:
	string transactionType;
	string transactionDate;
	string transactionDescription;
	string payment;
	string deposit;
	string balance;
	
public:
//	Exception class
	class StringLengthError{
	private:
		string explanation;
	public:
		StringLengthError(string explain){
			explanation = explain;
		}
		string getExplanation(){
			return explanation;
			}
	};

	//	Exception class
	class FoundMatchException{
	private:
		int matchingNumber;
	public:
		FoundMatchException(int match){
			matchingNumber = match;
		}
		int getMatchingNumber(){
			return matchingNumber;
		}
	};

		//	Exception class
	class NextCheckException{
	private:
		int nextCheck;
	public:
		NextCheckException(int next){
			nextCheck = ++next;
		}
		int getNextNumber(){
			return nextCheck;
		}
	};

	// default construstor
	Checkbook();
	// constructor
	Checkbook(string,string, string, string, string, string);
	// destructor
//	~Checkbook();

	static int checkNumber; 				// static member variable
	static vector<int> duplicateVector;  	// static member variable
	
	void setBalance(string bal);
	string getBalance() const;

	void setDate(string date);
	string getDate()const;

	void setTransactionType(string);
	string getTransactionType() const;

	static int getCheckNumber();
	static void setCheckNumber(int);
	//static int Checkbook::getNextCheck();  // original ... get extra qualification error in member Checkbook
	static int getNextCheck();  // when Checkbook removed .... i get a ton of error messages 
	static bool isMatchingCheckNumber(int, string);

	void setDescription(string desc);
	string getDescription() const;

	void setPayment(string pay);
	string getPayment() const;

	void setDeposit(string dep);
	string getDeposit() const;
	
};

#endif