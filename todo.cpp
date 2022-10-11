// Contributors: Nathan Green, Nate Castle, Keegan Hauser

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using List = std::vector<std::pair<std::string, bool>>;

std::ifstream LoadFile(std::string filename);
std::string SaveFile(std::string filename);
const void PrintList(List list);
void SortList(List &list);
void ToggleItem(std::string task);
void AddItem(List &list);
void DeleteItem(List &list);


int main(int argc, char *argv[]) {

    if(argc != 2)
        return;

    
}
