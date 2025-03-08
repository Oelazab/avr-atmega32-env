/*
 * UART_program.cpp
 * Created: 6/3/2025
 * Author: Omar El-Azab
 */

#include "../inc/UART_interface.h"

// UART initialization function
void UART_Init(uint32_t baud_rate)
{
    uint16_t ubrr_value = (F_CPU / (16UL * baud_rate)) - 1; // UBRR Value

    // Set baud rate
    UBRRH = (uint8_t)(ubrr_value >> 8); // Load upper 8-bits of UBRR value
    UBRRL = (uint8_t)ubrr_value;        // Load lower 8-bits of UBRL value

    // Enable transmitter and receiver
    // UCSRB = (1 << RXEN) | (1 << TXEN);
    UCSRB = 0b00011000;
    // RX Complete Interrupt Enable                     -> 0
    // TX Complete Interrupt Enable                     -> 0
    // USART Data Register Empty Interrupt Enable       -> 0
    // Receiver Enable                                  -> 1
    // Transmitter Enable                               -> 1
    // Character Size Bit 2                             -> 0
    // Receive Data Bit 8                               -> 0
    // Transmit Data Bit 8                              -> 0
    /*
     * ---------------------------------------------------- Bit 7
     * RXCIE: RX Complete Interrupt Enable -> 0
     * Writing this bit to one enables interrupt on the RXC Flag. 
     * A USART Receive Complete Interrupt will be generated only if the RXCIE bit is written to one, 
     * the Global Interrupt Flag in SREG is written to one and the RXC bit inUCSRA is set.
     * ---------------------------------------------------- Bit 6
     * TXCIE: TX Complete Interrupt Enable -> 0
     * Writing this bit to one enables interrupt on the TXC Flag. 
     * A USART Transmit Complete Interrupt will be generated only if the TXCIE bit is written to one, 
     * the Global Interrupt Flag in SREG is written to one and the TXC bit in UCSRA is set.
     * ---------------------------------------------------- Bit 5
     * UDRIE: USART Data Register Empty Interrupt Enable -> 0
     * Writing this bit to one enables interrupt on the UDRE Flag. 
     * A Data Register Empty Interrupt will be generated only if the UDRIE bit is written to one, 
     * the Global Interrupt Flag in SREG is written to one and the UDRE bit in UCSRA isset.
     * ---------------------------------------------------- Bit 4
     * RXEN: Receiver Enable -> 1
     * Writing this bit to one enables the USART Receiver. 
     * The Receiver will override normal port operation for the RxD pin when enabled. 
     * Disabling the Receiver will flush the receive buffer invalidating the FE, DOR, and PE Flags.
     * ---------------------------------------------------- Bit 3
     * TXEN: Transmitter Enable -> 1
     * Writing this bit to one enables the USART Transmitter. 
     * The Transmitter will override normal port operation for the TxD pin when enabled. 
     * The disabling of the Transmitter (writing TXEN to zero) will not become effective until 
     * ongoing and pending transmissions are completed, that is, when the transmit Shift Register 
     * and transmit Buffer Register do not contain data to be transmitted. 
     * When disabled, the transmitter will no longer override the TxD port.
     * ---------------------------------------------------- Bit 2
     * UCSZ2: Character Size -> 0
     * The UCSZ2 bits combined with the UCSZ1:0 bit in UCSRC sets the number of data bits 
     * (Character Size) in a frame the receiver and transmitter use. 
     * ---------------------------------------------------- Bit 1
     * RXB8: Receive Data Bit 8 -> 0
     * RXB8 is the ninth data bit of the received character when operating with serial frames with nine data bits. 
     * Must be read before reading the low bits from UDR.
     * ---------------------------------------------------- Bit 0
     * TXB8: Transmit Data Bit 8 -> 0
     * TXB8 is the ninth data bit in the character to be transmitted when operating with serial frames with nine data bits.
     * Must be written before writing the low bits to UDR.
     */
   
     
    // ----- Set frame format: 8 data bits, 1 stop bit (UCSZ0 and UCSZ1)
    // UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
    UCSRC = 0b10000100;
    // Register Select          -> 1
    // USART Mode Select        -> 0
    // Parity Mode Bit 1        -> 0
    // Parity Mode Bit 0        -> 0
    // Stop Bit Select          -> 0
    // Character Size Bit 1     -> 1
    // Character Size Bit 0     -> 1
    // Clock Polarity           -> 0
    /*
     * ---------------------------------------------------- Bit 7
     * Register Select -> 1 This bit selects between accessing the UCSRC or the UBRRH Register.
     * It is read as one when reading UCSRC.
     * The URSEL must be one when writing the UCSRC.
     * ---------------------------------------------------- Bit 6
     * USART Mode Select -> 0 This bit selects between Asynchronous and Synchronous mode of operation.
     * UMSEL -> 0 | Mode -> Asynchronous Operation
     * UMSEL -> 1 | Mode -> Synchronous Operation
     * ---------------------------------------------------- Bit 4,5
     * UPM1:0: Parity Mode
     * These bits enable and set type of parity generation and check.
     * If enabled, the transmitter will automatically generate and send the parity of the transmitted data bits within each frame.
     * The Receiver will generate a parity value forthe incoming data and compare it to the UPM0 setting.
     * If a mismatch is detected, the PE Flag in UCSRA will be set.
     * UPM1 -> 0 | UPM0 -> 0 | Parity Mode -> Disabled
     * UPM1 -> 0 | UPM0 -> 1 | Parity Mode -> Reserved
     * UPM1 -> 1 | UPM0 -> 0 | Parity Mode -> Enabled, Even Parity
     * UPM1 -> 1 | UPM0 -> 1 | Parity Mode -> Enabled, Odd Parity
     * ---------------------------------------------------- Bit 3
     * Stop Bit Select -> 0 This bit selects the number of Stop Bits to be inserted by the Transmitter.
     * The Receiver ignores this setting.
     * USBS -> 0 | Stop Bit(s) -> 1-bit
     * USBS -> 1 | Stop Bit(s) -> 2-bit
     * ---------------------------------------------------- Bit 1,2
     * The UCSZ1:0 bits combined with the UCSZ2 bit in UCSRB sets the number of data bits
     * (Character Size) in a frame the Receiver and Transmitter use.
     * UCSZ2 -> 0 | UCSZ1 -> 0 |  UCSZ0 -> 0 |  Character Size -> 5-bit
     * UCSZ2 -> 0 | UCSZ1 -> 0 |  UCSZ0 -> 1 |  Character Size -> 6-bit
     * UCSZ2 -> 0 | UCSZ1 -> 1 |  UCSZ0 -> 0 |  Character Size -> 7-bit
     * UCSZ2 -> 0 | UCSZ1 -> 1 |  UCSZ0 -> 1 |  Character Size -> 8-bit
     * UCSZ2 -> 1 | UCSZ1 -> 0 |  UCSZ0 -> 0 |  Character Size -> Reserved
     * UCSZ2 -> 1 | UCSZ1 -> 0 |  UCSZ0 -> 1 |  Character Size -> Reserved
     * UCSZ2 -> 1 | UCSZ1 -> 1 |  UCSZ0 -> 0 |  Character Size -> Reserved
     * UCSZ2 -> 1 | UCSZ1 -> 1 |  UCSZ0 -> 1 |  Character Size -> 9-bit
     * ---------------------------------------------------- Bit 0
     * Clock Polarity -> 0 This bit is used for Synchronous mode only.
     * Write this bit to zero when Asynchronous mode is used.
     * The UCPOL bit sets the relationship between data output change and data input sample, and the synchronous clock (XCK).
     * UCPOL -> 0
     * Transmitted Data Changed (Output of TxD Pin) -> Rising XCK Edge
     * Received Data Sampled (Input on RxD Pin)     -> Falling XCK Edge
     * UCPOL -> 1
     * Transmitted Data Changed (Output of TxD Pin) -> Falling XCK Edge
     * Received Data Sampled (Input on RxD Pin)     -> Rising XCK Edge
     */
}

// Function to transmit a single byte over UART
void UART_Transmit(uint8_t data)
{
    while (!(UCSRA & (1 << UDRE))); // Wait for the transmit buffer to be empty
    UDR = data;                     // Put data into the buffer, sends the data
}

// Function to receive a single byte from UART
uint8_t UART_Receive(void)
{
    while (!(UCSRA & (1 << RXC)));  // Wait for data to be received    
    return UDR;                     // Get and return received data from buffer
}

// Function to transmit a string over UART
void UART_SendString(const char *str)
{
    while (*str) UART_Transmit(*str++);
}