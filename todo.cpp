/*
============================================================
	
		--------------
		Basic Todo App
		--------------

Code: 	Aaron Whitley
	Joseph Ten Eyck

Notes:
	- Todo list items are strings held in a vector.
	- Vector items are read from a .txt file with
	    carriage return seperating the items
	    within the file. 
	    This happens upon application start.
	- Vector items are overwritten to the same .txt
	    file with the same formatting upon
	    application close.

============================================================
 */

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <fstream>
#include <iterator>
#include <ios>
#include <limits>


using std::string;
using std::cout;
using std::cin;
using std::vector;


// Main menu function
void MainMenu(vector<string>& todoList,std::filesystem::path& savePath);

// Display todo list
void DisplayList(vector<string>& todoList);

// Add item function. Takes in vector reference, returns void.
void AddItem(vector<string>& todoList);

// Delete item function. Takes in vector reference, returns void.
void DeleteItem(vector<string>& todoList);

// Toggle item done or not function. Takes in vector reference, returns void.
void ToggleItemStatus(vector<string>& todoList);

// Sort item list by completeness function. Takes in vector reference, returns void.
void SortList(vector<string>& todoList);

// Get path for save file
std::filesystem::path getPath(string& saveFile);


// MAIN =========================================================

int main(int argc, char** argv) {

	// Get save file name from command line argument.
	if(argv != NULL){
		string saveFile{argv[1]};
		
		// Get save file path
		std::filesystem::path savePath = getPath(saveFile);
		

		// If a save file exists with given name, open it.
		if(std::filesystem::exists(savePath)){
			std::ifstream inFile; 
			inFile.open(savePath);
			
			// Create vector, write to vector from file.
			vector<string> todoList;
			string str;
			while(std::getline(inFile, str)){
				if(str.size() > 0)
					todoList.push_back(str);
			}		
		        inFile.close();
			 
			// Call main menu
			MainMenu(todoList, savePath);
		}
		// No save file exists with given name.
		else{

			// Get save file path.
			std::filesystem::path savePath = getPath(saveFile);

			//Creat empty vector, call main menu.
			vector<string> todoList;
			MainMenu(todoList, savePath);
		}
	}
	return 0;
}


// Function definitions ============================================

// Main Menu	
void MainMenu(vector<string>& todoList, std::filesystem::path& savePath){

	int choice{0};
	
	do{
		DisplayList(todoList);

		cout << "\n\t\t=============";
		cout << "\n\t\t  Main Menu";
		cout << "\n\t\t=============";

		// Main menu presented to user
		cout << "\n";
		cout << "[1] Add Item\n";
		cout << "[2] Delete Item\n";
		cout << "[3] Enter List Item to Toggle Status\n";
		cout << "[4] Sort List by Completeness\n";
		cout << "[5] Exit\n";
		cout << "\n" << "~ Enter menu choice #: ";
		cin >> choice;
	
		// Switch for menu selection
		switch(choice){
			case 1:
				//cout << "Add Item\n";
				AddItem(todoList);
				break;
			case 2:
				//cout << "Delete Item\n";
				DeleteItem(todoList);
				break;
			case 3:
				//cout << "Toggle Status\n";
				ToggleItemStatus(todoList);
				break;
			case 4:
				//cout << "Sort by Completeness\n";
				SortList(todoList);
				break;
			case 5:
				cout << "\n\n\t\t ~ Goodbye! ~\n\n";
				break;
			default: 
				cout << "~ Invalid menu choice\n";
		}
	} while(choice != 5);

	// Save back to file
	std::ofstream outFile;
	outFile.open(savePath);
	for(int i=0; i<todoList.size(); ++i){
		outFile << todoList[i] << "\n";
	}
	outFile.close();
}

// Display todo list
void DisplayList(vector<string>& todoList){
	
	if(todoList.size() == 0){
		cout << "\n\t--------------";
		cout << "\n\t  Empty List";
		cout << "\n\t--------------\n\n";
	}
	else{
		cout << "\n\t-------------";
		cout << "\n\t  Todo List";
		cout << "\n\t-------------\n\n";


		for(int i = 0; i < todoList.size(); i++){
			cout << i+1 << ") " << todoList[i] << "\n";
		}	
		cout << "\n";
	}
}

// Add item
void AddItem(vector<string>& todoList){

	char again = 'n';

	DisplayList(todoList);

	// Take in new list item from user. Add to end of vector.
	do{
		string newItem;
		cout << "~ Enter new todo item: ";
		cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		std::getline(cin, newItem);
		todoList.push_back(newItem);
		DisplayList(todoList);
		cout << "\n~ Item added!";
		cout << "\n~ Add another item? (y/n): ";
		cin >> again;

	} while(again == 'Y' || again == 'y');
}

// Delete item
void DeleteItem(vector<string>& todoList){

	int item{0};
	char again = 'n';

	// Display list, get user item choice to delete, delete that item from vector.
	do{
		DisplayList(todoList);
		cout << "~ Enter item number to delete: ";
		cin >> item;
		todoList.erase(todoList.begin() + (item - 1));
		DisplayList(todoList);
		cout << "~ Delete another item? (y/n): ";
		cin >> again;

	} while(again == 'Y' || again == 'y');
}

// Sort list
void SortList(vector<string>& todoList){


	cout << "\n\t~~~~~~~~~~~~~~~";
	cout << "\n\t  Sorted List";
	cout << "\n\t~~~~~~~~~~~~~~~\n\n";

	char ch = '[';
	std::cout << '\n';
	for(int i = 0; i < todoList.size(); i++){
		if(todoList[i].find(ch) != string::npos)
			std::cout << todoList[i] << '\n';
	}
	for(int i = 0; i < todoList.size(); i++){
		if(todoList[i].find(ch) == string::npos)
			std::cout << todoList[i] << '\n';
	}
}

// Toggle item status
void ToggleItemStatus(vector<string>& todoList){
	
	int item;
	char ch = '[';

	DisplayList(todoList);
	cout << "~ Enter item number to toggle completion status: ";
	cin >> item;
        std::cout << todoList[item - 1] << '\n';	
	if(todoList[item - 1].find(ch) != string::npos)
		todoList[item - 1].erase(0,6);
	else
		todoList[item - 1] = "[DONE]" + todoList[item - 1];

	DisplayList(todoList);
}

// Get path for save file
std::filesystem::path getPath(string& saveFile){

	// Get path to saveFile directory (assuming it is in the exe directory).
	std::filesystem::path savePath{std::filesystem::canonical("/proc/self/exe")};
	savePath.remove_filename();
	savePath += saveFile;

	return savePath;

}
