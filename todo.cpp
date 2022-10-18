#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <iostream>
#include <utility>
#include <fstream>
#include <string>
#include <vector>
#include <array>

using ListItem = std::pair<std::pair<std::pair<std::string, std::vector<std::pair<std::string, bool>>>, std::string>, bool>; 

std::string PrintAndGetLine(std::string str) {
	std::cout << str;
	std::ws(std::cin);
	std::getline(std::cin, str);
	return str;
}

void PrintItems(std::vector<ListItem> todos) {
  	int i { 1 };
	std::string bar = "==========================================================================";
  	std::cout << bar << "\n\n";
  	for (const auto [todo, complete] : todos) {
    		std::cout << (complete ? "\t[+] " : "\t[-] ") << i++ << ". " << todo.first.first.substr(0, todo.first.first.length() - 1) << "\t\t#" << todo.second << "\n";
  		if (todo.first.second.size() > 0) {
			int j { 1 };
			for (const auto [subTask, subComplete] : todo.first.second) {
				std::cout << (subComplete ? "\t\t[+] " : "\t\t[-] ") << j++ << ". " << subTask << "\n";
			}
		}
	}
  	std::cout << "\n" << bar << "\n\n";
}

int Prompt(std::string output, int max) {
	char n { 'x' };
  	while (n > max || n < 0) {
    		std::cout << output;
    		std::cin >> n;
		n -= '0';
    		std::cout << "\n";
  	}
 	return (int)n;
}

int PrintMenu(std::array<std::string, 10> menu) {
  	for (const auto & choice : menu) {
    		std::cout << "\t" << choice << "\n";
  	}
  	return Prompt("\nEnter Choice: ", 10);
}

std::vector<std::pair<std::string, bool>> LoadSubTasks(std::string str){
	std::vector<std::pair<std::string, bool>> subTasks;
	while (str.length() > 0){
		subTasks.push_back({str.substr(2, str.find("*") - 2), (str[0] == '1')});
		str = str.substr(str.find("*") + 1);
	}
	return subTasks;
}

void LoadTodos(std::vector<ListItem> & todos, std::string filename) {
  	std::ifstream file { filename };
  	std::string str;
  	while (getline(file, str)) {
    		todos.push_back({{{str.substr(2, str.find("|") - 1), LoadSubTasks(str.substr(str.find("`") + 1))}, str.substr(str.find("|") + 1, str.find("`") - str.find("|") - 1)}, (str[0] == '1')});
  	}
}

void SaveTodos(std::vector<ListItem> todos, std::string filename) {
  	std::ofstream file { filename };
  	for (const auto & [todo, isComplete] : todos) {
    		file << (isComplete ? "1 " : "0 ") << todo.first.first << todo.second << "`";
		for (const auto & [subtask, subcomplete] : todo.first.second) {
			file << (subcomplete ? "1 " : "0 ") << subtask << "*";
		}
		file << "\n";
  	}
  	std::cout << "\nFile Successfully Saved.\n";
}

int GetItemNumber(int size, std::string output) { return Prompt(output, size); }

std::string UpperCaseAndTrim(std::string str) { 
	boost::algorithm::trim(str);
	boost::algorithm::to_upper(str);
	return str;
}

std::vector<std::pair<std::string, bool>> GetSubTasks() {
	std::string task;
	std::vector<std::pair<std::string, bool>> subTasks;
	while (true) {
		task = PrintAndGetLine("\nPlease Enter a Subtask (type \"stop\" to stop this prompt): ");
		if (UpperCaseAndTrim(task) == "STOP") {
			break;
		}
		boost::algorithm::trim(task);
		subTasks.push_back({task, false});
	}
	return subTasks;
}

void ToggleTask(std::vector<ListItem> & todos, bool complete) {
        const auto i { GetItemNumber(todos.size(), "\nPlease Enter Task Number: ") };	
	for (auto & [subtask, subcomplete] : todos.at(i - 1).first.first.second) {
		subcomplete = complete;
	}
	if (complete) {
		todos.push_back({todos.at(i - 1).first, complete});
    		todos.erase(todos.begin() + i - 1);
	}
	else {
		todos.insert(todos.begin(), {todos.at(i - 1).first, false});
		todos.erase(todos.begin() + i);
	}
}

