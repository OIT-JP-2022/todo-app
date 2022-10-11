#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

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
void printListOfPairs();
void sortListOfPairs();
void editOption();
void toggle();

int main(int argc, char** argv) {
	openFile(inFILE, argv);
	parseList(inFILE);
	inFILE.close();
	while(mainmenu(argv));
}

bool mainmenu(char** argv) {
	char menu;
	int num;
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
		sortListOfPairs();
		printListOfPairs();
		editOption();
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
	}
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
		if(complete != ""){
			int num = stoi(complete);
			listOfPairs.emplace_back(num, task);
		}
		else break;
	}
}

void addListPair(){
	string task;
	cout << "\n\n Please enter your task: \n";		
	cin.ignore();
	std::getline(cin, task);
	listOfPairs.emplace_back(0, task);
	cout << "\nYour task kas been entered, thank you!\n";
}

void saveListOfPairs(std::ofstream& outFILE, char** argv){
	outFILE.open(argv[1]);
	for(int i=0; i<listOfPairs.size();i++){
        outFILE<<listOfPairs.at(i).first<<'|'<<listOfPairs.at(i).second;
        if (i != (listOfPairs.size()-1))
        outFILE << '\n';
    }	
}

void printListOfPairs(){
	//cout << "Incomplete Tasks:\n";
	for(int i=0; i<listOfPairs.size();i++){
		cout << " " << i+1 << ". ";
		if(listOfPairs.at(i).first==0){
		cout << "Incomplete: "<<listOfPairs.at(i).second<<'\n';
		}
		if(listOfPairs.at(i).first==1){
		cout << "Complete: "<<listOfPairs.at(i).second<<'\n';
		}
	}
}

void sortListOfPairs(){
	std::sort(listOfPairs.begin(), listOfPairs.end(), 
	[] (const auto &x, const auto &y) { return x.first < y.first; });
}

void toggle(){
	cout << "Please enter the line number of the task you wish to toggle\n";
	int num;
	cin >> num;
	if(listOfPairs.at(num-1).first == 0)
		listOfPairs.at(num-1).first = 1;
	else listOfPairs.at(num-1).first = 0;
}

void deleteTask(){
	cout << "Please enter the line number of the task you wish to delete\n";
	int num;
	cin >> num;
	bool check = true;
	while(check){
		if(listOfPairs.size() >= num){
			listOfPairs.erase(listOfPairs.begin()+num-1);
			check = false;
		}
		else {
			cout << "Your number is outside of the range of tasks, try again\n";
			cin >> num;
		}
	}
}

void editOption(){
	cout << "\n(T)oggle task status\n";
	cout << "(R)eturn to Main Menu\n";
	cout << "(D)elete a task\n";
	char response;
	cin >> response;
	switch (response) {
	case 't':
	case 'T':
		toggle();
		sortListOfPairs();
		printListOfPairs();
		break;
	case 'r':
	case 'R':		
		break;
	case 'd':
	case 'D':
		deleteTask();		
		sortListOfPairs();
		printListOfPairs();
		break;
	default:
		cout << " Menu item not understood, please try again.\n\n";
		break;
	}
}