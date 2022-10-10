#include <iostream>
#include <fstream>
using namespace std;
std::ifstream inFILE;

bool mainmenu();
void openFile(std::ifstream& inFILE, char** argv);

int main(int argc, char** argv) {
	system("clear");
	
	openFile(inFILE, argv);
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
		//stub call to new task
		system("pause");
		system("clear");
		return true;
		break;
	case 'v':
	case 'V':
		//call to view the list
		system("pause");
		system("clear");
		return true;
		break;
	case 'q':
	case 'Q':
		return false;
		break;
	default:
		cout << " Menu item not understood, please try again.\n\n";
		system("pause");
		system("clear");
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
		cin.clear();
		cin.get();
		system("clear");
	}
	cin.clear();
	cin.get();
	system("clear");
}