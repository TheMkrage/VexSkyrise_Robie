# VexSkyrise_Robie
The code for Robie, the 2014-2015 VEX Robot for VEX Team 9983B. 

## Robot Overview
Our robot can stack a 6 section tall skyrsie along with 6 cubes on the skyrise in a single match.  The drive train is H-Drive and the lift is a nested elevator. Our claw is a modified vex claw that is modified to open wider.  Also, there is a passive cube claw below the skyrise claw.  Our robot does not contain any pneumatics.

### Sensors
1. Gyro
2. 2 Encoders on Drive
3. 1 Encoder on the Elevator
4. 1 Bumper Switch to Stop the Elevators
5. 1 Bumper Switch to Reset the Gyro

### Skills
*Robot:* 

## Code Overview

### Features
1. LCD Auto Picker
2. Straight Strafing
3. 8 Point and 12 Point Auto
4. PID Loops that are used in Auto

Auto  | Method Name
------------- | -------------
12 Point Red  | startRed12();
12 Point Blue  | startBlue12();
8 Point Red  | startRed8();
8 Point Blue | startBlue8();
