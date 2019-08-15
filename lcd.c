/*
 * lcd.c
 *
 *  Created on: 30/05/2017
 *      Author: lab industrial 2
 */
#include <lcd.h>

void LCDinit(void)
{
    //clear SEL control port
    clrBits(portCtrlSEL,portCtrl);
    //set out´s control port
    setBits(portCtrlDIR,portCtrl);
    //clear SEL data port
    clrBits(portDataSEL,portData);
    //set out´s data port
    setBits(portDataDIR,portData);

    //clear all outputs
    clrBits(portDataOUT,portData);
    clrBits(portCtrlOUT,portCtrl);

    //start LCD
    LCDoff();
    delay_ms(250);delay_ms(250);delay_ms(250);delay_ms(250);
    LCDon();

    // required by display controller to allow power to stabilize
    delay_ms(LCD_Startup);

    // required by display initialization
    LCDwriteNibble(0x20,0);
    delay_ms(20);
    LCDwriteNibble(0x20,0);
    delay_ms(1);
    LCDwriteNibble(0x20,0);

    // set interface size, # of lines and font
    LCDcmd(FUNCTION_SET);

    // turn on display and sets up cursor
    LCDcmd(DISPLAY_SETUP);

    // set cursor movement direction
    LCDcmd(ENTRY_MODE);
    LCDclear();
}

void LCDwriteNibble(unsigned char dato,unsigned char ComDat)
{
    //ALWAYS SEND THE UPPER NIBBLE

    unsigned char x;
    if(ComDat==0)//write command to LCD
        RS_L();
    else//write data to LCD
        RS_H();

    //check which bits are used for data
    x=dato>>4;//upper nibble
    portDataOUT=(portDataOUT&0xF0)|x;
    EN_H();
    //wait at least 350nSeg
    __delay_cycles(200);//200uSeg@1MHz
    EN_L();
}

void LCDwrite(unsigned char dat,unsigned char ComDat)
{
    LCDwriteNibble(dat,ComDat);//upper nibble

    dat=(dat<<4);//lower nibble
    LCDwriteNibble(dat,ComDat);
}

void LCDcmd(unsigned char cmd)
{
    LCDwrite(cmd,0);
}

void LCDputChar(unsigned char dat)
{
    LCDwrite(dat,1);
}

void LCDputStr(const unsigned char str[])
{
    unsigned char i=0;
    while(str[i]!=0)
    {
           LCDputChar(str[i++]);
    }
}

void LCDputStr1(unsigned char str[])
{
    unsigned char i=0;
    while(str[i]!=0)
    {
           LCDputChar(str[i++]);
    }
}

void delay_ms(unsigned char x)
{
    while(x>0)
    {
        //MCLK=1MHz
        __delay_cycles(1050);
        x--;
    }
}

