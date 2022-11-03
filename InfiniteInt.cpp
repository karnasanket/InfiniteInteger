/*
Author: Sanket Karna
Date: 1/21/2021
File: InfiniteInt.h
Desc: This class implements the method that was defined in InfiniteInt.h file. Check read me for more description on each method
*/
#include "InfiniteInt.h"
const InfiniteInt intMax = InfiniteInt(INT_MAX);
const InfiniteInt  intMin = InfiniteInt(INT_MIN);

InfiniteInt::InfiniteInt() : length(0), negative(false), head(nullptr), tail(nullptr) {} // default constructor

InfiniteInt::InfiniteInt(int other) {
    length = 0;
    head = tail = nullptr;
    head  = new Node<int>(); // allocated new node

    if(other < 0) { // if the int is negative, we keep track of it.
        negative = true;
        other = abs(other);
    }
    else {
        negative = false;
    }
     // if not negative
    while(other != 0){ // goes till other is finally 0
        int remainder  = other %10; // excludes the last single digit of the int
        insertFirst(remainder); // inserts into the linked list
        other = other /10; // shifts left from the end
    }
    Node<int>* copyHead = head;
    while(copyHead->getNext() != nullptr) { // sets nullptr
        copyHead = copyHead->getNext();
    }
    tail = copyHead;
    tail ->setNext(nullptr);
}

InfiniteInt::~InfiniteInt(){ //destructor
    clear(); // calls a clear method
}

InfiniteInt::InfiniteInt(const InfiniteInt& other) { // deep copy constructor
    copy(other); // calls the copy method that takes in the InfiniteInt to be copied
}

void InfiniteInt::insertLast(int& other){ // insert to the end of linked list method
    
    Node<int>* temp = tail; // copy of tail node
    Node<int>* temp2 =  new Node<int>(other); // temporary new node of the variable passes in
    temp2->setPrev(temp); //temp2 points to the same node before tail
    tail = temp2; // tail gets replaced by temp2
    tail->setNext(nullptr);

    if(tail->getPrev() == nullptr) { // if temp was null, then head is the new node (only true for the first iteration when the linked list is empty)
        head = temp2;
    }
    else { // else  
        temp->setNext(temp2); //sets the old tail's next
    }

    length++; // each time something gets added, legnth increases
}

void InfiniteInt::insertFirst(int& other) { // insert to the beginning of linked list method

    Node<int>* temp = head; // copy of head node 
    Node<int>* temp2 = new Node<int>(other); // temporary new node of the variable passed in
    temp2->setNext(temp); // temp2 points to the next node of head
    head = temp2; // head gets replaced by temp2
    head->setPrev(nullptr);

    if(temp == nullptr){ // if head was empty, tail and head point to the same node
        tail = temp2;
    }
    else {
        temp->setPrev(temp2); // else the old head's next is changed
    }
    length++; // each time something gets added, legnth increases
}

int InfiniteInt::numDigits(void){ //return the length of the current linked list
    return length; 
}

void InfiniteInt::clear() { // clear method for destructor 
    Node<int>* curr = head; // copy head pointer
    while(curr != nullptr) { // iterates through the head
        Node<int>* next = curr->getNext(); // new node for curr to point to when current curr gets deleted
        delete curr; // deletes curr
        curr = next; 
    }
    head = nullptr; // once empty, head and tail are set to null.
    tail = nullptr;
    length = 0;
}

void InfiniteInt::copy(const InfiniteInt& other) { // copy method for deep copying a InfiniteInt
    length = other.length; 
    negative = other.negative;

    Node<int>* thisNode = head = new Node<int>; // new head node
    thisNode->setNext(nullptr);
    thisNode->setPrev(nullptr);
    Node<int>* otherHead = other.head;
    thisNode->setItem(otherHead->getItem());

    while(otherHead->getNext() != nullptr){ // iterates through
        Node<int>* newNode = new Node<int>;
        newNode->setItem(otherHead->getNext()->getItem());
        newNode->setPrev(thisNode);
        newNode->setNext(nullptr);
        thisNode->setNext(newNode);
        thisNode = newNode; // head gets set
        otherHead = otherHead->getNext();
        tail = newNode; // tail gets set
    }
}

InfiniteInt::operator int() const { // infinite int and int conversion

    InfiniteInt thisCopy(*this);

    if(thisCopy < intMin) { // checks for int max and int min
        cout << "Your infiniteint is too small to convery to an int" << endl;
    } else {
        cout << "Your infiniteint is too big to convert into an int" << endl;
    }

    string str; 
    int value;
    Node<int>* thisHead = this->head; // copy head
    while(thisHead != nullptr){ // iterates through nullptr
        value = thisHead->getItem();
        str += to_string(value); // str adds the ints
        thisHead = thisHead->getNext(); 
    }
    int result = stoi(str); // converts into int
    if(this->negative){
        result *= -1; // if negative
    }

    return result;
}

