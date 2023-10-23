#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <fstream>
#include "Person.h"

using namespace std;


static vector<Person*> PersonList; //to store all persons created through CreateItem function.


/*Person class constructor
* Parameters: nameIn - Person's Name
*/
Person::Person(string nameIn) {
	personName = nameIn;

	//Assigning a unique ID
	time_t currentTime = time(NULL);
	string timestr = ctime(&currentTime);
	personID = timestr.substr(0, timestr.size()-1); //to get rid of the extra new line at the end
}

/*Person class constructor
* Parameter: nameIn - personName, IDIn - personID
*/
Person::Person(string nameIn, string IDIn)
{
	personName = nameIn;
	personID = IDIn;
}

//Person Name mutator
void Person::setName(string newName)
{
	personName = newName;
}

//Person ID mutator
void Person::setID(string newID) 
{
	personID = newID;
}

//Person name accessor
string Person::getName() 
{
	return personName;
}

//Person ID accessor
string Person::getID() 
{
	return personID;
}

/*CreatePerson
* Creates Person class objects and adds them to Person List.
* Parameter - name of the person being created, no return.
*/
void Person::CreatePerson(string nameInput)
{
	Person* createdPerson = new Person(nameInput); //create person pointer
	PersonList.push_back(createdPerson);
	cout << createdPerson->getName() << " person was created!" << endl;
}

/*DisplayPersons
* Displays all the person objects in the vector: PersonList
* No parameter, no return
*/
void Person::DisplayPersons()
{
	//check if the person list is empty and exit function if true.
	if (PersonList.size() == 0) 
	{
		cout << "No previously created persons found." << endl;
		return;
	}

	cout << "Here are the previously created persons:" << endl;
	cout << "______________________________________________" << endl;

	//Traverse through item list and print info of each
	for (int i = 0; i < PersonList.size(); ++i) 
	{
		cout << "Person " << i + 1 << ": " << endl;
		cout << "Name - " << PersonList.at(i)->getName() << endl;
		cout << "Person ID - " << PersonList.at(i)->getID() << endl << endl;
	}

	cout << "______________________________________________" << endl;
}

/*DeletePerson
* Deletes the person object with the given name
* Parameter - name of the person object to be deleted, no return.
*/
string Person::DeletePerson(string deleteName)
{
	string deletedID;
	int personNameOccurances = Person::CheckInArray(deleteName);
	//Check if the given names exists, or is repeared. Proceed accordingly
	if (personNameOccurances == 0)
	{
		//Case: No person with the given name exists
		cout << "No person with such name exists. Nothing to delete." << endl;
		return "No ID returned";
	}
	else if (personNameOccurances == 1)
	{
		//Case: Only one person with given name exists
		for (int i = 0; i < PersonList.size(); ++i) 
		{
			if (PersonList.at(i)->getName()._Equal(deleteName)) 
			{
				deletedID = PersonList.at(i)->getID();
				delete PersonList.at(i); //free dynamically allocated memory
				PersonList.erase(PersonList.begin() + i); //remove from vector
				cout << "Person deleted successfully." << endl;
				return deletedID;
			}
		}
		
	}
	else if (personNameOccurances > 1)
	{
		//Case: More than one person with the given name exists
		cout << "More than one person in the list has the name " + deleteName << endl;
		cout << "Please refer to the list below. Copy and paste the ID of the person to be delted" << endl;

		Person::DisplayPersons();

		cout << "Paste the person ID below: " << endl;
		getline(cin, deleteName); //reusing the deleteName string for ID input

		for (int i = 0; i < PersonList.size(); ++i) 
		{
			if (PersonList.at(i)->getID()._Equal(deleteName)) 
			{
				deletedID = PersonList.at(i)->getID();
				delete PersonList.at(i); //free dynamically allocated memory
				PersonList.erase(PersonList.begin() + i); //remove from vector
				cout << "Person deleted successfully." << endl;
				return deletedID;
			}
		}
		cout << "No such ID found. Nothing was delted." << endl;
		return "No ID returned";
	}

}

/*CheckInArray:
* Returns the number of objects with a given name in the PersonList
* Parameter checkName - the name to check for number of occurances in PersonList
* Return - returns number of occurances of checkName in PersonList
*/
int Person::CheckInArray(string checkName)
{
	int count = 0;
	for (int i = 0; i < PersonList.size(); ++i)
	{
		if (checkName == PersonList.at(i)->personName)
		{
			count++;
		}
	}
	return count;
}

/*FindPersonByName
* Returns a pointer of person with the given name
* Parameter - findName: the name to be searched in the vector
* Return - the Person object's pointer with the passed name
*/
Person* Person::FindPersonByName(string findName)

{
	for (int i = 0; i < PersonList.size(); ++i) 
	{
		if (PersonList.at(i)->getName()._Equal(findName)) 
		{
			return PersonList.at(i);
		}
	}
	return nullptr;
}

/*FindPersonByID
* Returns a pointer of person with the given ID
* Parameter - findID: the ID to be searched in the vector
* Return - the Person object's pointer with the passed ID
*/
Person* Person::FindPersonByID(string findID)
{
	for (int i = 0; i < PersonList.size(); ++i) 
	{
		if (PersonList.at(i)->getID()._Equal(findID)) 
		{
			return PersonList.at(i);
		}
		
	}
	return nullptr;
}

/*ClearPersonList:
* Deletes all the items in the vector: PersonList. To be called when exiting the program
* No parameter, no return.
*/
void Person::ClearPersonList()
{
	for (int i = 0; i < PersonList.size(); ++i)
	{
		delete PersonList.at(i);
	}
	PersonList.clear();
	PersonList.shrink_to_fit();
}

/*SavePersons:
* Saves data from PersonList vector to PersonData file
* No parameter, no return
*/
void Person::SavePersons() 
{
	fstream PersonFile;
	int result = remove("PersonData.txt");

	PersonFile.open("PersonData.txt", ios::app);

	if (PersonFile.is_open())
	{
		for (int i = 0; i < PersonList.size(); ++i)
		{
			PersonFile << PersonList.at(i)->getID() << endl;
			PersonFile << PersonList.at(i)->getName() << endl;

		}
		PersonFile.close();
		return;
	}
	else
	{
		cout << "File could not be opened" << endl;
		return;
	}
}

/*ExtractPersons
* Extracts data from PersonData file and saves them in PersonList. Called only in the begnning of the program.
* No parameter, returns the initial index to begin saving from when save() is called (to avoid overriding or repeat)
*/
void Person::ExtractPersons()
{
	fstream PersonFile;
	PersonFile.open("PersonData.txt", ios::in);

	if (PersonFile.is_open())
	{
		string name;
		string ID;

		while (getline(PersonFile, ID))
		{
			getline(PersonFile, name);

			Person* createdPerson = new Person(name, ID);
			PersonList.push_back(createdPerson);
		}
		PersonFile.close();
		return;

	}
}