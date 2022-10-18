#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <list>

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
using std::list;


 class Task {

   private:
	vector<Task> _SubTasks;


	public:
	bool _IsComplete;
	string _Task;
	Task() = default;
	Task(bool Complete, string task)
	{
	     _IsComplete = Complete; 
	    _Task = task;
	};
	auto printSub(){ 
		int i{};
		cout << "-Incomplete: \n";
		int size = _SubTasks.size();
		for (i = 0; i < size && _SubTasks.at(i)._IsComplete == 0; i++)
		{
				cout << "-"<< i + 1<< ". " << _SubTasks.at(i)._Task << '\n';
		}
		if (i != size)
			cout << "\n-Complete: " << "\n";
		for (i = i; i < size; i++)
		{
				cout << "-"<< i + 1<< ". " << _SubTasks.at(i)._Task << '\n';
		}
	}; 
	auto print(){ 
		cout << _Task << '\n';
		if (_SubTasks.size() > 0){
			cout << "Sub tasks:\n";
		       printSub();	
		}
	}; 
	auto addSubTask(Task task)
	{	
		_SubTasks.push_back(task);	
	};
};
auto sortListOfPairs(vector<Task>& listOfPairs) {
	sort(listOfPairs.begin(), listOfPairs.end(),
		[](const auto& x, const auto& y) { return x._IsComplete < y._IsComplete; });
};
auto printTasks(vector<Task>& listOfPairs) {
		int i{};
		cout << "Incomplete: \n";
		int size = listOfPairs.size();
		for (i = 0; i < size && listOfPairs.at(i)._IsComplete == 0; i++)
		{
				cout << i + 1<< ". ";
				listOfPairs.at(i).print();
		}

		if (i != size)
			cout << "\nComplete: \n";
		for (i = i; i < size; i++)
		{
				cout << i + 1<< ". ";
				listOfPairs.at(i).print();
		}
	}
	auto clrPrint(vector<Task>& listOfPairs) {
		cout << "\n\n\n	===Your ToDo list!===\n\n";
		if(!listOfPairs.empty()) {
			sortListOfPairs(listOfPairs);
			printTasks(listOfPairs);
		}
		else
		{
			cout << "\n You have no items in your list at the moment!";
			cout << "\n\n     ===> Editing is disabled <===\n\n";
		}
	}
//void
auto addSubTask(vector<Task>& listOfPairs){
	while(1){
		cout << "what task number would you like to add a subtask to?";
		string num{};
		cin.ignore();
		getline(cin, num);
		string task;
		cout << "Enter task: ";
		getline(cin,task);
		Task Task(0,task);
		if(stoi(num) <= listOfPairs.size()){
			listOfPairs.at(stoi(num) - 1).addSubTask(Task); 
			break;
		}	
		else
			cout<<"Outside of Range!\n";
	}
}


//Bool
auto parseList(string filename, vector<Task>& listOfPairs) {
	string task{};
	string buffer{};
	string complete{};

	ifstream inFILE(filename, std::ios::in);
	bool returnCheck = true;
	char firstChar = inFILE.peek();
	if (inFILE.is_open())
	{
		cout << "Writing from File..\n";
		for(string line {}; getline(inFILE, buffer);)
		{
			complete = buffer.substr(0,1);	
			task = buffer.substr(2, buffer.size()-2);
			int num = stoi(complete);
			listOfPairs.emplace_back(static_cast<bool>(num),task);
		}
		return true;
	}
	else return false;
}


//void
auto deleteTask(vector<Task> & listOfPairs) {
	int num{};
	clrPrint(listOfPairs);
	cout << "\n Please enter the line number of the task you wish to delete\n -->";
	cin >> num;
	bool check = true;
	while (check) 
	{
		if (listOfPairs.size() >= num) 
		{
			listOfPairs.erase(listOfPairs.begin() + num - 1);
			check = false;
		}
		else 
		{
			cout << "Your number is outside of the range of tasks, try again\n -->";
			cin >> num;
		}
	}
}
//void
auto toggle(vector<Task>& listOfPairs) {
	int num{};
	clrPrint(listOfPairs);	
	cout << "\n Please enter the line number of the task you wish to toggle\n -->";
	cin >> num;
	if (listOfPairs.size() >= num)
	{
		if (listOfPairs.at(num - 1)._IsComplete == 0){
			listOfPairs.at(num - 1)._IsComplete = 1;
		}
		else{
			listOfPairs.at(num - 1)._IsComplete = 0;
		}
		cout << "\n Your change to task \"" << num << ". "
		<< listOfPairs.at(num - 1)._Task << "\" has been made...\n";
	}
	else{
		cout << "\n Your choice is out of the range of tasks\n";
	}
}
//void
auto addListPair(vector<Task>& listOfPairs) {
	string task{};
	clrPrint(listOfPairs);
	cout << "\n Please enter your task: \n -->";
	cin.ignore();
	getline(cin, task);
	listOfPairs.emplace_back(0, task);
	cout << "\n Your task \""<</*( listOfPairs.end()-1) -> _Task*/ task <<"\"  has been entered, thank you!\n";
}
//void
auto saveListOfPairs(string filename, vector<Task>& listOfPairs) {
	ofstream outFILE(filename);
	for (int i = 0; i < listOfPairs.size(); i++) 
	{
		outFILE << listOfPairs.at(i)._IsComplete << '|' << listOfPairs.at(i)._Task;
		if (i != (listOfPairs.size() - 1))
			outFILE << '\n';
	}
}

//void
auto editMenu(vector<Task> & listOfPairs) {
	bool loop = true;
	
	while (loop) 
	{
		char response{};
		cout << "\n (T)oggle task status\n";
		cout << " (A)dd SubTask\n";
		cout << " (D)elete a task\n";
		cout << " (R)eturn to Main Menu\n\n -->";
		cin >> response;
		switch (response) 
		{
		case 't':
		case 'T': {
			toggle(listOfPairs);
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
		case 'a':
		case 'A': { 
			addSubTask(listOfPairs);
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
//void
auto mainmenu(vector<Task> & listOfPairs,char** argv) {
	char menu{};
		int num{};
		clrPrint(listOfPairs);

		cout << "\n Please choose from one of the following menu items\n";
		cout << " (A)dd new Task\n";
		cout << " (E)dit your List\n";
		cout << " (S)ave and Quit\n\n -->";
		cin >> menu;
		cout << "\n";
		switch (menu) 
		{
			case 'a':
			case 'A': {
				addListPair(listOfPairs);
				return true;
				break;
			}
			case 'e':
			case 'E': {
				if(!listOfPairs.empty()){
					clrPrint(listOfPairs);	
					editMenu(listOfPairs);
				}
				else{
					cout << "\n Your list is empty, you may not edit\n";
				}	
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
	vector<Task> listOfPairs{};
	if (parseList(argv[1], listOfPairs))
		while (mainmenu(listOfPairs,argv));
	else
	{
		cout << "\n\n File is not formatted correctly.\n";
		cout << " Please refer to the ReadMe file for proper formatting!\n\n";
		return 1;
	}
}
