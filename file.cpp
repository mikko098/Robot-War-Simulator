/**********|**********|**********|
Program: file.cpp
Course: Data Structures and Algorithms
Trimester: 2410
Name: Basil Aiman Bin Khairulanwar, Chan Ga Wai, Lai Cal Wyn, Mishal Mann Nair
ID: 1231303408, 1221305898, 1231303570, 1221305145
Lecture Section: TC2L
Tutorial Section: TT5L
Email: 1231303408@student.mmu.edu.my, 1221305898@student.mmu.edu.my, 1231303570@student.mmu.edu.my, 1221305145@student.mmu.edu.my
Phone: +60 10-220 6122, +60 11-6412 9980, +60 11-1083 1797, +60 19-443 2285
**********|**********|**********/
#include "file.h"

using namespace std;

Robot* InfoParser::identifyRobot(const string &rob, const string &name, Simulator *simulator, int x , int y )
{
    if (rob == "RoboCop")
    {
        return new RoboCop(name, simulator, x, y);
    }
    else if (rob == "Terminator")
    {
        return new Terminator(name, simulator, x, y);
    }
    else if (rob == "BlueThunder")
    {
        return new BlueThunder(name, simulator, x, y);
    }
    else if (rob == "Madbot")
    {
        return new MadBot(name, simulator, x, y);
    }
    else if (rob == "RoboTank")
    {
        return new RoboTank(name, simulator, x, y);
    }
    else if (rob == "UltimateRobot")
    {
        return new UltimateRobot(name, simulator, x, y);
    }
    else if (rob == "MedicBot")
    {
        return new MedicBot(name, simulator, x, y);
    }
    else if (rob == "MercyBot")
    {
        return new MercyBot(name, simulator, x, y);
    }
    else
    {
        throw string("Robot type not recognized.");
    }
    
}

void InfoParser::parseFile(const string &filename)
{
    ifstream inputFile(filename);
    if (!inputFile)
    {
        throw string("Error opening the input file.");
    }

    string line;
    while (getline(inputFile, line))
    {
        istringstream iss(line);
        string key;

        iss >> key;
        if (key == "M")
        {
            // ignore "M by N: "
            iss.ignore(8);
            // read N
            iss >> N;
            // read M
            iss >> M;
            // create 
            simulator = new Simulator(N, M);
        }
        else if (key == "steps:")
        {
            iss >> steps;
            simulator->setSteps(steps);
        }
        else if (key == "robots:")
        {
            iss >> numRobots;
            simulator->setnumRobots(numRobots);
        }
        else
        {
            // Read robot details
            string type = key;
            string name;
            string posX, posY;
            int x, y;
            iss >> name >> posX >> posY;

            if (posX == "random" || posY == "random")
                {
                    Robot *newRobot = identifyRobot(type, name, simulator);
                    simulator->addToLinkedList(newRobot);
                }
            else
                {
                    x = stoi(posX);
                    y = stoi(posY);
                    Robot *newRobot = identifyRobot(type, name, simulator, x, y);
                    simulator->addToLinkedList(newRobot);
                }
        }
    }

    inputFile.close();
}

void InfoParser::runSimulation(const string &filename)
{
    // create an output file stream using the filename provided
    ofstream outputFile(filename);

    // check if file name is valid and can be opened; else use terminal to display output
    if (outputFile.is_open())
    {
        simulator->setOutputFile(outputFile);
    }

    // print information regarding the simulation as provided in the input text file
    outputFile << "Grid Dimensions: " << N << " by " << M << endl;
    outputFile << "Steps: " << steps << endl;
    outputFile << "Number of Robots: " << numRobots << endl;
    simulator->displayRobotQueue();

    // run simulation
    simulator->runProgram();

    // display battlefield at the end of the simulation
    simulator->displayBattlefield();

    // display the robots alive on the battlefield
    simulator->displayRobotQueue();

    if (outputFile.is_open())
    {
        outputFile.close();
    }
}