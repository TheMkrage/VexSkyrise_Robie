/* Welcome Nick!
If you are reading this, chances are you are at state! I hope its cool.

To run auto, make sure that in Competition Code.c , the bool called "testingAuto" is set to true (Ctrl F to find it).
Then, you download code to robot and start.
Button 7D will run auto.  Prior to running auto, MAKE SURE, that the correct auto is selected on LCD.
If you feel lazy, there is a bool called "manualPickAuto".  Set this to true and then place the method
of the auto you wish to use in the if statement.
Just make sure to change it back if you use this feature

I'm pretty sure all autos have the right path, but if one does not, you are a smart boy and do not be afraid to call.

If you run into problems, some things that have been changed to fix problems in the past are the initial strafe power,
and the wait statements between each aspect of auto.

Our auto is still battery voltage dependent so switch out every 5-7 runs

BTW, BLUE12 was tuned at snakebot and hasnt been touched since, so the constants there will be most accurate.
Its ok to set multiple constants from different autos with the same value, but do not use the same constant in different autos.

Here is what you need to do to tune auto (and I recommend in this order)
BLUE12
BLUE8 (not a priority, but if you have time)
RED12
RED8  (not a priority, but if you have time)
Make small pole auto (same 4 both sides)
Test all other auto (the strafe ones) and make sure everything works because they have never been testing. */


const int  BLUE8_STRAFE_TIME =350;
const int  BLUE8_FIRST_BACKWARDS_FROM_MUSTARD_HOLDER = 190;
const int  BLUE8_SKYRISE_BASE_ANGLE =-500;
const int  BLUE8_MUSTARD_FORWARD =-92;
const int  BLUE8_LITTLE_ELEVATOR= 280;
const int  BLUE8_FULL_HEIGHT_ELEVATOR =700;
const int  BLUE8_FORWARD_TO_BASE =-125;
const int  BLUE8_TIME_TO_BRING_DOWN_EL =1200;
const int  BLUE8_FINAL_BACKWARDS = 150;

const int  BLUE12_STRAFE_TIME =400;
const int  BLUE12_FIRST_BACKWARDS_FROM_MUSTARD_HOLDER = 190;
const int  BLUE12_SKYRISE_BASE_ANGLE =-455;
const int  BLUE12_MUSTARD_FORWARD =-100;
const int  BLUE12_LITTLE_ELEVATOR= 180;
const int  BLUE12_FULL_HEIGHT_ELEVATOR =700;
const int  BLUE12_FORWARD_TO_BASE =-125;
const int  BLUE12_TIME_TO_BRING_DOWN_EL =1200;
const int  BLUE12_BACKWARDS_FROM_BASE = 150;
const int  BLUE12_ANGLE_TO_GET_CUBE = -900;
const int  BLUE12_FORWARD_TO_CUBE = 320;//
const int  BLUE12_ELEVATOR_CUBE_HEIGHT = BLUE12_FULL_HEIGHT_ELEVATOR + 390;
const int  BLUE12_ANGLE_TO_GET_TO_BASE_WITH_CUBE = 400;
const int  BLUE12_FORWARD_TO_BASE_WITH_CUBE = 80;

const int  RED12_STRAFE_TIME =300;
const int  RED12_FIRST_BACKWARDS_FROM_MUSTARD_HOLDER = 180;
const int  RED12_SKYRISE_BASE_ANGLE = 595;
const int  RED12_MUSTARD_FORWARD =-95;
const int  RED12_LITTLE_ELEVATOR= 180;
const int  RED12_FULL_HEIGHT_ELEVATOR =700;
const int  RED12_FORWARD_TO_BASE =-110;
const int  RED12_TIME_TO_BRING_DOWN_EL =1200;
const int  RED12_BACKWARDS_FROM_BASE = 150;
const int  RED12_ANGLE_TO_GET_CUBE = 930;
const int  RED12_FORWARD_TO_CUBE = 320;
const int  RED12_ELEVATOR_CUBE_HEIGHT = RED12_FULL_HEIGHT_ELEVATOR + 390;
const int  RED12_ANGLE_TO_GET_TO_BASE_WITH_CUBE = -320;
const int  RED12_FORWARD_TO_BASE_WITH_CUBE = 80;

const int  RED8_STRAFE_TIME =350;
const int  RED8_FIRST_BACKWARDS_FROM_MUSTARD_HOLDER = 180;
const int  RED8_SKYRISE_BASE_ANGLE = 595;
const int  RED8_MUSTARD_FORWARD =-95;
const int  RED8_LITTLE_ELEVATOR= 180;
const int  RED8_FULL_HEIGHT_ELEVATOR =700;
const int  RED8_FORWARD_TO_BASE =-110;
const int  RED8_TIME_TO_BRING_DOWN_EL =1200;
const int  RED8_FINAL_BACKWARDS = 150;
