#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <fstream>
#include <cctype>

using ListItem = std::pair<std::string, bool>;
std::vector<ListItem> itemList;
std::string filename;

void printItems() 
{
	int i = 1;

	for (auto item : itemList) 
	{
		item.second == false ? std::cout << "\t[-] " : std::cout << "\t[+] ";
		std::cout << i++ << ". " << item.first << "\n";
	}

	std::cout << "\n" << "//////////////////////////////////////////////" << "\n\n";
}

int inputMessage(std::string userMessage, int max_limit) 
{
	int i = 0;

	std::string input;

	while (( i < 1 || i > max_limit) && i != -1) 
	{
		std::cout << userMessage << " ";
		getline(std::cin, input);
		i = stoi(input);
		std::cout << "\n";
	}

	return  stoi(input);
}

int printMenu() 
{
	int input=0;

	std::cout << "\tHello Todo List!\n";
	std::cout << "Please select from the following items:\n\n";
	std::cout << "\t1. (A)dd Item\n";
	std::cout << "\t2. Mark Item (C)omplete\n";
	std::cout << "\t3. Mark Item (I)ncomplete\n";
	std::cout << "\t4. (D)elete Item\n";
	std::cout << "\t5. (S)ave All\n\n";
	
	std::cout << "\t6. (H)Search Item\n\n";
	std::cout << "//////////////////////////////////////////////" << "\n\n";

	return inputMessage("Enter Selection: ", 6);
}

void loadTodos()
{
	std::fstream file;
	file.open(filename, std::fstream::in);

	std::string message;

	while (getline(file, message)) 
	{
		itemList.push_back(std::make_pair(message.substr(2, message.find("\n")),
			(message[0] == '1' ? true : false)));
	}

	file.close();
	std::cout << "\nOpenned File: " << filename << ".txt";
	std::cin.clear();
	std::cin.get();
	system("clear");
}

void saveTodoList()
{
	std::fstream file;
	file.open(filename, std::fstream::out);

	for (auto item : itemList)
	{
		file << (item.second == true ? "1 " : "0 ") << item.first << "\n";
	}

	file.close();
	std::cout << "\nFile Saved at: " << filename << ".txt";
	
}

int getItemNumber() 
{ 
	return inputMessage("Enter Item Number: ", itemList.size()); 
}

 std::string Getinput()
{
	std::string line{};
	 getline(std::cin, line);
	 return line;
}
     
    void SearchItem()
{
	std::string Search{

		Getinput()
	};
	for(auto item : itemList)
	{
	  auto found = item.first.find(Search);
	  if(found != std::string::npos)
	  {

		  std::cout << found << '\n';
	item.second == false ? std::cout << "\t[-] " : std::cout << "\t[+] ";
		std::cout << item.first << '\n'; 
	}

	  }
			
	
}


void menuOptions(int menuSelection)
{
	std::string userInput;
	int itemNum = NULL;

	switch (menuSelection)
	{
	case 1:
	case 'a':
	case 'A':
		std::cout << "\nEnter Todo Item: ";
		getline(std::cin, userInput);
		std::cout << "\n";
		itemList.insert(itemList.begin(), std::make_pair(userInput, false));
		break;
	case 2:
	case 'c':
	case 'C':
		itemNum = getItemNumber();
		itemList.push_back(std::make_pair(itemList.at(itemNum - 1).first, true));
		itemList.erase(itemList.begin() + itemNum - 1);
		break;
	case 3:
	case 'i':
	case 'I':
		itemNum = getItemNumber();
		itemList.insert(itemList.begin(), std::make_pair(itemList.at(itemNum - 1).first, false));
		itemList.erase(itemList.begin() + itemNum);
		break;
	case 4:
	case 'd':
	case 'D':
		itemNum = getItemNumber();
		itemList.erase(itemList.begin() + itemNum - 1);
		break;
	case 5:
	case 's':
	case 'S':
		saveTodoList();
		break;
	
	case 6:
	case 'h':
	case 'H':
		printItems();
	 	SearchItem();
	       break;

	default:
		std::cout << "MENU ERROR: Please try another selection.\n\n";
		std::cin.clear();
		std::cin.get();
		system("clear");
		break;

	
	}
}

    
       
int main(int argc, char** argv)
{
	std::cin.clear();
	filename = (argc > 1 ? argv[1] : "todolist.txt");
	argc > 1 ? loadTodos() : (void)[] {};
	int menuSelection = 0;

	while (menuSelection != -1)
	{
		printItems();

		menuSelection = printMenu();

		menuOptions(menuSelection);


	}
}
