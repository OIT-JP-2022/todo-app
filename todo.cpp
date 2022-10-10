#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <vector>

using std::string;
using std::cout;
using std::cin;

void open_file(std::ifstream& infile, std::string filename);
enum Status{not_started = 1, in_progress, completed };

class todo_Item{

public:
    todo_Item() = default;
    ~todo_Item() = default;
    void set_description(std::string des) { description = des; }
    void set_itemID() { item_id++; }
    void print_item() { cout << item_id << ": " << description << "(" << m_status << ")\n"; }
    void set_status(int status);

    //getters/setters

private:
    std::string description;
    std::string m_status = "not started";
    int item_id = 1;
};

void todo_Item::set_status(int status){
    switch (status){
      case 1: m_status = "not started";
        break;
      case 2: m_status = "in progress";
        break;
      case 3: m_status = "completed";
        break;  
    }
}


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

    //Menu
    // welcome
    // 1: Create a new to-do item
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


