#ifndef TODO_ITEM_H
#define TODO_ITEM_H

#include <iostream>
#include <fstream>

#include <string>

using std::string;
using std::cout;
using std::cin;

enum Status{not_started = 1, in_progress, completed };

class todo_Item{

public:
    todo_Item() = default;
    ~todo_Item() = default;
    void set_description(std::string des) { description = des; }
    string get_description() { return description; }
    void set_itemID(int id) { item_id = id; }
    int get_itemID() { return item_id; }
    void print_item() { cout << item_id << ": " << description << " (" << print_status() << ")\n"; }
    string print_status();
    void change_status();
    bool get_status() { return completed;}

private:
    std::string description;
    bool completed = false;
    int item_id = 1;
};

string todo_Item::print_status(){
    if (completed)
        return "completed";
    else
      return "not started";   
}

void todo_Item::change_status(){
  if(completed)
    completed = false;
  else
    completed = true;
}

#endif