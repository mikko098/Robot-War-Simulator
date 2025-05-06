/**********|**********|**********|
Program: simulator.h
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
#include <cstdlib>
#include "robot.h"
#include "queue.h"
#include "vectorclass.h"
#include "circularlinkedlist.h"
#include <iomanip>

using namespace std;

class Robot;

class Simulator{

    private:

        int width;
        int height;
        int numSteps;
        int numRobots;
        Robot*** battlefield;
        CircularLinkedList robotQueue;
        Queue<Robot*> deathQueue;

    public:
        // CONSTRUCTOR
        Simulator(int, int);

        // DESTRUCTOR
        ~Simulator();

        // GETTERS
        int getWidth() const;
        int getHeight() const;

        // SETTERS
        void setWidth(int);
        void setHeight(int);
        void setSteps(int);
        void setnumRobots(int);

        // PRINT FUNCTIONS
        // Prints out the first letter of the robots name
        void printRobot(Robot*);

        // Prints out the entire battlefield using '.' for empty spaces and printRobot function for robots
        void displayBattlefield();

        // Prints out the number of lives left for each robot
        void printLives();

        // Prints out the number of eliminations for each robot
        void printElims();

        vectorClass<pair<string, int>> deadRobotDetails;

        //BATTLEFIELD ROBOT MANIPULATION FUNCTIONS
        // adds a robot to the battlefield
        void addRobot(Robot*, int, int);

        // remove the robot at the specified location from the battlefield
        void removeRobot(int, int);

        // return a pointer to the robot located at the specified position
        Robot *getRobot(int x, int y);

        // check whether the given position lies within the battlefield
        bool isWithinBounds(int x, int y);

        // remove target from battlefield -> add to deathQueue if lives > 0 else remove from battlefield
        void killTarget(Robot *);


        // ROBOT CIRCULAR LINKED LIST MANIPULATION FUNCTIONS
        // add the specified robot to the circular linked list
        void addToLinkedList(Robot *);

        // remove the specified robot from the circular linked list
        void removeFromLinkedList(Robot *);

        // replace one specified robot with another in the circular linked list
        void replaceInLinkedList(Robot *, Robot *);

        // print out the elements of the circular linked list
        void displayRobotQueue(); // for debugging


        // DEAD ROBOTS QUEUE MANIPULATION FUNCTIONS
        void enqueueDeadRobot(Robot *);
        Robot *dequeueDeadRobot();
        void printQueue(); // for debugging


        // RUNNING SIMULATION
        // loops numSteps times, executing each turn and calling respawnRobot at the end of each turn
        void runProgram();
        void executeTurn();

        // checks whether any robots are destroyed, if there are dead robots respawns them at a random position
        void respawnRobot();
        
        // OUTPUT FILE MANIPULATION
        // *out is the output stream used; the default is set to cout
        ostream *out = &std::cout;

        //used to change the output stream
        void setOutputFile(ostream &);
};