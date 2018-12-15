#ifndef __TM1637_H__
#define __TM1637_H__

/*
 * For standard types (e.g. uint8_t)
 */
#include "esp_common.h"
#include "i2c_master.h"

/*
 * TM1637 commands
 */
#define CMD_ADDR_FIXED      (0x22)  /* in datasheet 0x44 */
#define CMD_ADDR_AUTO_INC   (0x02)  /* in datasheet 0x40 */

/*
 * TM1637 addresses
 */
#define ADDR_GRID_1         (0x03)  /* in datasheet 0xC0 */
#define ADDR_GRID_2         (0x83)  /* in datasheet 0xC1 */
#define ADDR_GRID_3         (0x43)  /* in datasheet 0xC2 */
#define ADDR_GRID_4         (0xC3)  /* in datasheet 0xC3 */
#define ADDR_GRID_5         (0x23)  /* in datasheet 0xC4 */
#define ADDR_GRID_6         (0xA3)  /* in datasheet 0xC5 */

/*
 * TM1637 character encodings
 *         A
 *        ----
 *       |    |
 *     F | G  | B
 *       |----| 
 *     E |    | C
 *       | D  |
 *        ----  . DP
 * 
 * Segment order
 * | SEG1 | SEG2 | SEG3 | SEG4 | SEG5 | SEG6 | SEG7 | SEG8 |
 *    A      B      C      D      E      F      G      DP
 */
#define CHAR_0              (0xFC)
#define CHAR_1              (0x0C)
#define CHAR_2              (0xDA)
#define CHAR_3              (0xF2)
#define CHAR_4              (0x66)
#define CHAR_5              (0xB6)
#define CHAR_6              (0xBE)
#define CHAR_7              (0xE0)
#define CHAR_8              (0xFE)
#define CHAR_9              (0xF6)

#define CHAR_A              (0xEE)
#define CHAR_B              (0x3E)
#define CHAR_C              (0x9C)
#define CHAR_D              (0x7A)
#define CHAR_E              (0x9E)
#define CHAR_F              (0x8E)

#define CHAR_BLANK          (0x00)
#define CHAR_DASH           (0x02)

/*
 * TM1637 Input characters for mapping to encoding
 */
#define INPUT_CHAR_0        (char)('0')
#define INPUT_CHAR_1        (char)('1')
#define INPUT_CHAR_2        (char)('2')
#define INPUT_CHAR_3        (char)('3')
#define INPUT_CHAR_4        (char)('4')
#define INPUT_CHAR_5        (char)('5')
#define INPUT_CHAR_6        (char)('6')
#define INPUT_CHAR_7        (char)('7')
#define INPUT_CHAR_8        (char)('8')
#define INPUT_CHAR_9        (char)('9')

#define INPUT_CHAR_A        (char)('A')
#define INPUT_CHAR_B        (char)('B')
#define INPUT_CHAR_C        (char)('C')
#define INPUT_CHAR_D        (char)('D')
#define INPUT_CHAR_E        (char)('E')
#define INPUT_CHAR_F        (char)('F')

#define INPUT_CHAR_BLANK    (char)(' ')
#define INPUT_CHAR_DASH     (char)('-')

/*
 * Min. and Max. of range for displaying numbers
 */
#define NUMBER_RANGE_MIN    ((sint16)(-999))
#define NUMBER_RANGE_MAX    ((sint16)(9999))

/*
 * Variable for brightness
 */
extern uint8_t tm1637_brightness;

/*
 * Type for character to display
 */
typedef uint8_t tm1637_char_t;

/*
 * Type for character position
 */
typedef enum {
    POS_0 = 0,
    POS_1,
    POS_2,
    POS_3,
    POS_4,
    POS_5,
} tm1637_pos_t;

/*
 * Initialize TM1637
 */
void tm1637_init(void);

/*
 * Display a character on a specific position
 */
void tm1637_display_char(tm1637_char_t, tm1637_pos_t);

/*
 * Display number in range [NUMBER_RANGE_MIN;NUMBER_RANGE_MAX]
 */
void tm1637_display_number(int16_t);

/*
 * Clears the display
 */
void tm1637_clear(void);

/*
 * Maps numbers 0-9 and letters A-F to data
 */
tm1637_char_t tm1637_map_char(unsigned char);

/*
 * Sets the brightness; will be active with the next write cycle
 */ 
void tm1637_set_brightness(uint8_t);

#endif