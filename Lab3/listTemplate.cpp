// Jacob Welch Feb 4, 2023
// implementation of Lab 3

#include "listTemplate.hpp"

template <typename T>
void Collection<T>::add(const T& item) {
    if (beginning_ == 0) {                                                  // if the collection is empty
        beginning_ = new node<T>(item);                                     // assing the beginning pointer to a new node with the data passed in   
        ending_ = beginning_;                                               // set the ending to the new node since there is only 1 in the collection
    }
    else {
        node<T> *temp = new node<T>(item);                                  // if the collection is not empty, create a temperary node and set it to the data passed in
        ending_->setNext(temp);                                             // set the next_ pointer of the last element in collection to the new node 
        ending_ = ending_->getNext();                                       // and then set the ending of the collection to the new node we created, this effectively adds new elements to the end of the collection
    }
}

template <typename T>
void Collection<T>::print() {
    node<T> *temp = beginning_;                                             // sets a temporary node to the beginning of the collection
    while (temp != 0) {                                                     // while temp is still pointing to something
        std::cout << temp->getData() << std::endl;                          // print out the data in the node the temp pointer is pointing at
        temp = temp->getNext();                                             // set temp to the next element in the collection
    }   
    
}

template <typename T>
void Collection<T>::remove(const T& item) {
    node<T> *finder = beginning_;                                           // set a pointer of type node to the beginning of the collection, the purpose of this pointer is to act as an iterator through the collection
    while (finder != 0) {                                                   // while finder is still pointing at the collection
        node<T> *rightSide = finder->getNext();                             // create a new node that is equal to the element infront of the finder, the purpose of this pointer is to detect what the data infront of finder will be before having to iterate to that element
        if (rightSide->getData() == item) {                                 // if rightside's data is equal to the data we want to remove
            if (rightSide->getNext() == 0) {                                // this detects if the element is the end of the collection
                ending_ = finder;                                           // we will set the end of the collection equal to the finder 
                delete rightSide;                                           // we will delete rightside (which contains the data we want to remove)
                finder->setNext(0);                                         // this ensures that finder's next_ pointer is not dangling
                return;                                                     // finish the function since we are at the end of the collection
            }
            else {                                                          // if rightside IS NOT the last element in the collection
                finder->setNext(rightSide->getNext());                      // set finder's next_ pointer to rightside's next_ pointer (effectively skipping over the rightside element)
                delete rightSide;                                           // delete rightside
                finder = finder->getNext();                                 // set finder to the next element in the collection
            }
        }
        else {
            finder = finder->getNext();                                     // if rightside's data is not equal to the data we want to remove, set finder to the next element in the collection
        }
    }
}

template <typename T>
T Collection<T>::last() {
    return ending_->getData();
}

template <typename T>
bool equal(const Collection<T> &col1, const Collection<T> &col2) {
    node<T> *temp1 = col1.beginning_;                                       // set a temp node to the beginning of the first collection
    node<T> *temp2 = col2.beginning_;                                       // set another temp node to the beginning of the second collection
    while((temp1 != 0) && (temp2 != 0)) {                                   // while we are not at the end of either collection
        if(temp1->getData() != temp2->getData()) {                          // if the data at an element in the first collection is NOT equal to the data in the same element in the second collection
            return false;                                                   // the function will return false
        }
        else {
            temp1 = temp1->getNext();                                       // if not, set each temp pointer to the next element in the collection
            temp2 = temp2->getNext();
        }
    }
    return true;                                                            // if we get through both collections with nothing mismatched, the function will return true
}