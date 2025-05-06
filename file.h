/**********|**********|**********|
Program: file.h
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
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "circularlinkedlist.h"
#include "robot.h"
#include "simulator.h"

using namespace std;

class InfoParser
{
public:
    void parseFile(const string &filename);
    void runSimulation(const string &filename);
    Robot *identifyRobot(const string &rob, const string &name, Simulator *simulator, int x = -1, int y = -1);

private:
    int N, M, steps, numRobots;
    Simulator *simulator = nullptr;
};