/*  Test_task
 *
 *  This routine serves as a test task.  It verifies the basic task
 *  switching capabilities of the executive.
 *
 *  Input parameters:  NONE
 *
 *  Output parameters:  NONE
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.OARcorp.com/rtems/license.html.
 *
 *  $Id: tasks.c,v 1.7.2.1 2000/05/05 12:58:06 joel Exp $
 */

#include <rtems.h>
#include <leon3_bprint.h>

/* functions */

rtems_task Init(rtems_task_argument argument);

rtems_task ROBOTAvoidObstacles(rtems_task_argument unused);
rtems_task ROBOTAdvanceInPath(rtems_task_argument unused);
rtems_task ROBOTCalculatePath(rtems_task_argument unused);
rtems_status_code task_delay_until(rtems_interval ticks_from_boot);

/* global variables */

/*
 *  Keep the names and IDs in global variables so another task can use them.
 */

extern rtems_id Task_id[4]; /* array of task ids */
extern rtems_name Task_name[4]; /* array of task names */

/* configuration information */

#include <bsp.h> /* for device driver prototypes */

#define CONFIGURE_INIT
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_TASKS             4

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_EXTRA_TASK_STACKS         (3 * RTEMS_MINIMUM_STACK_SIZE)

#include <confdefs.h>

/*
 *  Handy macros and static inline functions
 */

/*
 *  Macro to hide the ugliness of printing the time.
 */

#define print_time(_s1, _tb, _s2) \
  do { \
    printf( "%s%02d:%02d:%02d   %02d/%02d/%04d%s", \
       _s1, (_tb)->hour, (_tb)->minute, (_tb)->second, \
       (_tb)->month, (_tb)->day, (_tb)->year, _s2 ); \
    fflush(stdout); \
  } while ( 0 )

/*
 *  Macro to print an task name that is composed of ASCII characters.
 *
 */

#define put_name( _name, _crlf ) \
  do { \
    uint32_t c0, c1, c2, c3; \
    \
    c0 = ((_name) >> 24) & 0xff; \
    c1 = ((_name) >> 16) & 0xff; \
    c2 = ((_name) >> 8) & 0xff; \
    c3 = (_name) & 0xff; \
    putchar( (char)c0 ); \
    if ( c1 ) putchar( (char)c1 ); \
    if ( c2 ) putchar( (char)c2 ); \
    if ( c3 ) putchar( (char)c3 ); \
    if ( (_crlf) ) \
      putchar( '\n' ); \
  } while (0)

/*
 *  This allows us to view the "Test_task" instantiations as a set
 *  of numbered tasks by eliminating the number of application
 *  tasks created.
 *
 *  In reality, this is too complex for the purposes of this
 *  example.  It would have been easier to pass a task argument. :)
 *  But it shows how rtems_id's can sometimes be used.
 */

#define task_number( tid ) \
  ( rtems_object_id_get_index( tid ) - \
     rtems_configuration_get_rtems_api_configuration()->number_of_initialization_tasks )

#include <stdio.h>
#include <stdlib.h>

/*
 *  Keep the names and IDs in global variables so another task can use them.
 */

rtems_id Task_id[4]; /* array of task ids */
rtems_name Task_name[4]; /* array of task names */

rtems_task Init(rtems_task_argument argument) {
	rtems_status_code status;
	rtems_time_of_day time;

	puts("\n\n*** CLOCK TICK TEST ***");

	//TODO fijar el time of day a 05/04/2019 utilizando rtems_clock_set

	time.year = 2019;
	time.month = 04;
	time.day = 05;
	time.hour = 0;
	time.minute = 0;
	time.second = 0;
	time.ticks = 0;

	status = rtems_clock_set(&time);

	Task_name[1] = rtems_build_name('T', 'A', '1', ' ');
	Task_name[2] = rtems_build_name('T', 'A', '2', ' ');
	Task_name[3] = rtems_build_name('T', 'A', '3', ' ');

	status = rtems_task_create(Task_name[1], 1, RTEMS_MINIMUM_STACK_SIZE * 2,
	RTEMS_DEFAULT_MODES,
	RTEMS_DEFAULT_ATTRIBUTES, &Task_id[1]);
	status = rtems_task_create(Task_name[2], 1, RTEMS_MINIMUM_STACK_SIZE * 2,
	RTEMS_DEFAULT_MODES,
	RTEMS_DEFAULT_ATTRIBUTES, &Task_id[2]);
	status = rtems_task_create(Task_name[3], 1, RTEMS_MINIMUM_STACK_SIZE * 2,
	RTEMS_DEFAULT_MODES,
	RTEMS_DEFAULT_ATTRIBUTES, &Task_id[3]);

	status = rtems_task_start(Task_id[1], ROBOTAvoidObstacles, 1);
	status = rtems_task_start(Task_id[2], ROBOTAdvanceInPath, 2);
	status = rtems_task_start(Task_id[3], ROBOTCalculatePath, 3);

	status = rtems_task_delete( RTEMS_SELF);
}

rtems_task ROBOTAvoidObstacles(rtems_task_argument unused) {
	//TODO completar.
	rtems_time_of_day time;
	rtems_status_code status;

	for (;;) {
		//Saco el tiempo del sistema con en la anterior práctica
		status = rtems_clock_get(RTEMS_CLOCK_GET_TOD, &time);
		leon3_print_string(" Avoid Obstacles ");
		print_time(" - rtems_clock_get - ", &time, "\n");
		status = task_delay_until(2);
	}
	leon3_print_string(" Avoid Obstacles\n");
}

rtems_task ROBOTAdvanceInPath(rtems_task_argument unused) {
	//TODO completar.
	rtems_time_of_day time;
	rtems_status_code status;
	status = task_delay_until(3); //Offset inicial

	for (;;) {
		status = rtems_clock_get(RTEMS_CLOCK_GET_TOD, &time);
		leon3_print_string(" Advance ");
		print_time(" - rtems_clock_get - ", &time, "\n");
		status = task_delay_until(4);
	}
}

rtems_task ROBOTCalculatePath(rtems_task_argument unused) {
	//completar.
	rtems_time_of_day time;
	rtems_status_code status;
	status = task_delay_until(1); //Offset inicial

	for (;;) {
		//Saco el tiempo del sistema con en la anterior práctica
		status = rtems_clock_get(RTEMS_CLOCK_GET_TOD, &time);
		leon3_print_string(" Calculate Path ");
		print_time(" - rtems_clock_get - ", &time, "\n");
		status = task_delay_until(4);
	}
}

rtems_status_code task_delay_until(rtems_interval ticks_from_boot) {
	rtems_interval current_time;
	rtems_status_code status = 0;
	rtems_clock_get(RTEMS_CLOCK_GET_TICKS_SINCE_BOOT, &current_time);
	if (ticks_from_boot > current_time) {
		status = rtems_task_wake_after(ticks_from_boot - current_time);
	}
	return status;
}
