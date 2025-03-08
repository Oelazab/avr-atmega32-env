/*
 * UART_interface.h
 * Created: 6/3/2025
 * Author: Omar El-Azab 
 */ 

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "UART_register.h"                  // For direct register access
#include "../UTILES_LIB/STD_TYPES.h"        // Standard Types

#define F_CPU 16000000UL

// Function Prototypes
void UART_Init(uint32_t baud_rate);
void UART_Transmit(uint8_t data);
uint8_t UART_Receive(void);
void UART_SendString(const char* str);

#endif