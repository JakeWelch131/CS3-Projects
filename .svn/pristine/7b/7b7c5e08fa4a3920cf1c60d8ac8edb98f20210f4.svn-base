// Meyers Singleton Logger
// Jacob Welch
// 03/15/2024

#include <iostream>
#include <string>
#include <fstream>

using std::cout; using std::endl; using std::string;

class Logger {
    public: 
        static Logger* instance() {
            static Logger object;
            return &object;
        }

        void report(const string& input) {
            std::ofstream fout;
            fout.open("log.txt", std::fstream::out | std::fstream::app);
            fout << input << std::endl;
            fout.close();
        }

        void helloWorld() {
            report("hello World!");
        }

        void loremIpsum() {
            report("Lorem ipsum dolor sit amet.");
            report("Ut minus autem est atque nulla ut consequatur vitae.");
        }

        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

    private:
        Logger(){cout << "default ctor invoked" << endl;}
};

int main() {
    Logger *ptr = Logger::instance();
    ptr->helloWorld();
    ptr->loremIpsum();

    /*Logger wrong1;                //returns error "Logger::Logger()" (declared at line 35) is inaccessible"
    Logger wrong2;
    wrong2 = wrong1;
    wrong.helloWorld();*/
}