/*
Course:		CIT 237 C++
Class D/H:	M/W 5:30-8:20 pm
Professor:	Peter Morgan
Assignment: Project III
Title:		Checking Account Register App
Student:	Thomas Newell
Due Date:	08/12/2015
*/

// This program uses a class declared "Checkbook" to parallel a check register for a banking account
// The user selects from a variety of commmands of which action to take.  Actions include:
// setting initial balance, depositing, withdrawing (debit card or atm transactions), 
// check writing (user or program selected), inputing from a file or outputing to a file. 

// The program uses exception throws to handle inaccurate user input in the command selection code
// as well as in the check number incrementation of checks seeing to it that no duplicate check # is used.

// users enter ints and doubles in local check#, payment and desposits before being converted to strings 
// for constructor instantiation.  Also, values are converted from strings to doubles and back to strings
// for purposes of calculation when having selected n, c, w and d.

// The program useds an overloaded getline function to set the initial balance

// --------- this is just a check register, NOT an atm or bank transaction ---------
// --------- > Incompleted or Suggestions < ------------
// program fails if:
// 	- record a new check option is used and when payment amount is entered 
// 	- once set initial balance is used, it should be disabled for any further use

// program needs:
//	-develop function to produce date entry
//	-date formatting
//	-format output to be reader friendly
//	-currency formatting
// 	-to ask if unidentified user has an account
//	-if no account...create one
//	-if withdrawing from account, write transaction to file
//	-to reject withdraws that attempt to overdraw user balance
//	-to be further modularized

#include "Checkbook.h"
#include <iostream> // for cout/cin
#include <iomanip> // for setw()
#include <cstdlib> // for exit()
#include <fstream> // for output and input streams
using namespace std;

void showMenu();										
void showRegister(vector<Checkbook> &);
void printToFile(fstream &, vector<Checkbook> &);		
void openForOutput(fstream &, string);
void openForInput(fstream &, string);					
vector<Checkbook> readFromFile(fstream &, string);

string getValidSelection();					
int inputNumber();
string inputGetlineString();				
string inputGetlineString(string);
double inputDouble();						
double inputDouble(double);
double processBalance(string, double, Checkbook &);

