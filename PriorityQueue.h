/* 
 * File:   PriorityQueue.h
 * Author: Elissa Abou Hassan
 *
 * Created on November 18, 2022, 7:09 PM
 */

/*-- PriorityQueue.h -----------------------------------------------------------
    This header file defines a template class PriorityQueue.  
    ElementType is a type parameter received from a client program.

    Basic Operations: 
        Constructor:            construct an empty queue
        Copy Constructor:       create a copy of a queue
        Destructor:             delete queue from memory
        Node(class):            to instantiate a new node
        =:                      assignment operator
        isEmpty:                checks if list is empty
        enqueue:                add new element to the queue
        dequeue:                remove one element from the front of the queue
        front:                  returns data of the front element
        << and display:         Displays all the queue elements
------------------------------------------------------------------------------*/

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H


#include <iostream>
using namespace std;


template<typename ElementType>

class PriorityQueue{
    
    /***** Data Members *****/
    private:
        class Node{
            public:
                /***** Node Data Members *****/
                ElementType data;
                int priority;
                Node* next;

                /***** Node Constructor *****/
                Node(ElementType value, int priority):
                data(value), priority(priority), next(NULL)
                {}
        };
        
        Node* myBack; //pointer to last node
        Node* myFront; //pointer to first node
        int mySize; //size of queue
     
    /***** Function Members *****/
    /***** Constructors *****/
    public:
        
        /*----------------------------------------------------------------------
            Construct a PriorityQueue object.

            Precondition:  None.
            Postcondition: An empty queue object has been constructed (myFront
                     and myBack are initialized to NULL and mySize is 0)
        ----------------------------------------------------------------------*/
        PriorityQueue():
        mySize(0), myBack(NULL), myFront(NULL)
        {}
        
        
        /*----------------------------------------------------------------------
            Copy Constructor 

            Precondition:  orig is the queue to be copied and is received as 
                a const reference parameter.
            Postcondition: A copy of orig has been constructed.
        ----------------------------------------------------------------------*/
        PriorityQueue(const PriorityQueue<ElementType> &orig);
        
        
        /*----------------------------------------------------------------------
            Assignment Operator 
        
            Precondition:  rightHandSide is the queue to be assigned
                and is received as a const reference parameter.
            Postcondition: The current queue becomes a copy of rightHandSide
                and a const reference to it is returned.
        ----------------------------------------------------------------------*/
        const PriorityQueue<ElementType> &operator=
                            (const PriorityQueue<ElementType> & rightHandSide);
        
        
        /*----------------------------------------------------------------------
            Class destructor 

            Precondition:  None
            Postcondition: The nodes in the queue have been deallocated.
        ----------------------------------------------------------------------*/
        ~PriorityQueue();
        
        
        /*----------------------------------------------------------------------
            Check if stack is empty.
        
            Precondition:  None
            Postcondition: Returns true if queue is empty and false otherwise.
        ----------------------------------------------------------------------*/
        bool isEmpty() const;
        
        
        /*----------------------------------------------------------------------
            Add new element to the queue.
        
            Precondition:  takes an item data of type ElementType 
                    and priority of type integer.
            Postcondition: The item is added after the last existing 
                                    element with higher or equal priority.
        ----------------------------------------------------------------------*/
        void enqueue(ElementType data, int priority = 1);
        
        
        /*----------------------------------------------------------------------
            Remove one element from front of queue.
        
            Precondition:  None
            Postcondition: Front element removed (if queue is empty display 
                        error message).
        ----------------------------------------------------------------------*/
        void dequeue();
        
        
        /*----------------------------------------------------------------------
            Return the data of the front element
        
            Precondition:  None
            Postcondition: Returns data of front element (if queue is empty 
                    display error message and return garbage value).
        ----------------------------------------------------------------------*/
        ElementType front() const;
        
        
        /*----------------------------------------------------------------------
            Display values stored in the queue. 

            Precondition:  ostream out is open.
            Postcondition: PriorityQueue's contents have been output to out.
        ----------------------------------------------------------------------*/
        void display(ostream & out) const;
        
};

/* Prototype of output operator */ 
template <typename ElementType>
ostream &operator<<(ostream &out, const PriorityQueue<ElementType> &queue);



