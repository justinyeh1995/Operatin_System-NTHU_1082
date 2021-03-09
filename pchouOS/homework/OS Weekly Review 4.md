# OS Weekly Review 4


###### tags: `Operating System`

# part 1

1. What is the difference between a program and a process? Which one is active and which one is passive?

    > program: passive, executable code 
    > process: active, an instance of a program in execution

2. What is a job?

    > synonym with "process" , but "process" is preferred

3. What is a task?

    > informal word for process ("multitasking")
    > from real-time systems, maybe lighter weight than process

4. What is the text section of a process's memory?

    > code

5. What is the difference between the data section and heap section of a process's memory?

    > data section: global variables
    > heap section: dynamic allocated variables or classes

6. What is kept in the stack section of a process's memory?

    > temporary data (e.g. function parameters, return addresses, local variables for function)

7. Besides the content of the main memory in a process's address space, what other state does a process have (that is maintained by the OS)?

    > program state: (program counter, registers)

8. What are the five states of a process (in the textbook's terminology)?

    > new, ready, running, waiting, terminated

9. On a single processor, how many processes can be in running state at a time? in ready state? in waiting state?

    > **one process** can be in **running state** at a time
    > **several processes**  can be in **ready state** or **waiting state** at a time

10. Why would a process enter waiting state?

    > the process is waiting for some event ("blocked"), could be I/O

11. From which three states may a process transition to ready state?

    > new, running, waiting

12. How can a process transition from running to ready state without doing any system call?

    > interrupt

13. In the process control block (PCB), what is the meaning of the following fields?
    a. program counter
    b. process number
    c. CPU registers
    d. memory management information
    e. accounting information
    f. I/O status information

    > a. 就是計結的 program counter
    > b. 每個 process 有獨一無二的 ID
    > c. 就是 CPU registers
    > d. memory allocated to the process
    > e. CPU used, clock time elapsed since start, time limits
    > f. I/O devices allocated to process, list of open files

14. What is a thread of execution?

    > lightweight process, a basic unit of program execution

15. On a single(-core) processor,
    a. how many processes can be running at a time?
    b. how many threads can be running at a time?

    > one
    > multiple (multiple threads may belong to one process) (不確定)

16. On a multiprocessor system,
    a. how many processes can be running at a time?
    b. how many threads can be running at a time?

    > multiple
    > multiple

17. What is the definition of the degree of multiprogramming? Does it reflect
    a. the number of processors in the system?
    b. the number of processes currently running, waiting, ready?
    c. the number of threads currently running, waiting, ready?
    d. the amount of main memory in the system?
    e. the scheduling policy?

    > number of processes kept in memory
    > 系統內存在執行的 process 數目
    > 
    > (這邊不確定QQ)
    > a. X
    > b. O
    > c. X
    > d. X
    > e. X

18. What is the difference between an I/O-bound and a CPU-bound process?

    > I/O-bound: spends more time doing I/O than computation => many short CPU bursts
    > CPU-bound: spends more time doing computation than I/O => few but long CPU bursts

19. What doe context switching mean?

    > Switch to a different process to run
    > 
    > - Kernel saves the state of currently running process
    > - Kernel restores the saved state of the target process

20. What are the possible triggers for context switch?

    > interrupt or system call

21. What are the steps taken by the kernel to switch from process P1 to process P2?

    > 1. Kernel saves the state of currently running process
    > 2. Kernel restores the saved state of the target process

22. What kinds of support can hardware provide to help reduce the overhead of context switching?

    > depending on memory speed, #registers => 加快 memory speed, 加多 #registers

23. What is a pid?

    > each process has a unique identifier (pid)

24. In Unix-like system, how is fork() used for creating a new process?

    > fork() : parent clones itself
    > 
    > - child process duplicates address space of the parent (i.e., a copy)
    > - child and parent execute concurrently after fork

25. After fork() creates the child process, where in the program does the child process start running?

    > child runs the same program image as parent

26. What is the meaning of the return value of fork()?
	> 0 for child process
	> pid of child for parent process

27. What does exec() do? Does it create a new process? Does exec() return?
	> replaces process itself with specified program
	> If successful, exec() does not return
	> But if error, returns -1 with error code in a global variable `errno`

28. How does a shell launch a program as a new process using fork() and exec()?
	> calls `fork()` -> Child process calls `exec()` -> Parent either continue running shell or `wait()` for child to finish

29. What is copy-on-write? How does it improve the efficiency of the original implementation of fork()?
	> no need to store extra copy of same data
	> 

30. How many processes are created by the following example? Explain

    ```c
    #include <stdio.h>
    #include <unistd.h>
    int main() {
	    for (int i=0; i<3; i++) {
		    fork();
	    }
	    return 0;
    }
    ```
    > ~~6個(應該吧？)~~
    > 8個啦
    > init: 1
    > i = 0: 1->2
    > i = 1: 2->4
    > i = 2: 4->8
    > 執行結果: 1 parent, 7 child
    > ![](https://i.imgur.com/eNR4H1Q.png)

31. How does a process terminate voluntarily?
	> process call `exit()`

32. What are three reasons a child process may be terminated?
	> `exit()`, `kill()`, OS clean up

33. What does cascaded termination mean?
	> parent die, kill all children (recursive)

34. What is an orphan process? a zombie process?
	> orphan process: parent die, child alive
	> zombie process: child die, parent alive

35. What happens if the parent of a zombie process does not call wait()?
	> the zombie pid will not be released

36. What happens on termination of the orphan processes whose parent died before it had a chance to call wait() on its children? What is a solution?
	> the process will not be cleaned up
	> ancestor call `wait()`
    
37. What is the name of the "root" process in traditional Unix, with a pid of 1? What is the Linux version called?
	> `init` (traditional Unix) or `systemd` (Linux)
    
38. What is the main advantage of shared memory communication over message passing and why? What must be performed carefully for shared memory to work consistently?
	> shared memory communication: 速度快，但是要做資料同步
	>  message passing: 容易維護
	>  

39. What are some ways to ensure shared data are not written simultaneously in inconsistent ways?
	> by locking or scheduling

40. When is shared memory not an option for two processes to communicate?
	> need to across machine

41. What does it mean that message passing calls such as send() or receive() may block?
	> 在blocking send的情況下，在兩邊都準備好之前是block的狀態
	>
	> 在nonblocking & Bounded buffer:
	> sender is blocked if buffer is full
	> receiver blocked if buffer is empty
	> 
	> 在nonblocking & unBounded buffer:
	> receiver blocks only if buffer empty


42. In the pseudocode for shared memory communication, what are the purposes of
    variables named in and out? Which variable is modified by consumer and which is
    modified by producer? Can both the sender and receiver be modifying the same
    variable at the same time, assuming they can run at the same time?
	> in/out: buffer 的位置
	> consumer: out
	> producer: in
	> NO

43. What is "direct communication" (style of message passing) between two processes?
    How many processes can a link be associated with? How many links can exist
    between a given pair of processes?
	> Processes must name each other explicitly
	> One link is associated with exactly two processes
	> one

44. In direct communication, how is receive() in asymmetric naming different from
    receive() in symmetric naming? Can more than one sender process can send
    messages to a given receiver process? If so, can the receiver know the identity of the sender and how?
	> symmetric: sender and receiver name each other(ex p2p)
	> asymmetric: sender names the target process to send to(ex: server), receiver receives from ANY process and gets sender ID
	> 
    
45. Why does direct communication have the limited modularity problem? How is it
    solved by indirect communication?
	>  Limited modularity: if name of a process changed, all old names need to be updated
	>  
	>  mailbox handle(不確定)

46. Does indirect communication allow one sender and multiple receivers to share the same mailbox?
	> Yes.
	> Below is OS dependent:
	> 1. Allow a link to be associated with at most N processes 
    > 2. Allow only one process at a time to execute a receive() operation

47. Is a synchronous call blocking or nonblocking? What about an asynchronous call?
	> Blocking (“synchronous”)
	> Nonblocking (“asynchronous”)

48. How does a nonblocking sender/receiver know when the communication is
    completed (i.e., data has been sent or data is ready to be received)?
	> a separate call to check if done (like polling)

49. What is rendezvous communication? Are its sender and receiver blocking and
    nonblocking? How much buffer is required, if any? How do you pronounce
    "rendezvous"?
	> blocking send, blocking receive (rendezvous)
	> zero buffer
	> 我都念rendezvous，但是老師都念rendezvous，我上網去查結果使念rendezvous

50. in bounded buffer communication, under what buffer condition does the sender
    block and does the receiver block?
	> sender is blocked if buffer is full
	> receiver blocked if buffer is empty

51. in infinite buffer communication, under what buffer condition does the sender block and does the receiver block?
	> receiver blocks only if buffer empty
	> sender never block
    
52. what does RPC mean?
    > Remote Procedure Calls
    > Allows a program to call procedures on another machine.

53. what is a **stub** function for an RPC on the **client** side, and what does it have to do?
    > “marshaling”: packs parameters into a message
    > calls OS to send directly to server (network)
    > waits for result to return from server (network)

54. What is a **stub** function on the **server** side, and what does it have to do?
    > receives call from a client, “de-marshaling”: unpacks param
    > calls the corresponding procedure
    > returns results to the caller (network)

55. What do **`marshaling`** and **`demarshaling`** mean during an RPC call? Why can't raw data be sent in their original binary representation? What are example types that cause problems?
    > marshaling: packs parameters into a message
    > de-marshaling: unpacks param
    > Data representation issue:
    > There may be different data representation on different machine.
    > ex: 32-bit data is integer or float number?

56. Why pointers cause problems when passed as parameters or returned in RPC?
    > Address Space issue.
    > Different machine may have different address space.
    > ex: 16-bit pointer on machine A but 32-bit pointer on machine B

57. Can RPC always succeed? What kind of problems can happen?
    > No.
    > Communication issue may happen.
    > The problem in network cause some massages not to be sent/received correctly.
# part 2

1. Write a generator for powers of 2:
    ```python
    def gen_powers_of_2():
    ```
   such that if you test it interactively,
   ```python=
   >>> g = gen_powers_of_2()
   >>> next(g)
   >>> 2
   >>> next(g)
   >>> 4
   >>> next(g)
   >>> 8
   >>> [next(g) for i in range(5)]
   >>> [16, 32, 64, 128, 256]
   ```
   >```python=
   >def gen_powers_of_2():
   >    x = 2
   >    while(True):
   >        yield x
   >        x = x*2
   >```
2. Write a generator for elements of a binary tree in post-order (i.e., left child recursively, right child recursively, root). Assume the same kind of tree representation as on slide 11:
   T = (17, (12, (6, None, None), (14, None, None)), (35, (32, None, None), (40, None, None))) for the tree ![](https://i.imgur.com/eFLvCm9.png)
    >```python=
    >def postorder(T):
    >    if not T:
    >        return
    >    yield from postorder(T[1])
    >    yield from postorder(T[2])
    >    yield T[0]
    >```

3. Rewrite the `make_item()` generator on slide 21 to eliminate the for c loop. Hint: slide 13.
    >```python=
    >def make_item():
    >    import string
    >    while True:
    >        yield from string.ascii_uppercase+'\n'
    >```

4. The **consumer()** on slide 22 is a "pull"-style communication because the consumer asks for the next item (implicitly called by the for loop) from the generator, which does a yield of the next value.
   Rewrite the **producer()** as a function and **consumer()** as a generator such that the producer "pushes" the items by calling the **send(v)** method (slide 23) to send value v to the consumer, which receives the value from `yield` (as an expression) and calls the **use_item()** function on each value. In this case, `yield` just serves the purpose of "receive".

   ```python=
    def producer():
        import string
    # basically the same as make_item() on slide 21, except 
    # 1. instantiate revised consumer as a generator g, and
        g = consumer()
    # 2. call next() on g once to kickstart it
        next(g)
    # 3. inside loop, yield c is replaced by a g.send(v)
        while True:
            for c in string.ascii_uppercase:
                g.send(c)
    def consumer():
    # 1. inifinite loop,
        while True:
    # 1.1  c = yield, to receive the value sent by producer,
            c = yield
    # 1.2  call use_item(c), found on slide 27
            use_item()
    if __name__ = "__main__":
        producer()
    ```

  



# Sockets programming in Python
Make a minimal web server at port 8086 in Python by displaying the browser's HTTP request header received and then reply with the HTTP reply header and a minimal page in HTML.
Use the template shown on slide 34 and print the request; however, since the request is in bytes type instead of `str` type, To convert to `str` for printing, you can call the ``.decode( 'utf8' )`` method on the bytes data. The HTTP response should look like this:

```html=
HTTP/1.1 200 OK
Date: <!--fill in your own date time, like unix date command-->
Server: Python <!--or call it anything you like-->
Last-Modified: <!--fill in your own date time-->
Content-Length: <!--length of content-->
Content-Type: text/html
Connection: Closed

<html>
<body>
<h1>Hello world</h1>
</body>
</html>
```

Start your web server from the command line
`$ python3 webserv.py`
Open your own browser to localhost:8086, and it should render the HTML as a web page.

```python=
import socket
import time

host = socket.gethostbyname('localhost')
port = 8086

s = socket.socket()
s.bind((host,port))
s.listen(5)

while True:
    c, client = s.accept()
    req = c.recv(1024).decode('utf-8')
    print("from: ",client)
    print("HTTP request:" )
    print(req)
    reply = "HTTP/1.1 200 OK\n"
    reply += "Date: " + time.asctime(time.localtime()) + "\n"
    reply += "Server: Python\n"
    reply += "Last-Modified: " + time.asctime(time.localtime()) + "\n"
    reply += "Content-Length: chunk\n"
    reply += "Content-Type: text/html\n"
    reply += "Connection: Closed\n"
    reply += "\n"
    reply += "<html>\n"
    reply += "<body>\n"
    reply += "<h1>Hello, World</h1>\n"
    reply += "</body>\n"
    reply += "</html>\n"
    print("My HTTP Response:\n%s" %(reply) )
    c.send(bytes(reply, 'utf-8'))
    c.close()

```