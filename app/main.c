#include <msp430.h>
#include <stdbool.h>
#include <stdio.h>

int main(void){
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    
    // Disable the GPIO power-on default high-impedance mdoe to activate
    // previously configure port settings
    PM5CTL0 &= ~LOCKLPM5;

    // setup of GPIO Port 3
    // cols : P3.0 - P3.3 on MSP, Pins 1 - 4 on Keypad
    // rows : P3.4 - P3.7 on MSP, Pins 5 - 8 on Keypad

    //   Value, MSP Col, MSP Row, KeyPad Pin Col, Keypad Pin Row

    //    || 1, P3.3, P3.7, 4, 8 | 2, P3.2, P3.7, 3, 8 | 3, P3.1, P3.7, 2, 8 | A, P3.0, P3.7, 1, 8 ||
    //    || 4, P3.3, P3.6, 4, 7 | 5, P3.2, P3.6, 3, 7 | 6, P3.1, P3.6, 2, 7 | B, P3.0, P3.6, 1, 7 ||
    //    || 7, P3.3, P3.5, 4, 6 | 8, P3.2, P3.5, 3, 6 | 9, P3.1, P3.5, 2, 6 | C, P3.0, P3.5, 1, 6 ||
    //    || *, P3.3, P3.4, 4, 5 | 0, P3.2, P3.4, 3, 5 | #, P3.1, P3.4, 2, 5 | D, P3.0, P3.4, 1, 5 || 


   /* while(true)
    {
    } */

    // set up P6.6 (LED) as output
    P6DIR |= BIT6;
    P6OUT &= ~BIT6;

    // Set up P1.0 (LED) as output
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    int row[] = {0, 0, 0, 0};
    int col[] = {0, 0, 0, 0};

    int i;
    i = 0;

    row[i] = findRow();
    col[i] = findCol();
    i++;

    while(i < 4)
    {
        if(P3IN == 240) // if button has been released
        {
            row[i] = findRow();
            col[i] = findCol();
            i++;
        }
        else {
        }
    }

    if(row[0] == 8 && row[1] == 8 && row[2] == 7 && row[3] == 5)
    {
        if(col[0] == 1 && col[1] == 2 && col[2] == 3 && col[3] == 1)
        {
            P1OUT |= BIT0;
            P6OUT |= BIT6;
        }
    }



    return 0;

}

int findRow(void)
{
   // set up columns as outputs
   P3DIR |= BIT3; // set P3.3 as output
   P3DIR |= BIT2; // set P3.2 as output
   P3DIR |= BIT1; // set P3.1 as output
   P3DIR |= BIT0; // set P3.0 as output

   // set up rows as inputs
   P3DIR &= ~BIT7; // set P3.7 as input, clear value
   P3DIR &= ~BIT6; // set P3.6 as input, clear value
   P3DIR &= ~BIT5; // set P3.5 as input, clear value
   P3DIR &= ~BIT4; // set P3.4 as input, clear value

   // enable resistors on P3.4 - P3.7
   P3REN |= BIT4;
   P3REN |= BIT5;
   P3REN |= BIT6;
   P3REN |= BIT7;
   P3OUT &= ~BIT4;
   P3OUT &= ~BIT5;
   P3OUT &= ~BIT6;
   P3OUT &= ~BIT7; 

   // set all columns HIGH
   P3OUT |= BIT3;
   P3OUT |= BIT2;
   P3OUT |= BIT1;
   P3OUT |= BIT0;

   int keyIn;

   // reading row input (00001111 - 15)
   // if button is pushed, one of these four
    // 10001111 - 143, ROW 8
    // 01001111 - 79, ROW 7
    // 00101111 - 47, ROW 6
    // 00011111 - 31, ROW 5
    int i;
    int row;
    keyIn = P3IN;

    switch(keyIn)
    {
        case 143:           // in ROW 8
            P1OUT &= ~BIT0;
            P6OUT |= BIT6;
            return 8;
        case 79:            // in ROW 7
            P1OUT &= ~BIT0;
            P6OUT |= BIT6;
            return 7;
        case 47:            // in ROW 6
            P1OUT &= ~BIT0;
            P6OUT |= BIT6;
            return 6;
        case 31:            // in ROW 5
            P1OUT &= ~BIT0;
            P6OUT |= BIT6;
            return 5;
        default:            // no buttons pushed
            P1OUT |= BIT0;
            P6OUT &=~ BIT6;
            findRow();      // call function again until button is pushed

    }
    
}

int findCol(void)
{
    // set all columns to inputs
    // set all row to outputs

   // set up columns as inputs
   P3DIR &= ~BIT3; // set P3.3 as input, clear
   P3DIR &= ~BIT2; // set P3.2 as input, clear
   P3DIR &= ~BIT1; // set P3.1 as input, clear
   P3DIR &= ~BIT0; // set P3.0 as input, clear

   // set up rows as outputs
   P3DIR |= BIT7; // set P3.7 as output, clear value
   P3DIR |= BIT6; // set P3.6 as output, clear value
   P3DIR |= BIT5; // set P3.5 as output, clear value
   P3DIR |= BIT4; // set P3.4 as output, clear value

   // set all rows HIGH
   P3OUT |= BIT7;
   P3OUT |= BIT6;
   P3OUT |= BIT5;
   P3OUT |= BIT4;

   // enable resistors on P3.0 - P3.3
   P3REN |= BIT0;
   P3REN |= BIT1;
   P3REN |= BIT2;
   P3REN |= BIT3;
   P3OUT &= ~BIT0;
   P3OUT &= ~BIT1;
   P3OUT &= ~BIT2;
   P3OUT &= ~BIT3; 

    int i;
    int col;
    int keyIn;
    keyIn = P3IN;

    switch(keyIn)
    {
        case 241:           // in COL 1
            return 1;
        case 242:            // in COL 2
            return 2;
        case 244:            // in COL 3
            return 3;
        case 248:            // in COL 4
            return 4;
        default:            // no buttons pushed
            findCol();       // call function again

    }

}
