#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <unistd.h>

using std::cout;
using std::cin;
using std::string;

std::ifstream inFILE;
std::ofstream outFILE;
std::vector<std::pair<int,string>> listOfPairs;


bool mainmenu(char** argv) {
	char menu;
	int num;
	sortListOfPairs();
	clrPrint();
	cout << "\n Please choose from one of the following menu items\n";
	cout << " (A)dd new Task\n";
	cout << " (E)dit your List\n";
	cout << " (S)ave and Quit\n\n -->";
	cin >> menu;
	cout << "\n";
	switch (menu) {
		case 'a':
		case 'A':{
			addListPair();
			return true;
			break;
		}
		case 'e':
		case 'E':{
			clrPrint();
			editMenu();
			return true;
			break;
		}
		case 's':
		case 'S':{
			saveListOfPairs(outFILE, argv);
			cout << "\n Your file has been saved.  Have a nice day!\n\n\n\n";
			sleep(3);
			system("clear");
			return false;
			break;
		}
		default:{
			cout << " Menu item not understood, please try again.\n\n";
			return true;
			break;
		}
	}
}

void openFile(std::ifstream& inFILE, char** argv) {
	inFILE.open(argv[1]);
	system("clear");
	cout << "\n You are opening \"" << argv[1] 
	<< "\"\n This To-Do list will be imported...\n" << std::endl;
	sleep(3);
	if (!inFILE.is_open())	{
		cout << " Sorry, there was an error opening your file! Please try again."
			<< "\n\n";
	}
}

void parseList(std::ifstream& inFILE) {
	string task;
	string complete;
	while (!inFILE.eof()) {
		char checkChar;
		inFILE.get(checkChar);
		if(checkChar != '1' || checkChar != '0')
			break;
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
	clrPrint();
	cout << "\n Please enter your task: \n -->";		
	cin.ignore();
	std::getline(cin, task);
	listOfPairs.emplace_back(0, task);
	cout << "\n Your task has been entered, thank you!\n";
	sleep(2);
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
	for(int i=0; i<listOfPairs.size();i++){
		cout << " " << i+1 << ". ";
		if(i+1 < 10)
			cout << " ";
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
	int num;
	clrPrint();
	cout << "\n Please enter the line number of the task you wish to toggle\n -->";
	cin >> num;
	if(listOfPairs.at(num-1).first == 0)
		listOfPairs.at(num-1).first = 1;
	else listOfPairs.at(num-1).first = 0;
	cout << "\n Your change to task \"" << num << ". " 
			<< listOfPairs.at(num-1).second << "\" has been made...\n";
	sleep(2);
}

void deleteTask(){
	int num;
	clrPrint();
	cout << "\n Please enter the line number of the task you wish to delete\n -->";
	cin >> num;
	bool check = true;
	while(check){
		if(listOfPairs.size() >= num){
			listOfPairs.erase(listOfPairs.begin()+num-1);
			check = false;
		}
		else {
			cout << "Your number is outside of the range of tasks, try again\n -->";
			cin >> num;
		}
	}
}

void editMenu(){
	bool loop = true;
	while(loop){
		char response;
		cout << "\n (T)oggle task status\n";
		cout << " (D)elete a task\n";
		cout << " (R)eturn to Main Menu\n\n -->";
		cin >> response;
		switch (response) {
		case 't':
		case 'T':
			toggle();
			sortListOfPairs();
			clrPrint();
			break;
		case 'r':
		case 'R':
			loop = false;
			break;
		case 'd':
		case 'D':
			deleteTask();		
			clrPrint();
			break;
		default:
			cout << " Menu item not understood, please try again.\n\n";
			break;
		}
	}
}

void clrPrint(){
	system("clear");
	cout << "\n ===Your ToDo list!===\n\n";
	printListOfPairs();
}

int main(int argc, char** argv) {
	openFile(inFILE, argv);
	parseList(inFILE);
	inFILE.close();
	while(mainmenu(argv));
}