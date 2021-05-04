#include "leon3_ev_handling.h"
#include "leon3_hw_irqs.h"
#include "leon3_uart.h"
#include "leon3_bprint.h"

#include "leon3_monotonic_clk.h"
#include "leon3_timer_unit_drv.h"
#include "leon3_timing_service_config.h"
#include "leon3_ttre.h"

void ROBOTAvoidObstacles(void){
	leon3_print_string(" Avoid Obstacles\n");
}
void ROBOTAdvanceInPath(void){
	leon3_print_string(" Advance\n");
}
void ROBOTCalculatePath(void){
	leon3_print_string(" Calculate Path\n");
}

// 10 TICKS PER SECOND
#define TICKS_PER_SECOND 10

int main() {
	uint32_t aux1,aux2;
	//Install handlers for enable and disable irqs
	leon3_install_handler(LEON3_SPARC_ENABLE_IRQ_TRAPVECTOR,leon3_trap_handler_enable_irqs);
	leon3_install_handler(LEON3_SPARC_DISABLE_IRQ_TRAPVECTOR ,
	leon3_trap_handler_disable_irqs);

	//Init Monotonic Clock
	InitMonotonicClock(date_time_to_Y2K(16, 4, 21, 0, 0, 1 ));

	TTRE_InitService(TICKS_PER_SECOND);
	TTRE_ProgramRoutine(ROBOTAvoidObstacles, 00000);
	TTRE_ProgramRoutine(ROBOTCalculatePath, 100000);
	TTRE_ProgramRoutine(ROBOTAvoidObstacles, 200000);
	TTRE_ProgramRoutine(ROBOTAdvanceInPath, 300000);
	TTRE_ProgramRoutineEveryTick(UpdateMonotonicClock);

	//Init Timing Service
	InitTimingService(TICKS_PER_SECOND, IRQHandlerExecuteProgrammedRoutines);

	aux2=0;

	while(1){
		aux1=GetUniversalTime_Y2K();
		//Cada segundo mostramos el tiempo
		if(aux1!=aux2){
			leon3_sys_call_disable_irqs();
			print_date_time_from_Y2K(aux1);
			aux2=aux1;
			leon3_sys_call_enable_irqs();
		}
	}
	return 0;
}
