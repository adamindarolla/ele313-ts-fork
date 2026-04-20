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
    int distnorth;
    int distsouth;
    int disteast;
    int distwest;
    int SensorValue[8]; // array for sensor values
    
    // we are palm beach pete
void minAndMaxFunction(int arr[], string fName[], string lName[], int& min, int& max, int siz, int& minPosition, int& maxPosition)

    
    // Task 1
    
    while(1) {
        for (unsigned int i = 0; i < 8; i++) {
            SensorValue[i] = get_prox(i);
        }
    delay_ms(100);
    }
    //switch int SensorValue[i]{
    //case SensorValue[1] 
    
        
    //check if no walls nearby
    for (int i = 0; i < siz; i++)
	{
		if (min > arr[i])
		{
			min = arr[i];
			minPosition = i;
		}

		if (arr[i] > max)
		{
			max = arr[i];
			maxPosition = i;

// finding which side of puck max sensor reading is on
    switch (maxPosition) {
        case 0
			bool wall = 0; //right
        case 1
			bool wall = 0;
        case 2
			bool wall = 0;
        case 3
			bool wall = 0;
		case 4
			bool wall = 1; //left
        case 5
			bool wall = 1;
        case 6
			bool wall = 1;
        case 7
			bool wall = 1;
	}
 


    
    			}

    }
}

#define STACK_CHK_GUARD 0xe2dee396
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

void __stack_chk_fail(void)
{
    chSysHalt("Stack smashing detected");
}
