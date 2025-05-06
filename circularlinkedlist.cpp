/**********|**********|**********|
Program: circularlinkedlist.cpp
Course: Data Structures and Algorithms
Trimester: 2410
Name: Basil Aiman Bin Khairulanwar, Chan Ga Wai, Lai Cal Wyn, Mishal Mann Nair
ID: 1231303408, 1221305898, 1231303570, 1221305145
Lecture Section: TC2L
Tutorial Section: TT5L
Email: 1231303408@student.mmu.edu.my, 1221305898@student.mmu.edu.my, 1231303570@student.mmu.edu.my, 1221305145@student.mmu.edu.my
Phone: +60 10-220 6122, +60 11-6412 9980, +60 11-1083 1797, +60 19-443 2285
**********|**********|**********/

#include "circularlinkedlist.h"
#include <iostream>

using namespace std;

CircularLinkedList::CircularLinkedList() : front(nullptr), rear(nullptr), size(0) {}

CircularLinkedList::~CircularLinkedList()
{
    while (front != nullptr)
    {
        removeRobot(0);
    }
}

void CircularLinkedList::addRobot(Robot *value)
{
    //Create a new node with the robot pointer
    Node *temp = new Node;
    temp->data = value;
    if (front == nullptr)
    {
        front = temp;
    }
    else
    {
        rear->link = temp;
    }
    rear = temp;
    rear->link = front;
}

void CircularLinkedList::removeRobot(Robot *robot)
{
    // Handle the case when the list is empty
    if (front == nullptr)
    {
        throw("Empty Robot Queue");
        return;
    }

    Node *ptr = front;
    Node *prev = nullptr;
    bool found = false;

    // Check if the front node is the one to be deleted
    if (front->data == robot)
    {
        found = true;
        Node *temp = front;
        if (front->link == front)
        { // Only one node in the list
            rear = nullptr;
            front = nullptr;
        }
        else
        {
            // Update front and rear links
            front = front->link;
            rear->link = front;
        }
        delete temp;
    }
    else
    {
        // Traverse the list to find the node to delete
        do
        {
            prev = ptr;
            ptr = ptr->link;
            if (ptr->data == robot)
            {
                found = true;
                break;
            }
        } while (ptr != front);

        if (found)
        {
            // Remove the node by updating the links
            Node *temp = ptr;
            prev->link = ptr->link;
            if (ptr == rear)
            {
                rear = prev;
            }
            delete temp;
        }
    }

    if (!found)
    {
        throw("Robot to be removed from Circular Linked List was not found.");
    }
}

void CircularLinkedList::replaceRobot(Robot *newrob, Robot *oldrob)
{
    Node* temp = front;
    while (temp->data != oldrob)
    {
        temp = temp->link;
        if (temp == front)
            throw("Robot to be replaced in Circular Linked List was not found.");
    }

    temp->data = newrob;
}



bool CircularLinkedList::isEmpty() const
{
    return front == nullptr;
}

Node* CircularLinkedList::getFront()
{
    return front;
}