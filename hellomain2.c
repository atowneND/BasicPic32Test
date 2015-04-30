/* 
 * File:   hellomain2.c
 * Author: ashley
 *
 * Created on April 29, 2015, 8:27 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "configbitsrev2014vC.h"
#include "SDlib.h"

/*
 * 
 */
int main(int argc, char** argv) {
    TRISB = 0;
    LATBbits.LATB12 = 1;

    //TRISD = 0;
    //LATDbits.LATD0 = 1;
    return (EXIT_SUCCESS);
}

