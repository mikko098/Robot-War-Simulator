/**********|**********|**********|
Program: robot.cpp
Course: Data Structures and Algorithms
Trimester: 2410
Name: Basil Aiman Bin Khairulanwar, Chan Ga Wai, Lai Cal Wyn, Mishal Mann Nair
ID: 1231303408, 1221305898, 1231303570, 1221305145
Lecture Section: TC2L
Tutorial Section: TT5L
Email: 1231303408@student.mmu.edu.my, 1221305898@student.mmu.edu.my, 1231303570@student.mmu.edu.my, 1221305145@student.mmu.edu.my
Phone: +60 10-220 6122, +60 11-6412 9980, +60 11-1083 1797, +60 19-443 2285
**********|**********|**********/
#include "robot.h"
#include <algorithm>


using namespace std;

// Constructor
Robot::Robot(string tempName, Simulator *simulator, int tempX, int tempY)
{
    sim = simulator;
    name = tempName;

    //If a position is specified, check if it is within the battlefield and unoccupied
    if (sim->isWithinBounds(tempX, tempY) && sim->getRobot(tempX, tempY) == nullptr)
    {
        x = tempX;
        y = tempY;
    }

    //Else check for a random position
    else
    {
        do
        {
            x = rand() % (sim->getWidth());
            y = rand() % (sim->getHeight());
        } while (sim->getRobot(x, y) != nullptr);
    }

    //Place the robot at the location in the battlefield grid
    sim->addRobot(this, x, y);
};

// Destructor

Robot::~Robot() {};

// Copy constructor

Robot::Robot(const Robot& robot)
{
    name = robot.name;       // Name of the Robot
    x = robot.x;             // X - coordinate
    y = robot.y;             // Y - coordinate
    lives = robot.lives;     // Number of lives remaining
    totalElims = robot.totalElims; // Number of eliminations
    sim = robot.sim;         // Pointer to simulator
}

// Move constructor

Robot::Robot(Robot &&robot)
    : name(move(robot.name)), // Name of the Robot
      x(robot.x),             // X - coordinate
      y(robot.y),             // Y - coordinate
      lives(robot.lives),     // Number of lives remaining
      totalElims(robot.totalElims),     // Number of eliminations
      sim(robot.sim)          // Pointer to simulator

{
    robot.getSimulator()->removeRobot(robot.getX(),robot.getY());
};

// Getters

int Robot::getX() const { return x; }

int Robot::getY() const { return y; }

string Robot::getName() const { return name; }

int Robot::getLives() const { return lives; }

int Robot::getUpgradeCounter() const { return upgradeCounter; }

int Robot::getElims() const { return totalElims; }

void Robot::resetUpgradeCounter() { upgradeCounter = 0 ;}

Simulator *Robot::getSimulator() const { return sim; }

// Setters

void Robot::setX(int temp) { x = temp; }

void Robot::setY(int temp) { y = temp; }

void Robot::setLives(int temp) { lives = temp; }

// Robot functions

void Robot::plusLives() { lives++; }

void Robot::decreaseLives() { lives--; }

void Robot::plusElims() { totalElims++, upgradeCounter++; }

ostream* Robot::output() {
    ostream *a = getSimulator()->out;
    return a;
}

ostream &operator<<(std::ostream &os, const Robot &robot)
{
    os << robot.name;
    return os;
}

vectorClass<pair<int, int>> Robot::getValidPositions()
{
    vectorClass<pair<int, int>> validPositions;

    for (int i = 0; i < directions.size(); i++)
    {
        int newX = getX() + directions.get(i).first;
        int newY = getY() + directions.get(i).second;

        if ((getSimulator()->isWithinBounds(newX, newY)))
        {
            validPositions.push({newX, newY});
        }
    }

    return validPositions;
}

// RoboCop
//-------------------------------------------------------------------------------------------------------------------------------------------

