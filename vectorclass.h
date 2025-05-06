/**********|**********|**********|
Program: vectorclass.h
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
#include <initializer_list>

template <typename T>
class vectorClass
{
    T *arr;
    int capacity;
    int Size;

public:
    vectorClass();
    ~vectorClass();
    vectorClass(std::initializer_list<T> initList);
    void push(T data);
    T get(int index);
    int size();
    T *begin();
    T *end();
};

#include "vectorclass.tpp" // Include the implementation here for templates

