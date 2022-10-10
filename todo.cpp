#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <fstream>
#include <chrono>
#include <thread>

using ListItem = std::pair<std::string,bool>;

void printItems(std::vector<ListItem> todos, std::string bar) {
  int i = 1;

  std::cout << bar << "\n\n";

  for (auto item : todos) {
    item.second == false ? std::cout << "\t[-] " : std::cout << "\t[+] ";
    std::cout << i++ << ". " << item.first << "\n";
  }

  std::cout << "\n" << bar << "\n\n";
}

int inputMessage(std::string msg, int upper) {
  int n = 0;

  while ( (n > upper || n < 1) && n != -1) {
    std::cout << msg << " ";
    std::cin >> n;
    std::cout << "\n";
  }

  return n;
}

int printMenu(std::string bar) {
  std::cout << "\t1. Add\n"

  << "\t2. Mark Complete\n"

  << "\t3. Mark Incomplete\n"

  << "\t4. Delete\n"

  << "\t5. Save\n\n"

  << bar << "\n\n";

  return inputMessage("Enter Choice: ", 5);
}

void loadTodos(std::vector<ListItem> todos, std::string filename) {
  std::fstream file;
  file.open(filename, std::fstream::in);

  std::string msg;

  while (getline(file, msg)) {
    std::cout << msg << std::endl;
    todos.push_back({msg.substr(2, msg.find("\n")), (msg[0] == '1' ? true : false)});
  }

  file.close();
}

void saveTodos(std::vector<ListItem> todos, std::string filename) {
  std::fstream file;
  file.open(filename, std::fstream::out);

  for (auto item : todos) {
    file << (item.second == true ? "1 " : "0 ") << item.first << "\n";
  }

  file.close();

  std::cout << "\nFile Successfully Saved.\n";

}

int getItemNumber(std::vector<ListItem> todos) { return inputMessage("Enter Item Number: ", todos.size()); }

void handleOption(int n, std::vector<ListItem> todos, std::string filename) {
  std::string message;
  int i = 0;

  switch(n) {
    case 1:
      std::cout << "\nEnter Message: ";
      std::cin >> message;
      std::cout << "\n";
      todos.insert(todos.begin(),{message,false});
      break;

    case 2:
      i = getItemNumber(todos);
      todos.push_back({todos.at(i-1).first,true});
      todos.erase(todos.begin() + i-1);
      break;
	  
    case 3:
      i = getItemNumber(todos);
      todos.insert(todos.begin(), {todos.at(i-1).first, false});
      todos.erase(todos.begin() + i);
      break;
	  
    case 4:
      i = getItemNumber(todos);
      todos.erase(todos.begin() + i-1);
      break;
	  
    case 5:
      saveTodos(todos, filename);
      break;
  }
}

int main(int argc, char** argv) {
  const std::string bar = "===================================================";

  std::vector<ListItem> todos;
  std::string filename = ( argc > 1 ? argv[1] : "default.txt" );

  argc > 1 ? loadTodos(todos, filename) : (void)[]{};

  int menuOption = 0;

  while (menuOption != -1) {
    printItems(todos, bar);
    
    menuOption = printMenu(bar);

    handleOption(menuOption, todos, filename);
  }

}
