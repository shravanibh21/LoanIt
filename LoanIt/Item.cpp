#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "Item.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

static vector<Item*> ItemList; //to store all items created through CreateItem function.

/*Item class constructor
* Parameters: nameIn - Item name, descripIn - Item description.
*/
Item::Item(string nameIn, string descripIn)
{
	itemName = nameIn;
	itemDescription = descripIn;
	
	//Assigning a unique ID
	time_t currentTime = time(NULL);
	string timestr = ctime(&currentTime);
	itemID = timestr.substr(0, timestr.size()-1); //to get rid of the extra new line that tiemstr gest from ctime
}

/*Item class constructor
* Parameter - nameIn - itemName, descripIn - itemDescription, IDin - itemID
*/
Item::Item(string nameIn, string descripIn, string IDIn)
{
	itemName = nameIn;
	itemDescription = descripIn;
	itemID = IDIn;
}

//itemName mutator
void Item::setName(string newName)
{
	itemName = newName;
}

//itemDescription mutator
void Item::setDescription(string newDescrip) 
{
	itemDescription = newDescrip;
}

//itemID mutator
void Item::setID(string newID) 
{
	itemID = newID;
}

//itemName accessor
string Item::getName() 
{
	return itemName;
}

//itemDescription accessor
string Item::getDescription() 
{
	return itemDescription;
}

//itemID accessor
string Item::getID() 
{
	return itemID;
}

/*CreateItem
* Creates item class objects and adds them to Item List.
* Parameter - name of the item being created, no return.
*/
void Item::CreateItem(string nameInput)
{
	//Take input on description of item
	string descripInput;
	cout << "Please enter a brief 2-3 words description for this item." << endl;
	getline(cin, descripInput);

	//Check for invalid input and ask again if needed
	while (descripInput.empty() || descripInput._Equal(" "))
	{
		cout << "Name cannot be blank. Please enter a valid name." << endl;
		getline(cin, descripInput);
	}

	Item* createdItem = new Item(nameInput, descripInput); //create item

	ItemList.push_back(createdItem);
	cout << createdItem->getName() << " item was created!" << endl;


}

/*Delete Item
* Delets the item with the name passed in argument
* Parameter - name of the item to be delted
* Return - the ID of the item deleted - to be used to delete any associated loans
*/
string Item::DeleteItem(string deleteName) 
{
	string deletedID;
	int itemNameOccurances = Item::CheckInArray(deleteName);

	//Check if the given names exists, or is repeared. Proceed accordingly
	if (itemNameOccurances == 0)
	{
		//Case: No item with the given name exists
		cout << "No item with such name exists. Nothing to delete." << endl;
		return "No ID returned";
	}
	else if (itemNameOccurances == 1)
	{
		//Case: Only one item with given name exists
		for (int i = 0; i < ItemList.size(); ++i) {

			if (ItemList.at(i)->getName()._Equal(deleteName)) {
				deletedID = ItemList.at(i)->getID();

				delete ItemList.at(i); //free dynamically allocated memory
				ItemList.erase(ItemList.begin() + i); //remove from vector
				cout << "Item deleted successfully." << endl;
				return deletedID;
			}
		}
	}
	else if (itemNameOccurances > 1)
	{
		//Case: More than one item with the given name exists
		cout << "More than one item in the list has the name " + deleteName << endl;
		cout << "Please refer to the list below. Copy and paste the ID of the item to be delted" << endl;

		Item::DisplayItems();

		cout << "Paste the item ID below: " << endl;
		getline(cin, deleteName); //reusing the deleteName string for ID input

		//Find item with pasted ID
		for (int i = 0; i < ItemList.size(); ++i)
		{	
			if (ItemList.at(i)->getID()._Equal(deleteName))
			{
				deletedID = ItemList.at(i)->getID();

				delete ItemList.at(i); //free dynamically allocated memory
				ItemList.erase(ItemList.begin() + i); //remove from vector
				cout << "Item deleted successfully." << endl;
				return deletedID;
			}
		}
		//If exited for loop, ID couldn't be found. Let user know.
		cout << "No such ID was found. Nothing was deletd." << endl;
		return "No ID returned";
	}

}

