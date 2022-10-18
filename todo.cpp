#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <list>
#include <iostream>
#include <vector>
#include <string>


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
	//Sorts task based on completed
	auto sortTasks(vector<Task>& tasks) {
		sort(tasks.begin(), tasks.end(),
			[](const auto& x, const auto& y) { return x._IsComplete < y._IsComplete; });
	};
	//print all sub tasks
	auto printSub() {
		int i{};
		cout << "-Incomplete: \n";
		int size = _SubTasks.size();
		for (i = 0; i < size && _SubTasks.at(i)._IsComplete == 0; i++)
		{
			cout << "-" << i + 1 << ". " << _SubTasks.at(i)._Task << '\n';
		}
		if (i != size)
			cout << "\n-Complete: " << "\n";
		for (i = i; i < size; i++)
		{
			cout << "-" << i + 1 << ". " << _SubTasks.at(i)._Task << '\n';
		}
	};
	//print task then call print sub tasks
	auto print() {
		cout << _Task << '\n';
		if (_SubTasks.size() > 0) {
			cout << "Sub tasks:\n";
			printSub();
		}
	};
	//Add Sub task
	auto addSubTask(Task task)
	{
		_SubTasks.push_back(task);
	};
	//Procedure to toggle a sub task
	auto toggleSubClass()
	{
		cout << "\n\n\n\n";
		print();
		string buffer{};
		cout << "\n Please enter the line number of the sub task you wish to toggle\n -->";
		getline(cin, buffer);
		int num = stoi(buffer);

		if (_SubTasks.size() >= num)
		{
			auto& ref = _SubTasks.at(num - 1);

			if (ref._IsComplete == 0) {
				ref._IsComplete = 1;
			}
			else {
				ref._IsComplete = 0;
			}

			cout << "\n Your change to task \"" << num << ". "
				<< ref._Task << "\" has been made...\n";
		}
		else {
			cout << "\n Your choice is out of the range of tasks\n";
		}
		sortTasks(_SubTasks);
	};
	//Delete sub task
	auto deleteTask()
	{
		print();
		int num{};
		cout << "\n Please enter the line number of the sub task you wish to delete\n -->";
		cin >> num;
		while (1)
		{
			if (_SubTasks.size() >= num)
			{
				_SubTasks.erase(_SubTasks.begin() + num - 1);
				break;
			}
			else
			{
				cout << "Your number is outside of the range of tasks, try again\n -->";
				cin >> num;
			}
		}
	};
	//returns task and subtasks as string to be saved
	auto saveTask()
	{
		string outPut{};
		if (_IsComplete == false)
			outPut = outPut + "0" + '|' + _Task;
		else
			outPut = outPut + "1" + '|' + _Task;
		for (int i = 0; i < _SubTasks.size(); i++)
		{
			outPut = outPut + '\n';
			if (_SubTasks.at(i)._IsComplete == false)
				outPut = outPut + "-0" + '|' + _SubTasks.at(i)._Task;
			else
				outPut = outPut + "-1" + '|' + _SubTasks.at(i)._Task;
		}
		return outPut;
	}
};
//go through tasks vector and tell each member to print itself
auto printTasks(vector<Task>& tasks) {
		int i{};
		cout << "Incomplete: \n";
		int size = tasks.size();
		for (i = 0; i < size && tasks.at(i)._IsComplete == 0; i++)
		{
				cout << i + 1<< ". ";
				tasks.at(i).print();
		}

		if (i != size)
			cout << "\nComplete: \n";
		for (i = i; i < size; i++)
		{
				cout << i + 1<< ". ";
				tasks.at(i).print();
		}
	}
//sorts tasks by completness then calls print function
auto clrPrint(vector<Task>& tasks) {
	Task task;
	cout << "\n\n	===Your ToDo list!===\n\n";
	if (!tasks.empty()) {
		task.sortTasks(tasks);
		printTasks(tasks);
	}
	else
	{
		cout << "\n You have no items in your list at the moment!";
		cout << "\n\n     ===> Editing is disabled <===\n\n";
	}
}

