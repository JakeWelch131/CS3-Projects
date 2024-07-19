#include <iostream>
#include <fstream>
#include <string>

int compareStrings(std::string, std::string);
std::string spaceString(int, int, std::string);

int main(int argc, char *argv[]) {

    if (argc == 3) {                                                                            // only run if there were 2 files inputted on command line                          
        std::ifstream file1;
        std::ifstream file2;

        std::string fileName = argv[1];
        std::string string1 = "";
        std::string string2 = "";

        file1.open(argv[1]);
        file2.open(argv[2]);

        int lineNumber = 1;
        
        while(!(file1.eof() && file2.eof())) {                                                  // loop only while both file1 and file2 are not at end of file
           
            if(file1.eof()) {                                                                   // if we are at the end of file1, then make strign1 empty
                string1 = "";      
            } 
            else {
                getline(file1, string1);                                                        // if not at end of file1, then get the line and assign it to string1
            }
            
            if(file2.eof()) {                                                                   // if we are at the end of file2, then make string2 empty
                string2 = "";             
            }
            else {
                getline(file2, string2);                                                        // if not at end of file2, then get the line and assign it to string2
            }

          

            if(string1 != string2) {
                int charPosition = compareStrings(string1, string2);                            // invokes compareStrings to find at which character the two strings differ
                std::string result = spaceString(charPosition, lineNumber, fileName);           // spaceString uses the position found in compareStrings, the length of the line number, and the length of the filename 
                std::cout << argv[1] << ": " << lineNumber << ": " << string1 << std::endl;     // to determine how many spaces to generate to properly insert the '^'
                std::cout << argv[2] << ": " << lineNumber << ": "  << string2 << std::endl;
                std::cout << result;
                if (!(file1.eof() && file2.eof())) {
                    std::cout << std::endl;                                                     // Add newline if it's not the last line
                }
            }
            ++lineNumber;                                                                       // increment lineNumber as we have moved on to a new line to read
        }
    file1.close();
    file2.close();
    }
    else {
        std::cerr << "Error: incorrect number of files entered on command line";
        exit(1);
    }


}

int compareStrings(std::string string1, std::string string2) {                                  // compareStrings is used to iterate through two strings and find at what position in the string array
    int counter = 0;                                                                            // the two strings are different 
    while(counter != string1.length() || counter != string2.length()) {                         // while we have not exceeded the length of the string
        char char1 = string1[counter];
        char char2 = string2[counter];
        if (char1 != char2) {                                                                   // return the counter if the two characters are not equal
            return counter;
        }
        ++counter;
    }
}

std::string spaceString(int charPosition, int lineNumberDigits, std::string inputFile) {        // spaceString determines the amount of spaces nneded before the '^' in order to show the difference in the two strings
    std::string numberToString = std::to_string(lineNumberDigits);                              // convert the lineNumber to a string in order to find how many characters it takes 
    int digits = numberToString.size();
    int fileSpaces = inputFile.size();                                                          // takes the size of the fileName string and saves to an int
    std::string result = "    ";                                                                // initial number of spaces based on spaces and ':'s needed in output
    for (int i = 0; i < charPosition + digits + fileSpaces; ++i) {                              // adds spaces to the result sting based on total number of spaces needed
        result += " ";
    }
    return result + "^";
}