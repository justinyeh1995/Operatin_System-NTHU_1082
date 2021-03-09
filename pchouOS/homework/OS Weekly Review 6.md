# OS Weekly Review 6



###### tags: `Operating System`

## part 1 EdSim51 SDCC
1. What is the difference between a subroutine and a function? Which one is more complicated?
	> function: complier support wrapper around subroutine
	> subroutine: ISA support call-return code fragment
	> function複雜多了

2. What instruction can be used for calling a subroutine?
	> `LCALL`, `LJMP`

3. What instruction is used for returning from a subroutine call?
	> `RET`, or `RETI`(interrupt 用得)
	> 

4. The subroutine-call instruction needs to specify the address of the subroutine to call, but the return instruction just returns without operand. How does it know where to return to?
	> LCALL, ACALL instructions => push(PC for next instruction),
	> pop(return address) from stack
•

5. What is the power-on value of the stack pointer SP?
	> 0x7

6. Which way does the 8051 stack grow? That is, when you PUSH, does the processor increment or decrement the stack pointer?
	> increment

7. if SP is currently pointing to address 8H, after a PUSH instruction, what address contains the newly pushed value, and what is the new value of SP?
   > PUSH: IDATA[++SP] = value
   > SP = 8H+1 = 9H
   > value is at IDATA[9H] 

8. if SP is currently pointing at address 9H, what address is the POP value read from?
   > POP: value = IDATA[SP- -]
   > SP = 8H
   > value is from IDATA[9H]

9. Can the program counter (PC) be modified by a MOV instruction? If not, what instruction (or sequence of instructions) can be used
   a. to assign a constant address to the PC?
   b. to assign a variable address in DPTR?
   > can't do a MOV instruction to/from PC(講義第4頁)
   > a. JMP address
   > b. push DPL, push DPH, then RET

10. Is 8051 a big-endian or little-endian architecture?
    > little-endian

11. If you do an LCALL to target address 1234H, and the SP is currently pointing at address 7H, what are the new values at address 8H and at address 9H after the call, and what is the new value of SP?
    > Suppose the code address of LCALL is 1234H
    > then 1234H + 3 = 1237H
    > After LCALL, IDATA[8H] = 37H, IDATA[9H] = 12H
    > new SP = 7H+2 = 9H

12. What is the addressing mode accepted by PUSH and POP instructions on 8051?
    > PUSH / POP only accepts Direct Mode
    > The operand is specitied by an 8-bit addreas field in the instruction.
