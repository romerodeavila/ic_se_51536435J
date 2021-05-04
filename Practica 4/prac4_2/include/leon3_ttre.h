/*
 * leon3_ttre.h
 *
 *  Created on: Apr 2, 2013
 *      Author: user
 */

#ifndef LEON3_TTRE_H_
#define LEON3_TTRE_H_



//Init Time Triggered Routine Execution Service
void TTRE_InitService(uint8_t ticks_per_second);


/** \brief Program Time Triggered Routine
 *
 *	\param routine routine to install
 *
 *	\param offset_in_microseconds offset in microseconds
 *
 *	\return 0  if routine is correctly programmed
 *			-1 if service is out of descriptors
 *			-2 if offset is out of hyperperiod
 */

uint8_t TTRE_ProgramRoutine(void (* routine) (void)
						 , uint32_t hyperperiod_offset_in_microseconds);


/** \brief Program Time Triggered Routine for every Tick
 *
 *	\param routine routine to install
 *
 *	\return 0  if routine is correctly programmed
 *			-1 if service is out of descriptors
 */

uint8_t TTRE_ProgramRoutineEveryTick(void (* routine) (void));


void IRQHandlerExecuteProgrammedRoutines(void);

#endif /* LEON3_TTRE_H_ */
