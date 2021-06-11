#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>
#include <RobotOpenGE.h>



/* I/O Setup */
ROJoystick usb1(1);         // Joystick #1 - number represents Joystick "number"
ROPWM leftDrive(0);  //Valid range between 0-255 - in channel 0
ROPWM rightDrive(1); //Same as above - in channel 1
//RODigitalIO dig0In(0, INPUT);    // DIO channel 0, input mode
//ROAnalog analogZero(0);     // Analog Channel 0


void setup()
{
  /* Initiate comms */
  RobotOpen.begin(&enabled, &disabled, &timedtasks);
}


/* This is your primary robot loop - all of your code
 * should live here that allows the robot to operate
 */
void enabled() {
  int leftPower = constrain((usb1.leftY() + usb1.rightX() - 127), 0, 255);
  int rightPower = constrain((usb1.leftY() - usb1.rightX() + 127), 0, 255);

  leftDrive.write(leftPower);
  rightDrive.write(rightPower);
}


/* This is called while the robot is disabled
 * All outputs are automatically disabled (PWM, Solenoid, Digital Outs)
 */
void disabled() {
  // safety code
  leftDrive.detach();
  rightDrive.detach();
}


/* This loop ALWAYS runs - only place code here that can run during a disabled state
 * This is also a good spot to put driver station publish code
 */
void timedtasks() {
//  RODashboard.publish("D0", dig0In.read());
//  RODashboard.publish("Uptime Seconds", ROStatus.uptimeSeconds());
//  RODashboard.publish("Proximity", proximity(analogZero.read()));
//  RODashboard.publish("left Y", usb1.leftY());
//  RODashboard.publish("right x", usb1.rightX());
}


// !!! DO NOT MODIFY !!!
void loop() {
  RobotOpen.syncDS();
}

//converts Ultrasonic Proximity 10-bit output to inches
float proximity(int integer){
 float inches = integer * 5 / 25.4;
 return inches;
}
