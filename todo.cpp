#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <vector>
#include <array>

using namespace std;
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::array;


int prompt(std::string msg, int max) {
  int n;

  while ( (n > max || n < 1) && n != -1) {
    std::cout << msg << " ";
    std::cin >> n;
    std::cout << "\n";
  }

  return n;
}


int printMenu(std::array<std::string, 5> menuItems) {
  for (const std::string & item : menuItems) {
    std::cout << "\t" << item << "\n";
  }

  std::cout << "\n";
  return prompt("Enter Choice: ", 5);
}


class toDo
{
        public:
        toDo(int completedness = 0, int indentation = 0, string description = "")
        {
                this->completeness = completedness;
    this->indentation = indentation;
                this->description = description;

        }

        void addDescription(string y){description = y;}
        void addCompleteness(string b){completeness = stoi(b);}

        void clear()
        {
                description = "";
                completeness = 0;
        }

  void printIndent() {
    for (int i = 0; i < this->indentation; i++) {
      cout << '\t';
    }
  }

        void print()
        {
    printIndent();
                cout << "Description: " << description << "\n";
    printIndent();
    cout << "Completeness: " << completeness<<"\n";
        }

  int indentation;
        int     completeness;
        string  description;
};



class toDoList
{
        public:
  std::vector<toDo> theList = {};
        toDoList() {theList = {};}

        void printList()
        {
                for(auto & i: theList)
                        i.print();
		cout << "\n";
        }

        void toDoAdder(toDo x) { theList.push_back(x);};        //This adds 'x' (toDo)  to our toDo list (theList)

        void loadList(string y)
  {
    ifstream file{y};
    string msg;

    while (getline(file, msg)) {
      theList.push_back(toDo{((int)msg[0]-48), ((int)msg[2]-48), msg.substr(4)});
    }
        }

  void save(string filename) {
    ofstream file {filename};

    for (const auto & [completedness, indentation, msg] : theList) {
      file << completedness << " " << indentation << " " << msg << "\n";
    }

    cout << "\nFile saved.\n";
  }
};


void handleOption(int n, toDoList & todo, string filename) {
  string message;
  std::vector<toDo> todos = todo.theList;

  switch(n) {
    case 1: {
        std::cout << "\nEnter Message: ";
        //std::cin >> message;
        //std::cout << "\n";
        //todos.(todos.begin(),{message,false});
      break;
    }

    case 2: {
        //const auto i {getItemNumber(todos)};
        //todos.push_back({todos.at(i-1).first,true});
        //todos.erase(todos.begin() + i-1);
        break;
    }
      
    case 3: {
        //const auto i {getItemNumber(todos)};
        //todos.insert(todos.begin(), {todos.at(i-1).first, false});
        //todos.erase(todos.begin() + i);
        break;
    }
      
    case 4: {
        //const auto i {getItemNumber(todos)};
        //todos.erase(todos.begin() + i-1);
        break;
    }
      
    case 5: {
        //saveTodos(todos, filename);
        break;
    }
  }
}

int main(int argc, char** argv)
{
        string argument = argv[1];
	int menuOption {0};
        toDoList myList;
	
	string filename{argc > 2 ? argv[2]:"default.txt"};
        
	if(argument.compare( "-l") == 0)
                myList.loadList(argv[2]);
        else if(argument.compare("-h") == 0)
        {
                cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"
                     << "||     +        TODO PROGRAM  +          ||\n"
                     << "||  +                            +       ||\n"
                     << "||              USER MANUAL              ||\n"
                     << "||                      +                ||\n"
                     << "||             +       +               , ||\n"
                     << "||    ,                                   ||\n"
                     << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"
                     << "                  |vv|             \n"
                     << "    ,  ,   ,       |vv|    ,       ,       \n"
                     << "                   |vv|       ,       ,    \n"
                     << "  ,    ,      ,    |vv|          ,         \n"
                     << "    ,      ,       |vv|    ,          ,    \n"
                     << "    ,   ,          |vv|                    \n"
                     << "                   |vv|      ,      ,      \n \n\n"

                     << "FLAGS:\n"
                     << "-h             Displays the program's manual\n"
                     << "-l             Loads a .txt file and displays its content\n";
        }
	else
        {
                cout<<"Usage: Loads or saves a todo list from a .txt document. EX: todo -l filename.txt \n";
        }//else if (argument.compare("-m") == 0)
	//{i
		std::array<std::string, 5> menuOptions = {
			"1. Add",
			"2. Mark Complete",
			"3. Mark Incomplete",
			"4. Delete",
			"5. Save"
	  	};

	//	if(argv[2] == NULL)
	//		filename="default.txt";
	
		while (menuOption != -1) {
	    		myList.printList();
	
	    		menuOption = printMenu(menuOptions);
	
    			handleOption(menuOption, myList, filename);
		}
	//}
	
}

//myList.printList();

// std::cout << "todo: make todo app THIS IS JASON!..." << '\n';
//}
