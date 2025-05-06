/**********|**********|**********|
Program: robot.h
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
#include "vectorclass.h"
#include <array>
#include "simulator.h"
#include <random>
#include <ctime>

using namespace std;

class Simulator;

class Robot{

    private:
        string name;            // Name of the Robot
        int x;                  // X - coordinate
        int y;                  // Y - coordinate
        int lives = 3;          // Number of lives remaining
        int upgradeCounter = 0; // Number of eliminations till upgrade
        int totalElims = 0;     // Number of eliminations
        Simulator* sim;

    public:
        // CONSTRUCTORS
        Robot(string, Simulator*, int x = -1, int y = -1);
        Robot(const Robot&);
        Robot(Robot &&other);

        // DESTRUCTOR
        virtual ~Robot();

        // GETTERS
        int getX() const;
        int getY() const;
        string getName() const;
        int getLives() const;
        int getElims() const;
        int getUpgradeCounter() const;
        Simulator* getSimulator() const;

        // SETTERS
        void setX(int);
        void setY(int);
        void setLives(int);

        // METHODS
        void plusElims();
        void plusLives();
        void resetUpgradeCounter();
        void decreaseLives();
        bool isAlive() const;
        void upgrade() const;
        virtual void action() = 0;
        vectorClass<pair<int, int>> getValidPositions();

        // OUTPUT MANIPULATION
        friend ostream &operator<<(ostream &os, const Robot &robot);
        ostream* output();

        // vector containing surrounding positions; used for move and bluethunder & madbot shoot functions
        vectorClass<pair<int, int>> directions = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};
};

class movingRobot: virtual public Robot
{
    public:
        using Robot::Robot;
        virtual void move() = 0;
};

class lookingRobot : virtual public Robot
{
    public:
        using Robot::Robot;
        virtual Robot*** look() = 0;
};

class shootingRobot : virtual public Robot
{
    public:
        using Robot::Robot;
        virtual void shoot() = 0;
};

class steppingRobot : virtual public Robot
{
    public:
        using Robot::Robot;
        virtual void step(Robot***) = 0;
};

class healingRobot : virtual public Robot
{
public:
    using Robot::Robot;
    virtual void heal(Robot ***) = 0;
};

//RobotCop class
class RoboCop : virtual public lookingRobot, virtual public movingRobot, virtual public shootingRobot
{
    public:
        RoboCop(string name, Simulator *bf, int x = -1, int y = -1)
            : Robot(name, bf, x, y), movingRobot(name, bf, x, y), lookingRobot(name, bf, x, y), shootingRobot(name, bf, x, y) {}
        RoboCop(Robot &&other)
            : Robot(std::move(other)){}
        virtual void move() override;
        virtual Robot ***look() override;
        virtual void shoot() override;
        virtual void displaylook(Robot ***);
        virtual void deletelook(Robot ***);
        virtual void action() override;
        virtual void upgrade();
};

// Terminator class
class Terminator : virtual public lookingRobot, virtual public movingRobot, virtual public steppingRobot
{
    public:
        Terminator(string name, Simulator *bf, int x = -1, int y = -1)
            : Robot(name, bf, x, y), movingRobot(name, bf, x, y), lookingRobot(name, bf, x, y), steppingRobot(name, bf, x, y) {}
        Terminator(Robot &&other)
            : Robot(std::move(other)){}
        virtual void move() override;
        virtual Robot ***look() override;
        virtual void displaylook(Robot ***);
        virtual void deletelook(Robot ***);
        virtual void step(Robot ***) override;
        virtual void action() override;
        virtual void upgrade();
};

// TerminatorRoboCop class
class TerminatorRoboCop : virtual public Terminator, virtual public RoboCop
{
    public:
        TerminatorRoboCop(string name, Simulator *bf, int x = -1, int y = -1)
            : Robot(name, bf, x, y), RoboCop(name, bf, x, y), Terminator(name, bf, x, y) {}
        TerminatorRoboCop(Robot&& other)
            : Robot(std::move(other)),
            RoboCop(std::move(other)),
            Terminator(std::move(other)){}
        void move() override;
        Robot ***look() override;
        void displaylook(Robot ***) override;
        void deletelook(Robot ***) override;
        void shoot() override;
        void step(Robot ***) override;
        void action() override;
        virtual void upgrade() override;
};

// BlueThunder class
class BlueThunder : virtual public shootingRobot
{
    private:
        int currentShootVariable = 0;

    public:
        BlueThunder(string name, Simulator *bf, int x = -1, int y = -1)
            : Robot(name, bf, x, y), shootingRobot(name, bf, x, y) {}
        BlueThunder(Robot &&other)
            : Robot(move(other)){};
        void shoot() override;
        void action() override;
        virtual void upgrade();
};

class MadBot : virtual public BlueThunder
{
    public:
        MadBot(string name, Simulator* bf, int x = -1, int y = -1) : Robot(name, bf, x, y), BlueThunder(name, bf, x, y){};
        MadBot(Robot &&other)
            : Robot(move(other)),
            BlueThunder(move(other)) {}
        void shoot() override;
        virtual void upgrade() override;
};

class RoboTank : virtual public MadBot
{
    public:
        RoboTank(string name, Simulator *bf, int x = -1, int y = -1) : Robot(name, bf, x, y), MadBot(name, bf, x, y), BlueThunder(name, bf, x, y){};
        RoboTank(Robot &&other)
            : Robot(move(other)),
            BlueThunder(move(other)),
            MadBot(move(other)) {}
        void shoot() override;
        virtual void upgrade() override;
};

class UltimateRobot : public TerminatorRoboCop, public RoboTank
{
    public:
        UltimateRobot(string name, Simulator *bf, int x = -1, int y = -1) : Robot(name, bf, x, y), RoboTank(name, bf, x, y), TerminatorRoboCop(name, bf, x, y), RoboCop(name, bf, x, y), Terminator(name, bf, x, y), MadBot(name, bf, x, y), BlueThunder(name, bf, x, y){};
        UltimateRobot(Robot &&other)
            : Robot(std::move(other)),
            BlueThunder(std::move(other)),
            MadBot(std::move(other)),
            RoboTank(std::move(other)),
            TerminatorRoboCop(std::move(other)),
            Terminator(std::move(other)),
            RoboCop(std::move(other)) {}
        void action() override;
        void shoot() override;
        virtual void upgrade() override;
};

/*  Additional Classes :
    MedicBot -> Heals any one adjacent robot each turn
    MercyBot -> Moves and heals any one adjacent robot each turn
*/

