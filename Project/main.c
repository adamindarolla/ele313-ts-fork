#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ch.h"
#include "hal.h"
#include "memory_protection.h"
#include <main.h>
#include "leds.h"
#include "spi_comm.h"
#include "sensors/proximity.h"
#include "motors.h"

messagebus_t bus;
MUTEX_DECL(bus_lock);
CONDVAR_DECL(bus_condvar);


int main(void)
{

    halInit();
    chSysInit();
    mpu_init();

    // Proximity
    messagebus_init(&bus, &bus_lock, &bus_condvar);
    proximity_start(0);
    calibrate_ir();

    //LED
    clear_leds();
    spi_comm_start();

    //Motors
    motors_init();

// our stuff
    bool wallsexplored=0;
    bool wall; // is this the boolean for if its left or right wall following??
    bool haveifoundawallyet=0; // this is for if its found a wall yet
    int distnorth; // distances travelled in each direction
    int distsouth;
    int disteast;
    int distwest;
    int SensorValue[8]; // array for sensor values


	// MOTORS
	void left_motor_set_speed(int motor_speed);
	void right_motor_set_speed(int motor_speed)

	//this is from gemini
	enum RobotState { NOWALL, FOUNDWALL };
	RobotState currentState = NOWALL;

	int followSide = -1; // 0 for Right, 1 for Left
	int threshold = 150; // Distance to trigger "Wall Found"

	
    // Task 1
    // check if its next to a wall
	// if yes - go forwards
	// if no - enter wall following mode
	// decide which side the wall is on

	//infinite goon loop Ithis is for whole thing)
	
	while(1) {
		
    //check if any walls nearby and which is strongest sensor
	int maxVal = 0; //
	int strongestSensor = -1; // Start with -1 (meaning no obstacle seen) - ok I do not get this bit
	int threshold = 50; // Minimum value before sensors kick in
		
	for (int i = 0; i < 8; i++) {
    int currentVal = get_prox(i);
    if (currentVal > maxVal) {
        maxVal = currentVal;
        strongestSensor = i;
    }
}
		if (currentState == NOWALL) {
			if (maxVal > threshold) {
			// this is when it has detected a wall
			// finding which side of puck max sensor reading is on
    switch (strongestSensor) {
        case 0
			followSide = 0; //right
			currentState = FOLLOWING;
        case 1
			followSide = 0;
			currentState = FOLLOWING;
        case 2
			followSide = 0;
			currentState = FOLLOWING;
        case 3
			followSide = 0;
			currentState = FOLLOWING;
		case 4
			followSide = 1; //left
			currentState = FOLLOWING;
        case 5
			followSide = 1;
			currentState = FOLLOWING;
        case 6
			followSide = 1;
			currentState = FOLLOWING;
        case 7
			followSide = 1;
			currentState = FOLLOWING;
	}	else   {
			// no wall detected - set motor speed to arbitrary value
  void left_motor_set_speed(int 200);
  void right_motor_set_speed(int 200); 
		

 

// this is where we need the bit for wall following
    
    			}

    }
}

#define STACK_CHK_GUARD 0xe2dee396
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

void __stack_chk_fail(void)
{
    chSysHalt("Stack smashing detected");
}
