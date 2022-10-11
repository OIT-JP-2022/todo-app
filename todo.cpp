// Contributors: Nathan Green, Nate Castle, Keegan Hauser

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>

using Item = std::pair<std::string, bool>;
using List = std::vector<Item>;

std::ifstream LoadFile(std::string filename);
List ReadFile(std::string filename);
std::string SaveFile(std::string filename);
const void PrintList(const List &list);
void SortList(List &list);
void ToggleItem(std::string task);
void AddItem(List &list);
void DeleteItem(List &list);

int main(int argc, char *argv[]) {

    if(argc != 2)
        return -1;

    List list = ReadFile(argv[1]);
    PrintList(list);
    
}

std::ifstream LoadFile(std::string filename) {
    std::ifstream infile;
    std::string line;
    
    return infile;
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
    for(const auto &item : list) {
        std::cout << std::boolalpha << item.first << ' ' << item.second << '\n';
    }    
}