class MedicBot : virtual public lookingRobot, virtual public healingRobot
{
    private:
        int heals = 0;
    public:
        MedicBot(string name, Simulator *bf, int x = -1, int y = -1)
            : Robot(name, bf, x, y), lookingRobot(name, bf, x, y), healingRobot(name, bf, x, y) {}
        MedicBot(Robot &&other)
            : Robot(move(other)) {}
        virtual Robot ***look() override;
        virtual void heal(Robot ***) override;
        virtual void displaylook(Robot ***);
        virtual void deletelook(Robot ***);
        virtual void action() override;
        virtual void upgrade();
        virtual void plusHeals();
        virtual int getHeals();
};

class MercyBot : virtual public movingRobot, virtual public MedicBot
{
    public:
        MercyBot(string name, Simulator *bf, int x = -1, int y = -1)
            : Robot(name, bf, x, y), movingRobot(name, bf, x, y), MedicBot(name, bf, x, y) {}
        MercyBot(Robot &&other)
            : Robot(std::move(other)),
            MedicBot(std::move(other)) {}
        virtual Robot ***look() override;
        void heal(Robot ***) override;
        virtual void move() override;
        virtual void displaylook(Robot ***);
        virtual void deletelook(Robot ***);
        virtual void action() override;
        virtual void upgrade() override;
};