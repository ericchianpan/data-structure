#ifndef Doublylinkedlist_HPP
#define Doublylinkedlist_HPP
#include <iostream>

template<class T>
class DoublyLinkedList;

template<class T>
class Node{
public:
    Node() {};
    Node(T data, Node* previous = nullptr, Node* next = nullptr)
        :_data(data), _previous(previous), _next(next) {};
    ~Node() {};
    void setData(T data) { _data = data; }
    void setPrevious(Node* node) { _previous = node; }
    void setNext(Node* node) { _next = node; }
    Node* previous() { return this->_previous; }
    Node* next() { return this->_next; }
    T data() { return this->_data; }
    template<class U> 
    friend class DoublyLinkedList;
private:
    Node* _previous = nullptr;
    Node* _next = nullptr;
    T _data;
};

template<class T>
class DoublyLinkedList{
public:
    DoublyLinkedList() { _listSize = 0; }
    ~DoublyLinkedList() { free(_head); delete _tail; }
    int listSize() { return _listSize; }
    void printList();
    void pushFront(T data);
    void pushBack(T data);
    void remove(T data);
    void clean();
    void reverse();
private:
    Node<T>* _head = new Node<T>;
    Node<T>* _tail= new Node<T>;
    int _listSize;
    void free(Node<T>* node);
    bool isEmpty();
};

template<class T>
void DoublyLinkedList<T>::printList()
{
    if(_head->_next == nullptr)
    {
        std::cout << "doubly linked list is empty" << std::endl;
        return;
    }
    Node<T>* ptr = _head->_next;
    while(ptr != nullptr)
    {
        std::cout << ptr->_data << std::endl;
        ptr = ptr->_next;
    }
}

template<class T>
void DoublyLinkedList<T>::pushFront(T data)
{
    if(_head->_next == nullptr)
    {
        Node<T>* newNode= new Node<T>(data);
        _head->_next = newNode;
        _tail->_previous = newNode;
    }
    else
    {
        Node<T>* newNode= new Node<T>(data);
        Node<T>* firstNode = _head->_next;
        _head->_next = newNode;
        firstNode->_previous = newNode;
        newNode->_next = firstNode;
    }
    _listSize++;
}

template<class T>
void DoublyLinkedList<T>::pushBack(T data)
{
    Node<T>* lastNode = _tail->_previous;
    Node<T>* newNode= new Node<T>(data);
    lastNode->_next = newNode;
    newNode->_previous = lastNode;
    _tail->_previous = newNode;
    _listSize++;
}

template<class T>
void DoublyLinkedList<T>::remove(T data)
{
    Node<T>* ptr = _head->_next;
    while(true)
    {
        if(ptr->_data == data) break;
        ptr = ptr->_next;
        if(ptr == nullptr)
        {
            std::cout << "can not delete " << data << std::endl;
            return;
        }
    }
    ptr->_previous->_next = ptr->_next;
    ptr->_next->_previous = ptr->_previous;
    _listSize--;
}

template<class T>
void DoublyLinkedList<T>::clean()
{
    Node<T>* ptr = _head->_next;
    _head->_next = nullptr;
    _tail->_previous = nullptr;
    while(ptr != nullptr)
    {
        ptr->_next = nullptr;
        ptr->_previous = nullptr;
        Node<T>* tmp = ptr;
        ptr = ptr->_next;
        delete tmp;
    }
    _listSize = 0;
}

template<class T>
void DoublyLinkedList<T>::reverse()
{
    Node<T>* ptr = _head->_next;
    _tail->_next = ptr;
    while(ptr!= nullptr)
    {
        Node<T>* tmp = ptr->_next;
        ptr->_next = ptr->_previous;
        ptr->_previous = tmp;
        if(tmp == nullptr)
        {
            _head->_next = ptr;
        }
        ptr = tmp;
    }
}

template<class T>
void DoublyLinkedList<T>::free(Node<T>* ptr)
{
    if(ptr == nullptr) return;
    free(ptr->_next);
    delete ptr;
}

template<class T>
bool DoublyLinkedList<T>::isEmpty()
{
    return _head->_next == nullptr;
}
#endif
