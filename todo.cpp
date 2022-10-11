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

using std::string;
using std::cout;



int main(int argc, char** argv) {

//Get list from file or let user start to make a list.

	// Get save file name from command line argument.
	if(argv != NULL){
		string saveFile{argv[1]};
		
		// Get path to saveFile directory (assuming it is in the exe directory).
		std::filesystem::path exePath{std::filesystem::canonical("/proc/self/exe")};
/*
		// If a save file exists, open it.
		if(std::filesystem::exists(exePath/){
			std::ifstream inFile;
			inFile.open();	
		}
*/		
	}

	cout << "\n" << exePath << "\n";


	return 0;
}




