#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include "Loan.h"
using namespace std;


static vector<Loan*> LoanList; //to store all items created through CreateItem function.


/*Loan class constructor
* Parameters: personIn - personLoaned, itemIn - itemLoaned
*/
Loan::Loan(Person* personIn, Item* itemIn) 
{
	personLoaned = personIn;
	personLoanedID = personLoaned->getID();
	itemLoaned = itemIn;
	itemLoanedID = itemLoaned->getID();
	
	//Allocating a unique loan ID based on creation date
	time_t currentTime = time(NULL);
	string timestr = ctime(&currentTime);
	loanID = timestr.substr(0, timestr.size()-1); //to get rid of the extra newline at the end
}

/*Loan class constructor
* Parameters: personIn - personLoaned, itemIn - itemLoaned, IDIn - loanID
*/
Loan::Loan(Person* personIn, Item* itemIn, string IDIn)
{
	personLoaned = personIn;
	personLoanedID = personLoaned->getID();
	itemLoaned = itemIn;
	itemLoanedID = itemLoaned->getID();
	
	loanID = IDIn;
}

//ID Accessor
string Loan::getID() 
{
	return loanID;
}

/*CreateLoan
* Creates loan class objects and adds them to loan List.
* No parameter, no return.
*/
void Loan::CreateLoan() 
{
	//To store new loan's attributes
	Item* thisLoanItem = nullptr;
	Person* thisLoanPerson = nullptr;

	string createLoanInput; //To take user input throughout the function.
	string yn; //To take yes/no input from user

	//Allocation of new loan's itemLoaned attribute

	cout << "Enter the name of the item being loaned: " << endl;
	getline(cin, createLoanInput);

	//Check for invalid input and ask again if needed
	while (createLoanInput.empty() || createLoanInput._Equal(" "))
	{
		cout << "Name cannot be blank. Please enter a valid name." << endl;
		getline(cin, createLoanInput);
	}

	//Check if the item name exists, or is repeated, proceed accordingly.
	if ( Item::CheckInArray(createLoanInput) == 0 ) 
	{
		//Case: Item does not exist

		cout << endl << "It looks like there is no such item created." << endl;
		cout << "Would you like to create one right now?" << endl;
		cout << "Enter 'y' for yes or 'n' for no" << endl;
		getline(cin, yn);
		
		//Create item if yes, notify incomplete loan creation if no.
		if ( yn._Equal("y") ) 
		{

			Item::CreateItem(createLoanInput);
			thisLoanItem = Item::FindItemByName(createLoanInput);
		}
		else 
		{
			cout << "Loan creation was incomplete as item could not be found." << endl;
			return;
		}
	} 
	else if (Item::CheckInArray(createLoanInput) == 1)
	{
		//Case: Only one item with the given name exists
		thisLoanItem = Item::FindItemByName(createLoanInput);
	}
	else if ( Item::CheckInArray(createLoanInput) > 1 ) 
	{
		//Case: More than one items with the given name exist

		cout << "It seems like there are more than one items with that name." << endl;
		cout << "Refer to the following list. Please copy and paste your desired item's ID." << endl;
		Item::DisplayItems();
		cout << "Paste Item ID below: " << endl;
		getline(cin, createLoanInput);

		thisLoanItem = Item::FindItemByID(createLoanInput);

		//Don't create loan if ID couldn't match a person in the list
		if (thisLoanItem == nullptr) 
		{
			cout << "No such item ID found. Loan creation unsucessful." << endl;
			return;
		}

	}
	


	//Allocation of new loan's personLoaned attribute

	cout << "Enter the name of the person the loan is being given to: " << endl;
	getline(cin, createLoanInput);

	//Check for invalid input and ask again if needed
	while (createLoanInput.empty() || createLoanInput._Equal(" "))
	{
		cout << "Name cannot be blank. Please enter a valid name." << endl;
		getline(cin, createLoanInput);
	}

	//Check if the person name exists, or is repeated, proceed accordingly.
	if (Person::CheckInArray(createLoanInput) == 0)
	{
		//Case: No person with the given names exists

		cout << endl << "It looks like there is no such person created." << endl;
		cout << "Would you like to create one right now?" << endl;
		cout << "Enter 'y' for yes or 'n' for no" << endl;
		getline(cin, yn);

		//Create item if yes, notify incomplete loan creation if no.
		if (yn._Equal("y")) 
		{
			Person::CreatePerson(createLoanInput);
			thisLoanPerson = Person::FindPersonByName(createLoanInput);
		}
		else 
		{
			cout << "Loan creation was incomplete as person could not be found." << endl;
			return;
		}
	}
	else if (Person::CheckInArray(createLoanInput) == 1)
	{
		//Case: One person with the given name exists
		thisLoanPerson = Person::FindPersonByName(createLoanInput);
	}
	else if (Person::CheckInArray(createLoanInput) > 1)
	{
		//Case: More than one person with the given name exists

		cout << "It seems like there are more than one person with that name." << endl;
		cout << "Refer to the following list. Please copy and paste your desired person's ID." << endl;
		Person::DisplayPersons();
		cout << "Paste Person ID below: " << endl;
		getline(cin, createLoanInput);

		thisLoanPerson = Person::FindPersonByID(createLoanInput);

		//Don't create loan if ID couldn't match a person in the list
		if (thisLoanPerson == nullptr) 
		{
			cout << "No such person ID found. Loan creation unsucessful." << endl;
			return;
		}
	}
	

	//Create the Loan object and store it in LoanList
	Loan* createdLoan = new Loan(thisLoanPerson, thisLoanItem);
	LoanList.push_back(createdLoan);

	cout << "Loan was created successfully!" << endl;
	
}

