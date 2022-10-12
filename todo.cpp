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
	    within the text. 
	    This happens upon application start.
	- Vector items are written to the same .txt
	    file with the same formatting upon
	    application close.

============================================================
 */

	// TODO: Display todo list with menu at bottom:
	// 	"1) Add item" DONE
	// 	"2) Delete item" DONE
	// 	"3) Enter list item # to toggle status (done vs not)"
	// 	"4) Sort list by complete vs not"
	// 	"5) Exit" DONE
	//
	// 	Functions:
	// 	- Menu handler IN PROGRESS
	// 	- Sort list
	// 	- toggle item completeness (add or delete "[DONE]" from beginning of item)
	// 	- Add list item DONE
	// 	- Delete list item DONE
	// 	- Display/refresh list on screen DONE
	//
	// 	Without functions:
	// 	- Load from .txt file DONE
	// 	- Save to .txt file DONE


#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <fstream>
#include <iterator>


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

// Exit function. Takes in vector reference, returns void.
void Exit(vector<string>& todoList);

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
		// Main menu presented to user
		cout << "\n";
		cout << "[1] Add Item\n";
		cout << "[2] Delete Item\n";
		cout << "[3] Enter List Item to Toggle Status\n";
		cout << "[4] Sort List by Completeness\n";
		cout << "[5] Exit\n";
		cout << "\n" << "Enter Choice: ";
		cin >> choice;
	
		// Switch for menu selection
		switch(choice){
			case 1:
				cout << "Add Item\n";
				AddItem(todoList);
				break;
			case 2:
				cout << "Delete Item\n";
				DeleteItem(todoList);
				break;
			case 3:
				cout << "Toggle Status\n";
				break;
			case 4:
				cout << "Sort by Completeness\n";
				SortList(todoList);
				break;
			case 5:
				cout << "Exit\n";
				break;
			default: 
				cout << "Invalid Input\n";
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
	
	for(int i = 0; i < todoList.size(); i++){
		cout << i+1 << ") " << todoList[i] << "\n";
	}
	cout << "\n";
}

// Add item
void AddItem(vector<string>& todoList){
	
	char again = 'n';

	// Take in new list item from user. Add to end of vector.
	do{
		string newItem;
		cout << "Enter new todo item: ";
		cin >> newItem;
		todoList.push_back(newItem);
		cout << "\nItem added!";
		cout << "\nAdd another item? (y/n): ";
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
		cout << "Enter item number to delete: ";
		cin >> item;
		todoList.erase(todoList.begin() + (item - 1));
		DisplayList(todoList);
		cout << "Delete another item? (y/n): ";
		cin >> again;

	} while(again == 'Y' || again == 'y');
}

// Sort list
void SortList(vector<string>& todoList){
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

// Get path for save file
std::filesystem::path getPath(string& saveFile){

	// Get path to saveFile directory (assuming it is in the exe directory).
	std::filesystem::path savePath{std::filesystem::canonical("/proc/self/exe")};
	savePath.remove_filename();
	savePath += saveFile;

	return savePath;

}




