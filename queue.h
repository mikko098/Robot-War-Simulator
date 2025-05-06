/**********|**********|**********|
Program: queue.h
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

#include <iostream>
using namespace std;

template <typename T>
class Queue
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(const T &data) : data(data), next(nullptr) {}
    };

    Node *front;
    Node *rear;
    int size;
    int cap;

public:
    //Constructor
    Queue(int capacity = 20);
    //Destructor
    ~Queue();

    void enqueue(const T &data);
    void dequeue();
    T peek() const;
    bool isEmpty() const;
    bool isFull() const;
    int getSize() const;
    void print() const;
};

#include "queue.tpp"
