#pragma once
#include "Item.h"
#include "Person.h"


class Loan 
{
public:
	string getID(); //ID Accessor

	static void CreateLoan();
	static void DeleteLoan(); // through user
	static void DeleteLoan_Item(string deletedItemID); //becasue the associated item was deleted
	static void DeleteLoan_Person(string deletedPersonID); // delete because the associated item was deleted
	static void DisplayLoans();
	static void ClearLoanList();

	//Saving and retrieving data
	static void SaveLoans();
	static void ExtractLoans();

private:
	Loan(Person* personIn, Item* itemIn); //constructor for brand new loan
	Loan(Person* personIn, Item* itemIn, string IDIn); //constructor for extracting previously saved loans
	Item* itemLoaned;
	string itemLoanedID = "None";
	Person* personLoaned;
	string personLoanedID = "None";
	string loanID = "No loan ID";
};