void RoboCop::move()
{
    
    random_device rd;
    // Use mersenne twister to generate a random seed
    mt19937 seed(rd());
    vectorClass<pair<int,int>> shuffleDirections = getValidPositions();

    // Shuffle the directions to ensure random order
    shuffle(shuffleDirections.begin(), shuffleDirections.end(), seed);

    // Current position
    int currX = getX();
    int currY = getY();
    bool validMove = false;

    // Check each direction for a valid move
    for (const auto &[newX, newY] : shuffleDirections)
    {
        if (getSimulator()->getRobot(newX, newY) == nullptr)
        {
            // Found a valid move
            getSimulator()->removeRobot(currX, currY);
            setX(newX);
            setY(newY);
            getSimulator()->addRobot(this, newX, newY);
            *output() << getName() << " moved to (" << newX << ", " << newY << ")" << endl;
            validMove = true;
            break;
        }
    }

    if (!validMove){
        *output() << "No valid move found for " << *this << endl;
    }
}

Robot ***RoboCop::look()
{
    // Initialize a 3x3 grid of robot pointers that contain null values
    Robot ***lookgrid = new Robot **[3];
    for (int i = 0; i < 3; ++i)
    {
        lookgrid[i] = new Robot *[3];
        for (int j = 0; j < 3; ++j)
        {
            lookgrid[i][j] = nullptr;
        }
    }


    // Check all positions one block away from the robot in all directions
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            int newX = getX() + dx;
            int newY = getY() + dy;
            if (getSimulator()->isWithinBounds(newX, newY))
            {
                lookgrid[dx + 1][dy + 1] = getSimulator()->getRobot(newX, newY);
            }
            else
            {
                lookgrid[dx + 1][dy + 1] = nullptr; // Position is out of bounds
            }
        }
    }

    return lookgrid;
}

// Function used for debugging purposes; to check what the robot sees
void RoboCop::displaylook(Robot ***x)
{
    for (int i = 0; i <= 2; ++i)
    {
        for (int j = 0; j <= 2; ++j)
        {
            if (x[i][j])
            {
                *output() << 'R';
            }
            else
            {
                *output() << '.';
            }
            *output() << " ";
        }
        *output() << endl;
    }
}

// destructor for looking grid
void RoboCop::deletelook(Robot ***lookgrid)
{
    for (int i = 0; i < 3; ++i)
    {
        delete[] lookgrid[i];
    }
    delete[] lookgrid;
}

void RoboCop::shoot()
{
    int targetX;
    int targetY;
    Robot *target = nullptr;
    
    // Generate a random number from 0 to 10
    int randNumX = rand() % 11;
    // Find the complement of that number with 10 
    int randNumY = 10 - randNumX;

    // randNumX + ranNumY = 10
    // Generate a random number between -randX and +randX as well as -randY andn +randY
    do 
    {
        targetX = getX() + rand() % (2*randNumX + 1) - randNumX;
        targetY = getY() + rand() % (2*randNumY + 1) - randNumY;
    } 
    while((targetX == getX() && targetY == getY())||!getSimulator()->isWithinBounds(targetX, targetY));
    // If target position is same as shooting object, generate new random numbers

    target = getSimulator()->getRobot(targetX, targetY);

    if (target != nullptr)
    {
        *output() << getName() << " shot the robot " << target->getName() << " at (" << target->getX() << ", " << target->getY() << ")" << endl;
        target->decreaseLives();
        getSimulator()->killTarget(target);
        plusElims();
        upgrade();
    }

    else
        *output() << getName() << " shot at the position (" << targetX << " , " << targetY << "). No robot shot." << endl;
}

void RoboCop::action(){

    Robot *** surroundingGrid = look();
    // Move one step in a random direction if possible, else stay still
    move();
    int i = 0;
    // Loops three times or until the robot upgrades
    while (i < 3 && getUpgradeCounter() != 3)
    {
        // Fire at random positions within a 10 x 10 grid 
        shoot();
        i++;
    }
    deletelook(surroundingGrid);
    *output() << endl;
}

void RoboCop::upgrade()
{
    if (getUpgradeCounter() == 3)
    {
        *output() << getName() << " is upgrading into a TerminatorRoboCop. " << endl;
        // Save the current coordinates before moving the object
        int oldX = getX();
        int oldY = getY();

        // Move the current object to create a new TerminatorRoboCop object
        TerminatorRoboCop *newrobptr = new TerminatorRoboCop(std::move(*this));
        newrobptr->resetUpgradeCounter();

        // Add the new robot to the battlefield
        newrobptr->getSimulator()->addRobot(newrobptr, oldX, oldY);

        // Replace the old robot in the linked list
        newrobptr->getSimulator()->replaceInLinkedList(newrobptr, this);
    }
}


