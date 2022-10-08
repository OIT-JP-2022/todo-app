#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <fstream>
#include <chrono>
#include <thread>

using ListItem = std::pair<std::string,bool>;

std::string filename;

std::vector<ListItem> list;

const std::string bar = "===================================================";

void printItems() {
  int i = 1;

  system("clear");

  std::cout << bar << "\n\n";

  for (auto item : list) {
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

int printMenu() {
  std::cout << "\t1. Add\n"

  << "\t2. Mark Complete\n"

  << "\t3. Mark Incomplete\n"

  << "\t4. Delete\n"

  << "\t5. Save\n\n"

  << bar << "\n\n";

  return inputMessage("Enter Choice: ", 5);
}

void loadTodos() {
  std::fstream file;
  file.open(filename, std::fstream::in);

  std::string msg;

  while (getline(file, msg)) {
    list.push_back(std::make_pair(msg.substr(2, msg.find("\n")), (msg[0] == '1' ? true : false)));
  }

  file.close();
}

void saveTodos() {
  std::fstream file;
  file.open(filename, std::fstream::out);

  for (auto item : list) {
    file << (item.second == true ? "1 " : "0 ") << item.first << "\n";
  }

  file.close();

  std::cout << "\nFile Successfully Saved.\n";

}

int getItemNumber() { return inputMessage("Enter Item Number: ", list.size()); }

void handleOption(int n) {
  std::string message;
  int i = 0;

  switch(n) {
    case 1:
      std::cout << "\nEnter Message: ";
      std::cin >> message;
      std::cout << "\n";
      list.insert(list.begin(),std::make_pair(message,false));
      break;

    case 2:
      i = getItemNumber();
      list.push_back(std::make_pair(list.at(i-1).first,true));
      list.erase(list.begin() + i-1);
      break;
	  
    case 3:
      i = getItemNumber();
      list.insert(list.begin(), std::make_pair(list.at(i-1).first, false));
      list.erase(list.begin() + i);
      break;
	  
    case 4:
      i = getItemNumber();
      list.erase(list.begin() + i-1);
      break;
	  
    case 5:
      saveTodos();
      std::this_thread::sleep_for(std::chrono::milliseconds(3000));
      break;
  }
}

int main(int argc, char** argv) {
  filename = ( argc > 1 ? argv[1] : "default.txt" );

  argc > 1 ? loadTodos() : (void)[]{};

  int menuOption = 0;

  while (menuOption != -1) {
    printItems();

    menuOption = printMenu();

    handleOption(menuOption);
  }