#include "leon3_uart.h"

//Estructura de datos que permite acceder a los registros de la
//UART de LEON3

struct UART_regs
{
/** \brief UART Data Register */
volatile uint32_t Data;				/* 0x80000100 */
/** \brief UART Status Register */
volatile uint32_t Status;       	/* 0x80000104 */
/** \brief UART Control Register */
volatile uint32_t Ctrl;				/* 0x80000108 */
/** \brief UART Scaler Register */
volatile uint32_t Scaler;			/* 0x8000010C */
};

//! LEON3 UART A Transmit FIFO is FULL
// Máscara del bit Transmit FIFO Full: 0x200
// Corresponde a que el bit de status TFF está activo
#define LEON3_UART_TFF (0x200)

//Hemos añadido los campos de los registros
//necesarios para implementar las nuevas funciones
#define LEON3_UART_RE  (0x001); // Receiver enable - Control
#define LEON3_UART_RIE (0x004); // Receiver interrupt enable - Control
#define LEON3_UART_LB  (0x080); // Loop back - Control
#define LEON3_UART_TFE (0x004); // Transmit FIFO empty - Status
#define LEON3_UART_LBN (0xFFFFFF7F); // !Loop back -Control

struct UART_regs *pLEON3_UART_REGS= (struct UART_regs *)0x80000100;

// status & máscara
#define leon3_UART_TF_IS_FULL() (LEON3_UART_TFF & pLEON3_UART_REGS->Status)

int8_t leon3_putchar(char c)
{

	uint32_t write_timeout = waitfor_TFF();
	//Espera mientras la cola de transmisión esté llena, hasta que TFF es 0

	if(write_timeout < 0xAAAAA){
		//Escribir el carácter en el registro Data
		pLEON3_UART_REGS -> Data=c;
		//Con -> apuntamos a la dirección del registro Data y guardamos c
	}
	return (write_timeout == 0xAAAAA);
}

char leon3_getchar(){

	return pLEON3_UART_REGS->Data;

}

//función devuelve 1 si y sólo si el campo Transmit_Fifo_EMPTY
//del registro Status de la UART toma valor 1.
//En caso contrario la función devuelve 0.
uint8_t leon3_UART_TF_IS_EMPTY(){
	uint8_t value = pLEON3_UART_REGS->Status & LEON3_UART_TFE;

	return value == (uint8_t) LEON3_UART_TFE;
}

//Pone a 1 el campo Receiver_enable del registro de control de la UART-A
//sin modificar el resto de campos de ese registro habilitando
//la recepción de datos a través de la UART.
void leon3_UART_RX_ENABLE(){
	pLEON3_UART_REGS->Ctrl = pLEON3_UART_REGS->Ctrl | LEON3_UART_RE;
}

//Pone a 1 el campo Receiver-interrupt_enable del registro de control de la UART-A
//sin modificar el resto de campos de ese registro habilitando interrupciones tras
//la recepción de datos a través de la UART.
void leon3_UART_RX_IRQ_ENABLE(){
	pLEON3_UART_REGS->Ctrl = pLEON3_UART_REGS->Ctrl | LEON3_UART_RIE;
}

//Función que recibe como parámetro el valor que se quiere fijar en el campo
//loop_back del registro de control de la UART-A, de forma que si
//set_rxtxloop vale 1 se habilita el modo LOOP_BACK de la UART y
//si vale 0 se deshabilita.
void leon3_UART_ConfigRXTXLoop(uint8_t set_rxtxloop){
	if(set_rxtxloop==1){
		pLEON3_UART_REGS->Ctrl=pLEON3_UART_REGS->Ctrl|LEON3_UART_LB;

	}else{
		pLEON3_UART_REGS->Ctrl=pLEON3_UART_REGS->Ctrl&LEON3_UART_LBN;
	}
}


int8_t waitfor_TFF (){ //Espera a que TFF se vacie
	  uint32_t write_timeout=0;
	  while (leon3_UART_TF_IS_FULL()){
		  write_timeout++;
	  }
	  return (write_timeout == 0xAAAAA);
}
