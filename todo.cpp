#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::string;

std::fstream openFile(std::string filename){
    std::fstream File;
    File.open(filename);
    if(!File){ //no file, make one
      std::ofstream File(filename); //no file, make one
    } 
    return File;

} 

int main(int argc, char *argv[]) {

  try {
    std::fstream todoFile = argc >= 2 ? openFile(argv[1]) : openFile("todo.txt");
  }catch (const string& ex){
    cout << ex;
  }
  
  

  // if (todoFile.is_open()){
  //   cout << "It worked\n";
  // }else {
  //   cout << "It didint worked\n";
  // }
  cout << "\n\n";
  return 0;
}