InfiniteInt& InfiniteInt::operator=(const InfiniteInt& other) { // copy const calls copy
    
    copy(other); 
    return *this; // returns this

}

InfiniteInt InfiniteInt::operator+(const InfiniteInt& other)  { // assignment operator overload +
    
    
    Node<int>* copyThis = tail->getPrev(); // gets to the last node of list
    Node<int>* copyOther = other.tail->getPrev(); // gets to the last node of list

    int thisLength = this->length; 
    int otherLength = other.length;
    int total = 0;
    InfiniteInt returnValue(total);

    if(!this->negative && !other.negative) { // if they are both positive
        
        returnValue = add(*this, other);
    }
    else if (this->negative && other.negative) { // if they are both negative
        returnValue = add(*this, other);
        returnValue.negative = true;
    }
    else if (this->negative && !other.negative){ // if lhs is negative
        this->negative = false;
        other.negative = false;
        if(*this < other) { // if this is smaller number than other
            returnValue = subtract(*this, other);
            returnValue.negative = false;
        }
        else { // if other is smaller number than this
            returnValue = subtract(*this, other);
            returnValue.negative = true;
        }
    }
    else if (!this->negative && other.negative){ // if rhs is negative
        this->negative = false;
        other.negative = false;
        if(*this < other) {
            returnValue = subtract(*this, other);
            returnValue.negative = true;
        }
        else {
            returnValue = subtract(*this, other); // calls the helper method
            returnValue.negative = false;
        }
    }

    return returnValue; // returns return val
}

InfiniteInt InfiniteInt::add(const InfiniteInt& list1, const InfiniteInt& list2) { // add()
    
    Node<int>* copyThis = list1.tail->getPrev(); // set to the last node
    Node<int>* copyOther = list2.tail->getPrev();

    int thisLength = list1.length; // gets the value to see which one is top and which one is bot
    int otherLength = list2.length;
    int lvalue = 0;
    bool carry = false;
    int carryVal = 0;
    InfiniteInt returnValue(lvalue); // initializes return val

    while(copyThis != nullptr || copyOther != nullptr) { 

        if(thisLength < otherLength) { // if this is smaller
            
            int newNum = ((copyThis->getItem()) ) + (copyOther->getItem()+ carryVal);
            if(newNum > 9){ // if number is bigger than 9, carry over
                copyOther = copyOther->getPrev();
                carry = true; // carry is true
                copyThis = copyThis->getPrev(); // iterate backwards
                int temp = newNum % 10; // get the last val of the double digit number
                returnValue.insertFirst(temp); // insert to the beginning of the insertFirst
            }
            else {
                carry = false; // carry is false
                copyOther = copyOther->getPrev(); // iterate backwards
                copyThis = copyThis->getPrev();
                returnValue.insertFirst(newNum); // insert the one digit num
                
            }
            if(carry){ // if carry is true carry val is 1, in addition, 2 number added can only be as big as 18. so 1 is the only carry
                carryVal = 1;
            }
            else {
                carryVal = 0;
            }
            if (copyThis == nullptr) { // when the smaller list reaches null
                while(carry) { // if there was stil  a carry pending
                    int temp = copyOther->getItem() + carryVal;
                    copyOther = copyOther->getPrev(); 
                    int temp2 = temp %10;
                    if(copyOther == nullptr) { // insert other is now null after prev
                        while(temp != 0) {
                            returnValue.insertFirst(temp2);
                            temp = temp/10;
                            carry = false; // carry set to false
                        }
                        
                    }
                    else {
                        
                        returnValue.insertFirst(temp2); // if more carry happens
                        copyOther = copyOther->getPrev();
                        
                        if( temp >9){
                            carry = true;
                            carryVal = 1;     
                        }
                        else {
                            carry = false;
                            carryVal = 0;
                        }
                    } 

                }
                    while(copyOther != nullptr) { // when one of the list reaches nullptr
                        int temp = copyOther->getItem();
                        returnValue.insertFirst(temp);
                        copyOther = copyOther->getPrev(); 
                    }     
   
            }
        }
        else if (otherLength < thisLength){ // same computation as before, only the top and bot changes
            int newNum = (copyThis->getItem() + carryVal ) + (copyOther->getItem());
            if(newNum > 9){
                copyOther = copyOther->getPrev();
                carry = true;
                copyThis = copyThis->getPrev();
                int temp = newNum % 10;
                returnValue.insertFirst(temp);   
            }
            else { 
                carry = false;
                copyOther = copyOther->getPrev();
                copyThis = copyThis->getPrev();
                returnValue.insertFirst(newNum);
                
            }
            if(carry){
                carryVal = 1;
            }
            else {
                carryVal = 0;
            }
            if (copyOther == nullptr) {
                while(carry) {
                    int temp = copyThis->getItem() + carryVal;
                    copyThis = copyThis->getPrev();
                    int temp2 = temp %10;
                    if(copyThis == nullptr){
                        while(temp != 0){
                            returnValue.insertFirst(temp2);
                            temp = temp /10;
                            carry = false;
                        } 
                    }
                    else {
                        returnValue.insertFirst(temp2);
                        if( temp >9){
                            carry = true;
                            carryVal = 1;     
                        }
                        else {
                            carry = false;
                            carryVal = 0;
                        }                    
                    }         
                }
                while(copyThis != nullptr) {
                    int temp = copyThis->getItem();
                    returnValue.insertFirst(temp);
                    copyThis = copyThis->getPrev(); 
                }     
   
            }
        }
        else { // if they are the same length
                
            int newNum = ((copyThis->getItem()) ) + (copyOther->getItem()+ carryVal);
            if(newNum > 9){
                copyOther = copyOther->getPrev();
                carry = true;
                copyThis = copyThis->getPrev();
                if(copyThis == nullptr || copyOther == nullptr){
                    while(newNum != 0){
                        int remainder  = newNum % 10;
                        returnValue.insertFirst(remainder); 
                        newNum = newNum /10;
                    } 
                }
                else {
                    int temp = newNum % 10;
                    returnValue.insertFirst(temp);  
                }     
            }
            else {
                carry = false;
                copyOther = copyOther->getPrev();
                copyThis = copyThis->getPrev();
                returnValue.insertFirst(newNum);
                
            }
            if(carry){
                carryVal = 1;
            }
            else {
                carryVal = 0;
            }
        } // this doesnt check for when one of the list turns null, becuase theye the same value
    }
    
    return returnValue;
}

