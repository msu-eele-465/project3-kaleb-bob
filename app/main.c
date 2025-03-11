#include <msp430.h>
#include <stdbool.h>
#include <stdio.h>

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
   int row;

   // reading row input (00001111 - 15)
   // if button is pushed, one of these four
    // 10001111 - 143, ROW 8
    // 01001111 - 79, ROW 7
    // 00101111 - 47, ROW 6
    // 00011111 - 31, ROW 5
    keyIn = P3IN;

    switch(keyIn)
    {
        case 143:           // in ROW 8
            row = 8;
            break;              
        case 79:            // in ROW 7
            row = 7;
            break;
        case 47:            // in ROW 6
            row = 6;
            break;
        case 31:            // in ROW 5
            row = 5;
            break;
        case 15:
            row = 10;     // no buttons pushed

    }
    return row;
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

    int col;
    int keyIn;
    keyIn = P3IN;

    // reading col input (11110000 - 240)
    // if button is pushed, one of these four
    // 11110001 - 241, COL 1
    // 11110010 - 242, COL 2
    // 11110100 - 244, COL 3
    // 11111000 - 248, COL 4

    switch(keyIn)
    {
        case 241:           // in COL 1
            col = 1;
            break;
        case 242:            // in COL 2
            col = 2;
            break;
        case 244:            // in COL 3
            col = 3;
            break;
        case 248:            // in COL 4
            col = 4;
            break;
      //  default:            // no buttons pushed
        //    findRow();
    }

    return col;

}

bool keyReleased(void)
{
        // show GREEN until code is entered
    int keyPush;
    keyPush = P3IN;
    if (keyPush < 241) // key released
    {
        return true;
    }
    else {              // key NOT released
        return false;
    }
}


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
   unlock();
}

// han shot first


void unlock(void)
{
    int r;
    int c;
    int i;
    int code;
    bool done;

    // password arrays
    int rCode[] = {8,7,5,7}; // row value of key
    int cCode[] = {2,3,2,1}; // col value of key

    done = false;
    code = 0;
    r = 10;
    i = 0;

    RGB(0); // locked

    while(i < 4)
    {
        // start of reading key input ----------------------
        while(r == 10)
        {
            r = findRow();
        }

        c = findCol();

        while(done != true)
        {
            done = keyReleased();
        }
        // end of reading key input ------------------------

        RGB(1); // unlocking color

        if(r == rCode[i] && c == cCode[i]) // comparing key to password
        {
            code++;
        }

        done = false; // reset for keyReleased function
        r = 10;       // reset for reading row of keypad
        i++;          // increment counter
    }


    // four keys have been pushed ----------------------------------

    if (code == 4)       // unlocked
    {
        RGB(2);            // unlocked color on RGB
        selectPattern();   // select pattern based on keypad input
    }
    else {          // locked
        unlock();   // repeat function
    }
}

void selectPattern(void)
{
        int r;
        int c;
        int prevR;
        int prevC;
        bool done;
        int key;
        int prevKey;

        done = false;
        r = 10;

        while(true) // since device in UNLOCKED, this will always read the input from the keypad and select a pattern
        {
            // if button is pushed, findRow() will return 5-8
            // if button is not pushed, findRow() will return 10
            r = findRow();
            if (r == 10) // button NOT pushed
            {
                r = prevR;
                c = prevC;
            }
            else        // button is pushed
            {
                c = findCol();
                while (done != true) // need to wait for button to be released
                {
                    done = keyReleased();
                }
            }

            // start of determining what key was pushed
            switch(r)
            {
                case 8:
                    switch(c)
                    {
                        case 1:
                            key = 10; // A
                        case 2:
                            key = 3;
                            break;
                        case 3:
                            key = 2;
                            break;
                        case 4:
                            key = 1;
                            break;
                        default:
                            key = 100;
                    }
                    break;
                case 7:
                    switch(c)
                    {
                        case 1:
                            key = 11; // B
                        case 2:
                            key = 6;
                            break;
                        case 3:
                            key = 5;
                            break;
                        case 4:
                            key = 4;
                            break;
                        default:    
                            key = 100;
                    }
                    break;
                case 6:
                    switch(c)
                    {
                        case 1:
                            key = 12; // C
                            break;      
                        case 2:
                            key = 9;
                            break;
                        case 3:
                            key = 8;
                            break;
                        case 4:
                            key = 7;
                            break;
                        default:
                            key = 100;
                    }
                    break;
                case 5:
                    switch(c)
                    {
                        case 3:
                            key = 0;
                            break;
                        default:
                            key = 100;
                    }
                    break;
            }
            // end of determining what key was pushed

            // A, B affect base rate
            // C affects cursor state
            // every number affects pattern


            
            if (key >= 0 && key <= 7) // changes LED pattern
            {
                setup();
                loop(key);
                // go to loop
                // setup();
                // loop(ledPatt)
            }
            else if (key == 10 || key == 11)    // changes LED pattern base rate
            {
                // go to base rate
            }
            else if (key == 12 || key == 9)     // changes cursor state
            {
                // go to cursor state
            } 

            done = false;   // reset
            r = 10;         // reset
            prevR = r;
            prevC = c;

        }
}

