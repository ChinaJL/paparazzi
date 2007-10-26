#ifndef ACTUATORS_BUSS_TWI_BLMC_HW_H
#define ACTUATORS_BUSS_TWI_BLMC_HW_H

#include <string.h>
#include "std.h"
#include "i2c.h"

#define ChopServo(x,a,b) Chop(x, a, b)
#define Actuator(i) buss_twi_blmc_motor_power[i]
#define ActuatorsCommit() {			\
    if ( buss_twi_blmc_status == BUSS_TWI_BLMC_STATUS_IDLE) {	\
      buss_twi_blmc_idx = 0;					\
      buss_twi_blmc_motor_power[0] = 0;				\
      buss_twi_blmc_motor_power[1] = 0;				\
      buss_twi_blmc_motor_power[2] = 0;				\
      buss_twi_blmc_motor_power[3] = 0;				\
      buss_twi_blmc_status = BUSS_TWI_BLMC_STATUS_BUSY;		\
      ActuatorsBussTwiBlmcSend();				\
    }								\
    else							\
      buss_twi_blmc_nb_err++;					\
  }

#define SERVOS_TICS_OF_USEC(s) ((uint8_t)(s)) 

#define BUSS_TWI_BLMC_STATUS_IDLE 0
#define BUSS_TWI_BLMC_STATUS_BUSY 1
#define BUSS_TWI_BLMC_NB 4
extern uint8_t buss_twi_blmc_motor_power[BUSS_TWI_BLMC_NB];
extern volatile bool_t  buss_twi_blmc_status;
extern volatile uint8_t buss_twi_blmc_nb_err;
extern volatile bool_t  buss_twi_blmc_i2c_done;
extern volatile uint8_t buss_twi_blmc_idx;
extern const uint8_t buss_twi_blmc_addr[];

#define ActuatorsBussTwiBlmcNext() {			\
    /* buss_twi_blmc_idx++; */				\
    /* if (buss_twi_blmc_idx < BUSS_TWI_BLMC_NB) { */	\
    /*  ActuatorsBussTwiBlmcSend(); */			\
    /* } */						\
    /* else */						\
      buss_twi_blmc_status = BUSS_TWI_BLMC_STATUS_IDLE;	\
  }

#define ActuatorsBussTwiBlmcSend() {					                     \
  const uint8_t msg[] = { buss_twi_blmc_addr[buss_twi_blmc_idx],	                     \
			  buss_twi_blmc_motor_power[buss_twi_blmc_idx]};                     \
  memcpy((void*)i2c_buf, msg, sizeof(msg));				                     \
  i2c_transmit(buss_twi_blmc_addr[buss_twi_blmc_idx], sizeof(msg), &buss_twi_blmc_i2c_done); \
}



#endif /* ACTUATORS_BUSS_TWI_BLMC_HW_H */
