#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "main.h"
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;

bool isRunning = true; //changed when user exits program

int main() 
{
	//Welcome message and initial setup
	cout << "Welcome to Loan it! This is a tool to track your loaned items." << endl;

	//Retreive previously saved data
	Item::ExtractItems(); 
	Person::ExtractPersons();
	Loan::ExtractLoans();

	//Begin with commands
	cout << endl << "Here is the list of available commands:" << endl << endl;
	MainMethods::DisplayCommands();

	//Run commands until program is exited
	while (isRunning) 
	{
		MainMethods::ExecuteCommand();
	}
	
}

/*Display Commands: 
* Displays a menu of all available commands to the user
* No parameter, No return
*/
void MainMethods::DisplayCommands() 
{
	cout << "Create Item: " << "Creates a new item to loan" << endl;
	cout << "Edit Item: " << "Edit the description of the item with given name" << endl;
	cout << "List Items: " << "Displays a list of existing items" << endl;
	cout << "Delete Item: " << "Deletes the item with given name" << endl; 
	cout << "Create Person: " << "Creates a person to loan to" << endl;
	cout << "List Persons: " << "Displays a list of existing persons" << endl;
	cout << "Delete Person: " << "Deltes the person with given name" << endl; 
	cout << "Create Loan: " << "Creates a loan entry" << endl;
	cout << "List Loans: " << "Displays a list of existing loans" << endl;
	cout << "Delete Loan: " << "Deletes the loan with given ID" << endl;
	cout << "Save: " << "Saves the data created so far" << endl;
	cout << "Exit: " << "Exits the program" << endl;
	cout << "Help: " << "Displays the list of available commands" << endl << endl;
}


/*ExecuteCommand: 
*Takes command input from user and executes them
* No parameter, No return
*/
void MainMethods::ExecuteCommand() 
{
	//Take command from user and convert to lowercase for accurate comparison.
	string command;
	cout << endl << "Enter a command" << endl;
	cout << "If you need help, type \"Help\" for list of available commands and their uses" << endl;
	getline(cin, command);
	std::transform(command.begin(), command.end(), command.begin(), tolower);

	string nameInput; //string to hold parameter inputs in certain commands.
	string yn; //string to hold yes/no inputs for certain methods.

	//Check commands and call relevent functions.
	if (command._Equal("help")) 
	{
		MainMethods::DisplayCommands(); //Help Menu displayed
	}
	else if (command._Equal("exit"))
	{
		MainMethods::Exit();
	}
	else if (command._Equal("save")) 
	{
		MainMethods::Save();
	}
	else if (command._Equal("create item"))
	{
		//Take input for name of item being created
		cout << "Please enter item's name." << endl;
		getline(cin, nameInput);

		//Check for invalid input and ask again if needed
		while (nameInput.empty() || nameInput._Equal(" "))
		{
			cout << "Name cannot be blank. Please enter a valid name." << endl;
			getline(cin, nameInput);
		}

		Item::CreateItem(nameInput);
	}
	else if (command._Equal("list items"))
	{
		Item::DisplayItems();
	}
	else if (command._Equal("create person"))
	{
		//Take input for name of person being created
		cout << "Please enter person's name." << endl;
		getline(cin, nameInput);

		//Check for invalid input and ask again if needed
		while (nameInput.empty() || nameInput._Equal(" "))
		{
			cout << "Name cannot be blank. Please enter a valid name." << endl;
			getline(cin, nameInput);
		}

		Person::CreatePerson(nameInput);
	}
	else if (command._Equal("list persons"))
	{
		Person::DisplayPersons();
	}
	else if (command._Equal("create loan"))
	{
		Loan::CreateLoan();
	}
	else if (command._Equal("list loans"))
	{
		Loan::DisplayLoans();
	}
	else if (command._Equal("delete item"))
	{
		cout << "Please note that deleting an item also deletes all the loans it is associated with." << endl;
		cout << "Would you like to proceed? Type 'y' for yes 'n' for no." << endl;
		getline(cin, yn);

		if (yn._Equal("y"))
		{
			//Take input on the name of the item to be deleted
			cout << "Please enter the name of the item to be deleted." << endl;
			getline(cin, nameInput);

			//Check for invalid input and ask again if needed
			while (nameInput.empty() || nameInput._Equal(" "))
			{
				cout << "Name cannot be blank. Please enter a valid name." << endl;
				getline(cin, nameInput);
			}

			Loan::DeleteLoan_Item(Item::DeleteItem(nameInput)); //Deletes the item as well as associated loans.
		}
	}
	else if (command._Equal("delete person"))
	{
		cout << "Please note that deleting a person also deletes all the loans they is associated with." << endl;
		cout << "Would you like to proceed? Type 'y' for yes 'n' for no." << endl;
		getline(cin, yn);

		if (yn._Equal("y"))
		{
			//Take input on the name of the person to be deleted
			cout << "Please enter the name of the person to be deleted." << endl;
			getline(cin, nameInput);

			//Check for invalid input and ask again if needed
			while (nameInput.empty() || nameInput._Equal(" "))
			{
				cout << "Name cannot be blank. Please enter a valid name." << endl;
				getline(cin, nameInput);
			}

			Loan::DeleteLoan_Person(Person::DeletePerson(nameInput)); //Deletes the person along with all their loans
		}
	}
	else if (command._Equal("delete loan"))
	{
		Loan::DeleteLoan();
	}
	else if (command._Equal("edit item"))
	{
		//Take input for name of item being created
		cout << "Please enter item's name." << endl;
		getline(cin, nameInput);

		//Check for invalid input and ask again if needed
		while (nameInput.empty() || nameInput._Equal(" "))
		{
			cout << "Name cannot be blank. Please enter a valid name." << endl;
			getline(cin, nameInput);
		}

		Item::EditItem(nameInput);
	}
	else
	{
		cout << "It looks like this command doesn't exist. Make sure you spell it right!" << endl;
	}
}


/*Save:
* Saves the data to ItemData, PersonData, and LoanData files appropriately
* No parameter, no return
* Uses global variables: saveItemIndex, savePersonIndex, saveLoanIndex to track the index where saving starts
*/
void MainMethods::Save() 
{
	Item::SaveItems();
	Person::SavePersons();
	Loan::SaveLoans();
	cout << "Data was saved successfully!" << endl;
}


/*Exit:
* Final save, free memory, terminate program
* No parameter, No Return
*/
void MainMethods::Exit() 
{
	string yn; //stores user's yes/no response
	cout << "Would you like to save before exiting? Type 'y' for yes or 'n' for no" << endl;
	getline(cin, yn);
	//Save the data one last time if the user says yes to the save reminder
	if (yn._Equal("y")) 
	{ 
		MainMethods::Save(); 
	}
		
	//Deleting all dynamically allocated objects of the program remaining in the vectors
	Item::ClearItemList();
	Person::ClearPersonList();
	Loan::ClearLoanList();

	cout << "Program terminated" << endl;
	isRunning = false; //exits loop in main, allows exiting main function
}