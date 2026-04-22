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



// adam was here

messagebus_t bus;
MUTEX_DECL(bus_lock);
CONDVAR_DECL(bus_condvar);



//tom was here
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

	rgb_led_name_t allRGBs[] = {LED2, LED4, LED6, LED8};

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
	int minirread = 300;
	int maxirread = 1000;
	


	

	
	enum RobotState { NOWALL, FOUNDWALL, EXPLORING };
	enum RobotState currentState = NOWALL;

	int followSide = 0; // 1 for Right, -1 for Left
	int threshold = 150; // Distance to trigger "Wall Found"
	int maxVal = 0;
	int strongestSensor;
	
    // Task 1
    // check if its next to a wall
	// if yes - go forwards
	// if no - enter wall following mode
	// decide which side the wall is on

	//infinite goon loop Ithis is for whole thing)
	
	while(1) {
		
    //check if any walls nearby and which is strongest sensor
	int maxVal = 0; 
		
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
			followSide = 1; //right
			currentState = FOUNDWALL;
        case 1
			followSide = 1;
			currentState = FOUNDWALL;
        case 2
			followSide = 1;
			currentState = FOUNDWALL;
        case 3
			followSide = 1;
			currentState = FOUNDWALL;
		case 4
			followSide = -1; //left
			currentState = FOUNDWALL;
        case 5
			followSide = -1;
			currentState = FOUNDWALL;
        case 6
			followSide = -1;
			currentState = FOUNDWALL;
        case 7
			followSide = -1;
			currentState = FOUNDWALL;
	}
				// sets which sensors are preffered side and offside
		if (followSide == 1){
			int prefFront = 0;
			int prefCorner = 1;
			int prefSide = 2;
			int prefBack = 3;
			int offFront = 7;
			int offCorner = 6;
			int offSide = 5:
			int offBack = 4;
		} else {
			int prefFront = 7;
			int prefCorner = 6;
			int prefSide = 5;
			int prefBack = 4;
			int offFront = 0;
			int offCorner = 1;
			int offSide = 2:
			int offBack = 3;
		}	
	}	else   {
			// no wall detected - set motor speed to arbitrary value
left_motor_set_speed(1000);
right_motor_set_speed(1000); 
    			}	
	}


// this is where we need the bit for wall following
		if (currentstate==FOUNDWALL) {
			// check if robot is close enough to the wall, turn towards wall
			if (prefSide<minirread){
				//turn towards wall
			}
			// check if robot is far enough away from any wall, turn away from wall
			if (prefSide>maxirread){
				//turn away from preffered wall
			}
			if (offSide>maxirread){
				// turn away from offside wall
			}
			//if robot is near 2 walls, turn relative to proximity of both walls
			if (prefSide>maxirread && offSide>maxirread){
				// if robot is too close to both walls, turn around 180 ish degrees
				
			}
			// if robot is too close to both walls, turn around 180 ish degrees

			// if wall is infront of robot, turn away from desired side

			
		}

		// exploration mode
	if (currentState == EXPLORING) {
	// check if wall is reached
		if SensorValue[0] > threshold || SensorValue[7] > threshold {
			left_motor_set_speed(500);
			right_motor_set_speed(-500);
			delay_ms(500);
			currentState = FOUNDWALL;

				// Here we need it to just do the wall following function for a small amount of time - in case there is any obstacle
				// or if it has not rotated exactly 90 degrees
				// then it turns 90 degrees

			delay_ms(3000);
			right_motor_set_speed(-500);
			left_motor_set_speed(500);
			delay_ms(500);

			if fabs( SensorValue[3] - SensorValue[4]) <= thresholdRear {
				currentState = EXPLORING;

						}
		
					}
				}
			}
		}

	if currentState = NOWALL {
		for (int i = 0; i <= 4; i++) 
		set_rgb_led(allRGBs[i], 10 , 0 , 0 );
	}
	else if currentState = FOUNDWALL {
		for (int i = 0; i <= 4; i++) 
		set_rgb_led(allRGBs[i], 0 , 10 , 0 );
	}
	else if currentState = EXPLORING {
		for (int i = 0; i <= 4; i++) 
		set_rgb_led(allRGBs[i], 0 , 0 , 10);
	}
	
	
		
	
	}
		

		
	}

#define STACK_CHK_GUARD 0xe2dee396
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

void __stack_chk_fail(void)
{
    chSysHalt("Stack smashing detected");
}
