# OS Weekly Review 2

###### tags: `Operating System`

1. Definitions and Short Answers - week 2 (9/16 lectures)
   1. What is the kernel part of an OS?
       > the "core" part that is resident and governs OS functionality
   3. What is a system program ?
       > associated with the operating system but are not necessarily part of the kernel.
       > Such as program loaders, interpreters, complier and linker.
   4. Is a web browser part of an OS? part of the kernel? part of system programs?
       > web browsers原則上是application programs—define the ways in which these resources are used to solve users’ computing problems
   6. Middleware is a set of software frameworks that provide additional services to what kind of users? What would be some example features?
       > programmar
       > support database, multimedia, cloud drive, location service 
       > provide additional services to application developers
   8. As a resource manager, what kinds of resources does an OS manage?
       > CPU time,storage space, use of I/O devices,
   10. What does API stand for? What kinds of API does an OS provide?
       > 讓programmer能跟系統互動
       > use of memory, I/O devices, storage,communication
      

   12. What is a bootloader ? How is it related to an OS?
       > 開機時執行的ROM code，將OS讀入記憶體
   14. How does a bootloader load an OS?
       > copying OS image from storage into memory (RAM)
   16. How does a CPU send a command to a device controller?
        > *Notification by device controller to CPU: "data ready” signal, aka “interrupt request” (IRQ)
   18. From textbook (page 7) A device controller maintains some " local buffer storage " and a set of special-purpose registers ". Where do these storage and registers reside? On CPU? in main memory? in cache? outside CPU?
       > outside CPU
       > ![](https://i.imgur.com/ZqSWlXH.png)

   20. What is a device driver ? hardware or software? part of the OS or in application program? What does it do?
       > Software
       > part of OS
       > in charge of a specific type of device a bridge between OS and devise controller

   22. What does IRQ stand for, and what is its purpose?
       > interrupt request
       > an signal sent to OS to request interupt
   24. How does a program for 8051 know when the UART has received a byte?
       > Testing RI flag, has two ways:
       > polling: Repeatedly checking RI until it is true
       > interupt: When the flag is set, automatically call a subroutine
       >  

   26. What does ISR stand for, and when is it invoked?
       > ISR: Interrupt Service Routine
       > It's invoked by receiving IQR.
   
   27. What is an interrupt vector ?
       > Interrupt vector: 對應的 ISR address
   
   28. What is an interrupt vector table ?
       > Interrupt vector table: a table store interrupt vectors, indexed by interrupt numbers.
   
   29. How does a processor decide which ISR to execute when there are multiple I/O devices?
       > determine by the priority of each IRQ
   
   30. How does a processor continue executing the user program after an ISR finishes?
       > CPU saves the address of interrupted routine before jumping to ISR
       > After finishing ISR, CPU will return to the interrupted routine by the address.
   
   31. What is a nested interrupt ?
       > while executing ISR, some architectures allow other high-priority interrrupt to come in.
   
   32. What is interrupt chaining ? (page 10 in textbook) Why is it useful?
   	    > element in the interrupt vector points to the head of a list of interrupt handlers
   	    > 不用cost overhead去搜尋整個interrupt table
   
   33. What is volatile memory vs. nonvolatile memory ? What are examples of each kind?
       > volatile memory: require power to maintain the stored data.
       > example: RAM, cache, register
       > 
       > nonvolatile memory: can save the stored data without power.
       > example: disk

   34. What is the purpose of a cache ? Can a processor run without a cache?
       > Purpose: reduce the time to read data from main memory, disk.
       > Yes, a processor can run without a cache.
   
   35. What is the priniciple of locality ? What are two kinds of locality ?
       > priniciple of locality: processor tend to access the same set of memory.
       > processor 存取記憶體的時候，傾向於存取較近的 memory.
       > temporal locality and spatial locality
       > 時間 locality / 空間 locality
   
   36. What does DMA stand for, and why is it used?
       > DMA: Direct Memory Access
       > Device controller transfers data from buffer direct to memory without CPU intervention.
       > frees up CPU from copying data between device & memory
   
   37. What are steps in a DMA setup, transfer, and completion?
       >  Device controller 在buffer storage 準備好 blocks of data
       >  直接傳入主記憶體
       >  傳送完成傳送訊號給CPU One interrupt is generated per block
   
   38. What is SRAM ? What is DRAM ? How many transistors per bit of storage is required for each technology? Which one is more complex to access for what reason?
       > SRAM: 只要通電就能一直保存 Data, 6 transistors per bit(for cache)
       > DRAM: 需要週期性充電才能保存 Data, 1 transistors per bit(for main memory)
       > DRAM is more complex because organized as row/column.
   
   39. In a uniprocessor, when the processor changes data in the **cache** , what should happen to the corresponding copy of data in main memory?

        > the corresponding copy of data in main memory is inconsistent with the data in cache.

   41. In a shared-memory multiprocessor system, when one processor changes data in a shared memory location, what should happen to the caches of other processors?

        > the other cached copies need to be "invalidated" (forces a cache miss, fetch from memory again)

   43. What is the **cache coherence** issue in a multiprocessor system?

         > change the copy in cache make it inconsistent with other copies

   45. On processors that support dual-mode operation ( **user mode** vs. **monitor mode** ), what are the two modes for?

         > user mode: execution done on behalf of a user (user code)
         > monitor mode: execution done on behalf of operating system

   47. What are alternative names for monitor mode?

         > a.k.a. **kernel** mode, **system** mode, **privileged** mode

   49. What are three ways to **switch** from user mode to kernel mode?

         > interrupt: triggered by hardware (timer, I/O, signal)
         > trap: executing a trap instruction (syscall instruction on MIPS)
         > fault: page fault, divide by zero, etc

   51. What are examples of **privileged instructions** ?

         > ex: direct I/O instruction, access special registers, instruction to return from interrupt

   53. How does the **syscall** instruction of the MIPS architecture indicate which system call to request? How does it pass arguments to the system call?
       >  將變數存入register \$v0 ->
       >  Then prepare register `$a0` as the argument to pass into SYSCALL ->
       >  Issue the syscall instruction using instruction `syscall` ->
       >  查看是否有回傳值
       >  
       >  load those values into registers
   55. is syscall a privileged instruction? why or why not?

         > **privileged instructions** can be executed **ONLY** in monitor mode, so **syscall** is not a **privileged instruction**.

   56. The **eret** instruction is used to return from a system call in MIPS architecture. Is it a privileged instruction? Why or why not?

         > **eret** can be executed **ONLY** in monitor mode, so **eret** is a **privileged instruction**.

   58. If the user code can **write to the interrupt vector table** , how can the user code gain access in privileged mode?
       >  stores a new address in the interrupt vector
       >  \---------------
       >  1. stores address of user code in interrupt vector table
       >  2. interrupt process
       >  3. Go to interrupt vector table
       >  4. Jump to the address stored in 1.
       >  5. Run the user code in privileged mode.
      
   60. How does **base+limit registers** scheme protect memory when there are multiple jobs running in the same memory space? What happens when the user code attempts to access a memory location without permission?

         > Base register: starting address of legal physical memory address
         > Limit register : size of the range
         > 利用此兩個 register 可檢查是否有戳到不該使用的 memory location
         > 
         > addressing error

   61. What is the mechanism for the OS to regain control when the user process hogs the CPU either intentionally or unintentionally (infinite loop without making system calls)?

        > **timer** can count number of blocks, will interrupt after a specified number of cycles

2. EdSim51 and 8051 - week 2 (9/18 lecture)
   1. What are the (direct) addresses of the 8051 general-purpose I/O (GPIO) ports P0 , P1 , P2 , and P3 ?
       > P0: 80H
       > P1: 90H
       > P2: A0H
       > P3: B0H
   3. What is the meaning of each of the following instructions in 8051?

      ```asm
      a. MOV A, #1    // *A = 1
      b. MOV A, 1     // *A = *(0x1), A = IDATA[1]
      c. MOV A, R1    // *A = *R1
      d. MOV A, @R1   // *A = *(*R1), A = IDATA[R1]
      e. MOV R1, A    // *R1 = *A
      f. MOV R1, #1   // *R1 = 1
      g. MOV R1, 34H  // *R1 = *(0x34), R1 = IDATA[0x34]
      h. MOV @R1, A   // *(*R1) = *A, IDATA[R1] = A
      i. MOV @R1, #1  // *(*R1) = 1, IDATA[R1] = 1
      j. MOV @R1, 34H // *(*R1) = *(0x34), IDATA[R1] = IDATA[34H]
      k. MOV 34H, A   // *(0x34) = *A, IDATA[34H] = A
      l. MOV 34H, #56H// *(0x34) = 56H, IDATA[34H] = 56H
      m. MOV 34H, 56H // *(0x34) = *(0x56), IDATA[34H] = IDATA[56H]
      n. MOV 34H, R1  // *(0x34) = *R1, IDATA[34H] = R1
      o. MOV 34H, @R1 // *(0x34) = *(*R1), IDATA[34H] = IDATA[R1]
      附註： register是地址
      ```
      
   3. Are the following allowed? If not, what assembly code does the intended operation, if any?
      ```
      a. MOV R1, R2
      b. MOV A, A
      c. MOV #20, R3
      ```
      > a. 
      > MOV A, R2
      > MOV R1, A
      > b.
      > MOV Reg, A
      > MOV A, Reg
      > c.
      > MOV A, #20
      > MOV A, R3

   4. What is a port latch ?
       >  port latch is a FlipFlop  that is Set or Cleared, to control and keep the Output state of each Pin
       >  控制output bit set 或是 clear
      
   6. What does it mean that 8051 GPIO ports are bit addressable ?
       > we can access the data by bit by bit

   8. What is the Intel assembly notation for "bit 3 of port P2 "?
       > P2.3
   10. What is the meaning of
      ```
      SETB P1.1 // set p1.1 bit to 1
      CLR P2.3 // set p2.3 bit to 0
      ```

    and why can't the same effect be achieved using a MOV instruction?
     > because MOV set the hole register
      
   8. If you want to set individual bits of a GPIO port without using SETB and CLR instructions, what instruction can you use? Hint: 8051 User's Guide , Table 3 on page 1-11, "Logical Instructions", find a combination of ANL , ORL , XRL instructions. What addressing modes should be used with these instructions? Use these instructions to implement the two bit set/clear instructions in the previous question.
       > set:
       > ANL A, #0 //將A變成0
       > ORL A, #03H // 將最右邊兩個bit設成1
       > ORL P1, A 
       > clear:
       > ORL A, #FF //將A變成1111 1111
       > XRL A, #3 //將A變成1111 1100
       > ANL P1, A
   10. What is a label in an assembly language program?
       > Symbolic names that mark addresses
   12. Given the sample program for setting P3<4:3>:
       ``` a
       Top: SETB P3.4
            SETB P3.3
            MOV P1, #24H
            CLR P3.3
            MOV P1, #24H
            CLR P3.4
            SETB P3.3
            MOV P1, #24H
            CLR P3.3
            MOV P1, #24H
            SJMP Top
       ```
       Rewrite it in C by filling in the blank ____ below:
       ```cpp
       int i;
       for (i = 0; i < 4; i++) {
           P3 = _____; // you may change = into &=, |=, etc
       }
       ```
       > (~i)&3 
       > ex: 
       > i = 0
       > ~(0000_0000) = 1111_1111 = -1
       > 1111_1111 & 0000_0011 = 0000_0011 = 3
   
   11. What does the following Intel 8051 assembly code do?
       Data1: DB "Hello world"
       a. Does it occupy any memory? In which space? (CODE? IDATA? XDATA?)
       b. What is the closest equivalent statement in C?
       c. Is the assembly version null-terminated? How do you find out?
       > a. Yes, occupy code memory
       > b. char Data1[]={"Hello world"}
       > c. No, it will be convert like this
       > DB 48h, 45h, ....44h for each charachter in ASCII
   12. Given the Intel 8051 assembly code:
       ```
       Data2: DB 25
       ```
       a. How many bytes does the 25 data occuply?
       b. What kind of address is Data2 ? In other words, what space (CODE, IDATA,XDATA, etc) and how many bytes?
       > a. 1 byte
       > b. #Data2 is address of code memory.
       > size of code memory 64KB -> need 16 bits (2 bytes)
       > code space and ???
       > 
   13. Given the Intel 8051 assembly code
       COUNT EQU 25
       a. How many bytes does the above line occupy in the assembled code, if any
       and in which memory?
       b. What is the equivalent statement in C?
       > a.
       > occupy no space
       > b.
       > #define COUNT 25
   14. If you want to display the digit "7" on the seven-segment LED with the additional vertical line on the upper left instead of just an upside-down L, what value do you write to P1 ?
       > 0xD8
       > 0xD8 = 1101 1000
       > ![](https://i.imgur.com/JOoPvcV.png)

   16. What is the advantage of using CLR A instruction over MOV A, #0 instruction, which does exactly the same thing (assign A = 0)? Hint: look up how these instructions are encoded.
       >  CLR operates slightly faster than MOV
       >  http://www.plctalk.net/qanda/showthread.php?t=107243


   18. What is the difference between A and ACC in 8051 assembly? Why do I have to say PUSH ACC and cannot say PUSH A ? (Similarly POP ACC but not POP A )?
       > A is **implied** address of Accumulator. 用來減少 code 長度
       > ACC is **direct** address of Accumulator.
       > PUSH / POP 必須要使用 direct mode.
   
   17. What is the effect of PUSH and POP on the stack? Explain in terms of the stack, i.e., SP and the memory location pointed by SP .
       > PUSH \<src\>: SP = SP+1, IDATA\[SP\] = data in address \<src\>
       > POP \<dest\>: data in address \<dest\> = IDATA\[SP\], SP = SP-1
   
   18. What does LCALL Display do (where Display is a code label)? Explain in terms of the program counter and the stack.
       > LCALL Display:
       > 1. push the next code address of "LCALL Display" on stack
       > 2. set PC to the code address of "Display"
       > 3. pop stack and set PC to the stored code address after finishing "Display".
   
   19. What does the RET instruction do? Does RET know if the subroutine was originally called by LCALL or ACALL instruction?
       > return from subroutine.
       > No
   
   20. What does the following instruction do:
       ``` a
       MOV DPTR, #LEDdata
       ```
       Assume LEDdata corresponds to address 0x2468, what is the new value of DPL and DPH ?
       > DPH: 0x24, DPL: 0x68
       > little endian
       > low address get 68
       > high address get 24
   
   21. What is the meaning of the instruction
       ```a
       MOVC A, @A+DPTR
       ```
       and how is it different from
       ```a
       MOV A, @Ri
       ```
       where Ri is either R0 or R1 ?
       > "MOVC A, @A+DPTR": A = CodeMemory\[ A + DPTR \]
       > "MOV A, @Ri": A = IDATA\[ Ri \]
       > MOVC get data from code memory, and MOV get data from IDATA memory.
   
   22. On a UART, what does RxD stand for? What is TxD ?
       > RxD: Recieve Data, TxD: Transmit Data
   
   23. How should the RxD and TxD signals of one system be connected to the RxD and TxD signals of another system that it communicated with?
       > RxD to TxD, TxD to RxD.
   
   24. On the 8051, what is the purpose of the SBUF special-function register? What happens when you move data to SBUF ? move data from SBUF ?
       > Reading/Writing register
       > move data to SBUF: send
       > move data from: receive
   
   25. How does a program know when there is valid data to be read from SBUF ?
       > Check "RI" signal is equal to 1 or not.
   
   26. Why is it necessary to clear RI bit after reading from SBUF ?
       > if not claer RI bit, we can't read the next data from SBUF
   
   27. What is the meaning of the code
       ```a
       Here: JNB RI, Here
       ```
       Rewrite this assembly code as a C statement.
       >```cpp
       > while( RI == 0 );
       >```
   28. What does 4800 baud mean for a UART?
       > baud: 傳輸速率的單位
       > 4800 baud: 每秒傳輸 4800 個字符
   29. On the 8051, what is the interrupt vector (i.e., address of the ISR) for Reset?
       > Reset: 0000H
   30. The interrupt vector for INT0 interrupt is at 03H, which leaves only 3 bytes for the interrupt vector for Reset. Why is 3 bytes sufficient?
       > 不知道啦，怎麼查都查不到
       > Interrupt vector contains the ISR address
       > The only thing to do is jump to the address
       > `LJMP Addr`
   31. The interrupt vector after 03H is 0BH, leaving only 8 bytes for the the INT0. Why is 8 bytes sufficient?

        > 8 bytes spaces are for **handler code** (if fit in 8 bytes), or jump to handler routine if too long

   33. When is the ```TI``` flag set to 1 by the UART?

        > when ready for next byte to transmit
        > 

   35. When the UART's ISR is invoked, is it caused by ```RI``` or ```TI``` becoming 1? Can it be both?

        > user must check whether TI or RI is on
        > one ISR for both Tx and Rx, so user is responsible for clearing the flag

   37. What is the purpose of the EA bit, which stands for "enable all (interrupts)"?

        > 設成0代表不能interrupt
        > 設成1代表可以interrupt

3. Short Assembly Programs

   1. Modify the Display subroutine so that it not only displays the digit but also switches to the next 7-segment LED. It just needs to a different digit at a time; does not need to keep all four.

      ```assembly
      Display: 	MOV DPTR, #LEDdata
      		MOVC A, @A+DPTR
      		;; your code to increment the LED ID,
      		;; which is defined by P3.3 and P3.4
      		MOV P1, A ;; light up the selected 7-segment LED
      		RET
      LEDdata: 	DB 0c0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H,80H,90H
      ```

      Test your code with polling version of UART (e.g., slide 12 of 02-EdSim51-IO.pdf). Remember to initialize UART and Timer as well as ```P3.3``` and ```P3.4``` . Try it out by typing digit characters into the Tx window and click send.
      
        ```
            ORG 0H
            MOV TMOD, #20H
            MOV TH1, #-6
            MOV SCON, #50H
            SETB TR1
        PollHere:
            JNB RI, PollHere
            MOV A, SBUF
            CLR RI
            ADD A, #-48
            LCALL Display
            JMP PollHere
        Display:
            MOV DPTR, #LEDdata
            MOVC A, @A+DPTR
            SETB P3.4
            SETB P3.3
            MOV P1, A
            CLR P3.3
            MOV P1, A
            CLR P3.4
            SETB P3.3
            MOV P1, A
            CLR P3.3
            MOV P1, A
            RET
        LEDdata:
            DB 0c0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H,80H,90H
            END
        ```
        
        
```
	ORG 0H
	MOV TMOD, #20H
	MOV TH1, #-6
	MOV SCON, #50H
	SETB TR1
PollHere1:
	JNB RI, PollHere1
	MOV A, SBUF
	CLR RI
	ADD A, #-48
	SETB P3.4
	SETB P3.3
	LCALL Display
	JMP PollHere2
PollHere2:
	JNB RI, PollHere2
	MOV A, SBUF
	CLR RI
	ADD A, #-48
	CLR P3.3
	LCALL Display
	JMP PollHere3
PollHere3:
	JNB RI, PollHere3
	MOV A, SBUF
	CLR RI
	ADD A, #-48
	CLR P3.4
	SETB P3.3
	LCALL Display
	JMP PollHere4
PollHere4:
	JNB RI, PollHere4
	MOV A, SBUF
	CLR RI
	ADD A, #-48
	CLR P3.3
	LCALL Display
	JMP PollHere1
Display:
	MOV DPTR, #LEDdata
	MOVC A, @A+DPTR
	MOV P1, A
	RET
LEDdata:
	DB 0c0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H,80H,90H
	END
```

   2. Convert your code to interrupt version, shown on slide, based on slide 26-27.


```
	ORG 0H
	JMP Main
	ORG 23H
	JMP Serial_ISR
Main:
	LCALL InitUart
	SETB ES
	SETB EA
PollHere1:
	JNB RI, PollHere1
	MOV A, SBUF
	CLR RI
	ADD A, #-48
	SETB P3.4
	SETB P3.3
	LCALL Display
	JMP PollHere2
PollHere2:
	JNB RI, PollHere2
	MOV A, SBUF
	CLR RI
	ADD A, #-48
	CLR P3.3
	LCALL Display
	JMP PollHere3
PollHere3:
	JNB RI, PollHere3
	MOV A, SBUF
	CLR RI
	ADD A, #-48
	CLR P3.4
	SETB P3.3
	LCALL Display
	JMP PollHere4
PollHere4:
	JNB RI, PollHere4
	MOV A, SBUF
	CLR RI
	ADD A, #-48
	CLR P3.3
	LCALL Display
	JMP PollHere1
Serial_ISR:
	JNB TI, Check_RI
	CLR TI
Check_RI:
	JNB RI, Serial_Done
	MOV A, SBUF
	CLR RI
	ADD A, #-48
	LCALL Display
Serial_Done:
	RETI
InitUart:
	MOV TMOD, #20H
	MOV TH1, #-6
	MOV SCON, #50H
	SETB TR1
Display:
	MOV DPTR, #LEDdata
	MOVC A, @A+DPTR
	MOV P1, A
	RET
LEDdata:
	DB 0c0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H,80H,90H
	END
```