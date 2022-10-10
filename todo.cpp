#include <iostream>

int main() {
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
		system("cls");
		return true;
		break;
	case 'v':
	case 'V':
		//call to view the list
		system("pause");
		system("cls");
		return true;
		break;
	case 'q':
	case 'Q':
		return false;
		break;
	default:
		cout << " Menu item not understood, please try again.\n\n";
		system("pause");
		system("cls");
		return true;
		break;
		}
	}
}