// Terminator
//---------------------------------------------------------------------------------------------------------------------------------------------

void Terminator::move()
{
    
    random_device rd;
    // Use mersenne twister to generate a random seed
    mt19937 seed(rd());
    vectorClass<pair<int, int>> shuffleDirections = getValidPositions();

    // Shuffle the directions to ensure random order
    shuffle(shuffleDirections.begin(), shuffleDirections.end(), seed);

    // Current position
    int currX = getX();
    int currY = getY();
    bool validMove = false;

    // Check each direction for a valid move
    for (const auto &[newX, newY] : shuffleDirections)
    {
        if (getSimulator()->getRobot(newX, newY) == nullptr)
        {
            // Found a valid move
            getSimulator()->removeRobot(currX, currY);
            setX(newX);
            setY(newY);
            getSimulator()->addRobot(this, newX, newY);
            *output() << getName() << " moved to (" << newX << ", " << newY << ")" << endl;
            validMove = true;
            break;
        }
    }

    if (!validMove)
    {
        *output() << "No valid move found for " << *this << endl;
    }
}

Robot ***Terminator::look()
{
    Robot ***lookgrid = new Robot **[3];
    for (int i = 0; i < 3; ++i)
    {
        lookgrid[i] = new Robot *[3];
        for (int j = 0; j < 3; ++j)
        {
            lookgrid[i][j] = nullptr;
        }
    }

    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            int newX = getX() + dx;
            int newY = getY() + dy;
            if (getSimulator()->isWithinBounds(newX, newY))
            {
                lookgrid[dx + 1][dy + 1] = getSimulator()->getRobot(newX, newY);
            }
            else
            {
                lookgrid[dx + 1][dy + 1] = nullptr; // Position is out of bounds
            }
        }
    }

    return lookgrid;
}

// Function used for debugging purposes; to check what the robot sees
void Terminator::displaylook(Robot ***x)
{
    for (int i = 0; i <= 2; ++i)
    {
        for (int j = 0; j <= 2; ++j)
        {
            if (x[i][j])
            {
                *output() << 'R';
            }
            else
            {
                *output() << '.';
            }
            *output() << " ";
        }
        *output() << endl;
    }
}

// destructor for looking grid
void Terminator::deletelook(Robot ***lookgrid)
{
    for (int i = 0; i < 3; ++i)
    {
        delete[] lookgrid[i];
    }
    delete[] lookgrid;
}

void Terminator::step(Robot*** lookgrid)
{
    bool stepped = false;

    // Check the 3x3 grid for enemy robots
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            // Skip the center position (the robot's current position)
            if (dx == 0 && dy == 0)
            {
                continue;
            }

            int newX = getX() + dx;
            int newY = getY() + dy;

            if (getSimulator()->isWithinBounds(newX, newY) && lookgrid[dx + 1][dy + 1] != nullptr)
            {
                // Found an enemy robot to step on
                *output() << getName() << " stepped on a robot at (" << newX << ", " << newY << ")" << endl;

                // Remove the enemy robot from the battlefield
                lookgrid[dx + 1][dy + 1]->decreaseLives();
                getSimulator()->killTarget(getSimulator()->getRobot(newX, newY));
                plusElims();

                // Move to the new position
                getSimulator()->removeRobot(getX(), getY());
                setX(newX);
                setY(newY);
                getSimulator()->addRobot(this, getX(), getY());

                stepped = true;
                break;
            }
        }
        if (stepped)
            {upgrade();
            break;}
    }

    if (!stepped)
    {
        // No enemy robot found in the 3x3 grid, behave like a movingRobot
        move();
    }
}

void Terminator::action()
{
    // Looks at surroundings
    Robot*** surroundingGrid = look();

    // Based on surroundings, either steps on robot or moves randomly
    step(surroundingGrid);

    // Deallocates the memory used for look()
    deletelook(surroundingGrid);

    *output() << endl;
}

