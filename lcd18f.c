/*
 * File:   lcd18f.c
 * Author: Huggie
 *
 * Created on November 6, 2012, 3:49 PM
 */

#include <xc.h>
#include "lcd18f.h"
#include "menu.h"



#pragma config CPUDIV = OSC1_PLL2
#pragma config PLLDIV = 2
#pragma config FOSC = HS
#pragma config VREGEN = OFF
#pragma config BOR=OFF
#pragma config PBADEN = OFF
#pragma config IESO =	OFF
#pragma config PWRT= OFF
#pragma config WDT = OFF
#pragma config DEBUG = OFF
#pragma config LVP =OFF
#pragma config STVREN = OFF

void main(void) {
    int cursor = 0;
    int menuPos = 0;

    int i = 0;

    struct Menu Main, *Current;
    init(&Main);

    Current = Main.subMenus;

    long int delay = 100000;
    long int k = 0; 

    printMenu(Current, &menuPos, &cursor);

    while(0){
        for(k = 0;k<delay;k++);
        Current = moveIn(Current, &menuPos, &cursor);
        for(k = 0;k<delay;k++);
        Current = moveIn(Current, &menuPos, &cursor);
        for(k = 0;k<delay;k++);
        moveDown(Current, &menuPos, &cursor);
        for(k = 0;k<delay;k++);
        Current = moveOut(Current, &menuPos, &cursor);

        for(k = 0;k<delay;k++);
        moveDown(Current, &menuPos, &cursor);
        for(k = 0;k<delay;k++);
        Current = moveIn(Current, &menuPos, &cursor);
        for(k = 0;k<delay;k++);
        Current = moveOut(Current, &menuPos, &cursor);
        while(1);
    }

    while(1){
        for(k = 0;k<delay;k++);
        Current = moveIn(Current, &menuPos, &cursor);
        for(k = 0;k<delay;k++);
        Current = moveIn(Current, &menuPos, &cursor);
        for(k = 0;k<delay;k++);
        moveDown(Current, &menuPos, &cursor);
        for(k = 0;k<delay;k++);
        Current = moveOut(Current, &menuPos, &cursor);

        for(k = 0;k<delay;k++);
        moveDown(Current, &menuPos, &cursor);
        for(k = 0;k<delay;k++);
        Current = moveIn(Current, &menuPos, &cursor);
        for(k = 0;k<delay;k++);
        Current = moveOut(Current, &menuPos, &cursor);

        for(k = 0;k<delay;k++);
        moveDown(Current, &menuPos, &cursor);
        for(k = 0;k<delay;k++);
        moveDown(Current, &menuPos, &cursor);
        for(k = 0;k<delay;k++);
        Current = moveOut(Current, &menuPos, &cursor);

        for(k = 0;k<delay;k++);
        moveDown(Current, &menuPos, &cursor);
        for(k = 0;k<delay;k++);
        Current = moveIn(Current, &menuPos, &cursor);
        for(k = 0;k<delay;k++);
        moveDown(Current, &menuPos, &cursor);
        for(k = 0;k<delay;k++);
        moveDown(Current, &menuPos, &cursor);
        for(k = 0;k<delay;k++);
        Current = moveOut(Current, &menuPos, &cursor);

        for(k = 0;k<delay;k++);
        moveDown(Current, &menuPos, &cursor);
        for(k = 0;k<delay;k++);
        moveDown(Current, &menuPos, &cursor);
        for(k = 0;k<delay;k++);
        Current = moveIn(Current, &menuPos, &cursor);
        for(k = 0;k<delay;k++);
        moveDown(Current, &menuPos, &cursor);
        for(k = 0;k<delay;k++);
        moveDown(Current, &menuPos, &cursor);
        for(k = 0;k<delay;k++);
        Current = moveOut(Current, &menuPos, &cursor);  

    }

}