//Procedure to add a sub task under a task
auto addSubTask(vector<Task>& tasks){
	while(1){
		cout << "\nEnter task number to add sub task: ";
		string num{};
		cin.ignore();
		getline(cin, num);
		string task;
		cout << "Enter sub task: ";
		getline(cin,task);
		Task Task(0,task);
		if(stoi(num) <= tasks.size()){
			tasks.at(stoi(num) - 1).addSubTask(Task); 
			break;
		}	
		else
			cout<<"Outside of Range!\n";
	}
}
//inputs file from argv into a Task vector
auto parseList(string filename, vector<Task>& tasks) {
	string task{};
	string buffer{};
	string complete{};

	ifstream inFILE(filename, std::ios::in);
	bool returnCheck = true;
	char firstChar = inFILE.peek();
	if (inFILE.is_open())
	{
		cout << "Fetching data from "<< filename <<"...\n";
		for(string line {}; getline(inFILE, buffer);)
		{
			if (buffer.substr(0, 1) == "-") {
				complete = buffer.substr(1, 1);
				task = buffer.substr(3, buffer.size() - 3);
				int num = stoi(complete);

				tasks.at(tasks.size() - 1).addSubTask({ static_cast<bool>(num), task });
			}
			else {
				complete = buffer.substr(0, 1);
				task = buffer.substr(2, buffer.size() - 2);
				int num = stoi(complete);
				tasks.emplace_back(static_cast<bool>(num), task);
			}
		}
		return true;
	}
	else return false;
}
//Procedure to delete task
auto deleteTask(vector<Task>& tasks) {
	int num{};
	string buffer{};
	cout << "\n Please enter the line number of the task you wish to delete\n -->";
	cin >> num;
	while (1)
	{
		if (tasks.size() >= num)
		{
			cout << "Delete sub task? (y/n)\n-->";
			cin.ignore();
			getline(cin, buffer);
			if (buffer[0] == 'y' || buffer[0] == 'Y')
				tasks.at(num - 1).deleteTask();
			else {
				tasks.erase(tasks.begin() + num - 1);
			}
			break;
		}
		else
		{
			cout << "Your number is outside of the range of tasks, try again\n -->";
			cin >> num;
		}
	}
}
//Procedure to toggle a task completness
auto toggle(vector<Task>& tasks) {
	string buffer{};
	cout << "\n Please enter the line number of the task you wish to toggle\n -->";
	cin.ignore();
	getline(cin, buffer);
	int num = stoi(buffer);

	if (tasks.size() >= num)
	{
		cout << "\nToggle \n(T)ask \n(S)ubtask:\n-->";
		getline(cin, buffer);
		cout << '\n';

		if (buffer == "T" || buffer == "t")
		{
			auto& ref = tasks.at(num - 1);

			if (ref._IsComplete == 0) {
				ref._IsComplete = 1;
			}
			else {
				ref._IsComplete = 0;
			}

			cout << "\n Your change to task \"" << num << ". "
				<< ref._Task << "\" has been made...\n";
		}
		else
		{
			tasks.at(num - 1).toggleSubClass();
		}
	}
	else {
		cout << "\n Your choice is out of the range of tasks\n";
	}
}
//Procedure to add task
auto addTask(vector<Task>& tasks) {
	string task{};
	cout << "\n Please enter your task: \n -->";
	cin.ignore();
	getline(cin, task);
	tasks.emplace_back(0, task);
	cout << "\n Your task \""<< task <<"\"  has been entered, thank you!\n";
}
//Write Tasks to file
auto saveTasks(string filename, vector<Task>& tasks) {
	ofstream outFILE(filename);
	for (int i = 0; i < tasks.size(); i++) 
	{
		outFILE << tasks.at(i).saveTask();
		if (i < (tasks.size() - 1))
			outFILE << '\n';

	}

	cout << "\n Your file has been saved.  Have a nice day!\n\n\n\n";
}

auto locateItem(vector<Task> & tasks) {
	cout << "\nLocate text\n#";
	string buffer{};
	cin.ignore();
	getline(cin,buffer);
	int taskLocation = 0;
	for( auto & task:tasks)
	{
		if (task._Task.find(buffer) != std::string::npos)
			break;
			
		taskLocation++;
	}
	cout << "Found at task " << taskLocation + 1 << " "; tasks.at(taskLocation).print();

}

//Menu to edit list:toggle, delete, add sub task
auto editMenu(vector<Task> & tasks) {
	if (!tasks.empty()) {
		bool loop = true;

		while (loop)
		{
			clrPrint(tasks);
			char response{};
			cout << "\n (T)oggle task status\n";
			cout << " (A)dd SubTask\n";
			cout << " (D)elete a task\n";
			cout << " (R)eturn to Main Menu\n\n -->";
			cin >> response;
			clrPrint(tasks);
			switch (response)
			{
			case 't':
			case 'T': {
				toggle(tasks);
				break;
			}
			case 'a':
			case 'A': {
				addSubTask(tasks);
				break;
			}
			case 'd':
			case 'D': {
				deleteTask(tasks);
				break;
			}
			case 'r':
			case 'R': {
				loop = false;
				break;
			}
			default: {
				cout << " Menu item not understood, please try again.\n\n";
				break;
			}
			}
			clrPrint(tasks);
		}
	}
	else {
		cout << "\n Your list is empty, you may not edit\n";
	}
}
//Menu to add task, edit list, or save and quit
auto mainmenu(vector<Task> & tasks,char** argv) {
	char menu{};
		int num{};
		clrPrint(tasks);

		cout << "\n Please choose from one of the following menu items\n";
		cout << " (A)dd new Task\n";
		cout << " (E)dit your List\n";
		cout << " (L)ocate list item\n";
		cout << " (S)ave and Quit\n\n -->";
		cin >> menu;
		cout << "\n";
		clrPrint(tasks);
		switch (menu) 
		{
			case 'a':
			case 'A': {
				addTask(tasks);
				return true;
				break;
			}
			case 'e':
			case 'E': {
				editMenu(tasks);
				return true;
				break;
			}
			case 'l':
		 	case 'L':{
				 locateItem(tasks);
 				 return true;
				 break;
				 }
			case 's':
			case 'S': {
				saveTasks(argv[1], tasks);
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
//main simple vector creation, parse from file, and menu startup
int main(int argc, char** argv) {
	vector<Task> tasks{};
	if (parseList(argv[1], tasks))
		while (mainmenu(tasks, argv));
	else
	{
		cout << "\n\n File is not formatted correctly.\n";
		cout << " Please refer to the ReadMe file for proper formatting!\n\n";
		return 1;
	}
}
