#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::string;

std::fstream openFile(const string& filename){
    std::fstream open_file;
    open_file.open(filename, std::ios_base::app | std::ios_base::in | std::ios_base::out);
    if(!open_file) std::ofstream File(filename); //no file, make one
    if (open_file.fail()) throw "Open file failed."; // File doesn't open, error out
    return open_file;
} 

char menu()
{
    char choice;
    cout << "-----ToDo Actions-----" << "\n";
    cout << "a: add items" << "\n";
    cout << "q: quit" << "\n";
    cout << "\n";
    cout << "Enter option: ";
    cin >> choice;
    return std::tolower(choice);
}

void printVector(const std::vector<string>& vector, const string& title = "-------ToDo List------\n") 
{
  cout << title;
  for (int i = 0; i < vector.size(); ++i){
    cout << (i+1) << ") " << vector[i] << "\n";
  }
}

void enterItem(const string& filename)
{
  std::fstream myFile = openFile(filename);
  string item = "";
  cout << "Enter item: ";
  cin.ignore();
  getline(cin, item);
  myFile << "- [ ] " << item << "\n";
  myFile.close();
}

std::vector<string> getTasks(const string& filename){
  std::fstream myFile = openFile(filename); 
  std::vector<string> tasks;
  string text;
  while (getline(myFile, text))
  {
    tasks.push_back(text);
  }
  myFile.close();

  return tasks;
}

int main(int argc, char *argv[]) {
  std::string filename = argc >= 2 ? argv[1] : "todo.txt"; // arg or defaul

  bool exit = false;
  do{
    printVector(getTasks(filename));
    switch(menu()){
      case 'a': enterItem(filename); break;
      case 'q': exit = true; break;
    }
  }while (!exit);

  cout << "\nHave a good day!\n";
  return 0;
}
