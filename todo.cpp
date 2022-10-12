#include "todo_list.h"

void display_menu(List& new_list, string filename);
void open_file(List& tmp_list, std::string filename);
void save_file(List& tmp_list, std::string filename);

int main(int argc, char** argv) {
    std::cout << "todo: make a todo app..." << '\n';

    if (argc <= 1)
    {
       std::cout << "No Extra Command Line Argument Passed Other Than Program Name. Ex: ./todo filename.txt \n";
        return 0;
    }

    string filename = argv[1];
    
    List new_list;

    open_file(new_list, filename);

    display_menu(new_list, filename);
    
}

void display_menu(List& new_list, string filename){

    int menuSelection;

    do
    {
        cout << "Select from the menu items below \n";
        cout << "1: Add a new to-do item \n";
        cout << "2: delete an item \n";
        cout << "3: change status of item \n";
        cout << "4: sort todo list \n";
        cout << "5: exit (changes will be saved upon exit) \n";
        cin >> menuSelection;

        switch(menuSelection)
        {
            case 1: 
                new_list.new_item();
                break;
            case 2:
                new_list.delete_item();
                break;
            case 3:
                new_list.change_status();
                break;
            case 4:
                new_list.sort_list();
                break;
            case 5:
                save_file(new_list, filename);
                return;
            default:
                cout << "Invalid selection\n";
                return;
        }

    } while (menuSelection != 5);
}

void open_file(List& tmp_list, std::string filename){
    
    std::ifstream infile(filename);

    if(!infile.is_open()){
        std::cout << "File does not exist. Creating new file.\n\n";
        std::ofstream new_file(filename);
    }
    else
    {
        std::string line;
        std::string parsedLine;

        while(!infile.eof())
        {
            if(getline(infile, line)){
                parsedLine = line.substr(line.find(' ') + 1, line.find(" (") - 3); 
                tmp_list.add_item(parsedLine);
            }
        }
        std::cout << "file opened successfully. \n";
        tmp_list.display_list();
    }

}

void save_file(List& tmp_list, std::string filename){
    tmp_list.output_tofile(filename);
}
