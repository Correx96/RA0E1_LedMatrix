#include "ledmatrix57.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>  // For memcpy

#define pinR1_Config        &IOPORT_CFG_CTRL, R1
#define pinR2_Config        &IOPORT_CFG_CTRL, R2
#define pinR3_Config        &IOPORT_CFG_CTRL, R3
#define pinR4_Config        &IOPORT_CFG_CTRL, R4
#define pinR5_Config        &IOPORT_CFG_CTRL, R5
#define pinR6_Config        &IOPORT_CFG_CTRL, R6
#define pinR7_Config        &IOPORT_CFG_CTRL, R7
#define pinC1_Config        &IOPORT_CFG_CTRL, C1
#define pinC2_Config        &IOPORT_CFG_CTRL, C2
#define pinC3_Config        &IOPORT_CFG_CTRL, C3
#define pinC4_Config        &IOPORT_CFG_CTRL, C4
#define pinC5_Config        &IOPORT_CFG_CTRL, C5

#define OFF                 BSP_IO_LEVEL_LOW
#define ON                  BSP_IO_LEVEL_HIGH

uint8_t x, y;

// Screenbuffer
static uint8_t LEDMATRIX_Buffer[LEDMATRIX_BUFFER_SIZE];

// Screen object
static LEDMATRIX_t LEDMATRIX;

/* Fills the Screenbuffer with values from a given buffer of a fixed length */
LEDMATRIX_Error_t ledmatrix_FillBuffer(uint8_t* buf, uint32_t len) {
    LEDMATRIX_Error_t ret = LEDMATRIX_ERR;
    if (len <= LEDMATRIX_BUFFER_SIZE) {
        memcpy(LEDMATRIX_Buffer,buf,len);
        ret = LEDMATRIX_OK;
    }
    return ret;
}

/* Fill the whole screen with the given color */
void ledmatrix_Fill(LEDMATRIX_COLOR color) {
    memset(LEDMATRIX_Buffer, (color == Black) ? 0x00 : 0xFF, sizeof(LEDMATRIX_Buffer));
}

uint8_t dotstatus;

/* Write the screenbuffer with changed to the screen */
void ledmatrix_UpdateScreen(void) {
    //REFRESH DATA ON LED MATRIX FROM BUFFER
    //EXECUTE EVERY 20 MS

    for (y = 0; y < LEDMATRIX_HEIGHT; y++)
    {
    //turn on ROW
    switch (y)
        {
        case 0:
            R_IOPORT_PinWrite(pinR1_Config, OFF);
        break;
        case 1:
            R_IOPORT_PinWrite(pinR2_Config, OFF);
        break;
        case 2:
            R_IOPORT_PinWrite(pinR3_Config, OFF);
        break;
        case 3:
            R_IOPORT_PinWrite(pinR4_Config, OFF);
        break;
        case 4:
            R_IOPORT_PinWrite(pinR5_Config, OFF);
        break;
        case 5:
            R_IOPORT_PinWrite(pinR6_Config, OFF);
        break;
        case 6:
            R_IOPORT_PinWrite(pinR7_Config, OFF);
        break;
        default:
        break;
        }


    for (x = 0; x < LEDMATRIX_WIDTH; x++)
        {
//        if (y == 3)
//            {
//            HAL_GPIO_WritePin(C1_GPIO_Port, C1_Pin, DOT_OFF);
//            HAL_GPIO_WritePin(C2_GPIO_Port, C2_Pin, DOT_OFF);
//            HAL_GPIO_WritePin(C3_GPIO_Port, C3_Pin, DOT_ON);
//            HAL_GPIO_WritePin(C4_GPIO_Port, C4_Pin, DOT_OFF);
//            HAL_GPIO_WritePin(C5_GPIO_Port, C5_Pin, DOT_OFF);
//            }
//        else
//            {
//            HAL_GPIO_WritePin(C3_GPIO_Port, C3_Pin, DOT_OFF);


        //if (LEDMATRIX_Buffer[x + (y / 8) * LEDMATRIX_WIDTH] && (1 << (y % 8)) == 1)
        //if ((LEDMATRIX_Buffer[y] && (1 << (x % 8))) == 1)
        if (LEDMATRIX_Buffer[y] & (1 << (x)))
            {dotstatus = 1;}
        else
            {dotstatus = 0;}

            //check pixel
            //pixel x,y

            switch (x)
            {
                case 0:
                if (dotstatus)
                    {R_IOPORT_PinWrite(pinC1_Config, ON);}
                else
                    {R_IOPORT_PinWrite(pinC1_Config, OFF);}
                break;
                case 1:
                if (dotstatus)
                    {R_IOPORT_PinWrite(pinC2_Config, ON);}
                else
                    {R_IOPORT_PinWrite(pinC2_Config, OFF);}
                break;
                case 2:
                if (dotstatus)
                    {R_IOPORT_PinWrite(pinC3_Config, ON);}
                else
                    {R_IOPORT_PinWrite(pinC3_Config, OFF);}
                break;
                case 3:
                if (dotstatus)
                    {R_IOPORT_PinWrite(pinC4_Config, ON);}
                else
                    {R_IOPORT_PinWrite(pinC4_Config, OFF);}
                break;
                case 4:
                if (dotstatus)
                    {R_IOPORT_PinWrite(pinC5_Config, ON);}
                else
                    {R_IOPORT_PinWrite(pinC5_Config, OFF);}
                break;

                default:
                break;
            }
            //}
        }

        R_BSP_SoftwareDelay(2, BSP_DELAY_UNITS_MILLISECONDS);

        R_IOPORT_PinWrite(pinR1_Config, ON);
        R_IOPORT_PinWrite(pinR2_Config, ON);
        R_IOPORT_PinWrite(pinR3_Config, ON);
        R_IOPORT_PinWrite(pinR4_Config, ON);
        R_IOPORT_PinWrite(pinR5_Config, ON);
        R_IOPORT_PinWrite(pinR6_Config, ON);
        R_IOPORT_PinWrite(pinR7_Config, ON);

    }
}