void RGB(int color)
{
    
    // setup RGB LED pinout
    P6DIR |= BIT0; // RED
    P6DIR |= BIT1; // GREEN
    P6DIR |= BIT2; // BLUE

    switch(color)
    {
        case 0: // locked
            P6OUT &= ~BIT0; // RED
            P6OUT |= BIT1; // GREEN
            P6OUT |= BIT2; // BLUE
            break;
        case 1: // being unlocked
            P6OUT &= ~BIT0; // RED
            P6OUT &= ~BIT1; // GREEN
            P6OUT |= BIT2; // BLUE
            break;
        case 2: // unlocked
            P6OUT &= ~BIT0; // RED
            P6OUT |= BIT1; // GREEN
            P6OUT &= ~BIT2; // BLUE
            break;

    }
    return;

}
/*
void RGBlock(void)
{
    TB0CTL |= TBCLR;    // clear timer and dividers
    TB0CTL |= TBSSEL__ACLK; // Source = ACLK (32768k)
    TB0CTL |= MC__UP;   // mode up

    TB1CTL |= TBCLR;    // clear timer and dividers
    TB1CTL |= TBSSEL__ACLK; // Source = ACLK (32768k)
    TB1CTL |= MC__UP;   // mode up

    TB0CCTL0 |= CCIE;   // enable TB0CCR0 Overflow IRQ
    TB0CCTL0 &= ~CCIFG; // clear CCR0 flag
    TB0CCTL1 |= CCIE;   // enable TB0CCR1 Overflow IRQ
    TB0CCTL1 &= ~CCIFG; // clear CCR1 flag
    TB0CCTL2 |= CCIE;   // enable TB0CCR2 Overflow IRQ
    TB0CCTL2 &= ~CCIFG; // clear CCR1 flag
    TB1CCTL0 |= CCIE;   // enable TB1CCR0 Overflow IRQ
    TB1CCTL0 &= ~CCIFG; // clear CCR1 flag
    __enable_interrupt();
    



    TB0CCR0 = 32768;    // CCR0 = 32768 // period of pulse
    TB0CCR1 = 25165;    // R
    TB0CCR2 = 7962;     // G

    TB1CCR0 = 3725;     // B

    while(1){}
}

#pragma vector = TIMER0_B0_VECTOR // puts everything high
__interrupt void ISR_TB0_CCR0(void)
{
    P6OUT |= BIT0; // RED
    P6OUT |= BIT1; // GREEN
    P6OUT |= BIT2; // BLUE
    TB0CCTL0 &= ~CCIFG;
}

#pragma vector = TIMER0_B1_VECTOR // pulls blue low
__interrupt void ISR_TB0_CCR1(void)
{
    P6OUT &= ~BIT2; // blue
    TB0CCTL1 &= ~CCIFG;
}

#pragma vector = TIMER0_B2_VECTOR // pulls green low
__interrupt void ISR_TB0_CCR2(void)
{
    P6OUT &= ~BIT1; //green
    TB0CCTL2 &= ~CCIFG;
}

#pragma vector = TIMER1_B0_VECTOR // pulls red low
__interrupt void ISR_TB1_CCR0(void)
{
    P6OUT &= ~BIT0; // red
    TB1CCTL0 &= ~CCIFG;
} */