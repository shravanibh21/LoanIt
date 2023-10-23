#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

class Person 
{
public:
	//Accessors
	string getName();
	string getID();

	//Mutator
	void setName(string newName);
	void setID(string newID);

	//Functions for individual persons
	static void CreatePerson(string nameInput);
	static string DeletePerson(string deleteName);
	static void DisplayPersons();
	static int CheckInArray(string nameCheck);

	//Functions for vector: PersonList
	static Person* FindPersonByName(string findName);
	static Person* FindPersonByID(string findID);
	static void ClearPersonList();

	//Saving and retrieving data
	static void SavePersons();
	static void ExtractPersons();

private:
	Person(string nameIn); //constructor that allocates new IDs to brand new persons
	Person(string nameIn, string IDIn); //constructor to extract persons with pre-existing IDs

	string personName = "No Name";
	string personID = "No ID";
};