13. Does 8051 allow PUSH A or POP A? If not, how do you push a value from the accumulator to the stack or pop a value from the stack into the accumulator?
	> invalid(資料來源：https://reurl.cc/b6D3gy)
	> ![](https://i.imgur.com/UTXVtTA.png)
	> ![](https://i.imgur.com/mvaacub.png)



14. Does 8051 allow PUSH R2 or POP R2? If not, how does SDCC generate code that pushes a value from register R2 or pop a value into register R2?
	> 使用“位址”取代一般暫存器別名，例如：“PUSH 00”取代“PUSH R0”

15. Why does C compiler need to save registers before a function call and restore registers after a function return?
	> 將psw, ACC....的資料取回(不確定)
	> 因為function call會用到register，把值洗掉

16. What does JC instruction do?
	> 	`JC rel`: 若C=1跳至rel

17. How does SDCC pass parameter to a function that expects
	![](https://i.imgur.com/H0coW3a.png)

    a. a single-byte parameter?
	> 上圖所示
	> 
    b. two single-byte parameters?
	> 上圖所示

    c. a single two-byte parameter?
	> 上圖所示

18. How does SDCC return a value from a function:
    a. a single byte return value?
	> one byte return value in DPL
	> 
    b. a two-byte return value?
	>  two byte value in DPL (LSB) and DPH (MSB)

## Cooperative Threads part 2
1. Why is 8051 called a Harvard architecture?
	> separate address spaces for code and data
3. What defines the context of a thread on an 8051?
	> PSW: program status word(不確定)
	> ![](https://i.imgur.com/lU0tkjA.png)

5. What does this C declaration do?
   `typedef void (*FunctionPtr)(void);`
   
    > 讓我們在 call ThreadCreate() 時可以直接打函數名稱（不確定）
   
4. In the testcoop.c file, what does this code do:
   ```c
   void _sdcc_gsinit_startup(void) {
   __asm
      ljmp _Bootstrap
   __endasm;
   }
   ```
   
    > 程式執行時會先執行 _sdcc_gsinit_startup(void) ，也就是會先執行 Bootstrap()

5. Why is the C function Bootstrap named _Bootstrap in assembly (i.e., prepended with an underscore)?

    > 由於要跳到 Bootstrap() ，而 8051 編譯後會在函數名稱前加上一個 _ ，因此需要 ljmp _Bootstrap ，才會跳到 Bootstrap()

6. In the Producer-Consumer example, what are the different ways threads can be created to run the Producer and Consumer functions?

    > (投影片 P.12)

7. In the memory allocation scheme for cooperative threads, what is the address range of the stack for thread 0? thread 1? thread 2? thread 3?

    > (投影片 P.24)

8. Register banks
   a. Which bits in which register do you set to select the register bank?
   b. When <RS1:RS0> = 2 (i.e., PSW<4:3> = 2), which IRAM addresses get mapped to registers R0-R7?
   > a. PSW[7:0] 的 PSW[4:3] 代表 Register Bank
   > b. R0-R7 = IRAM[0x08 ~ 0x0F]

9. What are the purposes of the macros
   a. SAVESTATE?
   b. RESTORESTATE?
   c. Is it necessary to push the registers R0-R7 onto the stack during SAVESTATE and pop them back into R7-R0 during RESTORESTATE?
   > a. Save the data about the interruptted thread.
   > b. Change the state to execute next thread
   > c. Depends on machine. If there're multiple register banks, it's no need to push R0-R7. If there's only 1 register bank, PUSH and POP is necessary.

10. Memory for variables
    a. What region of memory is available for use by the thread manager and application program as global variables after the register banks and stacks have been allocated?
    b. What is the purpose of the thread bitmap, which is a (global) variable maintained by the thread manager?
    > a. Region except addr 0x00~0x1F, 0x40 ~ 0x7F is available.
    > b. mantain the number of thread, and determine which thread id is used or not.

11. What are the four major steps of the Bootstrap routine?
    > 1. Initialize the thread bitmap
    > 2. Creat Thread for main()
    > 3. Set current Thread id to the thread id of main()
    > 4. Restore status of thread

12. Bootstrapping
    a. [slide 27] How should Boostrap initialize the thread bitmap?
    > bitmap = 0B0000

    b. [slide 28] When Bootstrap calls ThreadCreate(main) to create the context for main, which stack is used, and what is the content of that stack when ThreadCreate is first entered? How is the parameter passed and what does it mean?
    > the SP = 0x07 at first.
    > IDATA[0x08], IDATA[0x09] = the next PC of ThreadCreate(main) when ThreadCreate is first entered.
    > the parameter (function pointer of main) passed by DPTR.
    
    c. Does ThreadCreate() modify the current thread ID?
    > Nope 
    
    d. [slide 32] How does Bootstrap() start running the main() function whose context has been set up by ThreadCreate(main)?
    > Use RESTORESTATE to change the PC after return
    
    e. After Bootstrap starts running main's thread, what happens to the initial stack that Bootstrap used (from part b of this question)?
    > the initial stack will be used as register for the thread with register bank1

13. Thread creation
    a. If you can assume all threads must explicitly call ThreadExit() if they ever exit (and never implicitly call ThreadExit() when the function finishes), to create the new thread-0's context that can be restored to run main from the beginning, how should the ThreadCreate() function initialize the content of stack-0 (and set its SP value) and why?
    > 1. Set SP to the bank of new Thread
    > 2. PUSH address of request function
    > 3. PUSH initial value of ACC, B, DPL, DPH, PSW
    > 4. Set SP back
    
    b. How should ThreadCreate() initialize a thread's stack content before RESTORESTATE in order to support implicit call to ThreadExit() upon function return?
    > 1. Set SP to the bank of new Thread
    > 2. PUSH address of ThreadExit()
    > 3. PUSH address of request function
    > 4. PUSH initial value of ACC, B, DPL, DPH, PSW
    > 5. Set SP back

14. [slide 33] When main() calls ThreadCreate(Producer),
    a. which stack does main use to make this call?
    b. what is that stack's content upon entering the ThreadCreate function, assuming we do not need to support implicit ThreadExit (and therefore need not push ThreadExit's address upon ThreadCreate)?
    > a. stack = IDATA[0x40 ~ 0x4F]
    > b. let nxtPC = next PC of ThreadCreate(Producer)
    >    then the stack contains: DPL of nxtPC | DPH of nxtPC

15. [slide 34] By the time main() returns from ThreadCreate(Producer), which returns the thread ID of 1 for the newly created thread,
    a. what is on stack 0?
    b. what is on stack 1? and what is its savedSP value?
    c. what is the value of SP?
    d. what is the value of DPL and why?
    e. stack1 contains value 08H at address 56H, which is intended to be restored into PSW when thread1 resumes. Why value 08H?
    > 中文敘述: 在 main return from ThreadCreate(Producer) 的時候。
    > a. Nothing
    > b. address of producer, savedSP = [46H, 56H, --, --]
    > c. 0x3F
    > d. DPL = store return value of ThreadCreate(Producer)
    > e. 08H = 00001000, PSW[4:3] = 01 means using bank 1 for this thread.
16. Why should main() call Consumer() instead of creating another thread to run Consumer?
    > Save the memory usage.
    > There'll be 3 threads if main create another thread to run Consumer.

17. [slide 35] When main() calls Consumer(), what is the content of the stack upon entering Consumer?

    > main 中呼叫完 Consumer() 後該執行的指令位置（return address = main (3)）

18. [slide 36] When Consumer() calls ThreadYield(), what is the content of the stack upon entering ThreadYield()?

    > Consumer() 中呼叫完 ThreadYield() 後該執行的指令位置（return address = Consumer (2)）

19. [slide 37] What are the three major steps in ThreadYield()?

    > (1) SAVESTATE
    > (2) pick next thread
    > (3) RESTORESTATE

20. What does the thread0's stack look like aftelr ThreadYield() calls SAVESTATE?

    > (投影片 P.38 右上角)

21. When ThreadYield() is picking the next thread to context switch to,
    a. what data structure does it check to know what threads are available to choose from?
    
    > thread bitmap
    
    b. what stack is it running on during choosing the next thread?
    
    > stack of current thread (應該吧)
    
    c. what happens if an interrupt happens during this time? Can an interrupt cause any problems?

    > 投影片找過找不到 不知道上課影片有沒有提到

22. [slide 39-40] How does the SP change from the time ThreadYield() just before RESTORESTATE to just after RESTORESTATE?

    > SP被修改成「被挑選要切換到的 thread 的 saved SP 」
    > SP POP 5次

23. [slide 40] After ThreadYield() does RESTORESTATE, where and how does it "continue" running the thread it is restoring?

    > ThreadYield() does a RET to the caller function
    > then PC is now pointing to restoring thread 該執行的指令位置

## part 2 Definitions and Short Answers - CPU Scheduling


19. What are four cases when a preemptive CPU scheduler can take control?
20. What are the two cases when a nonpreemptive CPU scheduler can take control?
21. What kind of problem can be caused by preemptive scheduling that is not a problem for nonpreemptive?
22. Does a kernel have to be designed to be preemptive in order to support preemptive scheduling of user processes? Or can a nonpreemptive kernel also support preemptive scheduling of user processes?