
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"

#include "sigment.h"
extern unsigned char disp[]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10,0x08,0x03,0x46,0x21,0x06,0x0E,0x0B};
 void Set_segmentvalue(char ch)
{
     GPIO_PORTB_CR_R = 0x7F;
    switch(ch)
    {

        case 0:
            GPIO_PORTB_DATA_R = disp[0];
            break;
        case 1:
            GPIO_PORTB_DATA_R = disp[1];
            break;
        case 2:
            GPIO_PORTB_DATA_R = disp[2];
            break;
        case 3:
            GPIO_PORTB_DATA_R = disp[3];
            break;
        case 4:
            GPIO_PORTB_DATA_R = disp[4];
            break;
        case 5:
            GPIO_PORTB_DATA_R = disp[5];
            break;
        case 6:
            GPIO_PORTB_DATA_R = disp[6];
            break;
        case 7:
            GPIO_PORTB_DATA_R = disp[7];
            break;
        case 8:
            GPIO_PORTB_DATA_R = disp[8];
            break;
        case 9:
            GPIO_PORTB_DATA_R = disp[9];
            break;
        case 'A':
            GPIO_PORTB_DATA_R = disp[10];
            break;
        case 'B':
            GPIO_PORTB_DATA_R = disp[11];
            break;
        case 'C':
            GPIO_PORTB_DATA_R = disp[12];
            break;
        case 'D':
            GPIO_PORTB_DATA_R = disp[13];
            break;
        case 'E':
            GPIO_PORTB_DATA_R = disp[14];
            break;
        case 'F':
            GPIO_PORTB_DATA_R = disp[15];
            break;
        default :
            GPIO_PORTB_DATA_R = disp[16];
            break;
    }
}
