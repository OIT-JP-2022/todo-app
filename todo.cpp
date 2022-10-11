#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <string.h>
using namespace std;
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
 class toDo
{
public:
toDo(){

	this->completeness = 0;
	this->description = "";
 }

//toDo::toDo(string c, string d){
//this->completeness = stoi(c);
//this->description = d;
//}

void addDescription(string y){
	description = description + y;
}
void addCompleteness(string b){
        completeness = stoi(b);
}

void clear(){
description = "";
completeness = 0; //eeeeee
}


int completeness;
string description;
};



 class toDoList
{
public:
toDoList() {theList = {}; }

~toDoList(){
while(theList.size() != 0){
//delete theList.front();
theList.pop_front();
}

}

void printList(){
for(auto const& i: theList)// = theList.cbegin();i != theList.cend(); ++i){
{
cout << i.description << "\n";
cout << i.completeness << "\n"; 
}
}
void toDoAdder(toDo x) {

theList.push_front(x); //This adds 'x' (toDo)  to our toDo list (theList)

	          }
void loadList(string y){ //y is our file name variable
string desc;
string comp;

toDo myToDo;

cout << y << "\n";
string filename = y;
string words;
string word;
ifstream infile(filename);
if(!infile.is_open()){
	cout << "cannot open file " <<  filename << "\n";

}
toDo* item = new toDo();

while(infile >> word){
if(strcmp(word.c_str(), "Start:") == 0 && words.length() != 0){ //if word is start and nothing in list
comp = words;
//myToDo.addCompleteness(words); // Complete?
toDo* item = new toDo();
item->addDescription(desc);
item->addCompleteness(comp);

theList.emplace_back(item); //push to the bacc of myToDo
desc = "";
comp = "";
//myToDo.clear(); //clear desc
}
else if(strcmp(word.c_str(), "Start:") == 0 && words.length() == 0){
//myToDo.addCompleteness(words); //do nothing

//toDo* item = new toDo();
//item.addDescription(desc);
item.addCompleteness(comp);

theList.emplace_back(myToDo);

}

else if(strcmp(word.c_str(), "Completeness:") == 0){
desc = words;
//myToDo.addDescription(words); //adds missing words
words.clear(); //clear current list of words
}

else{
words + " " + word; //if normal word place at the back of list
}
}

}
std::list<toDo> theList = {};


};

int main(int argc, char** argv) {

cout << "You have entered " << argc << " arguments: " << "\n";
for(int i = 0; i <  argc; ++i)
	cout << argv[i] << "\n";

toDoList myList; //create instance of list
if(strcmp(argv[1],  "-l") == 0) { //check if -l
	myList.loadList(argv[2]);

 }

myList.printList();

// std::cout << "todo: make todo app THIS IS JASON!..." << '\n';
}