void Terminator::upgrade(){
    if (getUpgradeCounter() == 3)
    {
        *output() << getName() << " is upgrading into a TerminatorRoboCop. " << endl;
        // Save the current coordinates before moving the object
        int oldX = getX();
        int oldY = getY();

        // Move the current object to create a new TerminatorRoboCop object
        TerminatorRoboCop *newrobptr = new TerminatorRoboCop(std::move(*this));
        newrobptr->resetUpgradeCounter();

        // Add the new robot to the battlefield
        newrobptr->getSimulator()->addRobot(newrobptr, oldX, oldY);

        // Replace the old robot in the linked list
        newrobptr->getSimulator()->replaceInLinkedList(newrobptr, this);

    }
}


// BlueThunder
//---------------------------------------------------------------------------------------------------------------------------------------------

void BlueThunder::shoot(){
    vectorClass<pair<int, int>> shootPositions = getValidPositions();
    pair<int, int> currentShootDirection = shootPositions.get(currentShootVariable);

    //Calculate which direction to shoot in
    Robot* target = getSimulator()->getRobot(currentShootDirection.first,currentShootDirection.second);

    if (target == nullptr){
        *output() << getName() << " shot at the position (" << currentShootDirection.first << ", " << currentShootDirection.second << ")" <<endl;
    }
    else{
        *output() << getName() << " shot " << target->getName() << " located at the position (" << target->getX() << " , " << target->getY() << ")" << endl;
        target->decreaseLives();
        getSimulator()->killTarget(target);
        plusElims();
        upgrade();
    }
    currentShootVariable++;
    currentShootVariable = currentShootVariable % shootPositions.size();

    
}

void BlueThunder::action(){
    shoot();
    *output() << endl;
}

void BlueThunder::upgrade(){
    if (getUpgradeCounter() == 3)
    {
        *output() << getName() << " is upgrading into a Madbot. " << endl;
        // Save the current coordinates before moving the object
        int oldX = getX();
        int oldY = getY();

        // Move the current object to create a new MadBot object
        MadBot *newrobptr = new MadBot(move(*this));
        newrobptr->resetUpgradeCounter();
        // Add the new robot to the battlefield
        newrobptr->getSimulator()->addRobot(newrobptr, oldX, oldY);

        // Replace the old robot in the linked list
        newrobptr->getSimulator()->replaceInLinkedList(newrobptr, this);

    }
}


// TerminatorRoboCop
//---------------------------------------------------------------------------------------------------------------------------------------------

void TerminatorRoboCop::move()
{
    // Call the move function of the Terminator base class
    Terminator::move();
}

Robot ***TerminatorRoboCop::look()
{
    return Terminator::look(); // Using look implemented in Terminator
}

// Function used for debugging purposes; to check what the robot sees
void TerminatorRoboCop::displaylook(Robot ***grid)
{
    Terminator::displaylook(grid); // Using displaylook implemented in Terminator
}

void TerminatorRoboCop::deletelook(Robot ***grid)
{
    Terminator::deletelook(grid); // Using deletelook implemented in Terminator
}

void TerminatorRoboCop::shoot()
{
    RoboCop::shoot(); // Using shoot implemented in Robot
}

void TerminatorRoboCop::step(Robot*** lookgrid)
{
    Terminator::step(lookgrid); // Using step implemented in Terminator
}

void TerminatorRoboCop::action(){
    // Looks at surroundings
    Robot*** surroundingGrid = look();
    // Based on surroundings, either steps on a robot, or moves
    step(surroundingGrid);
    int i = 0;
    while (i < 3 && getUpgradeCounter()!=3)
        {
            shoot();
            i++;
        }
    deletelook(surroundingGrid);
    *output() << endl;
}

void TerminatorRoboCop::upgrade(){
    if (getUpgradeCounter() == 3)
    {
        *output() << getName() << " is upgrading into an Ultimate Robot. " << endl;
        // Save the current coordinates before moving the object
        int oldX = getX();
        int oldY = getY();

        // Move the current object to create a new MadBot object
        UltimateRobot *newrobptr = new UltimateRobot(std::move(*this));
        newrobptr->resetUpgradeCounter();

        // Add the new robot to the battlefield
        newrobptr->getSimulator()->addRobot(newrobptr, oldX, oldY);

        // Replace the old robot in the linked list
        newrobptr->getSimulator()->replaceInLinkedList(newrobptr, this);
    }
    
}


// Madbot
//---------------------------------------------------------------------------------------------------------------------------------------------