/*Delete Loan
* Deletes the loan object with the given ID
* Parameter - Loan ID of the object to be deleted, no return.
*/
void Loan::DeleteLoan()
{
	string deleteID;
	cout << "Please refer to the list below. Copy and paste the ID of the loan to be delted" << endl;

	Loan::DisplayLoans();

	cout << "Paste the loan ID below: " << endl;
	getline(cin, deleteID); //reusing the deleteName string for ID input

	for (int i = 0; i < LoanList.size(); ++i) 
	{
		if (LoanList.at(i)->getID()._Equal(deleteID)) 
		{
			delete LoanList.at(i); //free dynamically allocated memory
			LoanList.erase(LoanList.begin() + i); //remove from vector
			cout << "Loan deleted successfully." << endl;
			return;
		}
	}
	cout << "No such ID found. Nothing was delted." << endl;
	return;
}

/*DisplayLoans
* Lists all loans stored in vector: LoanList
* No parameters, no return
*/
void Loan::DisplayLoans() 
{
	//check if the LoanList is empty and exit function if true.
	if (LoanList.size() == 0) 
	{
		cout << "No previously created loans found." << endl;
		return;
	}

	cout << "Here are the previously created loans:" << endl;
	cout << "______________________________________________" << endl;
	
	//Traverse through item list and print info of each
	for (int i = 0; i < LoanList.size(); ++i) 
	{
		cout << "Loan " << i + 1 << endl;
		cout << "Loaned item's name - " << LoanList.at(i)->itemLoaned->getName() << endl;
		cout << "Loaned item's description - " << LoanList.at(i)->itemLoaned->getDescription() << endl;
		cout << "Person loaned to - " << LoanList.at(i)->personLoaned->getName() << endl;
		cout << "Loan ID - " << LoanList.at(i)->getID() << endl << endl;

	}

	cout << "______________________________________________" << endl;
}

/*ClearLoanList:
* Deletes all the items in the vector: LoanList. To be called when exiting the program
* No parameter, no return.
*/
void Loan::ClearLoanList()
{
	for (int i = 0; i < LoanList.size(); ++i)
	{
		delete LoanList.at(i); //call destructor on each
	}
	LoanList.clear(); //clear vector
	LoanList.shrink_to_fit(); //free any memory reserved by vector
}

/*SaveLoans:
* Saves data from LoanList vector to LoanData file
* No parameter, no return
*/
void Loan::SaveLoans() 
{
	fstream LoanFile;
	int result = remove("LoanData.txt");

	LoanFile.open("LoanData.txt", ios::app); //open append mode

	if (LoanFile.is_open())
	{
		for (int i = 0; i < LoanList.size(); ++i)
		{
			LoanFile << LoanList.at(i)->getID() << endl;
			LoanFile << LoanList.at(i)->itemLoaned->getID() << endl;
			LoanFile << LoanList.at(i)->personLoaned->getID() << endl;

		}
		LoanFile.close();
		return;
	}
	else
	{
		cout << "File could not be opened" << endl;
		return;
	}
}

/*ExtractLoans
* Extracts data from LoanData file and saves them in LoanList. Called only in the begnning of the program.
* No parameter, no return
*/
void Loan::ExtractLoans()
{
	fstream LoanFile;

	LoanFile.open("LoanData.txt", ios::in);

	if (LoanFile.is_open())
	{
		string IDItem;
		string IDPerson;
		string ID;

		while (getline(LoanFile, ID))
		{
			getline(LoanFile, IDItem);
			getline(LoanFile, IDPerson);

			Item* thisLoanItem = Item::FindItemByID(IDItem);
			Person* thisLoanPerson = Person::FindPersonByID(IDPerson);

			Loan* createdLoan = new Loan(thisLoanPerson, thisLoanItem, ID);
			LoanList.push_back(createdLoan); 
		}
		LoanFile.close();
		return;

	}
}

/*DeleteLoan_Item
* Called when associated item of a loan is deleted. Prevents further issues of referencing deleted items
* Parameter - ID of the item that was deleted, all loans of this item will be deleted.
* No return
*/
void Loan::DeleteLoan_Item(string deletedItemID)
{
	for (int i = 0; i < LoanList.size(); ++i)
	{
		if (LoanList.at(i)->itemLoanedID._Equal(deletedItemID))
		{
			delete LoanList.at(i); //free dynamically allocated memory
			LoanList.erase(LoanList.begin() + i); //remove from vector
		}
	}
}

/*DeleteLoan_Person
* Called when associated person of a loan is deleted. Prevents further issues of reference deleted items
* Parameter - ID of the person that was deleted, all loans to this person will be deleted.
* No return
*/
void Loan::DeleteLoan_Person(string deletedPersonID)
{
	for (int i = 0; i < LoanList.size(); ++i)
	{
		if (LoanList.at(i)->personLoanedID._Equal(deletedPersonID))
		{
			delete LoanList.at(i); //free dynamically allocated memory
			LoanList.erase(LoanList.begin() + i); //remove from vector
		}
	}
}
