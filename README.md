# Robot-War-Simulator
Turn based 2D battlefield simulator that simulates a robot war.

RoboCop
- Moves once per turn to a location that does not contain another robot.
- Fires thrice per turn at random positions within a city block distance of 10.
- Upgraded to TerminatorRoboCop after shooting and killing 3 robots.

Terminator
- Moves within its immediate 3x3 neighborhood each turn.
- Does not fire.
- Prefers stepping into enemy-occupied locations to kill them.
- Upgraded to TerminatorRoboCop after killing 3 robots by stepping.

TerminatorRoboCop
- Moves like a Terminator, stepping and killing robots in its path.
- Fires thrice per turn like RoboCop within a city block distance of 10.
- Upgraded to UltimateRobot after killing 3 more robots.

BlueThunder
- Does not move or observe surroundings.
- Fires once per turn at a neighboring cell, rotating clockwise each turn.
- Upgraded to MadBot after killing 3 robots.

MadBot
- Does not move.
- Fires once per turn at a random neighboring cell.
- Upgraded to RoboTank after killing 3 robots.

RoboTank
- Does not move.
- Fires once per turn at a random location on the entire battlefield.
- Upgraded to UltimateRobot after killing 3 robots.

UltimateRobot

- Moves like TerminatorRoboCop, stepping and killing other robots.
- Fires three times per turn at random battlefield locations.
- Final upgrade level, no further evolution.
