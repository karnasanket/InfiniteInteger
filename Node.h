/*
Author: Sanket Karna
File: Node.h
Date: 1/17/2021
Purporse; The purpose of this file is to provide the header methods of the Node class. In this class, we store the pointers to the next and previous nodes of a linked list,
as well as their values. We have getters and setters methods for these linked list actions for a easier user readibility. 
*/
#pragma once
#include <iostream>

template <class Item>
class Node {
    private:
        int value; // value of the node
        Node<Item>* next; // next node ptr
        Node<Item>* prev; // prev node ptr
    public:
        Node(); // 0 constructor
        Node(const Item& item);
        Node(const Item& value, Node<Item>* next, Node<Item>* prev); // default constructor
        void setItem(const Item& newItem); // sets the item of the node
        void setNext(Node<Item>* newNode); // sets the next node of the linked list
        void setPrev(Node<Item>* newNode); // sets the previous node of the linked list
        Item getItem(); // returns the item of the node
        Node<Item>* getNext(); // returns the next node ptr
        Node<Item>* getPrev(); // returns the prev node ptr
};
   
template <class Item>
Node<Item>::Node() : next(nullptr), prev(nullptr) {}// 0 constructor

template<class Item>
Node<Item>::Node(const Item& item) : value(item) {}
template <class Item>
Node<Item>::Node(const Item& value, Node<Item>* next, Node<Item>* prev) : value(0), next(nullptr), prev(nullptr){} // default constructor 

template <class Item>
void Node<Item>::setItem(const Item& newItem){ // sets the value of the node
    value = newItem;
}

template <class Item>
void Node<Item>::setNext(Node<Item>* newNode){ // sets the next node ptr
    next = newNode;
}

template <class Item>
void Node<Item>::setPrev(Node<Item>* newNode) { // sets the prv node ptr
    prev = newNode;
}

template <class Item>
Item Node<Item>::getItem(){ // returns the item in the current node
    return value;
}

template <class Item>
Node<Item>* Node<Item>::getNext(){ // returns the next node ptr
    return next;
}

template <class Item>
Node<Item>* Node<Item>::getPrev(){ // returns the prev node ptr
    return prev;
}