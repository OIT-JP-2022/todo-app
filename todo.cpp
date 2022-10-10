#include "todo.h"

void open_file(std::ifstream& infile, std::string filename);

int main(int argc, char** argv) {
    std::cout << "todo: make a todo app..." << '\n';

    if (argc <= 1)
    {
       std::cout << "No Extra Command Line Argument Passed Other Than Program Name. Ex: ./todo filename.txt \n";
        return 0;
    }

    string filename = argv[1];
    std::ifstream ifile;
    std::ofstream ofile;

    open_file(ifile,filename);

    std::vector<todo_Item> new_list;

    // TODO: 
    // 1: Menu a new to-do item
    // 2: delete an item
    // 3: change status of item.
    // 4: exit (changes will be saved upon exit)

    //after select 1
    todo_Item item;
    string temp_des;
    cout << "Enter a new item description: ";
    cin >> temp_des;    
    item.set_description(temp_des);
    if (new_list.size() != 0){
      item.set_itemID();
    }
    new_list.push_back(item);
    new_list[0].print_item();
}

void open_file(std::ifstream& infile, std::string filename){
    infile.open(filename);

    //to create file
    if(!infile.is_open()){
        std::cout << "file does not exist. \n";
        std::ofstream new_file(filename);
    }
    else
    {
        // open file, display file
        std::string line;

        while(!infile.eof())
        {
            std::getline(infile, line);
            std::cout << line;
        }
        std::cout << "file opened successfully. \n";
    }

}


