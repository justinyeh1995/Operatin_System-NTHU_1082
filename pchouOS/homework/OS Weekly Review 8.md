# OS Weekly Review 8



###### tags: `Operating System`


## Definitions and Short Answers
1. In the version of producer-consumer code that uses both in/out and count, race conditions could occur.


```cpp
// Producer
while (1) {
	nextItem = getItem();
	while (count==BUFSIZE) ;
	buffer[in] = nextItem;
	in = (in+1) % BUFSIZE;
	count++;
}
// Consumer
while (1) {
	while(count==0) ;
	item = buffer[out];
	out = (out+1) % BUFSIZE;
	count--;
}
```


a. Give one example where one process's update is lost due to overwriting by the other process, assuming preemptive scheduling.
> count++前，被另一個process幹走了，final result depends on which process finishes last

b. Explain how the race condition causes incorrect results.
> final result depends on which process finishes last

c. Where can you convert into critical sections to eliminate the race condition?
> count++, count--


2. What are the three requirements of a critical section?
	> mutual exclusion: 一次只允許一個process access 
	> bounded waiting: 時間到就滾
	> progress: 有空可以馬上進
4. Of the two software solutions to the critical section problem, why do they work, and what are their assumptions?
	a. nonpreemptive scheduling
	>  nonpreemptive沒有這個問題
	>  
	b. preemptive scheduling - using Peterson's Solution
	> 用while 迴圈busy wait(只有兩個process時)
4. If you perform nonpreemptive scheduling, can there be race condition? On a single-threaded uniprocessor? On a multiprocessor? Why or why not?
	>nonpreemptive優該都不會有問題吧？(不確定)
	>\----
	> "優該" 是三小