InfiniteInt InfiniteInt::operator-(const InfiniteInt& other)  {

    Node<int>* copyThis = this->tail; // sets to the last node
    Node<int>* copyOther = other.tail;
    int temp = 0;
    InfiniteInt returnValue(temp); // initialze return val


    if(!this->negative && !other.negative) { // if neither lists are negative
        if(*this < other){ // if this is smaller than other
            returnValue = subtract(*this, other);
            returnValue.negative = true;
        }
        else { // if other is smaller than this
            returnValue = subtract(*this, other);
            returnValue.negative = false;
        }
        
    }
    else if (this->negative && other.negative) { // if both lists are negative
        this->negative = false;
        other.negative = false;
        if(*this < other){ // if this is smaller than other
            returnValue = subtract(*this, other);
            returnValue.negative = false;
        }
        else {// if other is smaller than this
            returnValue = subtract(*this, other);
            returnValue.negative = true;
        }
    }
    else if(this->negative && !other.negative) { // if the rhs is negative
        this->negative = false;
        other.negative = false;
        returnValue = add(*this, other);
        returnValue.negative = true; // answer is always negative 
    }
    else if(!this->negative && other.negative){ // if the lhs is negative
        this->negative = false;
        other.negative = false; 
        returnValue = add(*this, other);
        returnValue.negative = false; // answer if always positive
    }
    return returnValue;
}

