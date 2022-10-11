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
	// 	"1) Add item"
	// 	"2) Delete item"
	// 	"3) Enter list item # to toggle status (done vs not)"
	// 	"4) Sort list by complete vs not"
	// 	"5) Exit"
	//
	// 	Functions:
	// 	- Menu handler
	// 	- Sort list
	// 	- toggle item completeness (add or delete "[DONE]" from beginning of item)
	// 	- Add list item
	// 	- Delete list item
	// 	- Display/refresh list on screen
	//
	// 	Without functions:
	// 	- Load from .txt file
	// 	- Save to .txt file


#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <fstream>
#include <iterator>

using std::string;
using std::cout;

// Main menu function
std::vector<string> MainMenu(std::vector<string> vect);  

// Add item function
std::vector<string> AddItem(std::vector<string> vect);

// Delete item function
std::vector<string> DeleteItem(std::vector<string> vect);

// Toggle item done or not function
std::vector<string> ToggleItemStatus(std::vector<string> vect);

// Sort item list by completeness function
std::vector<string> SortList(std::vector<string> vect);

// Exit function
std::vector<string> Exit(std::vector<string> vect);

int main(int argc, char** argv) {
	// Get save file name from command line argument.
	if(argv != NULL){
		string saveFile{argv[1]};
		
		// Get path to saveFile directory (assuming it is in the exe directory).
		std::filesystem::path savePath{std::filesystem::canonical("/proc/self/exe")};
		savePath.remove_filename();
		savePath += saveFile;

		// If a save file exists, open it.
		if(std::filesystem::exists(savePath)){
			std::ifstream inFile; 
			inFile.open(savePath);
			
			// Create vector, write to vector from file.
			std::vector<string> vect;
			std::string str;
			while(std::getline(inFile, str)){
				if(str.size() > 0)
					vect.push_back(str);
			}		
		        inFile.close();
			 
			// Call main menu
			vect = MainMenu(vect);

			// Save back to file
			std::ofstream outFile;
			outFile.open(savePath);
			for(int i=0; i<vect.size(); ++i){
				outFile << vect[i] << std::endl;
			}
			outFile.close();
		}
	}
	return 0;
}

// Main Menu	
std::vector<string> MainMenu(std::vector<string> vect){
	int choice;
	
	// Main menu presented to user
	std::cout << std::endl;
	std::cout << "[1] Add Item" << std::endl;
	std::cout << "[2] Delete Item" << std::endl;
	std::cout << "[3] Enter List Item to Toggle Status" << std::endl;
	std::cout << "[4] Sort List by Completeness" << std::endl;
	std::cout << "[5] Exit" << std::endl;
	std::cout << '\n' << "Enter Choice: ";
	std::cin >> choice;
	
	// Switch for menu selection
	switch(choice){
		case 1:
			std::cout << "Add Item" << std::endl;
			break;
		case 2:
			std::cout << "Delete Item" << std::endl;
			break;
		case 3:
			std::cout << "Toggle Status" << std::endl;
			break;
		case 4:
			std::cout << "Sort by Completeness" << std::endl;
			break;
		case 5:
			std::cout << "Exit" << std::endl;
			break;
		default: 
			std::cout << "Invalid Input" << std::endl;
	}
	// Return the vector 
	return vect;		
}



