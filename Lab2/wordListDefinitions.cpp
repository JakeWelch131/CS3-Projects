#include "WordList.hpp"
#include <algorithm>
// ========================= WordOccurence Class implementation==========================

WordOccurrence::WordOccurrence() {
    word_= "";
    num_= 0;
}

WordOccurrence::WordOccurrence(const string& word, int num) {
    word_ = word;
    num_ = num;
}

bool WordOccurrence::matchWord(const string& readString) {
    if (word_ == readString) {
        return true;
    }
    else {
        return false;
    }
}

void WordOccurrence::increment() {
    ++num_;
}

string WordOccurrence::getWord() const {
    return word_;
}

int WordOccurrence::getNum() const {
    return num_;
}

// ========================= WordList Class implementation ==============================

// Copy Ctor
WordList::WordList(const WordList& copy) {
    size_ = copy.size_;
    wordArray_ = new WordOccurrence[size_];
    for (int i = 0; i < size_; ++i) {
        wordArray_[i] = copy.wordArray_[i];
    }
}

// Dtor
WordList::~WordList() {
    delete[] wordArray_;
}

// Swap idiom
void WordList::swap(WordList& rhs) {
    WordOccurrence *temp = wordArray_;
    wordArray_ = rhs.wordArray_;
    rhs.wordArray_ = temp;
    int sizeTemp = size_;
    size_ = rhs.size_;
    rhs.size_ = sizeTemp;
}

// Assignment Overload
WordList& WordList::operator=(WordList rhs) {
    swap(rhs);
    return *this;
}

bool equal(const WordList& lhs, const WordList& rhs) {
    if (lhs.size_ != rhs.size_) {                                                       //easy check to see if they are not equal
        return false;
    }
    else {
        for (int i = 0; i < lhs.size_; ++i) {
            if (lhs.wordArray_[i].getWord() != rhs.wordArray_[i].getWord() ||           // iterates through the WordList array and checks that each word AND occurences of that word are the same
                lhs.wordArray_[i].getNum() != rhs.wordArray_[i].getNum()) {
                    return false;                                                       // if they are not all equal, then it will return false
                }
        }
        return true;
    }
}

void WordList::addWord(const string& newWord) {
    
    int i = 0;
    bool found = false;

    if (std::ispunct(newWord[0]) != 0) {                                                // if the string is a punctuation mark, quit the function
        return;
    }

    while (i < size_) {                                                                 // iterates through the WordList array searching if the word being passed in already exists 
        
        if (wordArray_[i].getWord() == newWord) {
            wordArray_[i].increment();                                                  // if the word is already in array, we will increment the occurences
            found = true;                                                               // and set found to true

            break;
        }
        else {
            ++i;
        }
    }

    if (!found) {                                                                       // if the word was not already in the array
        WordOccurrence *newArray = new WordOccurrence[size_ + 1];                       // create a pointer that points at a new array with a size_ + 1 to be able to fit new word
        for (int j = 0; j < size_; ++j) {
            newArray[j] = wordArray_[j];                                                // fill the existing array up with previous values
        }
        newArray[size_] = WordOccurrence(newWord, 1);                                   // set the last element in the new array to the word being passed in, with only 1 occurence
        delete[] wordArray_;                                                            // delete old array to free memory
        wordArray_ = newArray;                                                          // set the new array equal to the old one
        ++size_;                                                                        // increment the size of old array to fit the new word
    }
}

bool WordList::compareOccurrences(const WordOccurrence& lhs, const WordOccurrence& rhs){    // function used in sort to compare the occurences in each word so it will sort in ascending order
    return lhs.getNum() < rhs.getNum();
}

void WordList::print() {
    std::sort(wordArray_, wordArray_ + size_, compareOccurrences);                      // sort the wordArray_ with the compareOccurences function as the comparison function
    for (int i = 0; i < size_; ++i) {                                                   // loop through the array 
        if (wordArray_[i].getWord() == "") {                                            // if the word is a blank (weird bug I had) then skip that iteration
            continue;   
        }
        std::cout << wordArray_[i].getWord() << " " << wordArray_[i].getNum();          // print the word and its number of occurences
        if (i < size_ - 2) {                                                            // if the element is not the last word in the array, print an endline as well
            std::cout << std::endl;
        }
    }
}