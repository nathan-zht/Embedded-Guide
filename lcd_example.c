#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "lcd.h"
#include "utils.h"

int main(int argc, char** argv) {
    LCD_Init();
    while(1){
        LCD_WriteStringAtPos("HELLO WORLD", 0, 1);
        DelayAprox10Us(2000);
        LCD_DisplayClear();
//        LCD_ReturnHome();
    }
    return (EXIT_SUCCESS);
}

