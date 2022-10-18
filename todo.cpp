#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <vector>

using namespace std;
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::vector;

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

int main(int argc, char** argv)
{
        string argument = argv[1];
        toDoList myList;
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
                return 0;
        }

        myList.printList();
}

//myList.printList();

// std::cout << "todo: make todo app THIS IS JASON!..." << '\n';
//}
