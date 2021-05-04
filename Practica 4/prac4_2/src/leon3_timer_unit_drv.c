/*
 * leon3_timer_unit_ctrl.c
 *
 *  Created on: Mar 19, 2013
 *      Author: user
 */

#include "leon3_types.h"


//*******************************************************************
/** \brief structure for controlling Timer Registers */

struct Timer_regs{

	/** \brief Timer Counter Value Register */
	volatile uint32_t CounterValue;

	/** \brief Timer Reload Value Register */
	volatile uint32_t ReloadValue;

	/** \brief Timer Control Register */
	volatile uint32_t Ctrl;

	uint32_t 		  reserved;

};

//! LEON3 Timers integrated in the Timer Unit

#define LEON3_TIMER_UNIT_TIMERS 					2

//! LEON3 Timer Ctrl Masks

#define LEON3_TIMER_CHAIN_WITH_PREC_TIMER 	(0x020)
#define LEON3_TIMER_CLEAR_IRQ 				(0x010)
#define LEON3_TIMER_ENABLE_IRQ 				(0x008)
#define LEON3_TIMER_LOAD_TIMER 				(0x004)
#define LEON3_TIMER_RESTART 				(0x002)
#define LEON3_TIMER_ENABLE 					(0x001)


//*******************************************************************

/** \brief structure for controlling Timer Unit Registers */

struct TimerUnit_regs
{

	/** \brief Timer Unit Scaler Register */
	volatile uint32_t ScalerValue;			/* 0x80000300 */
	/** \brief Timer Unit Scaler Reload Value Register */
	volatile uint32_t ScalerReloadValue; 	/* 0x80000304 */
	/** \brief Timer Unit Configuration Register */
	volatile uint32_t ConfigReg; 			/* 0x80000308 */

	uint32_t 		 reserved; 				/* 0x8000030A */

	/** \brief Registers of the Timers*/
	volatile struct Timer_regs			Timer[LEON3_TIMER_UNIT_TIMERS];

};


//! LEON3 Timing Unit Masks

#define LEON3_TIMER_UNIT_ACTIVE_FREEZE (0x200)
#define LEON3_TIMER_UNIT_SEPARATE_IRQS (0x100)


//! LEON3 Timing Unit
struct TimerUnit_regs *pLEON3_TimerUnit_REGS = (struct TimerUnit_regs *)0x80000300;

//*******************************************************************

void leon3_TimerUnit_SetConfiguration( uint32_t scalerValue
									, bool_t timer_freeze_during_debug
									, bool_t separate_interrupts ){


	if(timer_freeze_during_debug)
		pLEON3_TimerUnit_REGS->ConfigReg|=LEON3_TIMER_UNIT_ACTIVE_FREEZE;
	else
		pLEON3_TimerUnit_REGS->ConfigReg&=(~LEON3_TIMER_UNIT_ACTIVE_FREEZE);

	if(separate_interrupts)
		pLEON3_TimerUnit_REGS->ConfigReg|=LEON3_TIMER_UNIT_SEPARATE_IRQS;
	else
		pLEON3_TimerUnit_REGS->ConfigReg&=(~LEON3_TIMER_UNIT_SEPARATE_IRQS);

	pLEON3_TimerUnit_REGS->ScalerReloadValue=scalerValue;
	pLEON3_TimerUnit_REGS->ScalerValue=scalerValue;

}


//*******************************************************************

uint8_t leon3_TimerConfig(uint8_t timerId
					, uint32_t timerValue
					, bool_t chain_with_prec_timer
					, bool_t restart_timer){


	uint8_t error=0;

	if(timerId < LEON3_TIMER_UNIT_TIMERS ){

		//Completar
		pLEON3_TimerUnit_REGS->Timer[timerId].CounterValue = timerValue;
				pLEON3_TimerUnit_REGS->Timer[timerId].ReloadValue = timerValue;
				if (chain_with_prec_timer){
					pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl |= LEON3_TIMER_CHAIN_WITH_PREC_TIMER;
				}
				else {
					pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl &= ~LEON3_TIMER_CHAIN_WITH_PREC_TIMER;
				}

				if (restart_timer){
					pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl |= LEON3_TIMER_RESTART;
				}
				else {
					pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl &= ~LEON3_TIMER_RESTART;
				}

		// Se carga el valor
		pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl|=LEON3_TIMER_LOAD_TIMER;

	}else
		error=1;

	return error;

}

//*******************************************************************

uint8_t leon3_TimerEnableIRQ(uint8_t timerId){

	uint8_t error=0;

	if(timerId < LEON3_TIMER_UNIT_TIMERS ){

		//Completar
		pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl |= LEON3_TIMER_ENABLE_IRQ;

	}else
		error=1;

	return error;


}

//*******************************************************************

uint8_t leon3_TimerDisableIRQ(uint8_t timerId){

	uint8_t error=0;

	if(timerId < LEON3_TIMER_UNIT_TIMERS ){

		//Completar
		pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl &= ~LEON3_TIMER_ENABLE_IRQ;

	}else
		error=1;

	return error;


}

//*******************************************************************

uint8_t leon3_TimerEnable(uint8_t timerId){

	uint8_t error=0;

	if(timerId < LEON3_TIMER_UNIT_TIMERS ){

		//Completar
		pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl |= LEON3_TIMER_ENABLE;

	}else
		error=1;

	return error;


}

//*******************************************************************

uint8_t leon3_TimerDisable(uint8_t timerId){

	uint8_t error=0;

	if(timerId < LEON3_TIMER_UNIT_TIMERS ){

		//Completar
		pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl &= ~LEON3_TIMER_ENABLE;

	}else
		error=1;

	return error;


}

//*******************************************************************

uint8_t leon3_TimerUnit_ClearIRQ(uint8_t timerId){

	uint8_t error=0;

	if(timerId < LEON3_TIMER_UNIT_TIMERS ){

		//Completar
		pLEON3_TimerUnit_REGS->Timer[timerId].Ctrl &= ~ LEON3_TIMER_CLEAR_IRQ;



	}else
		error=1;

	return error;

}

