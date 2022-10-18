#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <iostream>
#include <utility>
#include <fstream>
#include <string>
#include <vector>
#include <array>

using ListItem = std::pair<std::pair<std::pair<std::string, std::vector<std::pair<std::string, bool>>>, std::string>,bool>; 

void printItems(std::vector<ListItem> todos, std::string bar) {
  	int i {1};
  	std::cout << bar << "\n\n";
  	for (const auto [todo, isComplete] : todos) {
    		auto prefix{isComplete ? "\t[+] " : "\t[-] "};
    		std::cout << prefix << i++ << ". " << todo.first.first.substr(0, todo.first.first.length() - 1) << "\t#" << todo.second << "\n";
  		if(todo.first.second.size() != 0){
			int j {1};
			for (const auto [subtask, subcomp] : todo.first.second){
				std::cout << (subcomp ? "\t\t[+] " : "\t\t[-] ") << j++ << ". " << subtask << "\n";
			}
		}
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

int printMenu(std::array<std::string, 9> menuItems) {
  	for (const std::string & item : menuItems) {
    		std::cout << "\t" << item << "\n";
  	}
  	std::cout << "\n";
  	return prompt("Enter Choice: ", 9);
}

std::vector<std::pair<std::string, bool>> loadSubTasks(std::string msg){
	std::vector<std::pair<std::string, bool>> retvect;
	while(msg.length() > 0){
		retvect.push_back({msg.substr(2, msg.find("*") - 1), (msg[0] == '1')});
		msg = msg.substr(msg.find("*") + 1);
	}
	return retvect;
}

void loadTodos(std::vector<ListItem> & todos, std::string filename) {
  	std::ifstream file {filename};
  	std::string msg;
  	while (getline(file, msg)) {
    		std::cout << msg << std::endl;
    		todos.push_back({{{msg.substr(2, msg.find("|") - 1), loadSubTasks(msg.substr(msg.find("$") + 1))}, msg.substr(msg.find("|") + 1, msg.find("$") - 1)}, (msg[0] == '1')});
  	}
}

void saveTodos(std::vector<ListItem> todos, std::string filename) {
  	std::ofstream file {filename};
  	for (const auto & [todo, isComplete] : todos) {
    		file << (isComplete ? "1 " : "0 ") << todo.first.first << todo.second << "$";
		for( const auto & [subtask, subcomplete] : todo.first.second){
			file << (subcomplete ? "1 " : "0 ") << subtask << "*";
		}
		file << "\n";
  	}
	
  	std::cout << "\nFile Successfully Saved.\n";
}

int getItemNumber(int size, std::string userprompt) { return prompt(userprompt, size); }

std::string UpperCaseAndTrim(std::string str) { 
	boost::algorithm::trim(str); 
	boost::algorithm::to_upper(str);
	return str;
}
std::vector<std::pair<std::string, bool>> getSubtasks(){
	std::string task;
	std::vector<std::pair<std::string, bool>> retvect;
	while (true){
		std::cout <<"\nPlease Enter a Subtask (type \"stop\" to stop this prompt): ";
		std::ws(std::cin);
		std::getline(std::cin, task);
		if(UpperCaseAndTrim(task) == "STOP")
			break;	
		retvect.push_back({task, false});

	}
	return retvect;
}

void handleOption(int n, std::vector<ListItem> & todos, std::string filename) {
	const std::string bar = "=====================================================================";
	std::string task;
	std::string subtasks;
  	std::string hashtag;
  	switch(n) {
    		case 1: {	// Add Todo
        		std::cout << "\nEnter Task: ";
			std::ws(std::cin);
			std::getline(std::cin, task);
			std::cout << "\nEnter Hashtag: #";
			std::ws(std::cin);
			std::getline(std::cin, hashtag);
        		todos.insert(todos.begin(),{{{task + "|", getSubtasks()}, hashtag}, false});
      			break;
    		}
    		case 2: {	// Mark Complete
        		const auto i {getItemNumber(todos.size(), "\nPlease Enter Task Number: ")};
	        	todos.push_back({todos.at(i - 1).first, true});
    	    		todos.erase(todos.begin() + i - 1);
        		break;
    		}
		case 3: {	//Mark Subtasks Complete
			const auto i {getItemNumber(todos.size(), "\nPlease Enter Task Number: ")};
			const auto j {getItemNumber(todos.at(i -1).first.first.second.size(), "\nPlease Enter Subtask Number: ")};
			todos.at(i - 1).first.first.second.push_back({todos.at(i - 1).first.first.second.at(j - 1).first, true});
			todos.at(i - 1).first.first.second.erase(todos.at(i - 1).first.first.second.begin() + j - 1);
			break;
			}


	    	case 4: {	// Mark Incomplete
    	    		const auto i {getItemNumber(todos.size(), "\nPlease Enter Task Number: " )};
        		todos.insert(todos.begin(), {todos.at(i - 1).first, false});
	        	todos.erase(todos.begin() + i);
    	    		break;
    		}
		case 5: {	//Mark Subtask Incomplete
			const auto i {getItemNumber(todos.size(), "\nPlease Enter Task Number: ")};
			const auto j {getItemNumber(todos.at(i - 1).first.first.second.size(), "\nPlease Enter Subtask Number: ")};
			todos.at(i - 1).first.first.second.insert(todos.at(i - 1).first.first.second.begin(), {todos.at(i - 1).first.first.second.at(j - 1).first, false});
			todos.at(i - 1).first.first.second.erase(todos.at(i - 1).first.first.second.begin() + j);
			break;
		}

		case 6: {	// Search Hashtag
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
    		case 7: {	// Delete Todo
        		const auto i {getItemNumber(todos.size(), "\nPlease Enter Task Number: ")};
   		    	todos.erase(todos.begin() + i - 1);
        		break;
    		} 
    		case 8: {	// Save Todos
        		saveTodos(todos, filename);
        		break;
    		}
    		case 9: {	// Exit 
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
	loadTodos(todos, filename);       	
  	std::array<std::string, 9> menuOptions = {
    		"1. Add todo",
    		"2. Mark Task Complete",
		"3. Mark Subtask Complete",
    		"4. Mark Incomplete",
		"5. Mark Subtask Incomplete",
		"6. Search hashtag",
    		"7. Delete",
    		"8. Save",
    		"9. Quit"
  	};
  	while (menuOption != -1) {
		printItems(todos, bar);
    		handleOption(printMenu(menuOptions), todos, filename);
  	}
}
