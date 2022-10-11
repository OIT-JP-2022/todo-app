// Contributors: Nathan Green, Nate Castle, Keegan Hauser

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>
#include <numeric>

using Item = std::pair<std::string, bool>;
using List = std::vector<Item>;

List ReadFile(std::string filename);
std::string SaveFile(std::string filename);
const void PrintList(const List &list);
const void PrintPrompt();
void SelectMenuOption(List &list);
int GetUserInputInt();
std::string GetUserInputStr();
void SortList(List &list);
void ToggleItem(std::string task);
void AddItem(List &list);
void DeleteItem(List &list);

int main(int argc, char *argv[]) {

    if(argc != 2)
        return -1;

    List list = ReadFile(argv[1]);
    
    PrintPrompt();
    SelectMenuOption(list);

    PrintList(list);
}

List ReadFile(std::string filename) {
    List list;
    std::string token;
    std::ifstream infile;

    infile.open(filename);
    
    while(infile.peek() != EOF) {
        Item item;
        getline(infile, token, ',');
        item.first = token;
        getline(infile, token);
        std::istringstream(token) >> item.second;
        list.push_back(item);
    }
    return list;
}

const void PrintList(const List &list) {
    for(const auto &item : list)
        std::cout << std::boolalpha << item.first << ' ' << item.second << '\n';    
}

const void PrintPrompt() {
    std::vector<std::string> menuOptions {
        "1. Add task",
        "2. Delete task",
        "3. Toggle task completeness",
        "4. Sort list",
        "5. Save list"
    };

    for(auto &option : menuOptions)
        std::cout << option << '\n';
}

void SelectMenuOption(List &list) {
    int optionNumber = GetUserInputInt();

    switch(optionNumber) {
    case 1: {
        AddItem(list);
        break;
    }
    case 2: {
        break;
    }

    case 3: {
        break;
    }

    case 4: {
        break;
    }

    case 5: {
        break;
    }

    default: {
        break;
    }
    }
}

int GetUserInputInt() {
    std::string input;
    int num;

    do {
        std::cout << "Input option: ";
        std::cin >> input;
        
        try {
            num = std::stoi(input);
        } catch(...) {
            num = -1;
        }
    } while(num <= 0);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return num;
}

std::string GetUserInputStr() {
    std::string input;

    std::cout << "Input task name: ";
    getline(std::cin, input);

    return input;
}

void AddItem(List &list) {
    std::string taskDescription = GetUserInputStr();
    list.emplace_back(taskDescription, false);
}
