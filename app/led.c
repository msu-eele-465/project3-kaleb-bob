
#include "intrinsics.h"
#include <msp430fr2355.h>
#include <stdbool.h>

// declarations
int patt2count =0;
int patt3step =0;
int patt4count =0;
int patt5step =0;
int patt6step =0;
int patt7step =0;

// setup
void setup(){
    P1DIR |= BIT0;
    P1DIR |= BIT1;
    P1DIR |= BIT2;
    P1DIR |= BIT3;
    P1DIR |= BIT4;
    P1DIR |= BIT5;
    P1DIR |= BIT6;
    P1DIR |= BIT7;

    P1OUT &= ~BIT0;
    P1OUT &= ~BIT1;
    P1OUT &= ~BIT2;
    P1OUT &= ~BIT3;
    P1OUT &= ~BIT4;
    P1OUT &= ~BIT5;
    P1OUT &= ~BIT6;
    P1OUT &= ~BIT7;
}

// case 3
void case3patt(){
    
    switch(patt3step){
                case 0:
                    P1OUT = 24;
                    break;
                case 1:
                    P1OUT = 36;
                    break;
                case 2:
                    P1OUT = 66;
                    break;
                case 3:
                    P1OUT = 129;
                    break;
                case 4:
                    P1OUT = 66;
                    break;
                case 5:
                    P1OUT = 36;
                    break;
                default: 
                    P1OUT = 0xFF;
                    break;

    }
    _delay_cycles(525000); // 0.25
    patt3step++;
    if (patt3step > 5){
        patt3step = 0;
        return; // maybe comment out later
    }
}


// case 5
void case5patt(){
    
    switch(patt5step){
                case 0:
                    P1OUT = 1;
                    break;
                case 1:
                    P1OUT = 2;
                    break;
                case 2:
                    P1OUT = 4;
                    break;
                case 3:
                    P1OUT = 8;
                    break;
                case 4:
                    P1OUT = 16;
                    break;
                case 5:
                    P1OUT = 32;
                    break;
                case 6:
                    P1OUT = 64;
                    break;
                case 7:
                    P1OUT = 128;
                    break;
                default: 
                    P1OUT = 0xFF;
                    break;

    }
    _delay_cycles(525000);
    patt5step++;
    if (patt5step > 7){
        patt5step = 0;
        return; // maybe comment out later
    }
}

// case 6
void case6patt(){
    
    switch(patt6step){
                case 0:
                    P1OUT = 127;
                    break;
                case 1:
                    P1OUT = 191;
                    break;
                case 2:
                    P1OUT = 223;
                    break;
                case 3:
                    P1OUT = 239;
                    break;
                case 4:
                    P1OUT = 247;
                    break;
                case 5:
                    P1OUT = 251;
                    break;
                case 6:
                    P1OUT = 253;
                    break;
                case 7:
                    P1OUT = 254;
                    break;
                default: 
                    P1OUT = 0xFF;
                    break;

    }
    _delay_cycles(125000);
    patt6step++;
    if (patt6step > 7){
        patt6step = 0;
        return; // maybe comment out later
    }
}

// case 7
void case7patt(){
    
    switch(patt7step){
                case 0:
                    P1OUT = 1;
                    break;
                case 1:
                    P1OUT = 3;
                    break;
                case 2:
                    P1OUT = 7;
                    break;
                case 3:
                    P1OUT = 15;
                    break;
                case 4:
                    P1OUT = 31;
                    break;
                case 5:
                    P1OUT = 63;
                    break;
                case 6:
                    P1OUT = 127;
                    break;
                case 7:
                    P1OUT = 255;
                    break;
                default: 
                    P1OUT = 0xFF;
                    break;

    }
    _delay_cycles(525000);
    patt7step++;
    if (patt7step > 7){
        patt7step = 0;
        return; // maybe comment out later
    }
}


void loop(int pattern){
    int k;
    for(k = 0; k < 10; k++)
    {
        int i;
        int patt;
        patt = pattern;
        if (patt == 10 || patt == 11)
        {
            // change base rate
        }
        else if (patt == 12)
        {
            // cursor
        }
        else
        {
            switch(patt)
            {
                case 0 :                // display "10101010"
                    P1OUT = 170;
                    break;
                case 1 :                // display "10101010", wait one second, display "01010101"
                    P1OUT = 170;
                    __delay_cycles(1050000);
                    P1OUT = 85;
                    __delay_cycles(1050000); // one sec
                    break;
                case 2 :
                    P1OUT = patt2count;
                    __delay_cycles(525000); // 0.5 sec
                    patt2count++;
                    break;
                case 3 :
                    case3patt();
                    break;
                case 4 : 
                    P1OUT = patt4count;
                    __delay_cycles(262500); // 0.25 sec
                    patt4count--;
                    if (patt4count == 0){
                        patt4count = 255;
                    }
                    break;
                case 5 :
                    case5patt();
                    break;
                case 6 :
                    case6patt();
                    break;
                case 7 :
                    case7patt();
                    break;
                default:
                    P1OUT = 0xFF;
                    break;
            }
        }
    }

    
        
    return;

}
