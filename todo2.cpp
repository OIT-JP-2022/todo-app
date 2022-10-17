#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <iostream>
#include <utility>
#include <fstream>
#include <string>
#include <vector>
#include <array>

using ListItem = std::pair<std::pair<std::string, std::string>,bool>; 

void printItems(std::vector<ListItem> todos, std::string bar) {
  	int i {1};
  	std::cout << bar << "\n\n";
  	for (const auto [todo, isComplete] : todos) {
    		auto prefix{isComplete ? "\t[+] " : "\t[-] "};
    		std::cout << prefix << i++ << ". " << todo.first.substr(0, todo.first.length() - 1) << " #" << todo.second << "\n";
  	}
  	std::cout << "\n" << bar << "\n\n";
}

int prompt(std::string msg, int max) {	// this is only used once. If we get rid of this, we can handle it in the switch with the default case
  	int n;
  	while ( (n > max || n < 1) && n != -1) {
    		std::cout << msg << " ";
    		std::cin >> n;
    		std::cout << "\n";
  	}
 	return n;
}

int printMenu(std::array<std::string, 7> menuItems) {
  	for (const std::string & item : menuItems) {
    		std::cout << "\t" << item << "\n";
  	}
  	std::cout << "\n";
  	return prompt("Enter Choice: ", 7);
}

void loadTodos(std::vector<ListItem> todos, std::string filename) {
  	std::ifstream file {filename};
  	std::string msg;
  	while (getline(file, msg)) {
    		std::cout << msg << std::endl;
    		todos.push_back({{msg.substr(2, msg.find("|")), msg.substr(msg.find("|"))}, (msg[0] == '1')});
  	}
}

void saveTodos(std::vector<ListItem> todos, std::string filename) {
  	std::ofstream file {filename};
  	for (const auto & [todo, isComplete] : todos) {
    		file << (isComplete ? "1 " : "0 ") << todo.first << todo.second << "\n";
  	}
  	std::cout << "\nFile Successfully Saved.\n";
}

int getItemNumber(std::vector<ListItem> todos) { return prompt("Enter Item Number: ", todos.size()); }

std::string UpperCaseAndTrim(std::string str) { 
	boost::algorithm::trim(str); 
	boost::algorithm::to_upper(str);
	return str; 
}

void handleOption(int n, std::vector<ListItem> & todos, std::string filename) {
	const std::string bar = "=====================================================================";
	std::string task;
  	std::string hashtag;
  	switch(n) {
    		case 1: {	// Add Todo
        		std::cout << "\nEnter Task: ";
			std::ws(std::cin);
			std::getline(std::cin, task);
			std::cout << "\nEnter Hashtag: #";
			std::ws(std::cin);
			std::getline(std::cin, hashtag);
        		todos.insert(todos.begin(),{{task + "|", hashtag}, false});
      			break;
    		}
    		case 2: {	// Mark Complete
        		const auto i {getItemNumber(todos)};
	        	todos.push_back({todos.at(i - 1).first, true});
    	    		todos.erase(todos.begin() + i - 1);
        		break;
    		}
	    	case 3: {	// Mark Incomplete
    	    		const auto i {getItemNumber(todos)};
        		todos.insert(todos.begin(), {todos.at(i - 1).first, false});
	        	todos.erase(todos.begin() + i);
    	    		break;
    		}
		case 4: {	// Search Hashtag
			std::cout << "\nEnter Hashtag: #";
			std::ws(std::cin);
			std::getline(std::cin, hashtag);
			std::vector<ListItem> results;
			for (int i = 0; i < todos.size(); i++) {
				if (UpperCaseAndTrim(todos[i].first.second) == UpperCaseAndTrim(hashtag)) {
					results.push_back(todos[i]);
				}
			}
			std::cout << "\n\nTasks with hashtag #" << hashtag << ":\n";
			printItems(results, bar);
			break;
		}
    		case 5: {	// Delete Todo
        		const auto i {getItemNumber(todos)};
   		    	todos.erase(todos.begin() + i - 1);
        		break;
    		} 
    		case 6: {	// Save Todos
        		saveTodos(todos, filename);
        		break;
    		}
    		case 7: {	// Exit
        		exit(0);
    		}
		default: {
			std::cout << "\nInvalid Choice.\n";
		}
	}
}

int main(int argc, char** argv) {
  	const std::string bar = "======================================================================";
  	std::vector<ListItem> todos;
  	int menuOption {0};
  	std::string filename {argc > 1 ? argv[1] : "default.txt"};
  	std::array<std::string, 7> menuOptions = {
    		"1. Add todo",
    		"2. Mark Complete",
    		"3. Mark Incomplete",
		"4. Search hashtag",
    		"5. Delete",
    		"6. Save",
    		"7. Quit"
  	};
  	loadTodos(todos, filename);
        printItems(todos, bar);	
  	while (menuOption != -1) {
		printItems(todos, bar);
    		handleOption(printMenu(menuOptions), todos, filename);
  	}
}
