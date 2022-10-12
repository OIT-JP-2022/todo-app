#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using std::cout;
using std::cin;
using std::string;

std::vector<string> readToVector(const string& filename){
  std::ifstream myFile; 
  myFile.open(filename);
  if(myFile.fail()) throw "Error opening file.";  

  std::vector<string> lines;
  string line;
  while (getline(myFile, line))
  {
    lines.push_back(line);
  }
  myFile.close();
  return lines;
}

void writeFromVector (const string& filename, const std::vector<string>& vector){
  std::ofstream write_file;
  write_file.open(filename);
  if(write_file.fail()) throw "Error opening file.";  
  
  for (int i = 0; i < vector.size(); ++i){
    write_file << vector[i] << "\n";
  }
  write_file.close();
}

void printVector(const std::vector<string>& vector, const string& title = "-------ToDo List------") 
{
  cout << "\n" << title << "\n";
  for (int i = 0; i < vector.size(); ++i){
    cout << (i+1) << ") " << vector[i] << "\n";
  }
}

void printVector(const string& filename, const string& title = "-------ToDo List------") 
{
  auto toPrint = readToVector(filename);
  printVector(toPrint,title);
}

void enterItem(const string& filename)
{
  auto data = readToVector(filename);
  string item = "";
  cout << "Enter item: ";
  cin.ignore();
  getline(cin, item);
  data.push_back("- [ ] " + item + "\n");
  writeFromVector(filename,data);
}

void deleteItem(const string& filename)
{
  auto tasks = readToVector(filename);
  printVector(tasks,"----Edit ToDo List----");
  int item = 0;
  cout << "Which task would you like to delete: ";
  cin >> item;

  tasks.erase(tasks.begin()+(--item));
  writeFromVector(filename, tasks);
}

void editItem(const string& filename)
{
  auto tasks = readToVector(filename);
  printVector(tasks,"----Edit ToDo List----");
  int item = 0;
  cout << "Which task would you like to change: ";
  cin >> item;
  --item <= tasks.size() ? (tasks[item][3] = tasks[item][3] == 'X' ? ' ' : 'X') : throw "Select out of bounds.";
  writeFromVector(filename, tasks);
}

void sortListByCompleted(const string& filename)
{
  auto data = readToVector(filename);
  std::sort(data.begin(),data.end());
  writeFromVector(filename,data);
  printVector(data, "\n----- Sorted by completion-----\n");
}

void menu(const string& filename)
{
    char choice;
    bool exit = false;
    while(!exit){
          printVector(filename);
      cout << "-----ToDo Actions-----" << "\n";
      cout << "a: add items" << "\n";
      cout << "d: delete items" << "\n";
      cout << "m: mark items" << "\n";
      cout << "s: sort items" << "\n";
      cout << "q: quit" << "\n";
      cout << "\n";
      cout << "Enter option: ";
      cin >> choice;
      switch(std::tolower(choice)){
        case 'a': enterItem(filename); break;
        case 'm': editItem(filename); break;
        case 'd': deleteItem(filename); break;
        case 's': sortListByCompleted(filename); break;
        case 'q': exit = true; break;
      }
    }

}

int main(int argc, char *argv[]) {
  std::string filename = argc >= 2 ? argv[1] : "todo.txt"; // arg or defaul

  menu(filename);

  cout << "\nHave a good day!\n";
  return 0;
}
