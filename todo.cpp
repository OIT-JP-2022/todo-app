#include <iostream>
#include <fstream>
#include <utility>
#include <vector> 
#include <string> 

using listitem = std::pair<std::string,bool>;
using listitems = std::vector<listitem>;


bool lastCharBool(std::string str){
    return str.back() == '0';
}


listitems fileListToVector(char* fname){
    std::ifstream inFile{fname};
    if (!inFile.is_open())                                                              // inFile.fail() checks if a flag was set for file fname not existing 
        std::cout << "\nFile \'" << fname << "\' will be created as a todolist\n";    // If file was not originally found, one will be made during saving. Inform the user
    listitems items;
    std::string line;
    while (std::getline(inFile, line)){
        bool check = lastCharBool(line);
        line.pop_back();
        listitem newitem(line,check);
        items.push_back(newitem); 
    }
    return items;
}


void saveToFileListFromVector(const listitems& items, char* fname){
    std::remove(fname);
    std::ofstream outFile {fname};
    for (auto& item: items)
        outFile << item.first << item.second << "\n";
}


void print(const listitems& items){
    std::cout << "\n ===== List of all todo items ===== \n";
    if (items.empty()){
        std::cout << "\t** EMPTY **\n";
        return;
    }
    for (auto& item: items) {
        std::string check = (item.second) ? "✓" : "X";
        std::cout << "[" << check << "]\t" << item.first << "\n";
    }
}

std::string getUserInput(){
    std::cout << " =>";
    std::string option;
    std::getline(std::cin, option);
    return option;
}


bool addNewItem(listitems& items){
    print(items);
    std::cout << "Enter your ToDo list item to add or '-q' to quit adding:\n";
    std::string option = getUserInput();
    if (option == "-q")
        return false;

    for (auto& item: items)
        if (item.first == option){
            std::cout << "Item already in list";
            return true;
        }

    listitem newitem(option, false);
    items.push_back(newitem);

    std::cout << "Added a new incomplete item: \n" << option << "\n";
    return true;
}


bool updateItem(listitems& items){
    print(items);
    std::cout << "What Item would you like to update or '-q' to quit editing:\n";
    std::string option = getUserInput();
    if (option == "-q")
	  return false;

    for (auto& item: items)
        if (item.first == option)
            item.second = !item.second; // For any occurences of the item, set it to the opposite of previous

    return true;
}


bool removeItem(listitems& items){
    print(items);
    std::cout << "Enter your ToDo list item to add or '-q' to quit adding:\n";
    std::string option = getUserInput();
    if (option == "-q")
        return false;

    for (auto& item: items)
        if (item.first == option)
            items.erase(std::remove(items.begin(), items.end(), item), items.end());
    
    return true;
}


bool optionsMenu(listitems& items){
    std::cout << "\n";
    std::vector<std::string> MenuOptions
    {
        "1. Add new ToDo item",
        "2. Mark ToDo items Complete/Incomplete",
        "3. Remove ToDo item",
        "4. Sort ToDo items",
        "5. Save and Quit"
    };
    for(auto &item: MenuOptions)
        std::cout << item << "\n";

    std::string option = getUserInput();
    switch(option[0]){                      // TODO: Change methods of reading input here. Probably need a validate input function (function pointer vector?)
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

    listitems items(fileListToVector(fname));
    while (optionsMenu(items));
    saveToFileListFromVector(items, fname);

    return 0;
}
