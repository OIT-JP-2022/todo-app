#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

using Lines = std::vector<std::string>;

// Get list of todo-lists
auto getLists(const std::string & folderName) {
  std::vector<std::string> lists {};
  std::string currentPath{std::filesystem::current_path()};
  currentPath += "/" + folderName;
  for (const auto & file : std::filesystem::directory_iterator(currentPath)) {
    std::string tempName = std::filesystem::path(file).filename();
    if(tempName.find(".txt") != -1) {
      lists.push_back(tempName);
    }
  }
  return lists;
}

// Add new list
auto addList(Lines & lists, const std::string & input) {
  std::ofstream newFile("testDir/" + input + ".txt");
  newFile.close();
  lists.push_back(input + ".txt");
}

// Add list item
auto addTodo(Lines & todos, const std::string & todo) {
  todos.push_back(todo);
}

// Delete file/list
auto removeList(Lines & lists, int index) {
  std::string file = lists[index];
  lists.erase(lists.begin()+index);
  std::filesystem::remove("testDir/" + file);
}

//mnt/c/Users/blued/source/CST316LinuxStuff/todo-app/

// Delete todo item
auto removeTodo(Lines & todos, int index) {
  todos.erase(todos.begin()+index);
}

// Edit list item
auto editTodo(Lines & todos, int index, const std::string & todo) {
  todos[index] = todo;
}

// Print list item
auto print(const std::string & todo) {
  std::cout << todo << '\n';
}

// Print entire list
auto print(Lines & todos) {
  int count{1};
  for (const auto & todo : todos) {
	std::cout << count << ") ";
	print(todo);
	count++;
  }
}

// Read todo list from file
auto readTodos(const std::string & filename) {
  std::vector<std::string> todos{};

  std::ifstream input{filename};
  for (std::string line{}; std::getline(input, line); ) {
    addTodo(todos, line);
  }

  return todos;
}

// Write todo list to file
auto writeTodos(const Lines & todos, const std::string & folderName) {
  std::ofstream output{folderName};

  for (auto todo : todos) {
    output << todo << '\n';
  }
}

// Sub list screen menu
auto listPrompt() {	
  std::cout << "\n\t-------------";
  std::cout << "\n\t  List Menu";
  std::cout << "\n\t--------------\n";
  std::cout << "1) Add new item" << '\n';
  std::cout << "2) Delete item" << '\n';
  std::cout << "3) Edit item" << '\n';
  std::cout << "4) Close list" << '\n';
  std::cout << "\n\n\t~ Menu choice: ";
  int choice{};
  std::cin >> choice;
  return choice;
}

// Process list menu item
auto runList(Lines & todos) {
  print(todos);

  auto option = listPrompt();
  switch(option) {
	case 1: {
	  std::cout << "\t~ New item to add: ";
	  std::string input{};
	  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	  std::getline(std::cin, input);
          addTodo(todos,input);
	  break;
	  }
	case 2: {
	  int choice{};
	  std::cout << "\t~ Enter item# to delete: ";
	  std::cin >> choice;
	  removeTodo(todos,choice - 1);
	  break;
	  }
	case 3: {
	  int choice{};
	  std::string input{};
	  std::cout << "\t~ Enter item# to edit: ";
	  std::cin >> choice;
	  std::cout << "\n\t~ Enter new item: ";
	  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	  std::getline(std::cin, input);
	  editTodo(todos,choice - 1,input);
	  break;
	  }

	default: return false;
  }

  return true;
}

// Main list screen
auto mainPrompt(Lines & lists) {
  std::cout << "\n\t==============";
  std::cout << "\n\t  Todo Lists";
  std::cout << "\n\t==============\n";
  print(lists);
  std::cout << "\n\t1) Add new list" << '\n';
  std::cout << "\t2) Delete list" << '\n';
  std::cout << "\t3) Edit list" << '\n';
  std::cout << "\t4) Exit" << '\n';
  std::cout << "\n\n\t~ Menu choice: ";
  int choice{};
  std::cin >> choice;
  return choice;
}

// Process main menu item
auto runMain(Lines & lists) {


  auto option = mainPrompt(lists);
  switch(option) {
	case 1: {
	  std::cout << "\t~ New list name: ";
	  std::string input{};
	  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	  std::getline(std::cin, input);
	  addList(lists, input);
	  break;
	  }
	case 2: {
	  //TODO: create remove list function
	  int choice{};
	  std::cout << "\t~ Enter list# to delete: ";
	  std::cin >> choice;
	  removeList(lists,choice - 1);
	  break;
	  }
	case 3: {
	  int choice{};
	  std::cout << "\t~ Enter item# to edit: ";
	  std::cin >> choice;
	  std::string todoFile {lists[choice - 1]};
	  auto todos = readTodos(todoFile);
	  while(runList(todos)) {}
	  break;
	  }

	default: return false;
  }

  return true;
}

int main() {
  std::string folderName{"testDir"};
  auto lists = getLists(folderName);
  
  print(lists);

  while (runMain(lists)) {}
}