void MadBot::shoot(){
    vectorClass<pair<int,int>> shootPositions = getValidPositions();
    int randIndex = rand() % shootPositions.size();
    int targetX = shootPositions.get(randIndex).first;
    int targetY = shootPositions.get(randIndex).second;
    Robot *target = getSimulator()->getRobot(targetX, targetY);

    if (target == nullptr)
    {
        *output() << getName() << " shot at the position (" << targetX << " , " << targetY << "). No robot shot." <<endl;
    }
    else
    {
        *output() << getName() << " shot " << target->getName() << " located at the position (" << target->getX() << " , " << target->getY() << ")" << endl;
        target->decreaseLives();
        getSimulator()->killTarget(target);
        plusElims();
        upgrade();
    }

}

void MadBot::upgrade()
{
    if (getUpgradeCounter() == 3)
    {
        *output() << getName() << " is upgrading into a RoboTank. " << endl;
        // Save the current coordinates before moving the object
        int oldX = getX();
        int oldY = getY();

        // Move the current object to create a new MadBot object
        RoboTank *newrobptr = new RoboTank(std::move(*this));
        newrobptr->resetUpgradeCounter();

        // Add the new robot to the battlefield
        newrobptr->getSimulator()->addRobot(newrobptr, oldX, oldY);

        // Replace the old robot in the linked list
        newrobptr->getSimulator()->replaceInLinkedList(newrobptr, this);
    }
}

// RoboTank
//---------------------------------------------------------------------------------------------------------------------------------------------

void RoboTank::shoot()
{
    int targetX;
    int targetY;

    do {
    targetX = rand() % getSimulator()->getWidth();
    targetY = rand() % getSimulator()->getHeight();
    } while(targetX == getX() && targetY == getY());

    Robot *target = getSimulator()->getRobot(targetX, targetY);
    
    if (target == nullptr)
    {
        *output() << getName() << " shot at the position (" << targetX << " , " << targetY << "). No robot shot." << endl;
    }
    else
    {
        *output() << getName() << " shot " << target->getName() << " located at the position (" << target->getX() << " , " << target->getY() << ")" << endl;
        target->decreaseLives();
        getSimulator()->killTarget(target);
        plusElims();
        upgrade();
    }
}

void RoboTank::upgrade()
{
    if (getUpgradeCounter() == 3)
    {
        *output() << getName() << " is upgrading into an Ultimate Robot. " << endl;
        // Save the current coordinates before moving the object
        int oldX = getX();
        int oldY = getY();

        // Move the current object to create a new MadBot object
        UltimateRobot *newrobptr = new UltimateRobot(std::move(*this));
        newrobptr->resetUpgradeCounter();

        // Add the new robot to the battlefield
        newrobptr->getSimulator()->addRobot(newrobptr, oldX, oldY);

        // Replace the old robot in the linked list
        newrobptr->getSimulator()->replaceInLinkedList(newrobptr, this);
    }
}

// UltimateRobot
//---------------------------------------------------------------------------------------------------------------------------------------------

void UltimateRobot::shoot(){
    RoboTank::shoot();
}

void UltimateRobot::action()
{
    Robot ***surroundingGrid = look();
    step(surroundingGrid);
    int i = 0;
    while (i < 3)
    {
        shoot();
        i++;
    }
    deletelook(surroundingGrid);
    *output() << endl;
}

void UltimateRobot::upgrade(){}

// MedicBot
//---------------------------------------------------------------------------------------------------------------------------------------------

void MedicBot::plusHeals() { heals++; }

int MedicBot::getHeals() { return heals; }

Robot ***MedicBot::look()
{
    Robot ***lookgrid = new Robot **[3];
    for (int i = 0; i < 3; ++i)
    {
        lookgrid[i] = new Robot *[3];
        for (int j = 0; j < 3; ++j)
        {
            lookgrid[i][j] = nullptr;
        }
    }

    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            int newX = getX() + dx;
            int newY = getY() + dy;
            if (getSimulator()->isWithinBounds(newX, newY))
            {
                lookgrid[dx + 1][dy + 1] = getSimulator()->getRobot(newX, newY);
            }
            else
            {
                lookgrid[dx + 1][dy + 1] = nullptr; // Position is out of bounds
            }
        }
    }

    return lookgrid;
}

