# OS Weekly Review 9


###### tags: `Operating System`
Definitions and Short Answers
1. Given two processes

    ```cpp
    process1:
	    lock(mutex1)
	    lock(mutex2)
	    work()
	    unlock(mutex2)
	    unlock(mutex1)
    process2:
	    lock(mutex2)
	    lock(mutex1)
	    work()
	    unlock(mutex1)
	    unlock(mutex2)
    ```
   a. Do they always deadlock?
      > 不一定

   b. Do they sometimes deadlock? If so, describe one such condition
      > 如果 P1 lock mutex1, context switch to P2 and P2 lock mutex2, context switch to P1, P1 wait for mutex2
    

2. If two processes are not blocked but busy trying and keep failing to make progress, is it a deadlock?
	>  no, it's called livelock
	>  ex: Ethernet collision

3. What are the four necessary conditions of a deadlock?
	> mutual exclusion
	> hold and wait
	> No preemption of resource
	> circular wait

4. If **mutual exclusion** is a necessary condition for a deadlock, then does it mean that
   a. If you use a mutex then you always have the possibility of getting a deadlock?
   > no, 只有當上4面個情況成立時
   > depends on processes in safe state or not.

   b. If you use a counting semaphore of n > 1 then you won't get into a deadlock?
   > 不一定
   > ex:![](https://i.imgur.com/ByuhlTr.png)

5. If **hold-and-wait** is a necessary condition for a deadlock, then does it mean that
   a. If you acquire multiple resources, then you always have the possibility of getting into a deadlock?
   > no, 只有當上4面個情況成立時
   > depends on processes in safe state or not.

   b. If you acquire multiple resources but at most one at a time, then you won't get into a deadlock?
   > 不一定

6. If **no-preemption** is a necessary condition for a deadlock, then does it mean that
   a. All preemptive process (or thread) schedulers can get into deadlocks?
   > no, 只有當上4面個晴況成立時(幹要問幾遍???
   > depends on processes in safe state or not.
   
   b. If a process P1 holds a mutex but is now blocked while waiting to acquire another resource, preemption in this case means to temporarily allow another process P2 to acquire that mutex, finish, and give the mutex back to P1?
   > P1 跟 P1 打架???(笑死

7. If **circular-wait** is a necessary condition for a deadlock, then does it mean that
   a. Whenever you have a process P1 that is waiting to acquire an instance of a resource type R1 that is currently assigned to process P2 and P2 is waiting to acquire an instance of a resource type R2 that is currently assigned to process P1, then you have a deadlock?
   > 可以resource preemption阿白癡
   > 

8. A resource-allocation graph (RAG) can be used to model a system for deadlock analysis.
   a. Is a RAG a bipartite graph? If so, what are the two sets of vertices and what do they represent?
   > Set 1: Processes
   > Set 2: Resources
   > The edges in RAG only between Set 1 and Set 2
   
   b. Is a RAG a directed or undirected graph?
   > directed graph
   
   c. How is a resource request represented in the RAG?
   > the edge which from Process points to Recource 
   
   d. How is a resource assignment represented in the RAG?
   > the edge which from Recource points to Process 

9. Give a RAG that contains a cycle but does not have deadlock.
    > ![](https://i.imgur.com/V4c12VC.png)

10. In some RAG, having a cycle means a deadlock exists. Why would this be the case?
    > If every recource only has one instance, RAG with a cycle means a deadlock exists.

11. What is the meaning of deadlock prevention? What is its general approach?
	> ~~放棄找deadlock~~(no but actually yes) ?????
	> 預防 deadlock, 讓 mutual exclusion, Hold and wait, Resource Non-preemption, Circual Wait 其中一個不成立。

12. What is difficult about denying mutual exclusion as a way of achieving deadlock prevention?
	> 很有可能讓程式出現錯誤
	> Some Resources 不能被同時使用/修改 
	> ex: printer

13. What are two ways of eliminating hold-and-wait?
	> Allocate all requested resources before process starts
	> Process must hold no resource before request

14. What are disadvantages with the two ways of eliminating hold and wait above?
	> 第一個Impractical for most applications -- too "static" -> 記憶體爆炸
	> 第二個starvation possible, Low resource utilization
	> 
    > 1. 我窮逼沒資源 :poop: 
    > 2. 浪費時間
15. What are difficulties with deadlock prevention by allowing resource preemption?
    > allowing resource preemption: 資源不夠 -> 釋放其他process 的資源
    > Difficulty: 有些東西不能釋放 ex: mutex lock, pointer.
 
16. What is a way of breaking circular wait as the 4th way of deadlock prevention?
    > Resources 需求少的先做

17. For deadlock avoidance to work, what does each process have to declare?
    > the maximum number of resources of each type that it may need.

18. Does deadlock avoidance ensure that the system …
    > ![](https://i.imgur.com/xXontiz.png)

    

19. What is a claim in a deadlock avoidance algorithm?
    > Require a priori knowledge about resource needs
    > 要事先知道 每個 Process 需要多少資源

20. In the resource allocation graph (RAG) scheme of deadlock avoidance,
    a. Why does the RAG use only a claim edge but does NOT use an edge weight to indicate the max number of instances of a resource that the process may claim?
    > In scheme of deadlock avoidance, the resource number of each type is 1.(single-instances resources)
    
    b. What is the difference between a claim edge and a request edge in the resource allocation graph scheme of deadlock avoidance?
    > Suppose Edge is $P_i→R_j$
    > claim edge: $P_i$ **可能**會 request $R_j$
    > request edge: $P_i$ **一定**會 request $R_j$
    
    c. When a request is granted, what happens to the request edge?
    > Request edge 變成 assignment edge.
    
    d. When the resource is released, what happens to the assignment edge?
    > assignment edge 消失
    
    e. What does a cycle mean? Under what condition is a request granted?
    > ~~可能~~ 一定有 deadlock 因為 single-instances resources
    > only if no cycle created

21. To use the Banker's algorithm for deadlock avoidance,
    a. Banker's algorithm uses the Safety Algorithm to find a safety sequence. If such a sequence is found, is it a necessary condition or a sufficient condition that the system is in a safe state?
	> 充分條件
	> 就算沒有找到safety sequence還是有可能是safe

    b. What are variables m and n?
	> n = 有幾個process
	> m = resources 的種類

    c. What do Available[j] and Work[j] represent?
	> available:=#instances of resource type Rj that exist
	> 
	> work: #instances of resource type Rj not yet allocated
	> 
    d. What does the variable int Max[n][m] represent? Where does this matrix get its values from?
	> Pi may request up to Max[i,j] instances of resource type Rj
	> 
    e. What does the variable int Allocation[n][m] represent?
	> Pi is currently allocated Allocation[i,j] instances of Rj
	> 
    f. What is the meaning of variable int Need[n][m] and how does it get its values from?
	> Pi may need up to Need[i,j] more instances of Rj to complete its task
	> 
    g. In Step 3, Process Pi is chosen because its worst-case requests can be fulfilled, so why is Allocation[i][j] added back into Work[j] instead of being subtracted from Work[j]?
	> 代表Pi執行完後，有多少可以用

22. In the Resource-Request Algorithm, which decides whether a request Request i(by process Pi, of different resource types),
    a. If Requesti[:] ≤ Needi[:], does it mean that the request can be fulfilled? In other words, is it a necessary condition or a sufficient for granting the request?
	> 代表這個process的要求是正常的

    b. If the previous condition is a necessary condition, then what additional condition is needed in order to grant the request?
	> request <= availiable
	> 

    c. If the request cannot be granted, what happens?
	> 等吧孩子

23. A wait-for graph is used for deadlock detection of single-instance resource types.
    a. What is the wait-for graph that corresponds to the RAG below? ![](https://i.imgur.com/Zi9TGHi.png)
	> ![](https://i.imgur.com/D11OkMO.png)


    b. if the wait-for graph contains a cycle, does it mean there is definitely a deadlock or just possibility of a deadlock?
	> possibility
	> 
    c. if the processes are in a deadlock, does it mean there is definitely a cycle or possibility of a cycle?
	> definitely a cycle
	> 
    d. What is the complexity of cycle detection?
	> $O(n^2)$

24. For deadlock detection of multi-instance resource types, an algorithm essentially the same as the Safety Algorithm is used to detect cycles.
    a. How can you tell if the processes are deadlocked after running the algorithm?
    > If $Finish[i] != True$ for some i, then the processes are deadlocked
    
    b. How do you find all the processes that have the circular dependency in the deadlock?
    > $\forall i, Finish[i] = False$
    > 每個 $P_i$ 之間都有 circular dependency.

25. In practice, is the deadlock detection algorithm invoked on every request? Why or why not?
    > invoke depends on:
    > How often a deadlock is likely to occur
    > How many processes will need to be rolled back

26. What can an OS do after it detects a deadlock?
    a. Does it abort a process? If so, what are possible considerations?
    > Abort by Priority
    > 資源多的先幹掉、要求多的先幹掉
    
    b. What does roll back mean? Can every process be rolled back? What needs to happen first before a roll back?
    > Return to safe state, and restart processes.
    > Nope
    > ???
    
    c. Even if a system can recover from a deadlock, what problem may still happen to some unlucky process?
    > unlucky process: 一直被 Abort / Starvation