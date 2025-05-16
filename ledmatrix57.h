/**
 * This Library was originally written by Olivier Van den Eede (4ilo) in 2016.
 * Some refactoring was done and SPI support was added by Aleksander Alekseev (afiskon) in 2018.
 *
 * https://github.com/afiskon/stm32-ledmatrix
 *
 * DERIVATA LA LIB PER IL LEDMATRIX 5 X 7 gestiti direttamente da GPIO
 * 15/04/25
 *
 */

#ifndef __LEDMATRIX57_H__
#define __LEDMATRIX57_H__

#include <stddef.h>
#include <stdint.h>
#include "hal_data.h"

#ifdef LEDMATRIX_X_OFFSET
#define LEDMATRIX_X_OFFSET_LOWER (LEDMATRIX_X_OFFSET & 0x0F)
#define LEDMATRIX_X_OFFSET_UPPER ((LEDMATRIX_X_OFFSET >> 4) & 0x07)
#else
#define LEDMATRIX_X_OFFSET_LOWER 0
#define LEDMATRIX_X_OFFSET_UPPER 0
#endif

// LEDMATRIX OLED height in pixels
#ifndef LEDMATRIX_HEIGHT
#define LEDMATRIX_HEIGHT          7
#endif

// LEDMATRIX width in pixels
#ifndef LEDMATRIX_WIDTH
#define LEDMATRIX_WIDTH           5
#endif

#define DOT_ON  GPIO_PIN_SET
#define DOT_OFF GPIO_PIN_RESET

#ifndef LEDMATRIX_BUFFER_SIZE
#define LEDMATRIX_BUFFER_SIZE   LEDMATRIX_HEIGHT //LEDMATRIX_WIDTH * LEDMATRIX_HEIGHT / 8
#endif

// Enumeration for screen colors
typedef enum {
    Black = 0x00, // Black color, no pixel
    White = 0x01  // Pixel is set. Color depends on OLED
} LEDMATRIX_COLOR;

typedef enum {
    LEDMATRIX_OK = 0x00,
    LEDMATRIX_ERR = 0x01  // Generic error.
} LEDMATRIX_Error_t;

// Struct to store transformations
typedef struct {
    uint16_t CurrentX;
    uint16_t CurrentY;
    uint8_t Initialized;
    uint8_t DisplayOn;
} LEDMATRIX_t;

typedef struct {
    uint8_t x;
    uint8_t y;
} LEDMATRIX_VERTEX;

/** Font */
typedef struct {
    const uint8_t width;                /**< Font width in pixels */
    const uint8_t height;               /**< Font height in pixels */
    const uint8_t *const data;         /**< Pointer to font data array */
    const uint8_t *const char_width;    /**< Proportional character width in pixels (NULL for monospaced) */
} LEDMATRIX_Font_t;

extern const LEDMATRIX_Font_t Font_5x7;

// Procedure definitions
void ledmatrix_Init(void);
//void ledmatrix_Fill(LEDMATRIX_COLOR color);
void ledmatrix_UpdateScreen(void);
void ledmatrix_DrawPixel(uint8_t x, uint8_t y, LEDMATRIX_COLOR color);
char ledmatrix_WriteChar(char ch, LEDMATRIX_Font_t Font, LEDMATRIX_COLOR color);

//_END_STD_C

#endif // __LEDMATRIX57_H__
