## This program uses a class declared "Checkbook" to parallel a check register for a banking account

# cpp program

# compiled: g++ -o main checkbook.cpp checkregister.cpp

--------- this is just a check register, NOT an atm or bank transaction ---------

- The user selects from a variety of commmands of which action to take.  Actions include: setting initial balance, depositing, withdrawing (debit card or atm transactions), check writing (user or program selected), inputing from a file or outputing to a file. 

- The program uses exception throws to handle inaccurate user input in the command selection code as well as in the check number incrementation of checks seeing to it that no duplicate check number is used.

- users enter ints and doubles in local check#, payment and desposits before being converted to strings for constructor instantiation.  Also, values are converted from strings to doubles and back to strings for purposes of calculation when having selected n, c, w and d.

- The program useds an overloaded getline function to set the initial balance
