#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <array>

using ListItem = std::pair<std::string,bool>; 

void printItems(std::vector<ListItem> todos, std::string bar) {
  int i {1};

  std::cout << bar << "\n\n";

  for (const auto [text, isComplete] : todos) {
    auto prefix{isComplete ? "\t[+] " : "\t[-] "};
    std::cout << prefix << i++ << ". " << text << "\n";
  }

  std::cout << "\n" << bar << "\n\n";
}

int prompt(std::string msg, int max) {
  int n;

  while ( (n > max || n < 1) && n != -1) {
    std::cout << msg << " ";
    std::cin >> n;
    std::cout << "\n";
  }

  return n;
}

int printMenu(std::array<std::string, 5> menuItems) {
  for (const std::string & item : menuItems) {
    std::cout << "\t" << item << "\n";
  }

  std::cout << "\n";

  return prompt("Enter Choice: ", 5);
}

void loadTodos(std::vector<ListItem> todos, std::string filename) {
  std::ifstream file {filename};
  
  std::string msg;

  while (getline(file, msg)) {
    std::cout << msg << std::endl;
    todos.push_back({msg.substr(2), (msg[0] == '1')});
  }
}

void saveTodos(std::vector<ListItem> todos, std::string filename) {
  std::ofstream file {filename};
  
  for (const auto & [text, isComplete] : todos) {
    file << (isComplete ? "1 " : "0 ") << text << "\n";
  }

  std::cout << "\nFile Successfully Saved.\n";

}

int getItemNumber(std::vector<ListItem> todos) { return prompt("Enter Item Number: ", todos.size()); }

void handleOption(int n, std::vector<ListItem> & todos, std::string filename) {
  std::string message;

  switch(n) {
    case 1: {
        std::cout << "\nEnter Message: ";
        std::cin >> message;
        std::cout << "\n";
        todos.insert(todos.begin(),{message,false});
      break;
    }

    case 2: {
        const auto i {getItemNumber(todos)};
        todos.push_back({todos.at(i-1).first,true});
        todos.erase(todos.begin() + i-1);
        break;
    }
	  
    case 3: {
        const auto i {getItemNumber(todos)};
        todos.insert(todos.begin(), {todos.at(i-1).first, false});
        todos.erase(todos.begin() + i);
        break;
    }
	  
    case 4: {
        const auto i {getItemNumber(todos)};
        todos.erase(todos.begin() + i-1);
        break;
    }
	  
    case 5: {
        saveTodos(todos, filename);
        break;
    }
  }
}

int main(int argc, char** argv) {
  const std::string bar = "===================================================";

  std::vector<ListItem> todos;
  int menuOption {0};

  std::string filename {argc > 1 ? argv[1] : "default.txt"};

  std::array<std::string, 5> menuOptions = {
    "1. Add",
    "2. Mark Complete",
    "3. Mark Incomplete",
    "4. Delete",
    "5. Save"
  };

  loadTodos(todos, filename); 

  while (menuOption != -1) {
    printItems(todos, bar);
    
    menuOption = printMenu(menuOptions);

    handleOption(menuOption, todos, filename);
  }

}

