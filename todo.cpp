#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;
std::ifstream inFILE;
std::ofstream outFILE;
std::vector<std::pair<int,string>> listOfPairs;

bool mainmenu(char** argv);
void openFile(std::ifstream& inFILE, char** argv);
void parseList(std::ifstream& inFILE);
void waitThenClear();
void addListPair();
void saveListOfPairs(std::ofstream& outFILE, char** argv);

int main(int argc, char** argv) {
	//system("clear");	
	openFile(inFILE, argv);
	parseList(inFILE);
	inFILE.close();
	
	
	while(mainmenu(argv));
}

bool mainmenu(char** argv) {
	char menu;	
	cout << "\n Welcome to your ToDo list!";
	cout << "\n\n\n Please choose from one of the following menu items\n";
	cout << " (E)nter new Todo Task\n";
	cout << " (V)iew your Todo List\n";
	cout << " (S)ave and Quit\n\n";
	cout << " -> ";
	std::cin >> menu;
	cout << "\n";
	switch (menu) {
	case 'e':
	case 'E':
		addListPair();
		return true;
		break;
	case 'v':
	case 'V':
		// display vector list	
		// option to edit -> complete/uncomplete
		// save vector to file
		//waitThenClear();
		saveListOfPairs(outFILE, argv);
		return true;
		break;
	case 's':
	case 'S':
		saveListOfPairs(outFILE, argv);
		cout << "\nThank you, your file has been saved!\n";
		return false;
		break;
	default:
		cout << " Menu item not understood, please try again.\n\n";
		//waitThenClear();
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
		//waitThenClear();
	}	
	//waitThenClear();
}

void waitThenClear(){
	cin.ignore();
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

void addListPair(){
	string task;
	cout << "\n\n Please enter your task: \n";		
	cin.ignore();
	std::getline(cin, task);
	listOfPairs.emplace_back(0, task);
	cout << "\nYour task kas been entered, thank you!\n";
	//waitThenClear();
}

void saveListOfPairs(std::ofstream& outFILE, char** argv){
	outFILE.open(argv[1]);
	for(int i=0; i<listOfPairs.size();i++){
		outFILE<<listOfPairs.at(i).first<<'|'<<listOfPairs.at(i).second <<'\n';
	}	
}
// create save function
// create delete function
// edit completeness
// sort by completeness
// create add function