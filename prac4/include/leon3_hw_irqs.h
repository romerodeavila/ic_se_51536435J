/*
 * leon3_irqs.h
 *
 *  Created on: Feb 28, 2013
 *      Author: user
 */

#ifndef IRQS_H_
#define IRQS_H_

#include "leon3_types.h"

//Rutina que enmascara la interrupción externa cuyo nivel se pasa por parámetro.
uint8_t leon3_mask_irq (uint8_t irq_level);

//Rutina que desenmascara una interrupción externa cuyo nivel se pasa por parámetro.
uint8_t leon3_unmask_irq (uint8_t irq_level);

//Rutina que fuerza una interrupción externa cuyo nivel se pasa por parámetro.
uint8_t leon3_sparc_force_irq (uint8_t irq_level);



#endif
