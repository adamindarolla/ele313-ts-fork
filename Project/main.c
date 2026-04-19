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

    int selector;
    int wheelspeed=500;
    /* Infinite loop. */
    while (1)
    {
    	left_motor_set_speed(wheelspeed);
    	right_motor_set_speed(-wheelspeed);
    	selector=get_selector();
    			while (selector>0)
    			{

    		set_body_led(1);
    		chThdSleepMilliseconds(300);
    		set_body_led(0);
    		chThdSleepMilliseconds(300);

    		if (selector==1){
    			wheelspeed=wheelspeed*-1;

    		}
    		--selector;
    			}
// something random in file
    }
}

#define STACK_CHK_GUARD 0xe2dee396
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

void __stack_chk_fail(void)
{
    chSysHalt("Stack smashing detected");
}
