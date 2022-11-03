InfniteInt description

In this program, I made a Node.h class that stores the node of the Linked List that gets created to store the InfiniteInt object.
The node class has accessors method for a easy program readibility for accessing next() prev() or item()

In the InfiniteInt class:

Constructor(int) takes in a int. then insert it into the InfintieInt head object traversely. By doing num %10 and num/10 we traverse from the back of number
to the front till it turns 0. this method calls the insertFirst() method

Construtctor(InfiniteInt)
This method calls the copy method. copy method desc below

~Destructor() 
This method detroys each node individually by calling clear()

operator=(InfiniteInt)
Just like the copy constructor method this method calls copy()

copy() method
makes a new Head, that stores the old head in *this by traversing through the oldHead pointer

clear() method
this method clears the entire InfiniteInt object list. creates a copy of the list, then it deletes it traversely 

insertFirst(int) this method insert an interger value infront of the current list

insertLast(int) this method insert an itnerger value at the end of the current list

operator int() - this method takes the const InfiniteInt(MAX_VAL) and InfiniteInt(MIN_VAL) objects and checks if they are bigger/ smaller than the current this. and based on that 
it coverts it to integer

operator+(InfiniteInt) this method first checks  if two values are negative or not negative,  then calls the add() or subtract() method based on that

operator-(InfiniteInt) this method first checks if tow value are negative or not negative, then calls the subtract() method or add() based on that

add(InfiniteInt, InfiniteInt), this method check between the two lengths, then adds based on which list is on top. this helps add the carry values and such for regualr addition

subtract(InfiniteIntm InfiniteInt), this method first checks between two lengths of the lists, then it subtracs based on that. the top or bot is determines, then that is used for 
borrowing which helps do the subtraction of the two nodes from the back.

operator*(InfiniteInt) this methods calls the multiply method to multiply a whole list, and the last digit of the other list. it does that as we gor prev on the other list, and each backwards iteration makes the List*number value add a 0 to the end. and then we add the two newly created lists to get final value. this happens in a while loop

multiply(InfiniteIntm int, int) this method  multiplies an InfiniteInt list to a int, then count is checked to see if any zero addition at the end is needed

operator==(InfinteiteInt) this method checks the two lists to see if theyre equal. first checks lenght, but if theyre same, checks each node individaully

operator<(InfiniteInt) this method checks which list is smaller. checks negavtives first, then based on length, checks each node individually

operator << this method prints the InfiniteInt to the console. by iterating through the list

operator >> this method inputs from the console, then creates a InfiniteInt object



