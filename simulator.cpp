/**********|**********|**********|
Program: simulator.cpp
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
#include "simulator.h"

using namespace std;

// Constructor
Simulator::Simulator(int tempW, int tempH)
{
    // Initialize values for width and height, default values for numSteps and numRobots is set to 10
    width = tempW;
    height = tempH;
    numSteps = 10;
    numRobots = 10;

    // Allocate memory for the 2D battlefield
    battlefield = new Robot **[height];
    for (int i = 0; i < height; ++i)
    {
        battlefield[i] = new Robot *[width];
        for (int j = 0; j < width; ++j)
        {
            battlefield[i][j] = nullptr; // Initialize each cell to nullptr
        }
    }
}

// Destructor
Simulator::~Simulator()
{
    // Deallocate memory for the 2D battlefield
    for (int i = 0; i < height; ++i)
    {
        delete[] battlefield[i];
    }
    delete[] battlefield;
}

//getters
int Simulator::getWidth() const 
{
    return width;
}

int Simulator::getHeight() const
{
    return height;
}

//setters
void Simulator::setWidth(int w){
    width = w;
}

void Simulator::setHeight(int h)
{
    height = h;
}

void Simulator::setSteps(int s)
{
    numSteps = s;
}

void Simulator::setnumRobots(int nR)
{
    numRobots = nR;
}

void Simulator::setOutputFile(ostream & outfile)
{
    out = &outfile;
}


void Simulator::printRobot(Robot* robptr)
{
    *out << setw(3) << robptr->getName()[0];
}



void Simulator::displayBattlefield()
{
    *out << "   " ;

    for (int i = 0; i < width; ++i) {
        *out << setw(3) << i;
    }

    *out << endl;

    for (int i = 0; i < height; ++i)
    {
        *out << setw(3) << i;
        for (int j = 0; j < width; ++j)
        {
            if (battlefield[i][j])
            {
                printRobot(battlefield[i][j]);
            }
            else
            {
                *out << setw(3) << '.';
            }
        }
        *out << endl;
    }

    *out << endl;
}

void Simulator::addRobot(Robot *robot, int w, int h)
{
    if (isWithinBounds(w, h))
    {
        battlefield[h][w] = robot;
    }
}

void Simulator::removeRobot(int w, int h)
{
    if (isWithinBounds(w, h))
    {
        battlefield[h][w] = nullptr;
    }
}

bool Simulator::isWithinBounds(int w, int h)
{
    return w >= 0 && w < width && h >= 0 && h < height;
}

Robot *Simulator ::getRobot(int w, int h)
{
    if (isWithinBounds(w, h))
    {
        return battlefield[h][w];
    }
    return nullptr;
}

void Simulator::addToLinkedList(Robot *robot)
{
    robotQueue.addRobot(robot);
}

void Simulator::removeFromLinkedList(Robot *robot)
{
    robotQueue.removeRobot(robot);
}

void Simulator::replaceInLinkedList(Robot *newrobot, Robot* oldrobot)
{
    robotQueue.replaceRobot(newrobot, oldrobot);
}

void Simulator::enqueueDeadRobot(Robot *robot)
{
    deathQueue.enqueue(robot);
}

Robot *Simulator::dequeueDeadRobot()
{
    Robot* robptr = deathQueue.peek();
    deathQueue.dequeue();
    return robptr;
}

void Simulator::runProgram()
{
    if (robotQueue.isEmpty())
    {
        *out << "Queue is empty" << endl;
        return;
    }

    int count = 1;

    while (count <= numSteps)
    {
        *out << "---------------------  TURN NO: " << count << "  ---------------------" << endl;
        executeTurn();
        displayBattlefield();
        count++;
    }

    printLives();
    printElims();
}

void Simulator::executeTurn(){
    Node *temp = robotQueue.getFront();

    do
    {
        temp->data->action();
        temp = temp->link;
    } while (temp != robotQueue.getFront());
    respawnRobot();
}

void Simulator::respawnRobot(){
    //Check if deathqueue is empty; if empty do nothing, if not empty, addRobot back to the circular linked list to execute action next turn
    if (!deathQueue.isEmpty())
    {
        robotQueue.addRobot(deathQueue.peek());

        //Initialize newX and y
        int newX;
        int newY;

        //Loop for valid variables newX and newY on the Simulator to place the robot on
        do
        {
            newX = rand() % (getWidth());
            newY = rand() % (getHeight());
        } while (getRobot(newX, newY) != nullptr);

        //Set the newX and newY variables of the robot to the values generated
        deathQueue.peek()->setX(newX);
        deathQueue.peek()->setY(newY);
        addRobot(deathQueue.peek(), newX, newY);
        *out << *deathQueue.peek() << " respawned at the location (" << newX << ", " << newY << ")" << endl << endl;
        deathQueue.dequeue();
    }
}

void Simulator::printLives(){
    Node* temp = robotQueue.getFront();
    do
    {
        *out << *(temp->data) << " lives : " << temp->data->getLives() << endl;
        temp = temp->link;
    } while (temp != robotQueue.getFront());

    for (const auto &[name, x] : deadRobotDetails)
    {
        *out << name << " lives remaining : 0" << endl;
    }

    *out << endl;
}

void Simulator::printElims()
{
    Node *temp = robotQueue.getFront();
    do
    {
        *out << *(temp->data) << " elims : " << temp->data->getElims() << endl;
        temp = temp->link;
    } while (temp != robotQueue.getFront());

    for (const auto &[name, elims] : deadRobotDetails)
    {
        *out << name << " total eliminations : " << elims << endl;
    }
    *out << endl;
}

void Simulator::killTarget(Robot* target){
    Node* temp = robotQueue.getFront();

    //iterate through the list to get the target robot
    while (temp->link->data != target)
    {
        temp = temp->link;
    }

    //if target has any lives left, move to the dead robots queue
    if (target->getLives() > 0)
    {   
        enqueueDeadRobot(target);
        removeFromLinkedList(target);
        removeRobot(target->getX(), target->getY());
    }

    //if target has no more lives, permanently remove the robot
    else 
    {
        *out << "Robot " << *target << " has lost all its lives. " << endl;
        deadRobotDetails.push({target->getName(),target->getElims()});
        removeFromLinkedList(target);
        removeRobot(target->getX(), target->getY());
    }

    numRobots--;
    
}

void Simulator::displayRobotQueue()
{
    Node* front = robotQueue.getFront();
    if (front == nullptr)
    {
        *out << "List is empty" << endl;
        return;
    }

    Node *temp = front;
    *out << "Robots in the Circular Linked List are: " << endl;
    int i = 1;
    do
    {
        *out << i << " : " << * (temp->data) << " (" << temp->data->getX() << " ," << temp->data->getY() << ")" << endl;
        temp = temp->link;
        i++;
    } while (temp != front);
    *out << endl;
}

void Simulator::printQueue(){
    deathQueue.print();
}