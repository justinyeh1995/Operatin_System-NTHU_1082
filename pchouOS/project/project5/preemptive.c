#include <8051.h>

#include "preemptive.h"

/*
 * @@@ [2 pts] declare the static globals here using 
 *        __data __at (address) type name; syntax
 * manually allocate the addresses of these variables, for
 * - saved stack pointers (MAXTHREADS)
 * - current thread ID
 * - a bitmap for which thread ID is a valid thread; 
 *   maybe also a count, but strictly speaking not necessary
 * - plus any temporaries that you need.
 */
__data __at (0x30) char saved_sp[4];
__data __at (0x34) char mask;

__data __at (0x36) char sp_temp;
__data __at (0x37) char new_thread;




#define SAVESTATE \
            __asm \
            PUSH ACC\
            PUSH B\
            PUSH DPL\
            PUSH DPH\
            PUSH PSW\
            __endasm;\
            saved_sp[cur_thread] = SP;\





#define RESTORESTATE \
            SP = saved_sp[cur_thread];\
            __asm \
            POP PSW\
            POP DPH\
            POP DPL\
            POP B\
            POP ACC\
            __endasm; \
         




extern void main(void);

// void delay(unsigned char n){
//     time_temp[cur_thread] = time + n;
//     while( time_temp[cur_thread] != time ){}
//     //for(int i = 0 ; i<3000;i++){}
// }
unsigned char now(void){
    return time;
}

void Bootstrap(void) {
      mask = 0;
      TMOD = 0;  // timer 0 mode 0
      IE = 0x82;  // enable timer 0 interrupt; keep consumer polling
                // EA  -  ET2  ES  ET1  EX1  ET0  EX0
      TR0 = 1; // set bit TR0 to start running timer 0
      cur_thread = ThreadCreate( main );
      RESTORESTATE;
      
}
void myTimer0Handler(){
    EA = 0;
    SAVESTATE;
    __asm
        MOV A, R0
        PUSH ACC
        MOV A, R1
        PUSH ACC
        MOV A, R2
        PUSH ACC
        MOV A, R3
        PUSH ACC
        MOV A, R4
        PUSH ACC
        MOV A, R5
        PUSH ACC
        MOV A, R6
        PUSH ACC
        MOV A, R7
        PUSH ACC
    __endasm;
    time_sec = time_sec + 1;
    if(time_sec==8){ time = time + 1; time_sec = 0;}
    
    do{
    cur_thread = (cur_thread < 3 ) ?  cur_thread+1 : 0;
    if( cur_thread == 0 ){if( mask&1 ){break;}}
    else if( cur_thread == 1 ){if( mask&2 ){break;}}
    else if( cur_thread == 2 ){if( mask&4 ){break;}}
    else if( cur_thread == 3 ){if( mask&8 ){break;}}   
    } while (1);
    __asm
        POP ACC
        MOV R7, A
        POP ACC
        MOV R6, A
        POP ACC
        MOV R5, A
        POP ACC
        MOV R4, A
        POP ACC
        MOV R3, A
        POP ACC
        MOV R2, A
        POP ACC
        MOV R1, A
        POP ACC
        MOV R0, A
    __endasm;  
    RESTORESTATE;
    EA = 1;
    __asm 
        RETI
    __endasm;
       
}

/*
 * ThreadCreate() creates a thread data structure so it is ready
 * to be restored (context switched in).
 * The function pointer itself should take no argument and should
 * return no argument.
 */
ThreadID ThreadCreate(FunctionPtr fp) {
        EA = 0;
        // a., b.
         if( mask == 15 ) //mask = 0b1111, four thread
            return -1;
         

        if( !( mask & 1 ) ){
            mask = mask | 1;
            new_thread = 0;
        }else if( !( mask & 2 ) ){
            mask = mask | 2;
            new_thread = 1;
        }else if( !( mask & 4 ) ){
            mask = mask | 4;
            new_thread = 2;
        }else if( !( mask & 8 ) ){
            mask = mask | 8;
            new_thread = 3;
        }
         //c.
         sp_temp = SP;
         SP = (0x3F) + (0x10) * new_thread;
         //d.
         // DPL = (int)fp & (0x00FF);
         // DPH = (int)fp & (0xFF00);
         __asm
            PUSH DPL
            PUSH DPH
         __endasm;
              


    
         //e.
         __asm 
            ANL A, #0
            PUSH ACC
            PUSH ACC
            PUSH ACC
            PUSH ACC
         __endasm;
  

         //f.
         PSW = new_thread << 3;
         __asm 
            PUSH PSW
         __endasm;

         // g.
         saved_sp[new_thread] = SP;
         //h.
         SP = sp_temp;
         //i.
        EA = 1;
         return new_thread;
        
         
}



/*
 * this is called by a running thread to yield control to another
 * thread.  ThreadYield() saves the context of the current
 * running thread, picks another thread (and set the current thread
 * ID to it), if any, and then restores its state.
 */

void ThreadYield(void) {
      __critical{
      SAVESTATE;
      do{
         cur_thread = (cur_thread < 3 ) ?  cur_thread+1 : 0;
         if( mask & (1<<cur_thread) ){
            break;
         }      
      } while (1);
      RESTORESTATE;
      }
}


/*
 * ThreadExit() is called by the thread's own code to termiate
 * itself.  It will never return; instead, it switches context
 * to another thread.
 */
void ThreadExit(void) {
        EA = 0;
        if(cur_thread == 0) mask = mask - 1;
        else if( cur_thread == 1 )mask = mask - 2;
        else if( cur_thread == 2 )mask = mask - 4;
        else if( cur_thread == 3 )mask = mask - 8;

        if(  mask & 1  ){
            cur_thread = 0;
        }else if(  mask & 2  ){
            cur_thread = 1;
        }else if(  mask & 4  ){
            cur_thread = 2;
        }else if(  mask & 8  ){
            cur_thread = 3;
        }else{
            //RESTORESTATE;
            while(1){}
        }
        
        RESTORESTATE;
        EA = 1;
}
