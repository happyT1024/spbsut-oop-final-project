#ifndef NODE_H
#define NODE_H



template<class T>
class Node {
public:
    explicit Node(T value = 0)
            : prev(0), next(0), value(value) {}

    void init(Node *newPrev, Node *newNext) {
        prev = newPrev;
        newPrev->next = this;
        next = newNext;
        newNext->prev = this;
    }

    void push_back(Node *newNext) {
        next = newNext;
        newNext->prev = this;
    }

    void setPrev(Node *prev) {
        Node::prev = prev;
    }

    void setNext(Node *next) {
        Node::next = next;
    }

    void push_start(Node *newPrev) {
        prev = newPrev;
        newPrev->next = this;
    }

    Node *getNext() {
        return next;
    }

    Node *getPrev() {
        return prev;
    }

    T getValue() const {
        return value;
    }

    void setValue(T newValue) {
        value = newValue;
    }

    ~Node() {
        delete next;
    }

private:
    T value;
    Node *prev;
    Node *next;
};


#endif // NODE_H
