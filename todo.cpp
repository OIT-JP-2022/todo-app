#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::sort;
using std::string;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::pair;

bool parseList(string filename, vector<pair<int, string>>& listOfPairs) {
	string task{};
	string buffer{};
	string complete{};
	ifstream inFILE(filename, std::ios::in);
	bool returnCheck = true;

	//if (inFILE.peek() == -1)
		//returnCheck = false;
	//else
	//{
		while (inFILE.peek() != -1)
		{
			getline(inFILE, complete, '|');
			getline(inFILE, task, '\n');
			int num = stoi(complete);
			listOfPairs.emplace_back(num, task);
		}
	//}

	return returnCheck;
}
void printListOfPairs(vector<pair<int, string>>& listOfPairs) {
	int i {};
	cout << "Incomplete: \n";
	int size = listOfPairs.size();
	for (i = 0; i < size; i++){
		if(listOfPairs.at(i).first == 0){
			cout << i + 1<< ". " << listOfPairs.at(i).second << '\n';
		}
	}
	cout << "\nComplete: \n";
	for (i = i; i < size; i++)
	{
		cout << i + 1 << ". " << listOfPairs.at(i).second << '\n';
	}
}
void clrPrint(vector<pair<int, string>>& listOfPairs) {
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n ===Your ToDo list!===\n\n";
	if(!listOfPairs.empty())
		printListOfPairs(listOfPairs);
	else{
		cout << "\n You have no items in your list, yet!\n\n";
	}
}
void deleteTask(vector<pair<int, string>>& listOfPairs) {
	int num{};
	clrPrint(listOfPairs);
	cout << "\n Please enter the line number of the task you wish to delete\n -->";
	cin >> num;
	bool check = true;
	while (check) {
		if (listOfPairs.size() >= num) {
			listOfPairs.erase(listOfPairs.begin() + num - 1);
			check = false;
		}
		else {
			cout << "Your number is outside of the range of tasks, try again\n -->";
			cin >> num;
		}
	}
}
void toggle(vector<pair<int, string>>& listOfPairs) {
	int num{};
	clrPrint(listOfPairs);
	cout << "\n Please enter the line number of the task you wish to toggle\n -->";
	cin >> num;
	if (listOfPairs.at(num - 1).first == 0)
		listOfPairs.at(num - 1).first = 1;
	else listOfPairs.at(num - 1).first = 0;
	cout << "\n Your change to task \"" << num << ". "
		<< listOfPairs.at(num - 1).second << "\" has been made...\n";
}
void addListPair(vector<pair<int, string>>& listOfPairs) {
	string task{};
	clrPrint(listOfPairs);

	cout << "\n Please enter your task: \n -->";
	cin.ignore();
	getline(cin, task);

	listOfPairs.emplace_back(0, task);
	cout << "\n Your task has been entered, thank you!\n";
}
void saveListOfPairs(string filename, vector<pair<int, string>>& listOfPairs) {

	ofstream outFILE(filename);
	for (int i = 0; i < listOfPairs.size(); i++) {
		outFILE << listOfPairs.at(i).first << '|' << listOfPairs.at(i).second;
		if (i != (listOfPairs.size() - 1))
			outFILE << '\n';
	}
}
void sortListOfPairs(vector<pair<int, string>>& listOfPairs) {
	sort(listOfPairs.begin(), listOfPairs.end(),
		[](const auto& x, const auto& y) { return x.first < y.first; });
}
void editMenu(vector<pair<int, string>>& listOfPairs) {
	bool loop = true;
	while (loop) {
		char response{};
		cout << "\n (T)oggle task status\n";
		cout << " (D)elete a task\n";
		cout << " (R)eturn to Main Menu\n\n -->";
		cin >> response;
		switch (response) {
		case 't':
		case 'T': {
			toggle(listOfPairs);
			sortListOfPairs(listOfPairs);
			clrPrint(listOfPairs);
			break;
		}
		case 'r':
		case 'R': {
			loop = false;
			break;
		}
		case 'd':
		case 'D': {
			deleteTask(listOfPairs);
			clrPrint(listOfPairs);
			break;
		}
		default: {
			cout << " Menu item not understood, please try again.\n\n";
			break;
		}
		}
	}
}
bool mainmenu(vector<pair<int, string>>& listOfPairs,char** argv) {

	char menu{};
			int num{};

			sortListOfPairs(listOfPairs);
			clrPrint(listOfPairs);

			cout << "\n Please choose from one of the following menu items\n";
			cout << " (A)dd new Task\n";
			cout << " (E)dit your List\n";
			cout << " (S)ave and Quit\n\n -->";
		cin >> menu;
		cout << "\n";

		switch (menu) {
		case 'a':
		case 'A': {
			addListPair(listOfPairs);
			return true;
			break;
		}
		case 'e':
		case 'E': {
			clrPrint(listOfPairs);
			editMenu(listOfPairs);
			return true;
			break;
		}
		case 's':
		case 'S': {
			saveListOfPairs(argv[1], listOfPairs);
			cout << "\n Your file has been saved.  Have a nice day!\n\n\n\n";
			return false;
			break;
		}
		default: {
			cout << " Menu item not understood, please try again.\n\n";
			return true;
			break;
		}
		}
}
int main(int argc, char** argv) {

	vector<pair<int, string>> listOfPairs{};
	if (parseList(argv[1], listOfPairs))
		while (mainmenu(listOfPairs,argv));
	else
	{
		cout << "Bad File Name or empty file";
		return 1;
	}
}