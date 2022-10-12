#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::string;

std::fstream openFile(const string& filename){
    std::fstream File;
    File.open(filename, std::ios_base::app | std::ios_base::in | std::ios_base::out);
    if(!File){ //no file, make one
      std::ofstream File(filename); //no file, make one
    } 
    return File;
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

void printList(const string& filename) 
{
    std::fstream myFile = openFile(filename);
    string text;
    cout << "-------ToDo List------" << "\n";
    if (myFile.is_open())
    {
        while (getline(myFile, text))
        {
            cout << text << "\n";
        }
    }else{
      cout << "File not open";
    }
}

void enterItem(const string& filename)
{
    std::fstream myFile = openFile(filename);
    if (myFile.is_open())
    {
      string item = "";
      cout << "Enter item: ";
      cin.ignore();
      getline(cin, item);
      myFile << "- [ ] " << item << "\n";
    }else{
      cout << "File not open";
    } 
}


int main(int argc, char *argv[]) {
  std::string filename = argc >= 2 ? argv[1] : "todo.txt"; // arg or defaul

  bool exit = false;
  do{
    printList(filename);
    switch(menu()){
      case 'a': enterItem(filename); break;
      case 'q': exit = true; break;
    }
  }while (!exit);

  cout << "\nHave a good day!\n";
  return 0;
}