/*
 * Draw one pixel in the screenbuffer
 * X => X Coordinate
 * Y => Y Coordinate
 * color => Pixel color
 */
void ledmatrix_DrawPixel(uint8_t x, uint8_t y, LEDMATRIX_COLOR color) {
    if(x >= LEDMATRIX_WIDTH || y >= LEDMATRIX_HEIGHT) {
        // Don't write outside the buffer
        return;
    }
      // Draw in the right color
    if(color == White) {
        //LEDMATRIX_Buffer[x + (y / 8) * LEDMATRIX_WIDTH] |= 1 << (y % 8);
        LEDMATRIX_Buffer[y] |= 1 << (x % 8);
    } else {
        //LEDMATRIX_Buffer[x + (y / 8) * LEDMATRIX_WIDTH] &= ~(1 << (y % 8));
        LEDMATRIX_Buffer[y] &= ~(1 << (x % 8));
    }
}

/*
 * Draw 1 char to the screen buffer
 * ch       => char om weg te schrijven
 * Font     => Font waarmee we gaan schrijven
 * color    => Black or White
 */
char ledmatrix_WriteChar(char ch, LEDMATRIX_Font_t Font, LEDMATRIX_COLOR color) {
    uint32_t i, b, j;

    // Check if character is valid
    if (ch < 32 || ch > 126)
        return 0;

    // Char width is not equal to font width for proportional font
    const uint8_t char_width = Font.char_width ? Font.char_width[ch-32] : Font.width;
    // Check remaining space on current line
    if (LEDMATRIX_WIDTH < (LEDMATRIX.CurrentX + char_width) ||
        LEDMATRIX_HEIGHT < (LEDMATRIX.CurrentY + Font.height))
    {
        // Not enough space on current line
        return 0;
    }

    // Use the font to write
    for(i = 0; i < Font.width; i++) {
//        b = Font.data[(ch - 32) * Font.height + i];

        b = Font.data[((ch - 32)*5) + i];
        for(j = 0; j < Font.height; j++) {
            if((b >> j) & 0x01)  {              //(b << j) & 0x40 per specchiare il char visualizzato
                ledmatrix_DrawPixel(LEDMATRIX.CurrentX + i, (LEDMATRIX.CurrentY + j), (LEDMATRIX_COLOR) color);
            } else {
                ledmatrix_DrawPixel(LEDMATRIX.CurrentX + i, (LEDMATRIX.CurrentY + j), (LEDMATRIX_COLOR)!color);
            }
        }
    }

    // The current space is now taken
    //LEDMATRIX.CurrentX += char_width;

    // Return written char for validation
    return ch;
}

/* Position the cursor */
void ledmatrix_SetCursor(uint8_t x, uint8_t y) {
    LEDMATRIX.CurrentX = x;
    LEDMATRIX.CurrentY = y;
}
