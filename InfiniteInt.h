/*
Author; Sanket Karna
File: InfiniteInt.h
Date: 1/17/2021
Purpose: This class is a header file for InfiniteInt.cpp and it provides header methods to the methods that are going to be implemented in that class.
*/
#pragma once

#include <climits>
#include <iostream>
#include <istream>
#include "Node.h"
#include <string>

using namespace std;

class InfiniteInt 
{
    private:
        int length; // lengths of the current linked list
        mutable bool negative; // keeps track of negative linked lists
        Node<int>* head; // head ptr of the linked list
        Node<int>* tail; // tail ptr of the linked list

    public :
        InfiniteInt(); // default constructor
        explicit InfiniteInt(int other); // int paramarized constructor
        ~InfiniteInt(); // destructor
        InfiniteInt(const InfiniteInt& other); // copy constructor
        void insertFirst(int& value); // insert at the beginning of linked list method
        void insertLast(int& value); // insert at the end of linked list method
        int numDigits(void); // returns the length
        void clear(); // method that clears the entire linked list
        void copy(const InfiniteInt& other); // method that makes a copy of the linked list
        explicit operator int() const; // method that convers a InfiniteInt to and interger
        InfiniteInt& operator=(const InfiniteInt& other); // assignment operator 
        InfiniteInt operator+(const InfiniteInt& other); // adds 2 linked lists
        InfiniteInt add(const InfiniteInt& list, const InfiniteInt& list2);
        InfiniteInt operator-(const InfiniteInt& other); // subtracts 2 linked lists
        InfiniteInt subtract(const InfiniteInt& list1, const InfiniteInt& list2);
        InfiniteInt operator*(const InfiniteInt& other); // multiplies 2 linked lists
        InfiniteInt multiply(const InfiniteInt& ohter, int value, int count);
        bool operator==(const InfiniteInt& other); // checks if two linkes lists are equal
        bool operator<(const InfiniteInt& other); // checks if linked list 1 is smaller than linked list 2
        friend ostream& operator<<(ostream& out, const InfiniteInt& other);
        friend istream& operator>>(istream& in, InfiniteInt& other);
};



