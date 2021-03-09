
#include <8051.h>
#include "preemptive.h"

__data __at (0x3A) char next_car;
__data __at (0x3B) char Token;
__data __at (0x3C) char car;
__data __at (0x3D) char mutex;
__data __at (0x3E) char empty;
__data __at (0x3F) char Token2;
__data __at (0x2A) char id;
__data __at (0x2B) char car_name[4]; //B~E
__data __at (0x2F) char car_id;



#define L(x) LABEL(x)
#define LABEL(x) x##$


#define print(a, b)\
    TMOD |= 0x20;\
    TH1 = -6;\
    SCON = 0x50;\
    TR1 = 1;\
    for(id = 0; id < 4 ; id++){\
        if( id==0 ) SBUF = a;\
        else if( id == 1 ) SBUF = b;\
        else if( id == 2 ) SBUF = (time&7) + '0';\
        else if( id == 3 ) SBUF = '\n';\
        while( !TI ){}\
        TI = 0;\
    }\
    //EA = 1;


void Producer(void) {
        /* @@@ [6 pt]
            * wait for the buffer to be available, 
    * and then write the new data into the buffer */
   
        SemaphoreWaitBody(empty, L(__COUNTER__) );
        SemaphoreWaitBody(mutex, L(__COUNTER__) );
        EA = 0;
        if( Token == '0' ){ 
            Token = car_name[cur_thread];
            print(car_name[cur_thread],'i');
        }else if( Token2 == '0' ){
            Token2 = car_name[cur_thread];
            print(car_name[cur_thread],'i');
        }
        EA = 1;
        SemaphoreSignal(mutex);
        //EA = 1;
        delay(2);
        
        EA = 0;
        if( Token == car_name[cur_thread] ){
            Token = '0';
            print(car_name[cur_thread], 'o');
        }else if( Token2 == car_name[cur_thread] ){ 
            Token2 = '0';
            print(car_name[cur_thread], 'o');
        }
        EA = 1;
        SemaphoreSignal(empty);
        SemaphoreSignal(next_car);
        ThreadExit();
   
} 

void main(void) {
        SemaphoreCreate(mutex, 1);
        SemaphoreCreate(empty,2);
        SemaphoreCreate(next_car, 0);

        EA = 1;

        Token = '0';
        Token2 = '0';
        car = '1';
        
        car_id = ThreadCreate( Producer );
        car_name[ car_id ] = car;
        car = car+1;

        car_id = ThreadCreate( Producer );
        car_name[ car_id  ] = car;
        car = car+1;

        car_id = ThreadCreate( Producer );
        car_name[ car_id  ] = car;
        car = car+1;
        while(time < 0x1f){
            SemaphoreWaitBody(next_car, L(__COUNTER__) );
            car_id = ThreadCreate( Producer );
            // if( car == Token2 || car == Token ){
            //     car = (car == '5') ? '1' : car+1;
            // }
            car_name[ car_id  ] = car;
            car = (car == '5') ? '1' : car+1;
        }
        ThreadExit();
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