int main(){
	fstream outToFile; 		
	fstream readInFromFile;
	string outputFilename; 	
	string inputFilename;		
	string selection;
	string sel; 			
	string date; 				
	string desc;
	double pay; 			
	string str_pay = "";
	double dep; 			
	string str_dep = "";
	double bal; 			
	string str_bal = "";
	int size;
	vector<Checkbook> vect;
	Checkbook transaction();

	showMenu();

	do{ 			// do while ends just before main
		bool validSelection = true;
		size = vect.size();

		// validate user input until proper selection is given
		do{
			try{
				selection = getValidSelection();
				validSelection = false;
			}
			catch (Checkbook::StringLengthError str){
				cout << "Error: " << str.getExplanation() << " is invalid selection due to its length. "
					<< "Input choices are of one letter only. Try again. " << endl;
			}
			catch (string invalidSelectionException){
				cout << invalidSelectionException << endl;
			}
		} while (validSelection); // end of get selection


		// program falls through selection process
		// quits
		if (selection == "Q"){
			printToFile(outToFile, vect);

			exit(0);
		}  // end of "Q"
		
		// will open file for writing
		if (selection == "O"){
			bool openError = true;
			do{
				cout << "Enter name of output file? ";
				cin >> outputFilename;
				try{
					openForOutput(outToFile, outputFilename);
					openError = false;
				}
				catch (string openFileError){
					cout << openFileError << " Try again. ";
				}
			} while (openError);

		}  // end of "O"
		
		// will open file for reading
		else if (selection == "I"){
			bool openError = true;
			cout << "Enter name of input file? ";
			do{
				cin >> inputFilename;
				try{
					openForInput(readInFromFile, inputFilename);
					openError = false;
				}
				catch (string openFileError){
					cout << openFileError << " Try again. ";
				}
			} while (openError);

			if (readInFromFile){
				vect = readFromFile(readInFromFile, inputFilename);
				showRegister(vect);
			}
		}  // end of "I"

		// selects a user given check number
		else if (selection == "C"){
			bool match = true;
			int num;
			do{
				try{
					cout << "Check Number: ";
					num = inputNumber();
					match = Checkbook::isMatchingCheckNumber(num, "C");
					Checkbook::setCheckNumber(num);
				}
				catch (Checkbook::FoundMatchException num){
					cout << endl << num.getMatchingNumber() << " has already been used, use another check number. \n";
				}
			} while (match);

			sel = to_string(num);

			cout << "Enter date: ";
			date = inputGetlineString();

			cout << "Enter description of transaction. ";
			desc = inputGetlineString();

			cout << "What is the payment amount? ";
			pay = inputDouble();
			str_pay = to_string(pay);

			str_dep = "";

			bal = stod(vect[size - 1].getBalance()) - pay;
			str_bal = to_string(bal);
		}  // end of "C"
		
		// writes date to use on transaction, needs formatting
		else if (selection == "D"){
			sel = "D";

			cout << "Enter date:";
			date = inputGetlineString();

			cout << "Input description of transaction. ";
			desc = inputGetlineString();

			str_pay = "";

			cout << "What is the deposit amount? ";
			dep = inputDouble();
			str_dep = to_string(dep);

			bal = stod(vect[size - 1].getBalance()) + dep;
			str_bal = to_string(bal);

		}  // end of "D"

		// gives user the menu for transactions
		// can develop further help instructions for user
		else if (selection == "H"){
			showMenu();
		} // end of "H"

		// selects the very next check in numbered order
		else if (selection == "N"){
			bool isBad = true;
			string answer;
			int i = 0;
			int num = 0;
			num = Checkbook::getNextCheck();		// accesses current checkNumber and adds 1	
			
			do{
				try{
					cout << "\nIs " << num << " the next sequential check number? Y/N";
					cin >> answer;
					while (!(answer[i] == 'y' || answer[i] == 'Y')){
						num = Checkbook::getNextCheck();
						cout << "\nIs " << num << " the next sequential check number? Y/N";
						cin >> answer;
					}
					isBad = false;
				}
				catch (Checkbook::NextCheckException next){
					Checkbook::setCheckNumber(Checkbook::getCheckNumber() + 1); // auto increment to the next number
				}
			} while (isBad);
		}  // end of "N"

		// provides the user to give a initial starting balance
		else if (selection == "S"){
			sel = "S";

			cout << "Enter transaction date: ";
			date = inputGetlineString();

			// overloaded getline() function
			desc = inputGetlineString("Starting Balance");

			str_pay = "";

			str_dep = "";

			cout << "Enter a starting balance. ";
			bal = inputDouble();
			str_bal = to_string(bal);


		} // end of "S"

		// allows user to withdraw money
		else if (selection == "W"){
			sel = "W";

			cout << "Enter date: ";
			date = inputGetlineString();

			cout << "Input description of transaction. ";
			desc = inputGetlineString();

			cout << "What is the payment amount? ";

			pay = inputDouble();
			str_pay = to_string(pay);

			str_dep = "";

			bal = ((stod(vect[size-1].getBalance())) - (pay));   
			// cout << "About to call constructor. ";
			// system("pause");
			str_bal = to_string(bal);
		}
		else {
			continue;
		} // end of "W"

		// writes data to object for these selections/conditions ... "C", "D", "W", "S"
		if (outToFile){			// instantiate Checkbook class and push_back into vector
			if (selection == "C" || selection == "D" || selection == "W" || selection == "S"){
				Checkbook transaction(sel, date, desc, str_pay, str_dep, str_bal);  //<---- 
				vect.push_back(transaction);
			}
		}
		
		// shows data for the following selections/conditions ... "O", "N", "I"
		if (!(selection == "O" || selection == "N" || selection == "I")){
			showRegister(vect);
		}
	} while (true);  // end of first do while

	return 0;
}

void showMenu(){
	cout << "\'O\' ...specificy the name of the Output file." << endl;
	cout << "\'I\' ...specificy the name of the Input file." << endl;
	cout << "\'S\' ...set the initial balance." << endl;
	cout << "\'N\' ...get next check number." << endl;
	cout << "\'C\' ...record a new check." << endl;
	cout << "\'W\' ...withdraw via debit card purchase or from ATM" << endl;
	cout << "\'D\' ...deposit." << endl;
	cout << "\'H\' ...help (show menu)." << endl;
	cout << "\'Q\' ...quit to exit the program." << endl;
}

