#ifndef OWNITERATOR_H
#define OWNITERATOR_H


#include "Node.h"
#include <iterator>

template<typename ValueType>
class OwnIterator: public std::iterator<std::input_iterator_tag, ValueType>
{
public:
    explicit OwnIterator(Node<ValueType> * _p){
        p = _p;
    }
public:
    // OwnIterator(const OwnIterator &it);
    bool operator!=(OwnIterator const& other) const{
        return !this->operator==(other);
    }
    bool operator==(OwnIterator const& other) const{
        return p==other.p;
    }
    // typename OwnIterator::reference operator*() const;
    OwnIterator& operator++(){
        p = p->getNext();
        return *this;
    }

    ValueType operator*(){
        return p->getValue();
    };
    // OwnIterator& operator--();
private:
    Node<ValueType>* p;
};

#endif // OWNITERATOR_H