void ToggleSubTask(std::vector<ListItem> & todos, bool complete) {
	const auto i { GetItemNumber(todos.size(), "\nPlease Enter Task Number: ") };
	const auto j { GetItemNumber(todos.at(i - 1).first.first.second.size(), "\nPlease Enter Subtask Number: ") };
	if (complete) {
		todos.at(i - 1).first.first.second.push_back({todos.at(i - 1).first.first.second.at(j - 1).first, true});
		todos.at(i - 1).first.first.second.erase(todos.at(i - 1).first.first.second.begin() + j - 1);
	}
	else {
		todos.at(i - 1).first.first.second.insert(todos.at(i - 1).first.first.second.begin(), {todos.at(i - 1).first.first.second.at(j - 1).first, complete});
		todos.at(i - 1).first.first.second.erase(todos.at(i - 1).first.first.second.begin() + j);
	}
}

void HandleOption(int n, std::vector<ListItem> & todos, std::string filename) {
	std::string task;
	std::string hashtag;
	std::string subtasks;
  	switch (n) {
    		case 1: {	// Add Todo
        		task = PrintAndGetLine("\nEnter Task: ");
			hashtag = PrintAndGetLine("\nEnter Hashtag: #");
        		todos.insert(todos.begin(),{{{task + "|", GetSubTasks()}, hashtag}, false});
      			break;
    		}
    		case 2: {	// Mark Complete
			ToggleTask(todos, true);
        		break;
    		}
		case 3: {	//Mark Subtask Complete
			ToggleSubTask(todos, true);	
			break;
		}
	    	case 4: {	// Mark Incomplete
    	    		ToggleTask(todos, false);
    	    		break;
    		}
		case 5: {	//Mark Subtask Incomplete
			ToggleSubTask(todos, false);
			break;
		}
    		case 6: {	// Delete Task
        		const auto i { GetItemNumber(todos.size(), "\nPlease Enter Task Number: ")};
   		    	todos.erase(todos.begin() + i - 1);
        		break;
    		} 
		case 7: {	// Delete Subtask
			const auto i { GetItemNumber(todos.size(), "\nPlease Enter Task Number: ") };
			const auto j { GetItemNumber(todos.at(i - 1).first.first.second.size(), "\nPlease Enter Subtask Number: ") };
			todos.at(i - 1).first.first.second.erase(todos.at(i - 1).first.first.second.begin() + j);
			break;
		}
		case 8: {	// Search Hashtag
			hashtag = PrintAndGetLine("\nEnter Hashtag: #");
			std::vector<ListItem> results;
			for (int i = 0; i < todos.size(); i++) {
				if (UpperCaseAndTrim(todos[i].first.second) == UpperCaseAndTrim(hashtag)) {
					results.push_back(todos[i]);
				}
			}
			std::cout << "\n\nTasks with hashtag #" << hashtag << ":\n";
			PrintItems(results);
			break;
		}
    		case 9: {	// Save to File
        		SaveTodos(todos, filename);
        		break;
    		}
    		case 0: {	// Exit 
	       		exit(0);
    		}
		default: {
			std::cout << "\nInvalid Choice.\n";
		}
	}
}

int main(int argc, char** argv) {
  	std::vector<ListItem> todos;
  	int menuOption { 0 };
	std::string filename {argc > 1 ? argv[1] : "default.txt"};
	LoadTodos(todos, filename);       	
  	std::array<std::string, 10> menuOptions = {
    		"1. Add Task",
    		"2. Mark Task Complete",
		"3. Mark Subtask Complete",
    		"4. Mark Incomplete",
		"5. Mark Subtask Incomplete",
		"6. Delete Task",
    		"7. Delete Subtask",
		"8. Search by Hashtag",
    		"9. Save to File",
    		"0. Quit"
  	};
  	while (menuOption != -1) {
		PrintItems(todos);
    		HandleOption(PrintMenu(menuOptions), todos, filename);
  	}
}
