#include <iostream>
#include <fstream>
#include <vector>

using Lines = std::vector<std::string>;


auto prompt(std::string action) {
  std::cout << "What do you want to do " << action << "?\n";
  std::string line{};
  std::getline(std::cin, line);
  return line;
}

auto addTodo(Lines & todos, const std::string & todo) {
  todos.push_back(todo);
}

auto removeTodo(Lines & todos, int index) {
  todos.erase(todos.begin()+index);
}

auto editTodo(Lines & todos, int index, const std::string & todo) {
  todos[index] = todo;
}

auto searchTodo(const Lines & todos) {
  std::string keyword =  prompt("search");
  std::cout << "This is the keyword: " << keyword << '\n';
  
  for(const auto todo : todos) {
   // todo.find(keyword);
    if (todo.find(keyword) != std::string::npos)
      std::cout << todo << '\n';
    else
      std::cout << "no match" << '\n';
  }
}

auto print(const std::string & todo) {
  std::cout << todo << '\n';
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

auto run(Lines & todos) {
  print(todos);

  auto option = prompt("add");
  if (option == "a" || option == "add") {
    std::cout << "Add todo: ";
    std::string line{};
    std::getline(std::cin, line);
    addTodo(todos, line);
    return true;
  } else if (option == "q" || option == "quit") {
    return false;
  }

  std::cout << '\n';

  return true;
}

int main() {
  std::string filename{"todos.txt"};
  auto todos = readTodos(filename);
  print(todos);
 // while (run(todos)) {}
  searchTodo(todos);
  writeTodos(todos, filename);
}

