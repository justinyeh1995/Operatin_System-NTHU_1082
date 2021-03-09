# OS Weekly Review 1
###### tags: `Operating System`

1. Definitions and Short Answers - week 1 (9/9 lectures)

   1. What is **batch processing** ? What are its advantages? Disadvantages?
       > 批次處理程式。 Advantage: 多使用者共用一台機器、可以指定執行時間。 Disadvantage: CPU 經常閒置(因I/O較慢)、一次一件工作、程式之間沒有交流。
   2. What is **multiprogramming** ? What disadvantage of batch processing does it address?
       > 一次處理多件工作。程式A 處理 I/O 時，用 CPU 去跑別的程式B，解決了batch processing 的 CPU 閒置問題。
   3. Compare **multiprogramming** and **multitasking** in terms of number of users, number of jobs running, and need for support features.

      > |                  | **multiprogramming**             | multitasking                                     |
      > | ---------------- | -------------------------------- | ------------------------------------------------ |
      > | number of users  | multiple users                   | multiple users                                   |
      > | number of jobs   | multiple jobs                    | multiple jobs                                    |
      > | support features | CPU scheduling<br>I/O system<br>memory management | file system<br>virtual memory<br>synchronization |synchronization|
   4. What is an **instruction set architecture** (ISA)? How is it different from a CPU or a processor?
       > opcode, operand, register, addressing modes, assembly language, machine code,
       > 
       > ISA: 用來控制 CPU 的基本指令。根據 CPU 的設計適用不同的ISA。
   5. What are reasons for the trend from single processor to multiprocessor architectures?
       > 增加 Thoughput
       > Energy efficiency: same performance but much lower power!
   6. What makes tightly coupled multiprocessors difficult to **scale** to a large number of processors?
         > 因為太多CPU在同一個裝置，會造成太大的耗能，就算採用NUMA形式能解決耗能過大的問題，但是NUMA的access memory time會變長，所以 difficult to scale to a large number of processors
   7. What are examples of **real-time** systems? How do they differ from **high-performance** systems?
         > multimedia system, industrial control, flight or auto control, anti-lock brake
      >
      > 不見得會很快，但是一定會在時限內完成工作 
   8. What are examples of **hard real-time** vs **soft real-time** systems?
         > **soft real-time**: multimedia streaming
      >
      >  **hard real-time**: nuclear power plant controller

2. EdSim51 and 8051 - week 1 (9/11 lecture)

   1. What is an assembler?

        > 將 **assembly code** 組譯成 **object code**.

   2. Given the sample assembly program:

      ```
      ORG 0000H
      MOV 90H, #24H
      END
      ```

      a. What is a **directive** in this assembly program, and how is it different from an instruction?
      
      > ```ORG``` and ```END``` are **directive**, 跟 **instruction** 不同的是, **directive**並不會被組譯成 object program.
      
      b. What is an **instruction** ? What does the assembler do to an instruction?
      
      > ```MOV 90H, #24H``` is an **instruction**, **assembler** 會將 **instruction** 組譯成 object code.
      
      c. What is an **opcode** in the above example? An **operand** ?
      
      > ```MOV``` is an **opcode** in the above example.
      > ```90H``` and ```#24H``` are **operand**.

   3. What does ```90H``` refer to? What does ```#24H``` refer to? Why is there a # in front of 24H but not in front of ```90H``` ?

        > ```90H``` 代表 IDATA address 為 90(hex).
        > ```#24H``` 代表 constant value 為 24(hex).
        > ```#24H``` 前面有 # 的符號，代表的是純數值(constant value)。

   4. What is a **NOP** ? and how do you pronounce it?

        > means "do nothing", pronounce "no operation".

   5. Why is 8051 called a **Harvard architecture** ? How is it different from a **von Neumann** architecture?

        > **Harvard architecture** 是一種將 instruction 跟 data **分開**儲存的計算機結構，因此 8051 是一種 **Harvard architecture**。
        > **von Neumann architecture** 是一種將 instruction 跟 data **合併**儲存的計算機結構。

   6. What is a **PC** in a processor? What are the ways PC value can change?

        > **PC(program counter)** 指出 CPU 正在執行 program 的哪一個部分。
        > PC 在 processor 抓取 instruction 後會增加，也可以使用 **control transfer instruction** 給予 PC 新的 value 。

   7. How many bytes is 8051’s **code memory** ? How many bits are needed to represent the code address?

        > 64KB.
        > 16bits.

   8. What is **DPTR** in 8051? How is it related to **DPL** and **DPH** ?

        > **DPTR(Data Pointer)**，是 16 bits 的 register ，作為存取 data 的 pointer 使用。
        > DPTR可一分為二，作為兩個 8 bits 的一般 register 使用，分別為 **DPL** 和 **DPH**。

   9. How big is the IDATA memory in 8051?
       > 256 Bytes

   10. What is a special-function register (SFR)?
        > Can not be directly writable by normal instructions.
         >
            > Can be accessed by its name or by its address.
         >
            > Tied to some special function or status of the processor

   11. What is the meaning of **simplex** , **half-duplex** , and **full-duplex** communication? Which one is the UART (serial port)?
        > **simplex** : A simplex communication channel only sends information in one direction.
          >
             > **half-duplex** : data can be transmitted in both directions on a signal carrier except not at the same time
          >
             > **full-duplex** :  able to transmit data in both directions on a signal carrier at the same time
             >
             > full-duplex is UART(通用非同步收發傳輸器（Universal Asynchronous Receiver/Transmitter)

   12. if ```#24H``` refers to hex 24 integer value (“immediate”) in Intel assembly, why ```#FFH``` does not refer to hex FF integer value? Name two ways to express 0xFF in Intel assembly syntax.
            
        > because first integer is F(since F is not in 0..9) therefore is not an immediate 
         >
         > use #0FFH

   13. What is the meaning of `MOV A, 17` in 8051 assembly, and how is it different from ```MOV A, #17``` ? What about `MOV A, 17H` ? ```MOV A, #17H``` ?

         > ```MOV A, 17```: direct mode at decimal 17 (instead of hex)
         >
         > ```MOV A, #17```: immediate mode which present in decimal
         >
         > ```MOV A, 17H```: direct mode (IDATA address 0x17)
         >
         > ```MOV A, #17H```: immediate mode which present in Hex

   14. What is a **general-purpose input/output** (GPIO) port? What are they called on 8051?
       > 通用型之輸入輸出的簡稱
       > 功能類似8051的P0—P3

   15. Why do you have to write a **0 bit** to **turn on** an LED segment? Why write a **1 bit** to **turn off** ?
       > 0的話會接地通電，製造大電位差，所以0是turn on

   16. What is an “immediate” operand?
       > example: MOV A #17H
       > 上方的 #17H 就是 immediate operand.
   17. What is a "direct" operand?
       > example: MOV A 17H
       > 代表 A = data in address 0x17 in IDATA
       > 上方的 17H 就是 "direct" operand
   18. How do you pronounce “UART”? What is another more descriptive term for UART?
       > UART = Universal Asynchronous Receiver/Transmitter
       > 通用非同步收發傳輸器

