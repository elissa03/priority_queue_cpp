/*-- PriorityQueueTester.cpp ---------------------------------------------------
 
                Tester File for the PriorityQueue template class
 
------------------------------------------------------------------------------*/

/* 
 * File:   PriorityQueueTester.cpp
 * Author: Elissa Abou Hassan
 *
 * Created on November 18, 2022, 11:11 PM
 */

#include <cstdlib>
#include <cstring>

#include "PriorityQueue.h"

using namespace std;

void menu();

template <typename ElementType>
void userChoice(PriorityQueue<ElementType> &printerQueue, int choice);

int main(int argc, char** argv) {
    
    PriorityQueue<string> printerQueue; //empty queue
    int choice;
    
    menu();
    cin>>choice;
    
    do{
        //invalid choice
        if (choice < 0 || choice > 4) {
            menu();
            cin >> choice;           
        }
        //invoke userChoice
        else { 
            if (choice > 0 && choice <= 4) {
                
                userChoice(printerQueue, choice);
                menu();
                cin >> choice;
            }
        }
    }while(choice != 0); //exit program if choice is 0
    
    cout<<"\nEnd of program"<<endl;

    return 0;
}

void menu(){
   cout<<endl<<"  Priority Queue Menu"<<endl
        <<"======================================================"<<endl
        <<" 1) Add an item into the queue\n"
        <<" 2) Remove an item from the head of the queue\n"
        <<" 3) Display all items in the queue\n"
        <<" 4) Display the first item in the queue\n"
        <<" 0) Exit"<<endl<<"Please choose a number from the menu\n";
}

template <typename ElementType>
void userChoice(PriorityQueue<ElementType> &printerQueue, int choice){
    
    ElementType data;
    int priority;
    string ans;
    
    switch(choice){
        
        //enqueue
        case 1:{
            cout<<"Enter the item you want to add to the queue:\n";
            cin>>data;
            
            cout<<"Does the item have a specific priority (Y/y or N/n)?\n";
            cin>>ans;
            
            //for specified priority
            if(ans == "Y" || ans == "y"){
                cout<<"Enter the priority of the data (lowest 1 -> 5 highest):\n";
                cin>>priority;

                while(priority < 1 || priority > 5){
                    cout<<"\nPriority should be between 1 and 5\n";
                    cout<<"Enter the priority of the data (lowest 1 -> 5 highest):\n";
                    cin>>priority;
                }
                printerQueue.enqueue(data, priority);
            }
            //for default priority 1
            else{
                printerQueue.enqueue(data);
            }
            
            
            cout<<data<<" has been added into the queue successfully\n";
            
            break;
        }
        
        //dequeue
        case 2:{

            if(printerQueue.isEmpty()){
                cout<<"*** Empty Queue ***\n";
            }
            else{
                data = printerQueue.front();
                printerQueue.dequeue();
                cout<<data<<" has successfully been removed from the queue\n";
            }
            
            break;
        }
        
        //display queue
        case 3:{
            cout<<printerQueue;
            
            break;
        }
        
        //display front element
        case 4:{
            if(printerQueue.isEmpty()){
                cout<<"*** Empty Queue ***\n";
            }
            else{
                cout<<"The first item in the queue is :\n"
                    <<printerQueue.front()<<endl;
            }
           
            
            break;
        }
        
    }
    
}

