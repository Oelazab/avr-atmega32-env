/*
 * STD_TYPES.h
 * Created: 6/3/2025
 * Author: Omar El-Azab
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

// --------------------------------- Boolean type definition
/*typedef enum
{
	false,
	true
} bool;*/

// --------------------------------- 8 BIt
typedef unsigned char uint8_t;
typedef signed char sint8_t;

// --------------------------------- 16 BIt
typedef unsigned int uint16_t;
typedef signed short int sint16_t;

// --------------------------------- 32 BIt
typedef signed long int sint32_t;
typedef unsigned long int uint32_t;
typedef float f32;

// --------------------------------- 64 BIt
typedef double f64;

// --------------------------------- address to zero
#define NULL (void *)0

#endif