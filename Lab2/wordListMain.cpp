#include "WordList.hpp"
#include "wordListDefinitions.cpp"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    /*if (argc != 2) {
        std::cerr << "Incorrect amount of files. Please input 1 file.";
    }*/

    //std::string fileName = argv[1];
    std::ifstream file1;

    file1.open(argv[1]);

    char ch;
    std::string result;
    WordList list;
    
    while(file1.get(ch)) {
        if (!std::isspace(ch) && !std::ispunct(ch)) {
            result += ch;
        }
        else {
            list.addWord(result);
            result = "";
        }
    }  
    list.print();

    file1.close();
}