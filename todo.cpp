#include <iostream>
#include <fstream>
#include <utility>
#include <vector> 
#include <string> 

using listitem = std::pair<std::string,bool>;
using listitems = std::vector<listitem>;

int ValidateCall(int InputCount, char** argv);
bool OptionsMenu(std::fstream& file);
void Print(std::fstream& file);


std::vector<std::string> MenuOptions
{	
  "1. Add new ToDo item",
  "2. Mark ToDo items Complete/Incomplete",
  "3. Remove ToDo item",
  "4. Save and Quit"

};
int main(int argc,char*argv[]) 
{
    if (ValidateCall(argc,argv))
	  return 1;
  
    std::fstream ListFile(argv[1]);
    
    if (!ListFile){
        std::cout << "File could not be opened";
        return 1;
    }

    while (OptionsMenu(ListFile));
    return 0;
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


bool AddNewItem(std::fstream& file)
{
  Print(file);
  std::cout << "Enter your ToDo list item to add or '-q' to quit adding: \n =>";
  std::string item;
  std::getline(std::cin,item); 
  if (item == "-q")
	  return false;
  file.clear();
  file.seekg(0,std::ios::end);
  file << item  << "F\n";

  std::cout << "Added a new incomplete item: \n" << item << "\n";
  return true;
}


bool UpdateItem(std::fstream& file){
    Print(file);
    std::cout << "What Item would you like to update or '-q' to quit editing: \n =>";

    std::string item;
    std::getline(std::cin,item); 
    std::cout << item << "\n";
    if (item == "-q")
	  return false;

    std::string line;
    file.clear();
    file.seekg(0, std::ios::beg);
    int pos = 0;
    while(std::getline(file, line)){
        bool complete = LastCharBool(line);
        line.pop_back();
        
        
        if (line == item){
            (complete) ? line.append("F") : line.append("T");
            file.seekg(pos,std::ios::beg);
            file << line;
            
        }

        pos = file.tellg();
        
    }

    return true;
}


bool OptionsMenu(std::fstream& file)
{
 
 for(auto &item:MenuOptions)
   std::cout << item << "\n";
 std::cout << " =>";
 int option;
 std::cin>>option;
 switch(option){
	case 1:
         std::cin.ignore();
	 while (AddNewItem(file));
	 return true;
	case 2: 
	 //Mark Todo Items
	 std::cin.ignore();
         while (UpdateItem(file));
         return true;
	case 3: 
	 //Remove Todo Items
	 //method call
	 return true;
	case 4: 
	 //Save and quit
	 //method call
	 return false;
default:
std::cout << "You did not select a valid option!";
return true;
 }
}




void Print(std::fstream& file){
    std::cout << " ===== List of all todo items ===== \n";
    std::string item;
    file.clear();
    file.seekg(0, std::ios::beg);
    while (std::getline(file, item)){
        bool completed = LastCharBool(item);
        std::string check= (completed) ? "✓" : "X";
        item.pop_back();
        std::cout << "[" << check << "]\t" << item << "\n";
    }
}

