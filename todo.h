#include <iostream>
#include <fstream>
#include <vector>
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
    void set_itemID() { item_id++; }
    void print_item() { cout << item_id << ": " << description << " (" << m_status << ")\n"; }
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