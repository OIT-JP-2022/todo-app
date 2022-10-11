#include "todo.h"

void new_item(std::vector<todo_Item>& tmp_list);
void open_file(std::vector<todo_Item>& tmp_list, std::string filename);
void print_list(std::vector<todo_Item> tmp_list);
void delete_item(std::vector<todo_Item>& tmp_list);
void save_file(std::vector<todo_Item>& tmp_list, std::string filename);
void add_item(std::vector<todo_Item>& tmp_list, string& des);
void change_status(std::vector<todo_Item>& tmp_list);
void sort_list(std::vector<todo_Item>& tmp_list);

int main(int argc, char** argv) {
    std::cout << "todo: make a todo app..." << '\n';

    if (argc <= 1)
    {
       std::cout << "No Extra Command Line Argument Passed Other Than Program Name. Ex: ./todo filename.txt \n";
        return 0;
    }

    string filename = argv[1];
    int menuSelection;
    std::vector<todo_Item> new_list;

    open_file(new_list, filename);

    // TODO: 
    // 1: Menu a new to-do item
    // 2: delete an item
    // 3: change status of item.
    // 4: exit (changes will be saved upon exit)

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
                new_item(new_list);
                break;
            case 2:
                delete_item(new_list);
                break;
            case 3:
                change_status(new_list);
                break;
            case 4:
                sort_list(new_list);
                break;
            case 5:
                save_file(new_list, filename);
                return 0;
            default:
                cout << "Invalid selection\n";
        }

    } while (menuSelection != 5);
    
    //after select 1
    new_item(new_list);

    //after select 2
    std::vector<todo_Item>::iterator it;
    int itemNum;
    cout << "Which item do you want delete: ";
    cin >> itemNum;
    //TODO: check that number is in bounds
    new_list.erase(it + itemNum - 1);
}

void open_file(std::vector<todo_Item>& tmp_list, std::string filename){
    
    std::ifstream infile(filename);

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
            if(std::getline(infile, line)){
                cout << line << '\n';
                // add_item(tmp_list, line);
            }
        }
        std::cout << "file opened successfully. \n";
        print_list(tmp_list);
    }

}

void add_item(std::vector<todo_Item>& tmp_list, string& des){
    todo_Item item;
    item.set_description(des);
    if (tmp_list.size() != 0){
      item.set_itemID(tmp_list.size() + 1);
    }
    tmp_list.push_back(item);
}

void new_item(std::vector<todo_Item>& tmp_list){
    todo_Item item;
    string temp_des;
    cin.ignore();
    cout << "Enter a new item description: ";
    getline(cin, temp_des); 
    //TODO: make this into a member function if time   
    item.set_description(temp_des);
    if (tmp_list.size() != 0){
      item.set_itemID(tmp_list.size() + 1);
    }
    tmp_list.push_back(item);
    print_list(tmp_list);
}

void delete_item(std::vector<todo_Item>& tmp_list)
{
    int itemNum;
    cout << "Which item do you want delete: ";
    cin >> itemNum;
    std::vector<todo_Item>::iterator it = tmp_list.begin() + itemNum; 
    //TODO: check that number is in bounds
    if(itemNum > 0 && itemNum <= tmp_list.size())
        tmp_list.erase(it - 1);
    else
        cout << "Invalid selection\n";
    for(auto i = 0; i < tmp_list.size(); i++)
        tmp_list[i].set_itemID(i + 1);
    print_list(tmp_list);
}

void save_file(std::vector<todo_Item>& tmp_list, std::string filename){
    for (int i = 0; i < tmp_list.size(); i++){
        std::ofstream ofile(filename);
        ofile << tmp_list[i].get_description() << " " << tmp_list[i].print_status() << std::endl;;
        ofile.close(); 
    }

}

void change_status(std::vector<todo_Item>& tmp_list){
    int itemSelect;
    cout << "Select item to change status: ";
    cin >> itemSelect;
    tmp_list[itemSelect - 1].change_status();
    print_list(tmp_list);
}

void print_list(std::vector<todo_Item> tmp_list){ 
    cout << "\n======================================\n";
    cout << "Your list: \n";
    for(auto i: tmp_list)
        i.print_item();
    cout << "======================================\n\n";
}

void sort_list(std::vector<todo_Item>& tmp_list){
    for (auto i = 0; i < tmp_list.size(); i++){
        if(tmp_list[i].get_status() == true)
        { 
            tmp_list.push_back(tmp_list[i]);
            tmp_list[i].change_status();
            std::vector<todo_Item>::iterator it = tmp_list.begin() + i;
            tmp_list.erase(it);
        }
        
    }
    for(auto i = 0; i < tmp_list.size(); i++)
        tmp_list[i].set_itemID(i + 1);
    print_list(tmp_list);
}