InfiniteInt InfiniteInt::subtract(const InfiniteInt& list1, const InfiniteInt& list2) {
    Node<int>* copyThis = list1.tail->getPrev(); // set to the last node 
    Node<int>* copyOther = list2.tail->getPrev();

    int length1 = list1.length;
    int length2 = list2.length;
    bool borrow = false;
    bool loop = true;
    int lvalue = 0;
    InfiniteInt returnValue(lvalue);
    InfiniteInt temp1(list1); // to check the two lists to see which one is bigger
    InfiniteInt temp2(list2);
    if(length1 == length2) {
        if(temp1 < temp2){ // if lhs is smaller, then it goes on the bottom
            length1--;
            loop = true;
        }
        else if(temp2 < temp1){ // if rhs is smaller, it goes on the top
            length1++;
            loop = true;
        }
        else{
            returnValue.insertFirst(lvalue); // if theyare the same, answer is 0
            loop = false;
        }
    }
    
    if(loop) {
    while(copyThis != nullptr && copyOther != nullptr) 
        if(length1 < length2) { // if lhs is small, its the bot

            if(borrow == false) { // borrow is initially false
                int newNum = 0;
                if((copyOther->getItem() < copyThis->getItem())){
                    newNum = (copyOther->getItem() + 10) - copyThis->getItem(); // number is top smaller than bot, then borrow happens +10
                    borrow = true;
                }
                else { // if not smaller than bot
                    newNum = copyOther->getItem() - copyThis->getItem(); // simple subtraction
                    borrow = false;
                }
                returnValue.insertFirst(newNum); // insert the num value
                copyOther = copyOther->getPrev(); // iterate backwards
                copyThis = copyThis->getPrev();
            }
            
            else { // if borrow is true
                int newNum = 0;
                if((copyOther->getItem() < copyThis->getItem())){ // if the top is smaller than bot, then borrow happens but also -1 happens because of borrow
                    newNum = ((copyOther->getItem() + 10) - copyThis->getItem()) -1;
                    borrow = true;
                }
                else {
                    newNum = (copyOther->getItem() - copyThis->getItem()) - 1; // if top is not smaller, +10 doesnt happen, -1 happens because of borrow
                    borrow = false;
                }
                returnValue.insertFirst(newNum); //insert first 
                copyOther = copyOther->getPrev();
                copyThis = copyThis->getPrev();
            }
            

            if(copyThis == nullptr) { // if the smaller list becomes null
                if(borrow){
                    int temp = copyOther->getItem() - 1; // if final borrowing is still pending
                    returnValue.insertFirst(temp);
                    borrow = false;
                    copyOther = copyOther->getPrev();                
                }
                while(copyOther != nullptr) { // insert the rest into the answer
                    int temp = copyOther->getItem();
                    returnValue.insertFirst(temp);
                    copyOther = copyOther->getPrev();
                }
            }
        }
        else if (length2 < length1) { // if rhs is smaller than lhs 
            int newNum = 0;
            if (borrow ==  false) { 
                if((copyThis->getItem() < copyOther->getItem())){ // same coputation as above, just swithced lists
                    newNum = (copyThis->getItem() + 10) - copyOther->getItem();
                    borrow = true;
                }
                else {
                    newNum = copyThis->getItem() - copyOther->getItem();
                    borrow = false;
                }
                returnValue.insertFirst(newNum);
                copyOther = copyOther->getPrev();
                copyThis = copyThis->getPrev();
            }
            else {
                if((copyThis->getItem() < copyOther->getItem())){
                    newNum = ((copyThis->getItem() + 10) - copyOther->getItem())- 1 ;
                    borrow = true;
                }
                else {
                    newNum = (copyThis->getItem() - copyOther->getItem()) - 1 ;
                    borrow = false;
                }
                returnValue.insertFirst(newNum);
                copyOther = copyOther->getPrev();
                copyThis = copyThis->getPrev();                
            }
            
            if(copyOther == nullptr) {
                if (borrow){
                    int temp = copyThis->getItem() - 1;
                    returnValue.insertFirst(temp);
                    borrow = false;
                    copyThis = copyThis->getPrev();
                }
                while(copyThis != nullptr) {
                    int temp = copyThis->getItem();
                    returnValue.insertFirst(temp);
                    copyThis = copyThis->getPrev();
                }
            }
        }
    }

    return returnValue;
}

InfiniteInt InfiniteInt::operator*(const InfiniteInt& other) { // assigmnet operator * overload
    Node<int>* thisCopy = this->tail->getPrev(); // sets to the last node 
    Node<int>* otherCopy = other.tail->getPrev();
    
    int temp =0;
    int count = 0;
    int lengthOfOther = other.length;
    InfiniteInt returnValue(temp); // return values are creates for multiple lists computations
    int lvalue = 1;
    InfiniteInt returnValue2(lvalue);
    InfiniteInt returnValue3(lvalue);

    while(otherCopy != nullptr){  // while one lists value gets iterated, while multiplying it by the other list entirely
        returnValue = multiply(*this, otherCopy->getItem(), count); // multiplies one list * last node of other list
        count++; // count to keep track of how many variables of the other list have we gone through. its used to add 0 at the end of list
        returnValue2 = add(returnValue, returnValue2); // add the last two multipication
        otherCopy = otherCopy->getPrev(); // otherlist iterates backwards
    }
    returnValue2 = returnValue2 - returnValue3; // the previous added 1 to initialize the list, taking that 1 back

    if(this->negative || other.negative) {
        returnValue2.negative = true; // if either one is negative, answer is always negative
    }
    else {
        returnValue2.negative = false; // otherwise always positive
    }
    return returnValue2;
}

