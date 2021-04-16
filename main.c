#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/timer.h"
#include "utils/uartstdio.h"
#include "utils/uartstdio.c"
#include "sigment.h"

#define FONK_BUT  GPIO_PIN_2
#define MOD_BUT   GPIO_PIN_3
#define SURE_BUT  GPIO_PIN_4
#define AKIM_BUT  GPIO_PIN_5
#define AUTO_LED  GPIO_PIN_7
#define MANUL_LED GPIO_PIN_2
#define SOFT_LED  GPIO_PIN_3


bool Fonk_But(void)
{
    return GPIOPinRead(GPIO_PORTA_BASE, FONK_BUT);
}

bool Mod_But(void)
{
    return GPIOPinRead(GPIO_PORTA_BASE, MOD_BUT);
}

bool Sure_But(void)
{
    return GPIOPinRead(GPIO_PORTA_BASE, SURE_BUT);
}

bool Akim_But(void)
{
    return GPIOPinRead(GPIO_PORTA_BASE, AKIM_BUT);
}

bool Fonk_state = false;
bool Mod_state = false;
bool state2 = false;
bool Fonk_value = false;
bool Mod_value = false;
bool Sure_value = false;
bool Akim_value = false;

uint32_t Mod_cont = 0;
uint32_t Sure_cont = 0;
uint32_t Akim_cont = 0;
uint16_t data_log = 0;
uint32_t cont = 0;
void Timer1IntHandler(void)
{
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    cont++;
}

int main(void)
{
    SysCtlClockSet(
            SYSCTL_SYSDIV_5 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN
                    | SYSCTL_XTAL_16MHZ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinTypeGPIOOutput(
            GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
            GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | AUTO_LED);

    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,
                         FONK_BUT | MOD_BUT | SURE_BUT | AKIM_BUT);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, MANUL_LED | SOFT_LED);
    Set_segmentvalue(0);

    //TIMER1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER1_BASE, TIMER_A, SysCtlClockGet() / 10);
    IntEnable(INT_TIMER1A);
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER1_BASE, TIMER_A);

    while (1)

    {
        if (Fonk_value != Fonk_But())
        {
            Fonk_value = Fonk_But();
            Set_segmentvalue('F');
            SysCtlDelay(SysCtlClockGet() / 4);
            Set_segmentvalue(0);
            Mod_value = true;
            Sure_value = true;
            Akim_value = true;

            if (Fonk_value)
            {
                Fonk_state = true;
            }


        }

        if (Fonk_state)
        {
            if ((Mod_state != Mod_But()) && Mod_value)
            {
                Sure_value = false;
                Akim_value = false;
                Mod_state = Mod_But();
                if (Mod_state)
                {

                    Mod_cont++;
                    if (Mod_cont == 1)
                    {
                        GPIOPinWrite(GPIO_PORTB_BASE, AUTO_LED, AUTO_LED);
                        GPIOPinWrite(GPIO_PORTF_BASE, MANUL_LED, !MANUL_LED);
                        data_log = data_log | 0x01;

                    }
                    else if (Mod_cont == 2)
                    {
                        GPIOPinWrite(GPIO_PORTB_BASE, AUTO_LED, !AUTO_LED);
                        GPIOPinWrite(GPIO_PORTF_BASE, MANUL_LED, MANUL_LED);
                        GPIOPinWrite(GPIO_PORTF_BASE, SOFT_LED, SOFT_LED);
                        data_log = data_log | 0x02;

                    }
                    else if (Mod_cont == 3)
                    {
                        GPIOPinWrite(GPIO_PORTF_BASE, MANUL_LED, MANUL_LED);
                        GPIOPinWrite(GPIO_PORTF_BASE, SOFT_LED, !SOFT_LED);
                        Mod_cont = 0;
                        data_log = data_log | 0x04;
                    }
                }
            }

            else if (Sure_But() && Sure_value)
            {
                Sure_cont++;
                Mod_value = false;
                Akim_value = false;
                Set_segmentvalue(Sure_cont);
                data_log = data_log | Sure_cont << 3;
                SysCtlDelay(SysCtlClockGet() / 4);
                if (Sure_cont == 9)
                {
                    Sure_cont = -1;

                }

            }
            else if (Akim_But() && Akim_value)
            {
                Akim_cont++;
                Mod_value = false;
                Sure_value = false;
                Set_segmentvalue( Akim_cont);
                data_log = data_log | Akim_cont << 7;
                SysCtlDelay(SysCtlClockGet() / 4);
                if (Akim_cont == 9)
                {
                    Akim_cont = -1;

                }

            }
            else
            {

            }
        }
  }
}