6. Consider Peterson' solution,
	a. Does it need to temporarily disable interrupts in
	> 不用，他很厲害的用變數解決
	> turn //紀錄輪到誰執行
	> flag\[\] // 紀錄哪個process ready了
	> \-----
	> 紀錄 " Thread 是否 Ready", "是不是輪到此 thread"
	> ![](https://i.imgur.com/6SgWGdy.png)


	b. Does it work on processors with two hardware threads? With what kind of
	assumptions? When can it fail when the assumptions don't hold?
	> 如果compiler reorder instruction 他就爆了
	> \-----
	> CPU 不會 reoder instruction 啦，compiler 才會。
	> Assumption: no hardware support, can context switch anywhere!
	> 只能兩個 Thread 不能同時跑東西，不然會爛掉
6. Does a memory-barrier instruction do? How can it be used as part of a synchronization primitive?
	> Memory barriers: memory is loaded in code order
	> 就不會發生變數被修改後才被讀的問題(不確定)

8. Why is it inefficient to disable interrupts on a multiprocessor?
	> 一直disable會變成nonpreemptive
	> 能平行跑的只能一個一個跑

10. When atomic test-and-set is called as a C function, you successfully acquired the lock when it returns true or returns false? What is the lock value after?
	> return false
	> true
12. How can atomic compare-and-swap be used to implement a lock? What additional information can such a locking data type provide that is otherwise not available in atomic test-and-set?
	> 用`int` 存，可以存多種瑣(value could encode the owner of lock)
	>```c
	>int CompareAndSwap(int *val, int expected, int newVal){
    >    int temp = *val;
    >    if (*val == expected)
    >        *val = newVal;
    >    return temp;
    >}
	> ```
14. Can an atomic variable replace a critical section in general? In what case may it fail, if any?
	> single producer, multi-consumer他就爆了

16. How do you pronounce "Dijkstra"?
17. After declaring a semaphore S,
	a. what does wait(S) do? Under what condition would it block, and under what condition would it not block? What is its effect on S's value upon returning? What causes wait(S) to unblock?
	> request for resource S, if S not available then wait
	> while(s<=0);
	> S - -

	b. what does signal(S) do? Does it ever block? If so, under what condition, or if
	not, why not? What is its effect on S's value upon returning?
	> give up resource S
	> S++

13. What does the value of semaphore S represent when it is positive? when it is negative? When it is 0?
	> positive: 有空間
	> 0: 空間剛剛好
	> negative: 有人在等
15. How can a mutex be implemented using a semaphore?
	> binary semaphore is mutex
17. How can barrier synchronization be implemented using a semaphore? If a process P1 needs to execute A before Process P2 executes B, how can the code of the two processes be written? Explain how the waiting process can be unblocked even though the semaphore's value is initialized to 0.
	> P1 做完A後signal(0)，P2 在做B之前wait(0)
	> \---------
	> Signal(0)要做啥....
	> initial S = 0;
	> After finish A, signal(S)
	> Before start B, wait(S)
19. Is it always more efficient to use non-busy-wait semaphores? When is it more efficient to use busy-wait semaphores, if ever?
	> 當critical section小的時候，用busy wait比較效率
	> \-------
	> time for cirtical section < context switch
21. In the classical bounded-buffer problem of n-buffers, it declares three semaphores
	```cpp
	semaphore mutex = 1;
	semaphore full = 0;
	semaphore empty = n;
	```

	a. What is the purpose of the semaphore mutex? What resource does it protect?
	> protect critical section
	> \------
	> mutual exclusive access
	> ex: 1 Producer / n Consumer: produce & consume are mutual exclusive
	> 
	b. What is the purpose of the semaphore full?
	> buffer有東西
	> \---------
	> limit the number of Consumer

18. Continuing with the classical bounded-buffer problem, Producer's code looks like infinite loop with body:
```cpp
1 produce next item;
2 wait(empty); // wait empty
3 wait(mutex); // wait mutex
4 enqueue next item;
5 signal(mutex); // signal mutex
6 signal(full); // signal full

// Consumer's code looks like infinite loop with body
7 wait(full); // wait full
8 wait(mutex); // wait mutex
9 dequene the next item;
10 signal(mutex); // signal mutex
11 signal(empty); // signal empty
```

Fill in the blanks above (lines 2, 3, 5, 6, 7, 8, 10, 11) with the proper semaphores. Explain why they need to go in those places.

19. In the Readers-Writers classical synchronization problem, two semaphores `rw_mutex` and `mutex` are declared, in addition to an `int readcount=0`;
	a. what is the purpose of semaphore rw_mutex;? Why is it initialized to 1?
	> one writer to read/write
	> first reader to read
	> 只允許一人write
	
    b. what is the  purpose of semaphore named mutex in the code? Why is it initialized to 1 and use a separate int readcount = 0; instead of using a counting semaphore to keep track of the number of readers?
	> 只允許一人更新readcount
	> 
20. Continuing with the Readers-Writers classical synchronization problem, fill in the blanks below with the proper semaphores 
> ![](https://i.imgur.com/b6c74VA.png)


```cpp
(rw_mutex, mutex):
1 Writer():
	2 while (TRUE):
	3 wait(____)
	4 code for writing
	5 signal(___)
6 Reader():
	7 while (TRUE):
		8 wait(___)
		9 readcount += 1
	10 if (readcount == 1):
		11 wait(___)
		12 signal(___)
13 code to read data
	14 wait(___)
	15 readcount -= 1
	16 if (readcount == 0):
		17 signal(___)
		18 signal(___)
```
21. In the Dining Philosophers problem, if the code for each philosopher is written as the following infinite loop that make use of an array of semaphores 
```cpp
chopstick[5] = {1, 1, 1, 1, 1};
1 do {
2 wait(chopstick[i]);
3 wait(chopStick[(i + 1) % 5]);
4 eat rice;
5 signal (chopstick[i]);
6 signal (chopstick[ (i + 1) % 5] );
7 think;
8 } while (TRUE);
```
a. Explain a situation where a deadlock can occur.
	> 別人拿到你要的那一隻
b. Explain a situation where a philosopher might starve.
	> 大家都拿到一隻然後在等下一隻，大家都沒飯吃
c. What is the difference between deadlock and starvation?
	> deadlock有可能解，starvation會大家一起死
# Programming Exercise: 
Parking Simulation In this assignment, you are to implement a parking simulation program in Python using semaphores. A parking lot is a good match with (counting) semaphores because it is a resource with multiple instances (i.e., N parking spots). So, it will allow up to N simultaneous users to use the shared resources. Any time the occupancy is less than N, there is no blocking; but if more than N, then some will have to block.
2.1 You will need several data structures for the parking lot:
● a counting semaphore for the number of parking spots
● a list to represent the spots (i.e., record which car is parked in which position)
● another synchronizing data structure of your choice when modifying the list of spots
Use the following template for making the parking lot data structure import threading

```cpp
def MakeParkingLot(N):
global sem # semaphore for the parking lot
global spots # list for the spots
global spotsSync # for synchronizing access to spots
spots = [None for i in range(N)]
# your code to initialize sem and spotsSync
```


You have several choices of data structures for spotsSync and spots. You may even
choose some alternative to spots instead of the code shown here, but if you use a plain
list, then you would need something like a mutex, a lock, or another semaphore for
spotsSync. Check out the available synchronization primitives from threading
module. What would you choose and why?

2.2 Each car can be represented by a thread. In the next function, MakeCars(C), create C
threads and return a list of them.
```cpp
def MakeCars(C):
# your code here to spawn threads
# don’t forget to return the list
```
2.3 Next, write the function to be attached to each thread, i.e., the action of parking the car,
leaving it there for some time, and leaving. it will make use of the same global data
structures declared earlier. Use the comments in the following template code to fill in
the necessary statements.
```cpp
def Park(car):
global sem, spots, spotsSync
# 2.3.1 ############################
# if spot available, grab it; otherwise wait until available.
# Hint: don’t use if/else statement! this is just one line.
# 2.3.2 ###########################################
# after confirming one parking spot, modify the spots
# (Python list or your choice of list-like data structure to
# put this car into the spot. The following is an example
# of what it can do, but you may have a different way of
# grabbing parking spots.
# Do you need to protect access to the following block of
# code? If so, add code to protect it; if not, why not?
for i in range(len(spots)):
if spots[i] is None:
spots[i] = car
break
snapshot = spots[:] # make a copy for printing
# now let us print out the current occupancy
print("Car %d got spot: %s" % (car, snapshot))
# leave the car on the lot for some (real) time!
import time
import random
st = random.randrange(1,10)
time.sleep(st)
# now ready to exit the parking lot. What do we need to
# 2.3.3 ################################
# update the spots data structure by replacing the spot
# that current car occupies with the value None;
# protect code if needed
# (2) print out the status of the spots
print("Car %d left after %d sec, %s" %
(car, st, myCopySpots))
# 2.3.4 #################################
# (3) give the spot back to the pool
# (hint: semaphore operation)
# Finally, have the main program run it:
if __name__ == '__main__':
MakeParkingLot(5)
cars = MakeCars(15)
for i in range(15): cars[i].start()
```
Here is sample output. Your output may be in a different order, but it must be
consistent.
```cpp
$ python3 parking.py
Car 0 got spot: [0, None, None, None, None]
Car 1 got spot: [0, 1, None, None, None]
Car 2 got spot: [0, 1, 2, None, None]
Car 3 got spot: [0, 1, 2, 3, None]
Car 4 got spot: [0, 1, 2, 3, 4]
Car 0 left after 3 sec, [None, 1, 2, 3, 4]
Car 5 got spot: [5, 1, 2, 3, 4]
Car 2 left after 3 sec, [5, 1, None, 3, 4]
Car 6 got spot: [5, 1, 6, 3, 4]
Car 3 left after 4 sec, [5, 1, 6, None, 4]
Car 7 got spot: [5, 1, 6, 7, 4]
Car 6 left after 1 sec, [5, 1, None, 7, 4]
Car 8 got spot: [5, 1, 8, 7, 4]
Car 5 left after 3 sec, [None, 1, 8, 7, 4]
Car 9 got spot: [9, 1, 8, 7, 4]
Car 1 left after 8 sec, [9, None, 8, 7, 4]
Car 4 left after 8 sec, [9, None, 8, 7, None]
Car 10 got spot: [9, 10, 8, 7, None]
Car 11 got spot: [9, 10, 8, 7, 11]
Car 10 left after 3 sec, [9, None, 8, 7, 11]
Car 12 got spot: [9, 12, 8, 7, 11]
Car 7 left after 7 sec, [9, 12, 8, None, 11]
Car 13 got spot: [9, 12, 8, 13, 11]
Car 11 left after 5 sec, [9, 12, 8, 13, None]
Car 14 got spot: [9, 12, 8, 13, 14]
Car 8 left after 9 sec, [9, 12, None, 13, 14]
Car 9 left after 9 sec, [None, 12, None, 13, 14]
Car 13 left after 6 sec, [None, 12, None, None, 14]
Car 14 left after 6 sec, [None, 12, None, None, None]
Car 12 left after 9 sec, [None, None, None, None, None]
```
2.4 Show your typescript. Run your code multiple times. Does it show the same or different
output? Why?