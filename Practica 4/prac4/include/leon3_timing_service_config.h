/*
 * leon3_timing_service_config.h
 *
 *  Created on: Apr 2, 2013
 *      Author: user
 */

#include "leon3_types.h"

#ifndef LEON3_TIMING_SERVICE_CONFIG_H_
#define LEON3_TIMING_SERVICE_CONFIG_H_


	/** \brief Init Timing Service
	 *
	 *  \param ticks_per_second ticks per second
	 *  \param IRQHandler timer irq handler to install
	 *
	 */

	void InitTimingService(uint8_t ticks_per_second, void (* IRQHandler) (void));

	/** \brief return ticks per second passed to InitTimingService
	 * return 0 if InitTimingService has not been used
	 */
	uint8_t GetTicksPerSecond();

#endif /* LEON3_TIMING_SERVICE_CONFIG_H_ */
