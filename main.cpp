/**********|**********|**********|
Program: main.cpp
Course: Data Structures and Algorithms
Trimester: 2410
Name: Basil Aiman Bin Khairulanwar, Chan Ga Wai, Lai Cal Wyn, Mishal Mann Nair
ID: 1231303408, 1221305898, 1231303570, 1221305145
Lecture Section: TC2L
Tutorial Section: TT5L
Email: 1231303408@student.mmu.edu.my, 1221305898@student.mmu.edu.my, 1231303570@student.mmu.edu.my, 1221305145@student.mmu.edu.my
Phone: +60 10-220 6122, +60 11-6412 9980, +60 11-1083 1797, +60 19-443 2285
**********|**********|**********/
#include <iostream>
#include <ctime>
#include "file.h"

using namespace std;

int main()
{
    srand(time(0));
    InfoParser ip;

    string inputfile;
    string outputfile;

    cout << "Enter the file name to read from: ";
    cin >> inputfile;
    cout << "Enter the file name for the output to be displayed in: ";
    cin >> outputfile;

    try
    {
    ip.parseFile(inputfile);
    ip.runSimulation(outputfile);
    cout << "Simulation run succesfully." << endl;
    }
    catch (string error)
    {
        cout << error << endl;
    };
    return 0;
}