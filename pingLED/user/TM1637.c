#include <TM1637.h>

uint8_t tm1637_brightness = 0; /* display off */

/*
 * Initialize TM1637
 */
void tm1637_init(void)
{
    tm1637_brightness = 0; 
    tm1637_clear();
}

/*
 * Display a character on a specific position
 */
void tm1637_display_char(tm1637_char_t _char, tm1637_pos_t _pos)
{
    uint8_t address = 0x0;
    /* Get address for position */
    switch (_pos)
    {
        case POS_0:
            address = ADDR_GRID_1;
            break;
        case POS_1:
            address = ADDR_GRID_2;
            break;
        case POS_2:
            address = ADDR_GRID_3;
            break;
        case POS_3:
            address = ADDR_GRID_4;
            break;
        case POS_4:
            address = ADDR_GRID_5;
            break;
        case POS_5:
            address = ADDR_GRID_6;
            break;
        default:
            address = 0x0;
            break;
    }

    /* write to fixed address */
    i2c_master_start();
    i2c_master_writeByte(CMD_ADDR_FIXED);
    i2c_master_getAck();
    i2c_master_stop();

    /* write character data */
    i2c_master_start();
    i2c_master_writeByte(address);
    i2c_master_getAck();
    i2c_master_writeByte(_char);
    i2c_master_getAck();
    i2c_master_stop(); 

    /* display control command including DP and brightness */
    i2c_master_start();        
    i2c_master_writeByte(0x01 | tm1637_brightness); //set display on and set brightness
    i2c_master_getAck();
    i2c_master_stop(); 
}
/*
 * Display a number in range [NUMBER_RANGE_MIN;NUMBER_RANGE_MAX]
 */
void tm1637_display_number(int16_t _number)
{
    /* test range of number */
    if((NUMBER_RANGE_MIN <= _number) && (NUMBER_RANGE_MAX >= _number))
    {
        /* number in correct range */

        /* is it a negative number? */
        if(0 > _number)
        {
            /* negative number */

            /* char in POS_0 is always '-' to indicate negative number */
			tm1637_display_char(tm1637_map_char('-'), POS_0);

        }
        else
        {
            /* positive number */
            if(0==(_number / 1000))
            {
                /* smaller than 1000 */
            }
        }
    }
}

/*
 * Clears the display
 */
void tm1637_clear(void)
{
    tm1637_display_char(CHAR_BLANK, POS_0);
    tm1637_display_char(CHAR_BLANK, POS_1);
    tm1637_display_char(CHAR_BLANK, POS_2);
    tm1637_display_char(CHAR_BLANK, POS_3);
    tm1637_display_char(CHAR_BLANK, POS_4);
    tm1637_display_char(CHAR_BLANK, POS_5);
}

/*
 * Maps numbers 0-9 and letters A-F to data
 */
tm1637_char_t tm1637_map_char(unsigned char _char)
{
    tm1637_char_t retVal = CHAR_BLANK; /* default */
    switch (_char)
    {
        case INPUT_CHAR_0:
            retVal = CHAR_0;
            break;
        case INPUT_CHAR_1:
            retVal = CHAR_1;
            break;
        case INPUT_CHAR_2:
            retVal = CHAR_2;
            break;
        case INPUT_CHAR_3:
            retVal = CHAR_3;
            break;
        case INPUT_CHAR_4:
            retVal = CHAR_4;
            break;
        case INPUT_CHAR_5:
            retVal = CHAR_5;
            break;
        case INPUT_CHAR_6:
            retVal = CHAR_6;
            break;
        case INPUT_CHAR_7:
            retVal = CHAR_7;
            break;
        case INPUT_CHAR_8:
            retVal = CHAR_8;
            break;
        case INPUT_CHAR_9:
            retVal = CHAR_9;
            break; 
        case INPUT_CHAR_A:
            retVal = CHAR_A;
            break;
        case INPUT_CHAR_B:
            retVal = CHAR_B;
            break;
        case INPUT_CHAR_C:
            retVal = CHAR_C;
            break;
        case INPUT_CHAR_D:
            retVal = CHAR_D;
            break;
        case INPUT_CHAR_E:
            retVal = CHAR_E;
            break;
        case INPUT_CHAR_F:
            retVal = CHAR_F;
            break; 
        case INPUT_CHAR_DASH:
            retVal = CHAR_DASH;
            break;
        case INPUT_CHAR_BLANK:
            retVal = CHAR_BLANK;
            break;    
        default:
            retVal = CHAR_BLANK;
            break;                                                                                                                                                                              
    }

    return retVal;
}

/*
 * Sets the brightness; will be active with the next write cycle
 */ 
void tm1637_set_brightness(uint8_t _brightness)
{
#ifdef gfg
    if( _brightness <= 0xA)
    {
        tm1637_brightness = _brightness;
    }
    else   
    {
        tm1637_brightness = 0; /* display off */
    }
#endif
    tm1637_brightness = _brightness;
}