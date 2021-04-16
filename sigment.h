
#ifndef SIGMENT_H_
#define SIGMENT_H_
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *)0x40005524))
void Set_segmentvalue(char ch);
#endif /* SIGMENT_H_ */
