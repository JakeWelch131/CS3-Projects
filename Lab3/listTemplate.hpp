// Jacob Welch Feb 4, 2023
// header file for Lab 3

#ifndef LISTTEMPLATE_HPP_
#define LISTTEMPLATE_HPP_

#include <iostream>

// the pointer part of every list is the same
// lists differ by data part
template<typename T>
class Collection;

template<typename T>
bool equal(const Collection<T>&, const Collection<T>&);

template <typename T>
class node{
public:

            node(): next_(nullptr) {};
            node(const T& item) : data_(item), next_(nullptr) {};

  T         getData() const {return data_;}
  void      setData(const T& data){data_=data;}
  

  node<T>*  getNext() const;
  void      setNext(node<T> *const);

private:
  T         data_;
  node<T>   *next_;
};

template <typename T>
class Collection {
    public:
                        Collection() : beginning_(nullptr), ending_(nullptr) {};
              void      add(const T&);
              void      print();
              void      remove(const T&);
              T         last();
              friend bool     equal<T>(const Collection<T>&, const Collection<T>&);

    private: 
        node<T> *beginning_, *ending_;
};

//
// member functions for node
//
template <typename T>
node<T>* node<T>::getNext() const {
  return next_;
}

template<typename T>
void node<T>::setNext(node<T> *const next){
   next_=next;
}

#endif // LIST_HPP_