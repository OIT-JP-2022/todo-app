#include <iostream>
#include <fstream>
#include <utility>
#include <vector> 
#include <string> 
#include <list>
#include <bits/stdc++.h>
using listitem = std::pair<std::string,bool>;
using listitems = std::vector<listitem>;
int ValidateCall(int InputCount, char** argv);
bool OptionsMenu(listitems& items);
void Print(listitems& items);
bool SortList(listitems& items);
bool RemoveItem(listitems& items);
bool LastCharBool(std::string str);
listitems FileListToVector(std::fstream& file);
void SaveToFileListFromVector(listitems items, std::fstream& file);

int main(int argc,char*argv[]) 
{
    if (ValidateCall(argc,argv))
	  return 1;
  
    std::fstream ListFile(argv[1]);
    
    if (!ListFile){
        std::cout << "File could not be opened";
        return 1;
    }

    listitems items(FileListToVector(ListFile));


    while (OptionsMenu(items));
    
    SaveToFileListFromVector(items, ListFile);

    return 0;
}


listitems FileListToVector(std::fstream& file){
    listitems items;
    std::string line;
    while (std::getline(file, line)){
        bool check = LastCharBool(line);
        line.pop_back();
        listitem newitem(line,check);
        items.push_back(newitem); 
    }
    return items;

}

void SaveToFileListFromVector(listitems items, std::fstream& file){
    file.clear();
    file.seekg(0);
    for (auto& item: items)
        file << item.first << item.second << "\n";
}


int ValidateCall(int InputCount, char** argv)
{
  if (InputCount != 2)
  {
   std::cout << "The ToDO APP takes a file input and allows you to make changes to a 'ToDo list'\n"
             << "Proper calling method is: \n" << argv[0] << " <todolistfilename>\n";

   return 1;
  }
  return 0;
}


bool LastCharBool(std::string str){
    switch(str.back()){
        case 'T':
            return true;
    default:
            return false;
    }
}

bool RemoveItem(std::fstream& file)
{
	/*
	Print(file);
	std::cout << "Enter which Todo list item you would like to delete or enter '-q' to quit addin: \n =>";
	std::string item;
	std::getline(std::cin,item);
	if (item == "-q")
		return false;

	std::string line;
	file.clear();
	file.seekg(0,std::ios::beg);
	int pos = 0;
	while(std::getline(file, line))
	{
         
	line.pop_back(); //Remove the T or F flag.
	std::cout << line;
	if (line == item)
        {
	   
	   while(std::getline(file, line))	   
	   {

           
	   file.clear();
	   file.seekg(pos); //Brings us back to beginning
           file << line << "\n";
           pos = file.tellg();
	   std::getline(file, line);
	   
	   }
	
	file.seekg(pos - 1);   
        file
	}
	pos = file.tellg();
	}
	*/

		return true;
}
//void deleteItem(const string& filename)
//{
//  auto tasks = readToVector(filename);
//  printVector(tasks,"----Edit ToDo List----");
//  int item = 0;
//  cout << "Which task would you like to delete: ";
//  cin >> item;

//  tasks.erase(tasks.begin()+(--item));
//  writeFromVector(filename, tasks);
//}


bool AddNewItem(listitems& items)
{
  Print(items);
  std::cout << "Enter your ToDo list item to add or '-q' to quit adding: \n =>";
  std::string option;
  std::getline(std::cin, option);
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


bool UpdateItem(listitems& items){
    Print(items);
    std::cout << "What Item would you like to update or '-q' to quit editing: \n =>";
    std::string option;
    std::getline(std::cin,option); 
    if (option == "-q")
	  return false;
    
    for (auto& item: items)
        if (item.first == option)
            item.second = !item.second;

    return true;
}


bool OptionsMenu(listitems& items)
{
 
std::vector<std::string> MenuOptions
{	
  "1. Add new ToDo item",
  "2. Mark ToDo items Complete/Incomplete",
  "3. Remove ToDo item",
  "4. Sort ToDo items",
  "5. Save and Quit"

};
 for(auto &item:MenuOptions)
   std::cout << item << "\n";
 std::cout << " =>";
 int option;
 std::cin>>option;
 std::cin.ignore();
 switch(option){
	case 1:
	 while (AddNewItem(items));
	 return true;
	case 2: 
	 //Mark Todo Items
         while (UpdateItem(items));
         return true;
	case 3: 
	 //Remove Todo Items
//	 while(RemoveItem(items));
	 //method call
	 return true;
	case 4: 
	 //while(SortList(items));
	 return true;
	case 5: 
	 //Save and Quit
	 return false;
default:
std::cout << "You did not select a valid option!";
return true;
 }
}
/*
bool SortList(std::fstream& file){
	//std::sort(
        //file.seekg(0, std::ios::beg);
	//ListFile.begin(), ListFile.end();
        //};
	std::cout << "List has been Sorted! \n";
	Print(file);
	return false;
}*/

void Print(listitems& items){
    std::cout << " ===== List of all todo items ===== \n";
    for (auto& item: items) {
        std::string check = (item.second) ? "✓" : "X";
        std::cout << "[" << check << "]\t" << item.first << "\n";
    }
}

