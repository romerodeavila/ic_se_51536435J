/*
 * leon3_ttre.c
 *
 *  Created on: Apr 2, 2013
 *      Author: user
 */

#include "leon3_timing_service_config.h"
#include "leon3_timer_unit_drv.h"
#include "leon3_types.h"

uint8_t TTRE_TicksPerSecond=1;

#define TICKS_TO_MICROSECS 		(1000000/TTRE_TicksPerSecond)

//*******************************************************************
/** \brief time_triggered_routine_execution descriptor */

struct ttre_descriptor_t{

	/** \brief routine */
	void 		(* routine) (void);


	/** \brief pointer to the next descriptor */
	struct ttre_descriptor_t * next;

};


/** \brief MAX NUMBER OF DESCRIPTORS */
#define MAX_NUMBER_OF_TTRE_DESCRIPTORS 			30

//*******************************************************************
/** \brief ttre descriptor pool*/

static struct ttre_descriptor_t 		ttre_descriptors_POOL[MAX_NUMBER_OF_TTRE_DESCRIPTORS];

//*******************************************************************
/** \brief used irq handler routines */

static uint8_t used_ttre_descriptor=0;


/** \brief ttre programs */
static struct ttre_descriptor_t * ttre_program[TIMING_SERVICE_HYPER_PERIOD_IN_TICKS];

static struct ttre_descriptor_t * ttre_every_tick=NULL;

//*******************************************************************
/** \brief TickCounter*/
static uint32_t TTRE_TickCounter=0;

//*******************************************************************


void IRQHandlerExecuteProgrammedRoutines(void){


	struct ttre_descriptor_t * aux=ttre_every_tick;

	//Routines programmed Every Tick
	while(aux){
		if(aux->routine){
			aux->routine();
		}
		aux=aux->next;
	}

	//Routines programmed in specific ticks

	aux=ttre_program[TTRE_TickCounter];
	while(aux){
			if(aux->routine){
				aux->routine();
			}
			aux=aux->next;
	}

		//leon3_print_uint32(TTRE_TickCounter);
	TTRE_TickCounter++;

	if(TTRE_TickCounter>=TIMING_SERVICE_HYPER_PERIOD_IN_TICKS){
			TTRE_TickCounter=0;
	}

	leon3_TimerUnit_ClearIRQ(0);

}

//*****************************************************************************

void TTRE_InitService(uint8_t ticks_per_second){

	uint32_t i;

	//Init descriptors
	used_ttre_descriptor=0;

	TTRE_TicksPerSecond=ticks_per_second;

	for (i=0; i< (TIMING_SERVICE_HYPER_PERIOD_IN_TICKS); i++)
		ttre_program[i]=NULL;


}

//*****************************************************************************

uint8_t TTRE_ProgramRoutine(void (* routine) (void)
						 	 	 , uint32_t hyperperiod_offset_in_microseconds
						 	 	 , uint32_t WCET_in_microseconds){

	uint8_t error=0;
	uint16_t offset_in_ticks;

	struct ttre_descriptor_t * pAux=NULL;

	if(used_ttre_descriptor<MAX_NUMBER_OF_TTRE_DESCRIPTORS){
		pAux=&ttre_descriptors_POOL[used_ttre_descriptor];
		used_ttre_descriptor++;

	}

	if(pAux!=NULL){
		pAux->routine=routine;
		pAux->next=NULL;
		offset_in_ticks=hyperperiod_offset_in_microseconds/TICKS_TO_MICROSECS;
		//offset_in_ticks=hyperperiod_offset_in_microseconds;
		if(offset_in_ticks<TIMING_SERVICE_HYPER_PERIOD_IN_TICKS){

			if(ttre_program[offset_in_ticks]==NULL){
				ttre_program[offset_in_ticks]=pAux;

			}else{
				struct ttre_descriptor_t * pAux2=ttre_program[offset_in_ticks];
				while(pAux2->next){
					pAux2=pAux2->next;
				}
				pAux2->next=pAux;
			}
		}else
			error=-2;

	}else
		error=-1;

	return error;
}


//*****************************************************************************

uint8_t TTRE_ProgramRoutineEveryTick(void (* routine) (void)){

	uint8_t error=0;

	struct ttre_descriptor_t * pAux=NULL;

	if(used_ttre_descriptor<MAX_NUMBER_OF_TTRE_DESCRIPTORS){
		pAux=&ttre_descriptors_POOL[used_ttre_descriptor];
		used_ttre_descriptor++;

	}

	if(pAux!=NULL){
		pAux->routine=routine;
		pAux->next=NULL;

		if(ttre_every_tick==NULL){
			ttre_every_tick=pAux;

		}else{
				struct ttre_descriptor_t * pAux2=ttre_every_tick;
				while(pAux2->next){
					pAux2=pAux2->next;
				}
				pAux2->next=pAux;
		}

	}else
		error=-1;

	return error;

}
