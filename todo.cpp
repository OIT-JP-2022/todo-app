#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;
std::ifstream inFILE;
std::vector<std::pair<int,string>> listOfPairs;

bool mainmenu();
void openFile(std::ifstream& inFILE, char** argv);
void parseList(std::ifstream& inFILE);
void waitThenClear();

int main(int argc, char** argv) {
	system("clear");	
	openFile(inFILE, argv);
	parseList(inFILE);
	inFILE.close();
	while(mainmenu());
}

bool mainmenu() {
	char menu;	
	cout << "\n Welcome to your ToDo list!";
	cout << "\n\n\n Please choose from one of the following menu items\n";
	cout << " (E)nter new Todo Task\n";
	cout << " (V)iew your Todo List\n";
	cout << " (Q)uit\n\n";
	cout << " -> ";
	std::cin >> menu;
	cout << "\n";
	switch (menu) {
	case 'e':
	case 'E':
		//create new vector item
		waitThenClear();
		return true;
		break;
	case 'v':
	case 'V':
		// display vector list	
		// option to edit -> complete/uncomplete
		// save vector to file
		waitThenClear();
		return true;
		break;
	case 'q':
	case 'Q':
		return false;
		break;
	default:
		cout << " Menu item not understood, please try again.\n\n";
		waitThenClear();
		return true;
		break;
		}
	}

void openFile(std::ifstream& inFILE, char** argv) {
	inFILE.open(argv[1]);
	cout << "\n You are opening " << argv[1] << ", your ToDo list is being imported!\n" << std::endl;
	if (!inFILE.is_open())	{
		cout << " Sorry, there was an error opening your file! Please try again."
			<< "\n\n";
		waitThenClear();
	}	
	waitThenClear();
}

void waitThenClear(){
	cin.clear();
	cin.get();
	system("clear");
}

void parseList(std::ifstream& inFILE) {
	string task;
	string complete;
	while (!inFILE.eof()) {
		std::getline(inFILE, complete, '|');
		std::getline(inFILE, task, '\n');
		int num = stoi(complete);
		listOfPairs.emplace_back(num, task);
	}
}

// create save function
// create delete function
// edit completeness
// sort by completeness
// create add function