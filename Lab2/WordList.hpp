#ifndef CS3_LAB_2
#define CS3_LAB_2

#include <iostream>
#include <string>

using std::string;

class WordOccurrence {
public:
    WordOccurrence();
    WordOccurrence(const string&, int num);
    bool matchWord(const string &); // returns true if word matches stored
    void increment(); // increments number of occurrences
    string getWord() const; 
    int getNum() const;

private:
    string word_;
    int num_;
};

class WordList{
public:
    // add copy constructor, destructor, overloaded assignment
                        WordList() : size_(0) , wordArray_(nullptr) {};
                        WordList(const WordList&);
                        ~WordList();
    WordList&           operator=(WordList);
    void                swap(WordList&);

    // implement comparison as friend
    friend bool         equal(const WordList&, const WordList&);

    void                addWord(const string &);
    void                print();
    static bool         compareOccurrences(const WordOccurrence&, const WordOccurrence&);

    // Only use for testing purposes
    WordOccurrence *    getWords() const {return wordArray_;};
    int                 getSize() const {return size_;};
private:
    WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
                                // may or may not be sorted
    int size_;
};

#endif