/*EditItem
* Edits the description of the item with the passed name
* Parameter - name of the item to be edited, no return
*/
void Item::EditItem(string editItemName)
{
	Item* ItemToEdit = nullptr;
	int numberOfOccurances = Item::CheckInArray(editItemName);

	if (numberOfOccurances == 0)
	{
		cout << "No such item name found. No item to edit." << endl;
		return;
	}
	else if (numberOfOccurances == 1)
	{
		ItemToEdit = Item::FindItemByName(editItemName);
	}
	else if (numberOfOccurances > 1)
	{
		cout << "More than one item has this name." << endl;
		cout << "Please refer to the list below and paste the item ID of the item to be edited" << endl;
		Item::DisplayItems();
		cout << "Pasete item ID below" << endl;
		getline(cin, editItemName);
		ItemToEdit = Item::FindItemByID(editItemName);

		if (ItemToEdit == nullptr)
		{
			cout << "No such ID found. Nothing was edited." << endl;
			return;
		}
	}

	string newDescription;

	cout << "Enter the new description for this item:" << endl;
	getline(cin, newDescription);

	//Check for invalid input and ask again if needed
	while (newDescription.empty() || newDescription._Equal(" "))
	{
		cout << "Name cannot be blank. Please enter a valid name." << endl;
		getline(cin, newDescription);
	}

	ItemToEdit->setDescription(newDescription);
	cout << "Item edited successfully!" << endl;
	return;
}

/*Display Items
* Displays all the item objects in the vector: ItemList
* No parameter, no return
*/
void Item::DisplayItems()
{
	//check if the item list is empty and exit function if true.
	if (ItemList.size() == 0)
	{
		cout << "No previously created items found." << endl;
		return;
	}

	cout << "Here are the previously created items:" << endl;
	cout << "______________________________________________" << endl;

	//Traverse through item list and print info of each
	for (int i = 0; i < ItemList.size(); ++i)
	{
		cout << "Item " << i+1 << ": " << endl;
		cout << "Name - " << ItemList.at(i)->getName() << endl;
		cout << "Description - " << ItemList.at(i)->getDescription() << endl;
		cout << "Item ID - " << ItemList.at(i)->getID() << endl << endl;
	}
	
	cout << "______________________________________________" << endl;
}

/*CheckInArray:
* Returns the number of objects with a given name in the ItemList
* Parameter checkName - the name to check for number of occurances in ItemList
* Return - returns number of occurances of checkName in ItemList
*/
int Item::CheckInArray(string checkName) 
{
	int count = 0;
	for (int i = 0; i < ItemList.size(); ++i) 
	{
		if (checkName == ItemList.at(i)->itemName)
		{
			count++;
		}
	}
	return count;
}

/*FindItemByName
* Returns a pointer of item with the given name
* Parameter - findName: the name to be searched in the vector
* Return - the Item object's pointer with the passed name
*/
Item* Item::FindItemByName(string findName) 
{
	for (int i = 0; i < ItemList.size(); ++i) 
	{
		if (ItemList.at(i)->getName()._Equal(findName)) {
			return ItemList.at(i);
		}
	}
	return nullptr; //if exited for loop, couldn't find item, return null
}

/*FindItemByID
* Returns a pointer of item with the given ID
* Parameter - findID: the ID to be searched in the vector
* Return - the Item object's pointer with the passed ID
*/
Item* Item::FindItemByID(string findID)
{
	for (int i = 0; i < ItemList.size(); ++i) 
	{
		if (ItemList.at(i)->getID()._Equal(findID)) {
			return ItemList.at(i);
		}
	}
	return nullptr; //if exited for loop, couldn't find an item, return null
}

/*ClearItemList:
* Deletes all the items in the vector: ItemList. To be called when exiting the program
* No parameter, no return.
*/
void Item::ClearItemList()
{
	for (int i = 0; i < ItemList.size(); ++i) 
	{
		delete ItemList.at(i); //call descturctor on each
	}
	ItemList.clear(); //empty vector
	ItemList.shrink_to_fit(); //free any memory reseved by vector
}

/*SaveItems:
* Saves date from vector ItemList to ItemData file.
* No parameter, no return
*/
void Item::SaveItems() {
	fstream ItemFile;
	int result = remove("ItemData.txt");

	ItemFile.open("ItemData.txt", ios::app); //open in append mode

	if (ItemFile.is_open())
	{
		for (int i = 0; i < ItemList.size(); ++i) 
		{
			ItemFile << ItemList.at(i)->getID() << endl; 
			ItemFile << ItemList.at(i)->getName() << endl;
			ItemFile << ItemList.at(i)->getDescription() << endl;
			
		}
		ItemFile.close();
		return;
	}
	else 
	{
		cout << "File could not be opened" << endl;
		return;
	}
}

/*ExtractItems
* Extracts data from ItemData file and saves them in ItemList. Called only in the begnning of the program.
* No parameter, no return
*/
void Item::ExtractItems()
{
	fstream ItemFile;
	ItemFile.open("ItemData.txt", ios::in); //open read mode

	if (ItemFile.is_open())
	{
		string name;
		string description;
		string ID;

		while (getline(ItemFile, ID))
		{ 
			getline(ItemFile, name);
			getline(ItemFile, description);  
			
			Item* createdItem = new Item(name, description, ID); 
			ItemList.push_back(createdItem); //populate vector
		} 
		ItemFile.close();
		return;
	}
}
