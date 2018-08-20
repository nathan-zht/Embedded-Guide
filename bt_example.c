/* 
 * File:   main.c
 * Author: Monica Ignat
 *
 * Created on April 3rd, 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>
#include <stdbool.h>
#include <string.h>
#include "config.h"
#include "uart.h"
#include "lcd.h"
#include "uartjb.h"

#pragma config JTAGEN = OFF     
#pragma config FWDTEN = OFF      
/* ------------------------------------------------------------ */
/*						Configuration Bits		                */
/* ------------------------------------------------------------ */
// Device Config Bits in  DEVCFG1:	
#pragma config FNOSC =	FRCPLL
#pragma config FSOSCEN =	OFF
#pragma config POSCMOD =	XT
#pragma config OSCIOFNC =	ON
#pragma config FPBDIV =     DIV_2
// Device Config Bits in  DEVCFG2:	
#pragma config FPLLIDIV =	DIV_2
#pragma config FPLLMUL =	MUL_20
#pragma config FPLLODIV =	DIV_1

int main(int argc, char** argv) 
{
    char strTxt[cchRxMax], strTxti[cchRxMax];
    unsigned char cch, cchi;
    bool commandMode = false;

    //UARTJB and LCD basic initializations
    UARTJB_Init(9600); 
    //UART_Init(115200); 
    LCD_Init();
    //send a text to UART terminal on PC using UARTJB library
    UART_PutString("Basys MX3 #1 \n\r");
    UART_PutString("UART Demo Pmod \n\r");
    //UARTJB_PutString("D");
    //when sending a text file, make sure the content ends with CR+LF and your terminal is also setup accordingly, to transmit both characters
    //otherwise, the file sending will not function correctly
    while(1){  
        cch = UARTJB_GetString(strTxt, cchRxMax);
        if(cch > 0)
        {
          UART_PutString(strTxt);
          UART_PutString("\r\n");
          LCD_WriteStringAtPos(strTxt, 1, 0);
        } 
        cchi = UART_GetString(strTxti, cchRxMax);
        if(cchi > 0)
        {  
            LCD_WriteStringAtPos(strTxti, 0, 0);
            if(strcmp(strTxti,"cmd") == 0){
                    commandMode = true;
                    UARTJB_PutString("$$$");
                }
                else{
                    UARTJB_PutString(strTxti);  
                    UARTJB_PutString("\r\n");
                }
        }       
    }
    return (1);    
}