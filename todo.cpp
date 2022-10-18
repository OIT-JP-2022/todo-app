#include <iostream>
#include <fstream>
#include <vector>

using Lines = std::vector<std::string>;

auto prompt() {
  std::cout << "What do you want to do? ";
  std::string line{};
  std::getline(std::cin, line);
  return line;
}

auto addTodo(Lines & todos, const std::string & todo) {
  todos.push_back(todo);
}

auto addSubTodo(Lines & todos,const std::string & subtodo, int index) {
	if (todos[index-1].starts_with('X') == true) {
			std::cout << "Item already completed. \n\n";
			return;
	}
	else if (todos[index].starts_with(' ') == true)
			index++;
	std::string	new_subtodo = " --" + subtodo;
	todos.emplace(todos.begin()+index, new_subtodo);
}

auto removeTodo(Lines & todos, int index) {
  todos.erase(todos.begin()+index);
}

auto editTodo(Lines & todos, int index, const std::string & todo) {
  todos[index] = todo;
}

auto searchTodo(const Lines & todos) {
  std::string keyword =  prompt();
  std::cout << "\nTodo items found: \n";
  
  for(const auto todo : todos) {
    if (todo.find(keyword) != std::string::npos)
      std::cout << todo << '\n';
		}
	std::cout << "===================\n\n";
}

auto completeTodo(Lines & todos,int index) {
  std::string newstring = "X " + todos[index-1];
  editTodo(todos,index-1,newstring);
  while(todos[index].front() == ' ') {
    removeTodo(todos,index);
  }
}

auto print(const std::string & todo) {;
 std::cout  << todo << '\n';
}

auto print(Lines & todos) {
	for (const auto & todo : todos) {
    print(todo);
  }
}

auto readTodos(const std::string & filename) {
  std::vector<std::string> todos{};

  std::ifstream input{filename};
  for (std::string line{}; std::getline(input, line); ) {
    addTodo(todos, line);
  }

  return todos;
}

auto writeTodos(const Lines & todos, const std::string & filename) {
  std::ofstream output{filename};

  for (auto todo : todos) {
    output << todo << '\n';
  }
}

auto runAddOption(Lines & todos) {
		std::cout << "Add todo: ";
    std::string line{};
    std::getline(std::cin, line);
    addTodo(todos, line);
}

auto run(Lines & todos) {
  int menuSelection;
	print(todos);
  
	std::cout << "===================\n";

	std::cout << "Cabbage Todo List \n\n";
	
  std::cout << "1: add todo \n"
						<< "2: add sub todo \n"
						<< "3: remove todo \n"
						<< "4: edit todo \n"
						<< "5: search todo \n"
						<< "6: complete todo\n"
						<< "7: quit \n"
						<< "\n";
	std::cout << "Select a number: ";					
	std::cin >> menuSelection;
	std::cin.ignore();
	switch(menuSelection) {
		case 1:
				runAddOption(todos);
				break;
		case 2:
				addSubTodo(todos,"test subtodo", 1);
				break;
		case 3:
				std::cout << "Not implemented yet.\n";
				break;
		case 4:
				std::cout << "Not implemented yet.\n";
				break;
		case 5:
				searchTodo(todos);
				break;
		case 6:
				completeTodo(todos,3);
				break;
		case 7:
				return false;
				break;
    default:
				std::cout << "Invalid Selection. Try again \n";
	}

  return true;
}

int main() {
  std::string filename{"todos.txt"};
  auto todos = readTodos(filename);
 // print(todos);
	while (run(todos)) {}
  writeTodos(todos, filename);
}

