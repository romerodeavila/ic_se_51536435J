#include "leon3_ev_handling.h"
#include "leon3_hw_irqs.h"
#include "leon3_monotonic_clk.h"
#include "leon3_timer_unit_drv.h"
#include "leon3_timing_service_config.h"

#define TICKS_PER_SECOND 10

int main()
{
	uint32_t aux1,aux2;

	//Instalar manejadores para habilitar y deshabilitar irqs
	leon3_install_handler(LEON3_SPARC_ENABLE_IRQ_TRAPVECTOR,
	leon3_trap_handler_enable_irqs);
	leon3_install_handler(LEON3_SPARC_DISABLE_IRQ_TRAPVECTOR ,
	leon3_trap_handler_disable_irqs);

	//Inicializar Reloj Monotónico.
	InitMonotonicClock(date_time_to_Y2K(4, 5, 21, 14, 21, 1 ));

	//Iniciar el Servicio de Temporización para que se generen
	//10 interrupciones por segundo, y en cada interrupción
	//se invoque a la rutina que actualiza el reloj monotónico
	InitTimingService(TICKS_PER_SECOND,
	IRQHandlerUpdateMonotonicClock);

	aux2=0;

	while(1){
		aux1=GetUniversalTime_Y2K();
		//Cada 10 segundos imprimimos el tiempo
		if(((aux1%10)==0)&& aux1!=aux2){
			leon3_mask_irq(8); //Inicio sección crítica
			print_date_time_from_Y2K(aux1);
			leon3_unmask_irq(8); //Fin sección crítica
			aux2=aux1;
		}
	}
	return 0;
}
