#pragma once
#include <iostream>
#include <vector>
#include <map>
using namespace std;


class Item 
{
public:
	//Accessors
	string getName(); 
	string getDescription();
	string getID();

	//Mutators
	void setName(string newName);
	void setDescription(string newDescrip);
	void setID(string newID);

	//Functions on individual items
	static void CreateItem(string nameInput);
	static string DeleteItem(string deleteName);
	static void DisplayItems();
	static int CheckInArray(string checkName);
	static void EditItem(string editItemName);

	//Functions for vector: ItemList
	static Item* FindItemByName(string findName);
	static Item* FindItemByID(string findID);
	static void ClearItemList();

	//Saving and retrieving data
	static void SaveItems();
	static void ExtractItems();

private:
	Item(string nameIn, string descripIn); //constructor for brand new item
	Item(string nameIn, string descripIn, string IDIn); // constructor for extracting previously saved items

	string itemName = "No Name";
	string itemDescription = "No Description";
	string itemID = "No ID";
	
};