void showRegister(vector<Checkbook> &trans){
	cout << "\n\nOUTPUT: " << endl;
	cout << fixed << setprecision(2);
	for (int i = 0; i < trans.size(); i++){
		cout << trans[i].getTransactionType() << "|"
			<< trans[i].getDate() << "|"
			<< trans[i].getDescription() << "|";
		if (trans[i].getPayment() != ""){
			cout << stod(trans[i].getPayment()) << "|";
		}
		else{
			cout << trans[i].getPayment() << "|";
		}
		if (trans[i].getDeposit() != ""){
			cout << stod(trans[i].getDeposit()) << "|";
		}
		else{
			cout << trans[i].getDeposit() << "|";
		}
		if (trans[i].getBalance() != ""){
			cout << stod(trans[i].getBalance()) << endl;
		}
		else{
			cout << trans[i].getBalance() << endl;
		}
	}
}

void printToFile(fstream & outToFile, vector<Checkbook> & transaction){
	cout << "\nIn print to file. \n";
	cout << fixed << setprecision(2);
	for (int i = 0; i < transaction.size(); i++){

		outToFile << transaction[i].getTransactionType() << "|"
			<< transaction[i].getDate() << "|"
			<< transaction[i].getDescription() << "|"
			<< transaction[i].getPayment() << "|"
			<< transaction[i].getDeposit() << "|"
			<< transaction[i].getBalance() << endl;

	}
	outToFile.close();
}

vector<Checkbook> readFromFile(fstream & readInFromFile, string){
	vector <Checkbook>vect;
	string line;
	const int SIZE = 6;
	string arrayTransaction[SIZE];

	getline(readInFromFile, line);

	while (readInFromFile){
		int begin = 0;
		int x = 0;
		for (int i = 0; i < line.size(); i++){

			if (line[i] == '|'){
				if (begin == i){
					arrayTransaction[x] = "";
					begin = i + 1;
					x++;
				}
				else {
					arrayTransaction[x] = line.substr(begin, i - begin );
					begin = i + 1;
					x++;
				}
			}
			if (i == (line.size() - 1)){
				arrayTransaction[x] = line.substr(begin, (line.size() - 1 - begin));
			}
			//cout << "\n\n\narrayTransaction[" << x << "] is " << arrayTransaction[x];
		}

		Checkbook transaction(arrayTransaction[0], arrayTransaction[1], arrayTransaction[2], arrayTransaction[3], arrayTransaction[4], arrayTransaction[5]);
		
		vect.push_back(transaction);

		getline(readInFromFile, line);
	}

	readInFromFile.close();

	return vect;
}  // end of readInFromFile

void openForOutput(fstream & outToFile, string outputFilename){
	outToFile.open(outputFilename, ios::out | ios::app);
	// if file opened successfully
	if (outToFile.fail()){
		throw "Error opening the file.\n";
	}
	else{
		return;
	}
}

void openForInput(fstream & readInFromFile, string inputFilename){
	readInFromFile.open(inputFilename, ios::in);

	// if file opened successfully
	if (readInFromFile.fail()){
		cout << "Error opening the file.\n";
	}
	else{
		return;
	}
}

string getValidSelection(){
	string selection;
	string arraySelection[] = { "o", "O", "i", "I", "c", "C", "n", "N", "d", "D", "s", "S", "v", "V", "w", "W", "h", "H", "q", "Q" };

	cout << "\nCommand: ";
	cin >> selection;
	cin.ignore(80, '\n');

	if (selection.length() > 1){
		throw Checkbook::StringLengthError(selection);
	}
	else {
		for (int i = 0; selection[i] != 0; i++){
			if (selection[i] <= 122 && selection[i] >= 97)
				selection[i] -= 32;
		}
		for (string test : arraySelection){
			if (test == selection){
				return selection;
			}
			else
				continue;
		}		// end of for loop
		string invalidSelectionException = "Input Error: Selection was not recognized, please try again.";
		throw invalidSelectionException;
	} // end of else
} // end of getValidSelection

int inputNumber(){
	int num;
	while (!(cin >> num)){
		cin.clear();
		cin.ignore(80, '\n');
		cout << "\nThis was not a whole number, enter again. ";
	}
	cin.ignore(80, '\n');
	return num;
}

double inputDouble(){
	double num;
	bool useIgnore = true;
	while (!(cin >> num >> fixed >> setprecision(2))){
		cin.clear();
		cin.ignore(80, '\n');
		cout << "\nThis was not a number, enter again. ";
		useIgnore = false;
	}
	cin.ignore(80, '\n');
	return num;
}

string inputGetlineString(){
	string str;
	getline(cin, str);
	return str;
}

// overloaded getline function to handle setInitial balance
string inputGetlineString(string str){
	return str;
}
