#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H


#include <iostream>
#include <string>
#include <exception>
#include "OwnIterator.h"
#include "Node.h"

using std::cout;
using std::string;

template<class T>
class DLinkedList {
public:

    typedef OwnIterator<T> iterator;
    typedef OwnIterator<const T> const_iterator;

    OwnIterator<T> begin(){
        return OwnIterator<T>(head);
    }

    OwnIterator<T> end(){
        return OwnIterator<T>(tail->getNext());
    }

    const_iterator begin() const{

    }
    const_iterator end() const{

    }

    DLinkedList()
            : size(0), head(0), tail(0) {}

    DLinkedList(DLinkedList<T> const &list) {
        size = 1;
        Node<T> *a = list.head;
        Node<T> *tmp = new Node<T>(list.head->getValue());
        head = tmp;
        tail = tmp;
        for (int i = 0; i < list.size - 1; ++i) {
            a = a->getNext();
            this->push_back(a->getValue());
        }
    }

    void erase(int index){
            if (index >= size || index < 0) {
                throw std::runtime_error(std::string("Out of Range"));
            }
            if (index == 0){
                this->pop_start();
                return;
            }
            if (index == size-1){
                this->pop_back();
                return;
            }
            Node<T> *a = head;
            for (int i = 0; i < index; i++) {
                a = a->getNext();
            }
            Node<T> * pref = a->getPrev();
            Node<T> * next = a->getNext();
            a->setNext(0);
            delete a;
            pref->setNext(next);
            next->setPrev(pref);
            size--;
        }

    bool isEmpty() const {
        return size == 0;
    }

    void push_back(T value) {
        if (this->isEmpty()) {
            Node<T> *a = new Node<T>(value);
            head = a;
            tail = a;
        } else {
            Node<T> *a = new Node<T>(value);
            tail->push_back(a);
            tail = a;
        }
        size++;
    }

    void push_start(T value) {
        if (this->isEmpty()) {
            Node<T> *a = new Node<T>(value);
            head = a;
            tail = a;
        } else {
            Node<T> *a = new Node<T>(value);
            head->push_start(a);
            head = a;
        }
        size++;
    }

    void add(int index, T value) {
        if (index >= size || index < 0) {
            throw std::runtime_error(std::string("Out of Range"));
        }
        if (index == 0) {
            this->push_start(value);
            return;
        }
        Node<T> *a = head;
        Node<T> *node = new Node<T>(value);
        for (int i = 0; i < index - 1; i++) {
            a = a->getNext();
        }
        Node<T> *b = a->getNext();
        a->push_back(node);
        b->push_start(node);
        size++;
    }

    void changeValue(int index, T value) {
        if (index >= size || index < 0) {
            throw std::runtime_error(std::string("Out of Range"));
        }
        Node<T> *a = head;
        for (int i = 0; i < index; i++) {
            a = a->getNext();
        }
        a->setValue(value);
    }

    T getValue(int index) const {
        if (index >= size) {
            throw std::runtime_error(std::string("Out of Range"));
        }
        Node<T> *a = head;
        for (int i = 0; i < index; i++) {
            a = a->getNext();
        }
        return a->getValue();
    }

    void pop_back() {
        if (this->isEmpty()) {
            throw std::runtime_error(std::string("List is Empty"));
        }
        Node<T> *tmp = tail->getPrev();
        delete tail;
        tail = tmp;
        size--;
    }

    void pop_start() {
        if (this->isEmpty()) {
            throw std::runtime_error(std::string("List is Empty"));
        }
        Node<T> *tmp = head->getNext();
        head->setNext(0);
        delete head;
        tmp->setPrev(0);
        head = tmp;
        size--;
    }

    ~DLinkedList() {
        delete head;
    }

    int getSize(){return size;}

private:
    Node<T> *head;
    Node<T> *tail;
    int size;
};

#endif // DLINKEDLIST_H
