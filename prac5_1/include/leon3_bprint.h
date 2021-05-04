#ifndef LEON3_BPRINT_H_
#define LEON3_BPRINT_H_
#include "leon3_types.h"
#include "leon3_uart.h"

//transmite a través del puerto serie la cadena de caracteres
//pasada por parámetro.
int8_t leon3_print_string(char* str);

//transmite a través del puerto serie el entero transformado en
//cadena de caracteres.
int8_t leon3_print_uint8(uint8_t i);

int8_t leon3_print_uint32(uint32_t i);

#endif /* LEON3_BPRINT_H_ */
