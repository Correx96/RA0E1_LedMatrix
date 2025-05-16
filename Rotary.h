/*
 * Rotary encoder library for Arduino by @buxtronix
 * Modified by @CSoffiati 05/2025
 */

#ifndef rotary_h
#define rotary_h

#include "common_data.h"
#include "hal_data.h"

// Enable this to emit codes twice per step.
#define HALF_STEP

// Enable weak pullups
#define ENABLE_PULLUPS

// Values returned by 'process'
// No complete step yet.
#define DIR_NONE 0x0
// Clockwise step.
#define DIR_CW 0x10
// Anti-clockwise step.
#define DIR_CCW 0x20
// Default start state
#define R_START 0x0

unsigned char Rotary_process(ioport_ctrl_t *const  pinD1_ctrl, bsp_io_port_pin_t pinD1_number, ioport_ctrl_t *const  pinD2_ctrl, bsp_io_port_pin_t pinD2_number);
uint32_t digitalRead(ioport_ctrl_t *const  p_ctrl, bsp_io_port_pin_t pin_number);

#endif
