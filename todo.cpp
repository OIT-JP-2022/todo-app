#include <cassert>
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
	toDo()
	{
		this->completeness = 0;
		this->description = "";
	}

	void addDescription(string y){description = y;}
	void addCompleteness(string b){completeness = stoi(b);}

	void clear()
	{
		description = "";
		completeness = 0;
	}

	void print()
	{
		cout <<"\n Printing TODO ITEM \n" ;
		cout<<"Description: " << description << "\n Completeness: " << completeness<<"\n";
		cout << "END OF TODO PRINT \n";
	}

	int	completeness;
	string	description;
};



class toDoList
{
	public:
	toDoList() {theList = {};}

	void printList()
	{
		for(auto const& i: theList)			// = theList.cbegin();i != theList.cend(); ++i){
		{
			cout << "Description: " << i.description << "\n";
			cout << "Completeness: " << i.completeness << "\n \n"; 
		}
	}
	
	void toDoAdder(toDo x) { theList.push_back(x);};	//This adds 'x' (toDo)  to our toDo list (theList)

	void loadList(string y)
	{
		string filename = y;
		string words;
		string word;
		string desc = "";
		string comp = "";
		ifstream infile(filename);
		

		if(!infile.is_open())
			cout << "cannot open file " <<  filename << "\n";
	
	
		while(infile >> word)
		{
			if(word.compare("Start:") == 0 && words.length() != 0)
			{
				//This creates a toDo item and adds the current description and completeness level to it.
				//It then places this item at the back of myList.

				comp = words;
				toDo newItem;
				
				newItem.addDescription(desc);
				newItem.addCompleteness(comp);
				theList.push_back(newItem);
				
				desc = ""; 
				comp = "";
				words = "";
			}
			else if(word.compare("Start:") == 0 && words.length() == 0){}
			else if(word.compare("Completeness:") == 0)
			{
				//This sets desc and clears words
				desc = words;	
				words=""; 
			}
			else
			{
				//This appends the word to words
				words = words + (" " + word);
			}
		}

		//adds the last toDo item
		comp=words;
		toDo newItem;
                newItem.addDescription(desc);
                newItem.addCompleteness(comp);
		theList.push_back(newItem);
	}

	std::vector<toDo> theList = {};
};

int main(int argc, char** argv)
{
	string argument = argv[1];
	//for(int i = 0; i <  argc; ++i)
	//	cout << argv[i] << "\n";

	toDoList myList; //create instance of list
	if(argument.compare( "-l") == 0)  //check if -l
		myList.loadList(argv[2]);
	else if(argument.compare("-h") == 0)
	{
		cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"
		     << "||     +	 TODO PROGRAM  +          ||\n"
		     << "||  +				  +       ||\n"
		     << "||		 USER MANUAL		  ||\n"
		     << "||    			 +	          ||\n"
		     << "||		+	+	        , ||\n"
		     << "||    ,                                   ||\n"
		     << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"
		     <<	"		   |vv|		    \n"
		     << "    ,  ,   ,       |vv|    ,       ,       \n"
		     << "                   |vv|       ,       ,    \n"
		     << "  ,    ,      ,    |vv|          ,         \n"
		     << "    ,      ,       |vv|    ,          ,    \n"
		     << "    ,   ,          |vv|                    \n"
		     << "                   |vv|      ,      ,      \n \n\n"

		     << "FLAGS:\n"
		     << "-h		Displays the program's manual\n"
		     << "-l		Loads a .txt file and displays its content\n";
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