// Function used for debugging purposes; to check what the robot sees
void MedicBot::displaylook(Robot ***x)
{
    for (int i = 0; i <= 2; ++i)
    {
        for (int j = 0; j <= 2; ++j)
        {
            if (x[i][j])
            {
                *output() << 'R';
            }
            else
            {
                *output() << '.';
            }
            *output() << " ";
        }
        *output() << endl;
    }
}

// destructor for looking grid
void MedicBot::deletelook(Robot ***lookgrid)
{
    for (int i = 0; i < 3; ++i)
    {
        delete[] lookgrid[i];
    }
    delete[] lookgrid;
}

void MedicBot::heal(Robot ***lookgrid)
{
    bool healed = false;
    // Check the 3x3 grid for enemy robots
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            // Skip the center position (the robot's current position)
            if (dx == 0 && dy == 0)
            {
                continue;
            }

            int newX = getX() + dx;
            int newY = getY() + dy;

            if (getSimulator()->isWithinBounds(newX, newY) && lookgrid[dx + 1][dy + 1] != nullptr)
            {
                // Found an enemy robot to heal
                *output() << getName() << " healed " << *lookgrid[dx + 1][dy + 1] << " at (" << newX << ", " << newY << ") " << endl;

                    // Increase heals on MedicBot
                    healed = true;
                lookgrid[dx + 1][dy + 1]->plusLives();
                plusHeals();
                break;
            }
        }
        if (healed) {
            upgrade();
            break;
        }
    }
    
    if (!healed)
        *output() << getName() << " did not find any robots to heal. " << endl;
}

void MedicBot::action()
{
    Robot ***surroundingGrid = look();
    heal(surroundingGrid);
    deletelook(surroundingGrid);
    *output() << endl;
}

void MedicBot::upgrade()
{
    if (getHeals() == 3)
    {
        *output() << getName() << " is upgrading into a Mercy Bot. " << endl;
        
        // Save the current coordinates before moving the object
        int oldX = getX();
        int oldY = getY();

        // Move the current object to create a new Mercy object
        MercyBot *newrobptr = new MercyBot(std::move(*this));
        newrobptr->resetUpgradeCounter();

        // Add the new robot to the battlefield
        newrobptr->getSimulator()->addRobot(newrobptr, oldX, oldY);

        // Replace the old robot in the linked list
        newrobptr->getSimulator()->replaceInLinkedList(newrobptr, this);
    }
}

// MercyBot
//---------------------------------------------------------------------------------------------------------------------------------------------

void MercyBot::heal(Robot ***surroundingGrid)
{
    MedicBot::heal(surroundingGrid);
}

void MercyBot::move()
{
    
    random_device rd;
    // Use mersenne twister to generate a random seed
    mt19937 seed(rd());
    vectorClass<pair<int, int>> shuffleDirections = getValidPositions();

    // Shuffle the directions to ensure random order
    shuffle(shuffleDirections.begin(), shuffleDirections.end(), seed);

    // Current position
    int currX = getX();
    int currY = getY();
    bool validMove = false;

    // Check each direction for a valid move
    for (const auto &[newX, newY] : shuffleDirections)
    {
        if (getSimulator()->getRobot(newX, newY) == nullptr)
        {
            // Found a valid move
            getSimulator()->removeRobot(currX, currY);
            setX(newX);
            setY(newY);
            getSimulator()->addRobot(this, newX, newY);
            *output() << getName() << " moved to (" << newX << ", " << newY << ")" << endl;
            validMove = true;
            break;
        }
    }
}

Robot ***MercyBot::look()
{
    return MedicBot::look(); // Using look implemented in MedicBot
}

// Function used for debugging purposes; to check what the robot sees
void MercyBot::displaylook(Robot ***grid)
{
    MedicBot::displaylook(grid); // Using displaylook implemented in MedicBot
}

void MercyBot::deletelook(Robot ***grid)
{
    MedicBot::deletelook(grid); // Using deletelook implemented in MedicBot
}

void MercyBot::action()
{
    move();
    Robot ***surroundingGrid = look();
    heal(surroundingGrid);
    deletelook(surroundingGrid);
    *output() << endl;
}

void MercyBot::upgrade() {}
