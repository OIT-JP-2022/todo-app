#ifndef TODO_LIST_H
#define TODO_LIST_H
#include "todo_item.h"

#include <vector>

class List{
public:
    List() = default;

    void new_item();
    void delete_item();
    void add_item(string des);
    void change_status();
    void sort_list();
    void display_list(); 
    int get_size();
    todo_Item get_item(int index);
    void output_tofile(std::string filename);
    
private:
    std::vector<todo_Item> tmp_list;
};

void List::new_item(){

    string temp_des;
    cin.ignore();
    cout << "Enter a new item description: ";
    getline(cin, temp_des); 
    add_item(temp_des);
    display_list();
}

void List::delete_item()
{
    int itemNum;
    cout << "Which item do you want delete: ";
    cin >> itemNum;
    std::vector<todo_Item>::iterator it = tmp_list.begin() + itemNum; 

    if(itemNum > 0 && itemNum <= tmp_list.size())
        tmp_list.erase(it - 1);
    else
        cout << "Invalid selection\n";
    for(auto i = 0; i < tmp_list.size(); i++)
        tmp_list[i].set_itemID(i + 1);
    display_list();
}

void List::change_status(){
    int itemSelect;
    cout << "Select item to change status: ";
    cin >> itemSelect;
    tmp_list[itemSelect - 1].change_status();
    display_list();
}
int List::get_size() { return tmp_list.size(); }

void List::sort_list(){
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
    display_list();
}
void List::add_item(string des){
    todo_Item item;
    string description = des;
    item.set_description(description);
    if (tmp_list.size() != 0){
      item.set_itemID(tmp_list.size() + 1);
    }
    tmp_list.push_back(item);
}

void List::display_list(){ 
    cout << "\n======================================\n";
    cout << "Your list: \n";
    for(auto i: tmp_list)
        i.print_item();
    cout << "======================================\n\n";
}

void List::output_tofile(std::string filename){
    std::ofstream ofile(filename);
    for (int i = 0; i < tmp_list.size(); i++){
        ofile << (tmp_list[i]).get_itemID() << ": " << tmp_list[i].get_description() << " (" << tmp_list[i].print_status() << ")\n";
    }
    ofile.close(); 
}

#endif