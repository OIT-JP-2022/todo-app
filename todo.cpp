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
	//lists.push_back(WHAT???);
    std::cout << std::filesystem::path(file).filename() << "\n";
  }
  
  return lists;
}

// Add new list
auto addList(const std::string & input) {
  std::ofstream newFile(input + ".txt");
  newFile.close();
}

// Add list item
auto addTodo(Lines & todos, const std::string & todo) {
  todos.push_back(todo);
}

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

// Main list screen
auto mainPrompt() {
  std::cout << "\n\t==============";
  std::cout << "\n\t  Todo Lists";
  std::cout << "\n\t==============\n";
  std::cout << "1) Add new list" << '\n';
  std::cout << "2) Delete list" << '\n';
  std::cout << "3) Edit list" << '\n';
  std::cout << "4) Exit" << '\n';
  std::cout << "\n\n\t~ Menu choice: ";
  int choice{};
  std::cin >> choice;
  return choice;
}

// Process main menu item
auto runMain(Lines & lists) {
  ///////TODO function to print lists

  auto option = mainPrompt();
  switch(option) {
	case 1: {
	  std::cout << "\t~ New list name: ";
	  std::string input{};
	  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	  std::getline(std::cin, input);
	  addList(input);
	  break;
	  }
	case 2: {
	  int choice{};
	  std::cout << "\t~ Enter item# to delete: ";
	  std::cin >> choice;
	  removeTodo(lists,choice - 1);
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
	  //editList(lists,choice - 1,input);
	  break;
	  }

	default: return false;
  }

  return true;
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

int main() {
  std::string folderName{"testDir"};
  auto lists = getLists(folderName);
  
  //print(lists);

  //while (runMain(lists)) {}
}
