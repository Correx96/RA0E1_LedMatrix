# LED Matrix ASCII Display with Renesas FPB-RAE01

This project uses the Renesas FPB-RAE01 evaluation board to control a 5x7 LED matrix (Kingbright TA07-11GWA) and display ASCII characters. A hollow shaft rotary encoder is used to scroll through and generate ASCII characters in the range 32 to 122.

The firmware was developed using **e² studio** with the **Renesas Flexible Software Package (FSP)**.

## Features

- Display characters on a 5x7 LED matrix
- Character selection via rotary encoder
- Compatible with ASCII characters according to table and SIZE selected
- Developed for the Renesas FPB-RAE01 evaluation board

## Hardware

### Microcontroller Board
- **Renesas FPB-RAE01 Evaluation Board**

### LED Matrix
- **Type**: 5x7 LED matrix

#### LED Matrix Pin Mapping

| RA0E1 Pin | LED Matrix Pin |
|----------:|----------------|
| P207      | R7             |
| P208      | R6             |
| P201      | R5             |
| P100      | R4             |
| P101      | R3             |
| P102      | R2             |
| P103      | R1             |
| P008      | C5             |
| P009      | C4             |
| P012      | C3             |
| P013      | C2             |
| P014      | C1             |

> **Note**: "R" refers to rows and "C" to columns in the LED matrix.
> This way connecting the wires is an easy task.
> All these pins are selected in output mode.
> **Note**: I didn't check the wiring from the board to the led matrix. You might need to rotate the wiring on your prototype.
### Rotary Encoder

- **Type**: Hollow shaft rotary encoder
- **Connections**:
  - P407 → Input D1
  - P212 → Input D2
  - GND → Common ground
 > These pins are available with pull-up internal resistors.

## License

This project is open source and available under the MIT License.