/*========================== FUNCTION DEFINITIONS ============================*/


//Copy Constructor
template <typename ElementType>
PriorityQueue<ElementType>:: PriorityQueue(const PriorityQueue<ElementType> &orig){
    
    if(orig.isEmpty()){
        exit(1);
    }
    
    mySize = 0;
    myBack = NULL;
    myFront = NULL;
    
    Node* temp = orig.myFront;
    
    //traverse list and copy each element
    for(int i = 0; i < orig.mySize; i++){
        enqueue(temp->data, temp->priority);
        temp = temp->next;
    }
}

//Assignment Operator
template <typename ElementType>
const PriorityQueue<ElementType>& PriorityQueue<ElementType>:: operator=
                            (const PriorityQueue<ElementType> & rightHandSide){
    
    if(this == &rightHandSide){
        return *this;
    }
    this->~PriorityQueue();
    
    mySize = 0;
    myBack = NULL;
    myFront = NULL;
    
    //after deleting the list check if rightHandSide is empty
    if(rightHandSide.isEmpty()){
        return *this; //return *this
    }
    
    Node* temp = rightHandSide.myFront;
    
    //traverse list and copy each element
    for(int i = 0; i < rightHandSide.mySize; i++){
        enqueue(temp->data, temp->priority);
        temp = temp->next;
    }
    
}

//destructor
template <typename ElementType>
PriorityQueue<ElementType>:: ~PriorityQueue(){
    Node* temp;
    
    //traverse list and delete all nodes
    for (int i = 0; i < mySize; i++){
        temp = myFront;
        myFront = myFront->next;

        delete temp;
    }
}

//empty
template <typename ElementType>
bool PriorityQueue<ElementType>:: isEmpty() const{
    return mySize == 0;
}

template <typename ElementType>
void PriorityQueue<ElementType>:: enqueue(ElementType data, int priority = 1){
    
    Node* newNode = new Node(data, priority);
    
    //if the list is empty
    if(isEmpty()){
        myFront = newNode;
        myBack = newNode;
        mySize++;
        return;
    }
    
    Node* temp = myFront;
    
    //The front of queue has lesser priority than new node
    if(priority > myFront->priority){
        //insert new node before front
        newNode->next = myFront;
        myFront = newNode;
        mySize++;
    }
    
    //The back of queue has greater or equal priority to new node
    else if(priority <= myBack->priority){
        //insert new node after back
        myBack->next = newNode;
        myBack = newNode;
        mySize++;
    }
    
    else{
        //find position to insert new node
        while(temp->next != myBack && priority <= temp->next->priority){
            temp = temp->next;
        }
         
        newNode->next = temp->next;
        temp->next = newNode;
        
        mySize++;
    }
}


template <typename ElementType>
void PriorityQueue<ElementType>:: dequeue(){
    
    //if empty
    if(isEmpty()){
        cout<<"*** Empty Queue ***"<<endl;
        return;
    }
    
    Node* temp = myFront;
    
    //if there is only one element in queue
    if(mySize == 1){
        delete temp;
        myFront = NULL;
        myBack = NULL;
        mySize = 0;
    }
    //remove first element in queue
    else{
        myFront = myFront->next;
        delete temp;
        mySize--;
    }
}

//front data
template <typename ElementType>
ElementType PriorityQueue<ElementType>:: front() const{
    
    //if empty return garbage value
    if(isEmpty()){
        ElementType garbage;
        return garbage;
    }
    //else
    return myFront->data;
}

//display
template <typename ElementType>
void PriorityQueue<ElementType>:: display(ostream & out) const{
    
    Node* temp = myFront;
    out<<"The queue is:"<<endl;
    
    //if queue is empty
    if(isEmpty()){
        out<<"*** empty queue ***"<<endl;
        return;
    }
    
    //traverse queue and print each element
    for(int i = 0; i < mySize; i++){
        out<<temp->data<<" -> ";
        temp = temp->next;
    }
    out<<endl;
    
}


//output operator
template <typename ElementType>
ostream &operator<<(ostream &out, const PriorityQueue<ElementType> &queue){
    queue.display(out);
    return out;
}

#endif /* PRIORITYQUEUE_H */

