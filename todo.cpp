// Contributors: Nathan Green, Nate Castle, Keegan Hauser

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <limits>

using Item = std::pair<std::string, bool>;
using List = std::vector<Item>;

List ReadFile(std::string filename);
void SaveFile(std::string filename, List &list);
const void PrintList(const List &list);
const void PrintPrompt();
bool SelectMenuOption(List &list);
int GetUserInputInt();
std::string GetUserInputStr(std::string prompt);
void SortList(List &list);
void ToggleItem(List &list);
void AddItem(List &list);
void DeleteItem(List &list);
bool ConfirmDecision();
int SelectTask(List &list);

int main(int argc, char *argv[]) {
    List list;
    bool continueLoop = true;
    
    if(argc != 2)
        return -1;

    list = ReadFile(argv[1]);

    do {
        PrintPrompt();
        continueLoop = SelectMenuOption(list);
        SaveFile(argv[1], list);
        std::cout << "\nSaved list to \'" << argv[1] << "\'\n";
    } while(continueLoop);
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

void SaveFile(std::string filename, List &list) {
    std::ofstream outfile;
    outfile.open(filename);

    if(outfile.bad())
        return;
    
    for(const auto &item : list)
        outfile << item.first << ',' << item.second << '\n';

    outfile.close();
}

const void PrintList(const List &list) {
    int i = 1;
    
    std::cout << '\n';
    for(const auto &item : list)
        std::cout << std::boolalpha << std::setw(2) << ' ' << i++ << ". ["
                  << (item.second ? 'X' : ' ') << "] " << item.first << "\n";
}

const void PrintPrompt() {
    std::vector<std::string> menuOptions {
        "1. Add task",
        "2. Delete task",
        "3. Toggle task completeness",
        "4. Sort list",
        "5. Print list",
        "6. Exit"
    };

    for(auto &option : menuOptions)
        std::cout << option << '\n';
}

bool SelectMenuOption(List &list) {
    int optionNumber = GetUserInputInt();

    switch(optionNumber) {
    case 1: {
        AddItem(list);
        break;
    }
    case 2: {
        DeleteItem(list);
        break;
    }

    case 3: {
        ToggleItem(list);
        break;
    }

    case 4: {
        SortList(list);
        break;
    }
    case 5: {
        PrintList(list);
        break;
    }
    case 6: {
        return false;
        break;
    }
    default: {
        std::cout << "Unknown option.\n";
        break;
    }
    }
    return true;
}

int GetUserInputInt() {
    std::string input;
    int num;

    do {
        std::cout << "Input option: ";
        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        try {
            num = std::stoi(input);
        } catch(...) {
            num = -1;
        }
    } while(num <= 0);

    return num;
}

std::string GetUserInputStr(std::string prompt) {
    std::string input;

    std::cout << prompt;
    getline(std::cin, input);

    return input;
}

void AddItem(List &list) {
    std::string taskDescription = GetUserInputStr("Enter task description: ");
    list.emplace_back(taskDescription, false);
    std::cout << "\nAdded task \"" << taskDescription << "\" to list\n";
}

void DeleteItem(List &list) {
    int taskNum = SelectTask(list);
    
    if(ConfirmDecision()) {
        list.erase(list.begin() + taskNum - 1);
        std::cout << "\nDeleted task #" << taskNum << " from the list.\n";
    }
}

bool ConfirmDecision() {
    std::string input = GetUserInputStr("Are you sure? [y/n]: ");

    return tolower(input[0]) == 'y';
}

void ToggleItem(List &list) {
    int taskNum = SelectTask(list);
    Item *item = &list.at(taskNum - 1);
    
    item->second = !(item->second);
    std::cout << "\nTask #" << taskNum << " is now marked as " << (item->second ? "" : "in") << "complete.\n";
}

int SelectTask(List &list) {
    int taskNum;
    
    do {
        PrintList(list);
        taskNum = GetUserInputInt();
    } while(taskNum <= 0 or taskNum > list.size());

    return taskNum;
}

void SortList(List &list) {
    std::sort(
        list.begin(),
        list.end(),
        [](const Item &x, const Item &y) -> bool { return x.second < y.second; }
    );
    std::cout << "\nSorted the list based on completeness.\n";
}
