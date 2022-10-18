#include <iostream>
#include <fstream>
#include <vector>

int i = 0;
using Lines = std::vector<std::string>;

auto addTodo(Lines & todos, const std::string & todo) {
  todos.push_back(todo);
}
auto removeTodo(Lines & todos, int index) {
  todos.erase(todos.begin()+index);
}

auto editTodo(Lines & todos, int index, const std::string & todo) {
  todos[index] = todo;
}

auto print(const std::string & todo) {
 std::cout << todo << '\n';
}
auto searchTodo(Lines & todos, std::string input){ //search for exact phrase of todo
for(const auto & todo : todos) {
   i++;// dumb and bad putting this here because I can't believe i...
 if(input == todo)
    {
   // i++;
      std::cout << "Todo is in the: " << i << " number in elements"  << "\n"; //show index?
      //i = 0;
      print(todo); //user searches for item, prints it
    }
  }
 i = 0;
}
auto print(Lines & todos) {
  std::cout << "=-=-=-=-=-=-=-=-=- Printing Todo  =-=-=-=-=-=-=-=-=-=" <<  "\n";
  for (const auto & todo : todos) {
    print(todo);
    std::cout << "\n";
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

//add fileReadFrom

//1: Remove entire list, use for loop for current
//2: Add from txt to program in todos.
//3: Write to function like read but specific output file so can overwrite old todo


auto writeTodos(const Lines & todos, const std::string & filename) {
  std::ofstream output{filename};

  for (auto todo : todos) {
    output << todo << '\n';
  }
}

auto prompt() {
  std::cout << "What do you want to do? (add |a|, remove |r|, print |p|) " << '\n';
  std::string line{};
  std::getline(std::cin, line);
  return line;
}

auto run(Lines & todos) {
 // print(todos);

  auto option = prompt();
  if (option == "a" || option == "add") {
    std::cout << "Add todo: ";
    std::string line{};
    std::getline(std::cin, line);
    addTodo(todos, line);
    return true;
  } else if (option == "q" || option == "quit") {

}
    //else if remove
    else if(option == "r" || option == "remove"){
    std::cout << "Remove todo: ";
    std::string line{};
    std::getline(std::cin, line);
    int boi = stoi(line);
    removeTodo(todos, boi);
return true;
}
    //else if display/print

else if(option == "p" || option == "print"){
   // std::cout << " todo: ";
   // std::string line{};
    //std::getline(std::Cin, line);
    print(todos);
return true;
}
    //else if search/#
 else if(option == "s" || option == "search"){
    std::cout << "Search todo: ";
    std::string line{};
    std::getline(std::cin, line);
   // int boi = stoi(line);
    searchTodo(todos, line);
return true;
}
else if(option == "f" || option == "file"){
    std::cout << "Enter your file name to read from: ";
    std::string line{};
    std::getline(std::cin, line);
   //Call custom function using the file name like r 
    readTodos(line);
return true;
}


    //else if nest add

    return false;
  }

 // std::cout << "\n";

//  return true;
 //maybe delete this but idk

int main() {
  std::string filename{"todos.txt"};
  auto todos = readTodos(filename);

  while (run(todos)) {}

  writeTodos(todos, filename);
}

