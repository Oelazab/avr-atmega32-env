/*
 * AVR ATmega32
 * main.c
 * Created: 6/3/2025
 * Author : Omar El-Azab
 */

// ------------- Microcontroller Abstraction Layer
#include "MCAL/UART/inc/UART_interface.h"

// ------------- Utiles
#include "UTILES_LIB/STD_TYPES.h"
#include "UTILES_LIB/BIT_MATH.h"

int main(void)
{
	UART_Init(19200);
	UART_SendString("Hello, World!\r\n");
	while (1);
	return 0;
}