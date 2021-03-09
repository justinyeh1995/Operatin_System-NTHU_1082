# OS Weekly Review 3


###### tags: `Operating System`

## part1

1. A shell can implement all of the commands that it supports, as opposed to relying on
   external programs that are not part of the shells. What are the advantages and disadvantages?
   > shell that implement all commands:
   > big shell
   > efficient per command
   > add commands need to modify the shell
   > 
   > shell that relying on external programs:
   > small shell
   > less efficience per command
   > add commands no need to modify shell
2. Does the unix-style shell (such as bash, csh, etc) implement all of the commands that it can execute or not? Why is it a good idea?
    > shell that relying on external programs:(待查證)
    > 
    > smaller shell
    > add commands no need to modify shell
4. Does the shell (GUI, CLI, etc) run in user mode or kernel mode? Why?
    > in user mode
    > 要和user溝通，不一定所有功能都需要kernel mode
6. What is the purpose of a system call?
    > 使用kernel mode的功能
8. Are the functions in standard-I/O library <stdio.h> all system calls? For example,
   is printf() a system call? If not, how does it perform I/O operation? What actual
   system call does printf() call?
   > 1. No, printf() contains system calls, but sprintf() doesn't.
   > 2. printf is API
   > 3. ![](https://i.imgur.com/HbRgLBm.png)
   > 4. printf() calls write() which is a system call


6. Do all system calls execute in kernel mode?
    > yes

7. How are the functions in the POSIX API related to system calls?
    > API is a more simple and efficient way 
    > than system call.
    > API may or may not use system call
8. Why would an application programmer prefer programming using an API than making system calls directly?
    > 1. Simplicity 方便好寫
    > 2. Portability 可移植
    > 3. Efficiency 跑比較快

9. Do all <stdio.h> functions make one or more system calls in their implementation? Why or why not?
    > No, sprintf doesn't make any system call.
    > some API designed for convenience / formatting.

10. Does MS-DOS create a new process to run a user program? What happens to the shell when the user program is running and when it exits?
    > 1. No
    > 2. shell is closed/reloaded when the user program is running / exits. 

11. At what point does FreeBSD start the shell? Is there just one kind of shell?
    > Shell waits for process to terminate or continues with user commands.
    > No, FreeBSD has many kind of shell (ex: bash, tcsh ) 
 
12. How does a shell on FreeBSD start a process? What does the shell do when the
    process is executing?
    > 1. use **fork()** to create a process
    > 2. just wait for process ending or continues with user commands.

13. What are the purpose of system programs?
    > 1. Convenient for program development and execution
    > 2. Defines most users’ view of OS 

14. What is the difference between policy and mechanism?
    > policy: What will be done? What is allowed? ( 要完成的目標 )
    > mechanism: How to do it? ( 實作方法 )

15. MS-DOS has a simple structure consisting of BIOS and DOS device drivers, resident
    system program, and application program. What are the advantages and
    disadvantages with this minimal structure?
    > advantages: use the least memory
    > disadvantages: unsave, difficult to enhance

16. Do system programs in Unix including shells, compilers, and interpreters run in
    kernel mode or user mode?
    > user mode
    > ![](https://i.imgur.com/FEjhFac.png)


17. Is traditional Unix a two-layer or N-layer structure? What are its pros and cons?
    > traditional Unix is a two-layer structure.
    > pros: very efficient 
    > cons: difficult to implement and extend
    > (課本82頁最後一段)

18. In an N-layered OS structure, what layer is hardware? user interface? What is the
    dependency between a lower and an upper layer?
    > layer 0 = hardware ( bottom layer ), layer N-1 = user interface ( top layer )
    > Lower layers independent of upper layers
    > But Higher layer use services only of lower layers

19. What are the advantages of layers approach? What is a successful example use?
    What are the disadvantages compared to the 2-layer, tightly coupled structure?
    > easier debugging and maintenance
    > successful example: TCP/IP protocol stack
    > less efficient, difficult to define layers

20. What is the key idea with microkernel compared to monolithic kernel?

    > monolithic: two layers (users mode vs. kernel mode)
    > microkernel: move as much from the kernel into user space

22. Which of the following functions of a microkernel is done in kernel mode? in user mode?
    a. network driver
    b. device driver
    c. graphic driver
    d. interprocess communication
    e. CPU scheduling
    f. memory management
    g. file system
    h. application program
    
    > in kernel mode: d, e, f
    > in user mode:a,b ,c , g, h
    > 
    
22. How can a microkernel mode run an OS service in user mode while also protecting the rest of the system?

    > 因為 interprocess communication
24. Which of the following is easier or more efficient to do on a microkernel or a monolithic kernel? Why?
    a. port to a new architecture
    b. add new features
    c. OS overhead
    
    > a: microkernel ( microkernel 把本來在kernel中的部分功能模塊化當作 user 使之在 user mode 執行，因此較容易新增新架構)
    > b: microkernel (同上)
    > c: monolithic kernel (microkernel need more message passing for user-to-kernel communication)
    
24. What are the two main models for interprocess communication?

    > message-passing vs. shared-memory

26. How does a modular OS divide its functionality? What are the advantages of this organization?

    > 將除了 core components 之外的功能進行模塊化 (???不確定???)
    > CYC: divide by policy.?
    > lower overhead, more flexible

28. what are loadable kernel modules (LKM)? Do they run in the same address space as the kernel or different?

    > LKM 是將原本 kernal mode 中的功能模塊化後的模塊，loaded as needed, can be unloaded
    > same address space as the kernel

30. How would you characterize Linux and solaris? monolithic or microkernel? combined LKM or hardcoded services in kernel?

    > Linux and Solaris: monolithic + modular

32. Is Darwin a monolithic or microkernel? What are the advantages of kexts in this context?

    > microkernel
    > 
    > https://www.apriorit.com/dev-blog/430-macos-kext-development
    > A kernel extension (kext) is a special application bundle that extends the functionality of the macOS kernel.
    > A kext is the minimum unit of executable code that can be loaded and used in the kernel.
    > kext 的概念類似於 modular , 好處：lower overhead, more flexible

34. What is the purpose of the BSD Unix subsystem in Darwin?

    > CLI, file system, networking

36. Why does Android replace glibc with Bionic?

    > smaller than glibc for mobile

38. Since Android uses Linux kernel, does it mean it can also run executable programs for desktop and laptop Linux? Why or why not?

    > No, because Android use Java API while Linux use POSIX API

40. What is a core dump file? How is it different from a log file?

    >core dump file: captures memory of the process
    >log file: error information

42. What is a crash dump and how is it different from a core dump?

    >crash dump file: containing **kernel** memory
    >core dump file: captures memory of the **process**

## part 2

1. What is the interrupt vector (address of ISR) of UART on 8051?
    > 0023H
3. To use UART interrupt on the 8051, why is it it necessary to lay out the code memory this way:
   ```
   ORG 0H
   JMP Main
   ORG 23H
   JMP Serial_ISR
   Main: ...
   Serial_ISR: ...
   ```
   > (不確定)
   > on startup, jump to main()
   > 之後再跳到interupt
   > 
   > Because when UART interrupt occur, PC will jump to 0023H and execute  code until meet reti.
   > if not lay out like this way, you need to do every thing by at most 8 byte code memory.
   > Otherwise, the ISR may influence the other ISR.
   > ![](https://i.imgur.com/ZUKgGp7.png)

3. The UART uses Timer-1 to generate its timing. What do the following bit registers do?
   a. TR1
   b. ET1
   c. TF1 
   > TR1: start timer 1
   > ET1: interrupt enabled
   > TF1: ET1 的flag

4. What is SDCC?
    > Small Device C Compiler

5. What is the size (in terms of bits or bytes) of the following types in SDCC? and are
   they signed or unsigned?
   a. bit
   b. char
   c. byte
   d. int
   e. long
   f. float
   > a. 1 bit, unsigned
   > b. 1 byte, signed
   > c. 工三小....
   > d. 2 bytes, signed
   > e. 4 bytes, signed
   > f. 4 bytes, signed

6. What does SDCC do if you invoke it with the following arguments?
   a. sdcc file.c
   b. sdcc -S file.c
   c. sdcc -c file.c
   d. sdcc file.rel -o file.ihx
   > a. 完整compile和link和assemble
   > b. compile to assembly
   > c. compile and assemble but don't link
   > d. link後輸出輸出file.ihx

7. Why does main in .c file get translated into _main in the .asm file?
	> because The compiler inserts another _ in front when generating assembly code(待查證)

8. The .asm output from SDCC is different from Intel assembly syntax and therefore
   cannot be loaded directly into EdSim51 and run. So what file generated by SDCC (or
   related tools) in order to run on EdSim51?
    > sdcc	-c	file.c	
    > sdcc	-o	file.hex file.rel
    > then file.hex can run on EdSim51.
    >   
	> 或是 packihx main.ihx > main.hex 一勞永逸


9. In SDCC's <8051.h> header file, how is the GPIO port P1 declared so that it refers
   to special-function register at memory address 90H?
    > ```cpp
    > __sfr __at (0x90) P1;
    > ```

10. Why does SDCC require that you declare an ISR with the __interrupt keyword
    and a number such as (4) as in
    ```cpp
    void Serial_ISR(void) __interrupt(4) {
    ...
    }
    ```
    > 1. __interrupt: to tell compiler it's an interrupt. 
    > 2. $(4)$ is the interrupt number of serial port.

11. Why do we NOT recommend calling a function such as DisplayLED(char num)
    from within the ISR?
    > + should minimize amount of work spent in ISR
    > + ISR should do just enough transfer, leave longer task to be done in user code
    > 簡而言之，ISR runs in kernel mode, 直接在 kernel mode 做事，有可能會把電腦玩爛。

12. By observing SDCC's assembly output for the ISR that calls a function (slides 24 and
    26), what is the purpose of all the push (bits, acc, b, dpl, dph, 0+7, 0+6, … psw)
    instructions and all the corresponding pop instructions before the reti instruction?
    > Push: save the data may be modify by ISR.
    > Pop: reload the saved data from stack before return from interrupt.
    > 目的: 做完 ISR 回到 user code 時，不會影響到原本的data。

13. What is the purpose of calling main() in the function definition
    void _sdcc_gsinit_startup(void) { main(); }
    
    > 因為在 output 的 .ihx file 中的第一行是："__interrupt_vect: ljmp _sdcc_gsinit_startup"
    
14. What happens if you don't define the following routines to empty when compiling and
    linking with SDCC?
    ```c
    void _mcs51_genRAMCLEAR(void) {}
    void _mcs51_genXINIT(void) {}
    void _mcs51_genXRAMCLEAR(void) {}
    ```
    
    > 會引進library造成assembly code多了很多我們不想看到的東西
    > 這三個function是一個正常的c程式執行前會執行的，當我們把它覆蓋掉並設成空的function他就不會執行。
    > 原本的功能是為了清空記憶體好讓程式執行，但是在我們的模擬器上並沒有這樣子的問題
    
15. What clock frequency should be used when running the UART at 4800 baud?

    > 11.0592 MHz

17. How do you define a lookup table in SDCC to put data into CODE memory for mapping digits (0-9) to the LED segment to light up?

    > ```
    > LEDdata: DB 0C0H, 0F9H, 0A4H, 0B0H, 99H, 92H, 82H, 0F8H, 80H, 90H
    >          END
    > ```

19. On slide 21, the _sdcc_gsinit_startup() function contains inlined assembly code
    ```c
    __asm
    mov sp, #0x57
    
    __endasm;
    ```
    Can it be rewritten as C? How?
    
    > SP = 0x57;

## part 3

1. Try running the C program on slide 11. Make sure it compiles using the command on slide 15 and load the .ihx file into EdSim51 ("Load" button)
    > step1: 將main改成Main
    > step2: 下指令sdcc -c test0.c
    > step3: 下指令sdcc test0.rel
    > 解釋：這是其中一種方法，不然就要用寫四個函數的那個咚咚
    > 這是利用分開編譯，所以就不會被檢查到沒有main函數

2. Try running the two-file example (LEDtest0.c, LEDseg.c) shown on slide 16, compile and link with the commands on the slide, and load into EdSim51 to run.
    > step1: 將main改成Main
    > step2: 下指令sdcc -c LEDtest0.c
    > step3: 下指令sdcc -c LED7seg.c
    > step3: 下指令sdcc -o LEDtest0.ihx LEDtest0.rel LED7seg.rel
    > 解釋：順序一定要對，因為要決定哪個函數要先被執行，
    > 就連最後一個指令的檔案順序也要對

3. Try running the Serial Echo example on slide 18
    > step1: 複製講義上的code
    > step2: 下指令sdcc -c uartecho.c
    > step3: 下指令sdcc -o uartecho.hex uartecho.rel
    > 解釋： 改hex就成功了幹他娘
    > 

4. Try running the Polling UART example on slide 19
    > step1: 複製講義上的code
    > step2: 下指令sdcc -c polluart.c
    > step3: 下指令sdcc -o polluart.hex polluart.rel LED7seg.rel
    > 解釋： 改hex就成功了幹他娘

5. Try running the intrLED.c example on slide 20. What is the difference between the use of Main() in previous examples and main() in this example?
    > 如果用main的話就需要打
    ```cpp
    void _sdcc_gsinit_startup(void) {
        __asm
        mov sp, #0x57
        __endasm;
        main();
    }
    void _mcs51_genRAMCLEAR(void) {}
    void _mcs51_genXINIT(void) {}
    void _mcs51_genXRAMCLEAR(void){}
    ```
    > 這幾段code來調整，不然的話會引入很多library的怪東西，用Main的話就沒這個問題