InfiniteInt InfiniteInt::multiply(const InfiniteInt& list, int value, int count) {
    Node<int>* thisList = list.tail->getPrev(); // set to the last of list
    int temp = 0;
    int carry = 0;
    InfiniteInt returnValue(temp);
    while(thisList != nullptr){ // iterate through the list
        int mul  = thisList->getItem() * value + carry; // mutiply last node vs the value passed + varru, carry is 0 to start
        if (mul > 9){
            carry = mul / 10; // if carry is necessary
            int lvalue = mul % 10;
            thisList = thisList->getPrev();
            if(thisList == nullptr) { // if this list is at the end, insert the remaining carry/answer value in its own node
                while(mul != 0) {
                    int remainder = mul % 10;
                    returnValue.insertFirst(remainder);
                    mul = mul/10;
                }
                
            }
            else {
                returnValue.insertFirst(lvalue);// if its not at the nullptr
            }
            
            
        }
        else {  // if the number is not biget than 10 and carrry is required
            carry = 0;
            returnValue.insertFirst(mul);
            thisList = thisList->getPrev();
        }
    }

    for(int i = 0; i < count; i++){ // adds zero based on count 
        int lvalue = 0;
        returnValue.insertLast(lvalue); // adds zero
    }

    return returnValue;
}

bool InfiniteInt::operator==(const InfiniteInt &other)
    {
        Node<int> *temp1 = head; // copy head
        Node<int> *temp2 = other.head;
 
        int len1 = this->length;
        int len2 = other.length;
 
        bool result;
        int count = 0;
 
        if (len1 == len2) // if the length is equal
        {
            while (temp1 != nullptr)
            {
                if (temp1->getItem() == temp2->getItem()) // checks the first cal
                {
                    count++; // count to keep track of the number of matching nums
                    temp1 = temp1->getNext(); // the iterates through the rest to check the rest of the vals
                    temp2 = temp2->getNext();
                }
                else
                {
                    temp1 = temp1->getNext();
                    temp2 = temp2->getNext();
                }
            }
        }
        else
        {
            result = false;
        }
        if (count == len1) // if count and len are the same then the the BigInts match
        {
            result = true;
        }
        return result;
    }

bool InfiniteInt::operator<(const InfiniteInt& other) {
    Node<int>* thisList = this->head; //copy head
    Node<int>* otherList = other.head;

    int thisLength = this->length;
    int otherLength = other.length;

    if (this->negative && !other.negative) { // if lhs is negative, its smaller
        return true;
    }
    else if (!this->negative && other.negative) { // if rhs is negative, its smaller
        return false;
    }
    else if (this->negative && other.negative) { // if borth are negative
        if(thisLength > otherLength) { // if lhs is bigger in length, its smaller
        return true;
        }
        else if (thisLength < otherLength) { // if rhs is bigger in length, its smaller
            return false;
        }
        else {
            while(thisList != nullptr && otherList != nullptr) { // else it iterates through the list one by one
                if(thisList->getItem() == otherList->getItem()) {
                    thisList = thisList->getNext();
                    otherList = otherList->getNext();
                }
                else if(thisList->getItem() < otherList->getItem()){
                    return false;
                }
                else if(otherList->getItem() < thisList->getItem() ){
                    return true;
                }
            }
        }   
    }
    else {
        if(thisLength < otherLength) { // if they are both positive
            return true;
        }
        else if(otherLength < thisLength) { // chekcs for length
            return false;
        }
        else {
            while(thisList != nullptr && otherList != nullptr) {  // checks each item
                if(thisList->getItem() == otherList->getItem()) {
                    thisList = thisList->getNext();
                    otherList = otherList->getNext();
                }
                else if (thisList->getItem() < otherList->getItem()) {
                    return true;
                }
                else if (otherList->getItem() < thisList->getItem()) {
                    return false;
                }
            }
        }
    }

    return false; // 
}

ostream& operator<<(ostream& out, const InfiniteInt& other) // outputs the linked list
{
    Node<int>* temp = other.head; // temporary head
    if(other.negative) {
        out << '-';
    }

    while(temp->getNext() != nullptr){ // iterates through the entire InfiniteInt
        out << temp->getItem(); // stores each digit per node of linked list
        temp = temp->getNext();
    }
    
    return out; // returns the final output
}

istream& operator>>(istream& in, InfiniteInt& other) {
    int number; 
    in >> number; //inputs the number
    other = InfiniteInt(number); // makes the InfiniteInt object the number
    return in; // returns the final input
}