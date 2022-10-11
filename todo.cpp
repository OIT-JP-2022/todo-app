#include <iostream>
#include <fstream>
#include <utility>
#include <vector> 
#include <string> 

using listitem = std::pair<std::string,bool>;
using listitems = std::vector<listitem>;

void OpenFile(std::ifstream infile,std::string fname);
int ValidateCall(int InputCount, char** argv);
bool OptionsMenu(std::fstream& file);

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
  
  std::fstream InFile(argv[1],std::ios::in | std::ios::out);

  while (OptionsMenu(InFile));
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

bool AddNewItem(std::fstream& file)
{
  std::cout << "Enter your ToDo list item to add or '-q' to quit adding: \n =>";
  std::string item;
  std::getline(std::cin,item); 
  if (item == "-q")
	  return false;

  file.seekg(0,std::ios::end);
  file << "\n" << item  << " F";

  std::cout << "Added a new incomplete item: \n" << item << "\n";
  return true;
}

bool OptionsMenu(std::fstream& file)
{
 
 for(auto &item:MenuOptions)
   std::cout << item << "\n";
 int option;
 std::cin>>option;
 switch(option){
	case 1: 
	 while (AddNewItem(file));
	 return true;
	case 2: 
	 //Mark Todo Items
	 //method call
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
 }
}

void OpenFile(std::ifstream infile,std::string fname)
{
  
  std::cout << "===== Todo App ===== \n";
  
  infile.open(fname);
  
  std::cout << "\n You are opening " << fname << ", your ToDo list is being imported!\n";
}	
