#include <iostream>
#include <fstream>
#include <utility>
#include <vector> 
#include <string>
#include <algorithm>

using todoItem = std::pair<std::string,bool>;
using childVector = std::vector<todoItem>;
using todoPair = std::pair<childVector, todoItem>; // if child is null, then no children
using todoVector = std::vector<todoPair>;




bool lastCharBool(std::string str){
	return str.back() == '1';
}

std::string getTodoPairTask(const todoPair& pair){
	return pair.second.first;
}

void updateParents(todoVector& items){
	for (auto& item: items){
		bool childrenComplete = true;
		for (auto& childitem: item.first){
			if(!childitem.second){
				childrenComplete = false;
				item.second.second = false;
			}			
		}
		if(item.first.size() != 0)
			item.second.second = childrenComplete;
	}
}

todoVector fileListToVector(char* fname){
    std::ifstream inFile{fname};
    if (!inFile.is_open())                                                              // inFile.fail() checks if a flag was set for file fname not existing 
        std::cout << "\nFile \'" << fname << "\' will be created as a todoVector\n";    // If file was not originally found, one will be made during saving. Inform the user
    todoVector items;
    std::string line;
    while (std::getline(inFile, line)){
		bool check = lastCharBool(line);
        line.pop_back();
		if(line[0] == '\t'){
			line.erase(0,1);
			todoItem newitem(line,check);
			items.back().first.push_back(newitem);
		}
		else{        
			todoPair newitem(childVector{}, todoItem{line, check});
			items.push_back(newitem);
		}			
    }
	updateParents(items);
    return items;
}

void saveToFileListFromVector(const todoVector& items, char* fname){
    std::remove(fname);
    std::ofstream outFile {fname};
    for (auto& todoPair: items){
        todoItem parentInfo = todoPair.second;		
		outFile << parentInfo.first << parentInfo.second << "\n";
		for (auto& childitem: todoPair.first){		
			outFile << '\t' << childitem.first << childitem.second << "\n";
		}
	}
}

void printPairChildren(const todoPair& pairs){
	todoItem parentinfo = pairs.second;
	std::string check = (parentinfo.second) ? "✓" : "X";
    std::cout << "[" << check << "]\t" << parentinfo.first << "\n";
	for (auto& childitem: pairs.first){		
		std::string check = (childitem.second) ? "✓" : "X";
		std::cout << "\t[" << check << "]\t" << childitem.first << "\n";
	}
}

void print(const todoVector& items){
    std::cout << "\n ===== List of all todo items ===== \n";
    if (items.empty()){
        std::cout << "\t** EMPTY **\n";
        return;
    }
	for (auto& pair: items){
        printPairChildren(pair);
	}
	std::cout << "\n**At any time type # followed by text to search for an item\n\n";
}

bool searchPrint(const todoVector& items, std::string s){
	s.erase(0,1);
	std::cout << "\n\n\n\n\n\n\n\n";
		std::cout << "Your search yielded the following results:\n";
	for (const auto& item: items){
		if (getTodoPairTask(item) == s){
			printPairChildren(item);
			return true;
		}
		for (const auto& childitem: item.first){
			if (childitem.first == s){
				printPairChildren(item);
				return true;
			}
		}
	}
	return false;
}

bool isSearching(const todoVector& items, const std::string s){
	if(s[0] == '#'){
		searchPrint(items, s);
		return true;
	}
	return false;
}

std::string getUserInput(){
    std::cout << " =>";
    std::string option;
    std::getline(std::cin, option);
    return option;
}

