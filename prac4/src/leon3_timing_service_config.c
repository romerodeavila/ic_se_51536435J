#include "leon3_types.h"

#include "leon3_timer_unit_drv.h"
#include "leon3_ev_handling.h"
#include "leon3_hw_irqs.h"

#include "leon3_timing_service_config.h"

uint8_t TimingServiceTickPerSecond=0;

void InitTimingService(uint8_t ticks_per_second,
						void (* IRQHandler) (void)){


	//Deshabilitar interrupciones
	leon3_sys_call_disable_irqs();

	//Asignar a la variable TimingServiceTickPerSecond el valor del parámetro
	//ticks_per_second
	TimingServiceTickPerSecond=ticks_per_second;

	//Configurar la TimerUnit para que la salida del prescaler
	//tenga un período de 1 microsegundo (para un reloj de 20MHz)
	//se habilite el freeze durante la depuración
	//y se generen interrupciones separadas para los dos timers
	leon3_TimerUnit_SetConfiguration( 19, true , true );

	//Completar: Habilitar el timer 0
	leon3_TimerEnable(0);


	//Configurar el timer 0 para que se genere un underflow periódico con periodo
	//1000000UL/ticks_per_second
	//No encadenar los timers
	//reiniciar el timer tras el underflow
	leon3_TimerConfig(0, 1000000UL/ticks_per_second, false, true);

	//Completar: Instalar IRQHandler como manejador del vector 0x18
	leon3_install_handler(0x18, IRQHandler);


	//Completar: Habilitar iterrupción del timer 0
	leon3_TimerEnableIRQ(0);



	//Completar: Desenmascarar la interrupción externa 8
	leon3_unmask_irq(8);


	//Habilitar interrupciones
	leon3_sys_call_enable_irqs();


}

uint8_t GetTicksPerSecond(){
	return TimingServiceTickPerSecond;
}
