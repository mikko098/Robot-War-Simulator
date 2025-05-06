/**********|**********|**********|
Program: queue.tpp
Course: Data Structures and Algorithms
Trimester: 2410
Name: Basil Aiman Bin Khairulanwar, Chan Ga Wai, Lai Cal Wyn, Mishal Mann Nair
ID: 1231303408, 1221305898, 1231303570, 1221305145
Lecture Section: TC2L
Tutorial Section: TT5L
Email: 1231303408@student.mmu.edu.my, 1221305898@student.mmu.edu.my, 1231303570@student.mmu.edu.my, 1221305145@student.mmu.edu.my
Phone: +60 10-220 6122, +60 11-6412 9980, +60 11-1083 1797, +60 19-443 2285
**********|**********|**********/
#pragma once
#include "queue.h"
#include <iostream>
using namespace std;

template <typename T>
Queue<T>::Queue(int capacity) : front(nullptr), rear(nullptr), size(0), cap(capacity) {};

template <typename T>
Queue<T>::~Queue()
{
    while (!isEmpty())
    {
        dequeue();
    }
}

template<typename T>
bool Queue<T>::isFull() const
{
    return size == cap;
}

template <typename T>
bool Queue<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
void Queue<T>::enqueue(const T &data)
{
    Node* newNode = new Node(data);
    if (isFull())
        return;
    else if (isEmpty())
        front = rear = newNode;
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
    size++;
}

template <typename T>
void Queue<T>::dequeue()
{
    if (isEmpty())
        return;
    else
    {
        Node* removeNode = front;
        front = front->next;

        if (front == nullptr)
            rear = nullptr;
        
        delete removeNode;
        size--;
    }
}

template <typename T>
T Queue<T>::peek() const
{
    if (isEmpty())
    {
        cout << ("Queue is empty. Cannot peek.");
    }
    return front->data;
}

template <typename T>
int Queue<T>::getSize() const
{
    return size;
}

template <typename T>
void Queue<T>::print() const
{
    Node* nodeptr = front;
    int index = 0;
    while(nodeptr!= nullptr){
        cout << "Index " << index << " : " << *nodeptr->data << endl;
        nodeptr = nodeptr->next;
        index++;
    }
    
}