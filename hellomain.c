/* 
 * File:   hellomain.c
 * Author: ashley
 *
 * Created on April 28, 2015, 3:35 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "configbitsrev2014vC.h"

/*
 * 
 */
int main(int argc, char** argv) {
    LATE = 0;
    TRISE = 255;
    TRISEbits.TRISE0 = 0;
    asm volatile("ei");
    INTCONbits.MVEC = 1;
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE3 = 0;

    // BEGIN WVUSB CODE
    
    xmitTest();
    setLCDdefaults();
    
    // END WVUSB CODE
    
    
    
    // BEGIN TESTING
    
    timer_init(10);
    // initialize and print output
    initSPI2Master();
    //write2AllEnable();
   
    // END TESTING
    return (EXIT_SUCCESS);
}

void setLCDdefaults(void){
    LCD_init();
    LCD_clear();
    LCD_setpos(0,0);
    set_output_device(1);
}

int xmitTest(void){
    // initialize strings
    char* myname;
    myname = "Ashley Towne";
    serial_init(9600);

    // initialize LCD
    LCD_init();
    LCD_display_on();
    set_output_device(2); // select LCD as output

    // output to LCD
    LCD_clear();
    LCD_setpos(0,0);
    printf("%s",myname);
    LCD_setpos(1,0);

    // output to terminal
    set_output_device(1); // select UART as output device
    printf("This goes to terminal\n"); // write to the screen
    printf("%s\n", myname);
    // loop
    int foo = 0;
    unsigned char mystr;
    int ctr = 0;
    while(ctr<10)
    {
        ctr = ctr + 1;
        if (foo==0){mystr='0';}
        else if(foo==1){mystr = '1';}
        else if(foo==2){mystr = '2';}
        else if(foo==3){mystr = '3';}
        else if(foo==4){mystr = '4';}
        else if(foo==5){mystr = '5';}
        else if(foo==6){mystr = '6';}
        else if(foo==7){mystr = '7';}
        else if(foo==8){mystr = '8';}
        else if(foo==9){
            mystr = '9';
            foo = -1;
        }

        set_output_device(2);
        putu((char)(100+foo));
        set_output_device(1);
        LCD_char((char)(100+foo));

        foo = foo + 1;
    }

    putu('z');
    LCD_char('z');
    putu(EOF);
    return 1;
}

void serial_init6(unsigned long rate){
    U6MODEbits.ON = 1;      //Enable UART6
    U6MODEbits.BRGH = 1;    //Enable High Baud Rate
    U6STAbits.URXEN = 1;    //Enable UART6 Receiver
    U6STAbits.UTXEN = 1;    //Enable UART Transmitter

    long PBclock = get_pb_clock(); //Get peripheral bus clock frequency
    U6BRG = floor(PBclock/(4*rate)-1);  //Calculate and set U6BRG
}

char getu6(){
    char input;
    int b = 0;
    while(b == 0)                    //Wait for input
    {
        if(U6STAbits.URXDA == 1)
        {
            input = U6RXREG;         //Set input
            b = 1;                   //Exit loop
        }
    }
    return input;                    //Return input
}

void putu6(char output){
    int b = 0;
    while(b == 0)                     //Wait for output
    {
        if(U6STAbits.URXDA == 1)
        {
            U6TXREG = output;         //Set output
            b = 1;                    //Exit loop
        }
    }
}
