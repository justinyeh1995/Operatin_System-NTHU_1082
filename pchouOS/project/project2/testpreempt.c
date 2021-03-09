
#include <8051.h>
#include "preemptive.h"

__data __at (0x3A) char buffer;
__data __at (0x3B) char Token;
__data __at (0x3C) char buffer_full;


void Producer(void) {
		Token = 'A';
        while (1) {
                /* @@@ [6 pt]
                 * wait for the buffer to be available, 
                 * and then write the new data into the buffer */
                while( buffer_full ){
                    //ThreadYield();
                }
                __critical{
                buffer = Token;
                buffer_full = 1;
                Token = ( Token == 'Z' ) ? 'A' :  Token + 1;
                }
        }
}

void Consumer(void) {
        /* @@@ [2 pt] initialize Tx for polling */
        EA = 0;
        TMOD |= 0x20; // TMOD is also assigned by the (modified) Bootstrap code to set up the timer interrupt in timer-0 for preemption 
        TH1 = -6;
        SCON = 0x50;
        TR1 = 1;
        EA = 1;
        while (1) {
                while( !buffer_full ){
                    //ThreadYield();
                }
                __critical{
                SBUF = buffer;
		        buffer_full = 0;
                }
                while( !TI ){
			        //ThreadYield();
				}
                TI = 0;
        }
}

void main(void) {
        buffer_full = 0;
        ThreadCreate( Producer );
        Consumer();    
        
}

void _sdcc_gsinit_startup(void) {
        __asm
            ljmp  _Bootstrap
        __endasm;
}

void _mcs51_genRAMCLEAR(void) {}
void _mcs51_genXINIT(void) {}
void _mcs51_genXRAMCLEAR(void) {}
void timer0_ISR(void) __interrupt(1) {
        __asm
            ljmp _myTimer0Handler
        __endasm;
}