bool addNewItem(todoVector& items){
    print(items);
	std::cout << "Would you like to add a (p)arent task or (c)hild task?\n";
	std::cout << "... or enter '-q' to quit adding\n";
	std::string type = getUserInput();
	if (isSearching(items, type))
		return true;
	if (type == "-q")
		return false;
	std::cout << "Enter your ToDo list item to add:\n";
	std::string option = getUserInput();  
	if (isSearching(items, option))
		return true;  	
	for (auto& item: items){
		if (getTodoPairTask(item) == option){
			std::cout << "Item already in list as parent";
			return true;
		}		
		for (auto& childitem: item.first){		
			if (childitem.first == option){
				std::cout << "Item already in list as child";
				return true;
			}				
		}
	}
	if(type == "c"){
		std::cout << "Enter the parent you wish to add this child to:\n";
		std::string parent = getUserInput();
		if (isSearching(items, parent))
			return true;
		for (auto& item: items){
			if(getTodoPairTask(item) == parent){
				item.first.push_back(todoItem{option, false});
				std::cout << "Added a new incomplete child item: \n" << option << "\n";
			}
		}
	}
	else{
		todoPair newitem(childVector{}, todoItem{option, false});
		items.push_back(newitem);
		std::cout << "Added a new incomplete parent item: \n" << option << "\n";
	}  
	updateParents(items);
    return true;
}

bool updateItem(todoVector& items){
    print(items);
    std::cout << "What Item would you like to update or '-q' to quit editing:\n";
    std::string option = getUserInput();
    if (isSearching(items, option))
		return true;
	if (option == "-q")
	  return false;

    for (auto& item: items){
        if (getTodoPairTask(item) == option){
            item.second.second = !item.second.second; // For any occurences of the item, set it to the opposite of previous
			for (auto& childitem: item.first){
				childitem.second = item.second.second;
			}
		}
		for(auto& childitem: item.first){
			if (childitem.first == option){
				childitem.second = !childitem.second;
			}
		}
	}
	updateParents(items);
    return true;
}


bool removeItem(todoVector& items){
    print(items);
    std::cout << "Enter your ToDo list item to add or '-q' to quit adding:\n";
    std::string option = getUserInput();
    if (isSearching(items, option))
		return true;
	if (option == "-q")
        return false;

    for (auto& item: items){
        if (getTodoPairTask(item) == option){
            items.erase(std::find(items.begin(), items.end(), item));  //std::remove(items.begin(), items.end(), item), items.end());
			return true;
		}
		for(auto& childitem: item.first){
			if(childitem.first == option){
				item.first.erase(std::remove(item.first.begin(), item.first.end(), childitem), item.first.end());
			}
		}	
	}
	updateParents(items);
    return true;
}

void sortItems(todoVector& items) {
	sort(items.begin(), items.end(),
		[](const auto& x, const auto& y) { return x.second.second < y.second.second; });
	for (auto& parent: items){
		sort(parent.first.begin(), parent.first.end(),
		[](const auto& x, const auto& y) {return x.second < y.second; });
	}
	print(items);
}


bool optionsMenu(todoVector& items){
    std::cout << "\n";
    std::vector<std::string> MenuOptions
    {
        "1. Add new ToDo item",
        "2. Mark ToDo items Complete/Incomplete",
        "3. Remove ToDo item",
        "4. Sort ToDo items",
        "5. Save and Quit",
		"\n**At any time type # followed by text to search for an item"
    };
    for(auto &item: MenuOptions)
        std::cout << item << "\n";

    std::string option = getUserInput();
    switch(option[0]){                      // TODO: Change methods of reading input here. Probably need a validate input function (function pointer vector?)
		case '#':
			searchPrint(items, option);
			return true;
		case '1':
			while (addNewItem(items));
			return true;
		case '2':
			//Mark Todo Items
			while (updateItem(items));
			return true;
		case '3':
			//Remove Todo Items
			while(removeItem(items));
			return true;
		case '4':
			//while(sortItems(items));
			sortItems(items);
			return true;
		case '5':
			//Save and Quit
			return false;
		default:
			std::cout << "You did not select a valid option!";
			return true;
    }

}

int main(int argc,char*argv[]){

    char* fname{argv[1]};

    if (argc != 2)  // Check number of arguments (Program name, ToDo list file name)
    {
        std::cout << "The ToDo app takes a file name input and allows you to make changes to a 'ToDo list'\n"
                  << "Proper calling method is: \n" << argv[0] << " <filename.txt>\n";
        return 1;
    }

    todoVector items(fileListToVector(fname));
    while (optionsMenu(items));
    saveToFileListFromVector(items, fname);

    return 0;
}
