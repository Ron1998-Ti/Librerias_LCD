/*
 * lcd.h
 *
 *  Created on: 30/05/2017
 *      Author: lab industrial 2
 */
#include <msp430.h>

#ifndef LCD_H_
#define LCD_H_

#define setBits(port,bits) port|=bits
#define clrBits(port,bits) port&=(~bits)

//definitions for data port
#define portDataSEL P6SEL
#define portDataDIR P6DIR
#define portDataOUT P6OUT
#define portData    (BIT0+BIT1+BIT2+BIT3)

//definitions for control port
#define RS BIT4
#define EN BIT5
#define ONOFF BIT6
#define portCtrlSEL P6SEL
#define portCtrlDIR P6DIR
#define portCtrlOUT P6OUT
#define portCtrl    (RS+EN+ONOFF)

#define RS_H() setBits(portCtrlOUT,RS)
#define RS_L() clrBits(portCtrlOUT,RS)
#define EN_H() setBits(portCtrlOUT,EN)
#define EN_L() clrBits(portCtrlOUT,EN)

// set up the timing for the LCD delays
#define LCD_delay           5     // ~5mS
#define LCD_Startup         15    // ~15mS

// Command set for LCD display controller
#define LCD_CLEAR           0x01
#define LCD_HOME            0x02
#define LCD_CURSOR_OFF      0x0C
#define LCD_CURSOR_ON       0x0E
#define LCD_CURSOR_BLINK    0x0F
#define LCD_CURSOR_BACK     0x10
#define LCD_CURSOR_FWD      0x14
#define LCD_PAN_LEFT        0x18
#define LCD_PAN_RIGHT       0x1C

#define LCD_CURSOR_LINE1    0x02
#define LCD_CURSOR_LINE2    0xC0
#define LCD_CURSOR_LINE3    0x94
#define LCD_CURSOR_LINE4    0xD4

// display controller setup commands
#define FUNCTION_SET        0x28    // 4 bit interface, 2 lines, 5x8 font
#define ENTRY_MODE          0x06    // increment mode
#define DISPLAY_SETUP       0x0C    // display on, cursor off, blink off

//predefined commands
#define LCDline1()        {LCDcmd(LCD_CURSOR_LINE1);delay_ms(5);}// legacy support
#define LCDline2()        {LCDcmd(LCD_CURSOR_LINE2);delay_ms(5);}// legacy support
#define LCDline3()        {LCDcmd(LCD_CURSOR_LINE3);delay_ms(5);}// legacy support
#define LCDline4()        {LCDcmd(LCD_CURSOR_LINE4);delay_ms(5);}// legacy support
#define LCDclear()        {LCDcmd(LCD_CLEAR),delay_ms(5);}
#define shift_cursor()    LCDcmd(LCD_CURSOR_FWD)              // legacy support
#define cursor_on()       LCDcmd(LCD_CURSOR_ON)               // legacy support
#define LCDon()           setBits(portCtrlOUT,ONOFF)
#define LCDoff()          clrBits(portCtrlOUT,ONOFF)


// LCD functions
void delay_ms(unsigned char);
void delay_us(unsigned int);
void LCDcmd(unsigned char);
void LCDputChar(unsigned char);
void LCDinit(void);
void LCDwriteNibble(unsigned char,unsigned char);
void LCDputStr(const unsigned char[]);
void LCDputStr1(unsigned char str[]);


#endif /* LCD_H_ */
