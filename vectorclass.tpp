/**********|**********|**********|
Program: vectorclass.tpp
Course: Data Structures and Algorithms
Trimester: 2410
Name: Basil Aiman Bin Khairulanwar, Chan Ga Wai, Lai Cal Wyn, Mishal Mann Nair
ID: 1231303408, 1221305898, 1231303570, 1221305145
Lecture Section: TC2L
Tutorial Section: TT5L
Email: 1231303408@student.mmu.edu.my, 1221305898@student.mmu.edu.my, 1231303570@student.mmu.edu.my, 1221305145@student.mmu.edu.my
Phone: +60 10-220 6122, +60 11-6412 9980, +60 11-1083 1797, +60 19-443 2285
**********|**********|**********/
#include "vectorclass.h"
using namespace std;

// constructor
template <typename T>
vectorClass<T>::vectorClass()
{
    arr = new T[1];
    capacity = 1;
    Size = 0;
}

// destructor
template <typename T>
vectorClass<T>::~vectorClass()
{
    delete[] arr;
}

// constructor to initialize a vector using a list of values
template <typename T>
vectorClass<T>::vectorClass(initializer_list<T> initList) : arr(new T[1]), Size(0), capacity(1)
{   
    for (const auto &elem : initList)
    {
        push(elem);
    }
}

// push data into the vector
template <typename T>
void vectorClass<T>::push(T data)
{
    // if the size of the vector is equal capacity of the vector double the capacity and copy the values to a new vector
    // then delete old vector
    if (Size == capacity)
    {
        T *temp = new T[2 * capacity];
        for (int i = 0; i < capacity; i++)
        {
            temp[i] = arr[i];
        }
        delete[] arr;
        capacity *= 2;
        arr = temp;
    }
    arr[Size] = data;
    Size++;
}

// return the vector at a given position
template <typename T>
T vectorClass<T>::get(int index)
{
    if (index < Size)
        return arr[index];
    throw("Index not within range.");
}

// returns the size of the vector
template <typename T>
int vectorClass<T>::size()
{
    return Size;
}

// returns a pointer pointing to the start of the array
template <typename T>
T *vectorClass<T>::begin()
{
    return arr;
}

// returns a pointer pointing to the end of the array
template <typename T>
T *vectorClass<T>::end()
{
    return arr + Size;
}