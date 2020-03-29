Design a scheduling program to implements a Queue with two levels:
Level 1 : Fixed priority preemptive Scheduling
Level 2 : Round Robin Scheduling
For a Fixed priority preemptive Scheduling (Queue 1), the Priority 0 is highest priority. If one
process P1 is scheduled and running, another process P2 with higher priority comes. The
New process (high priority) process P2 preempts currently running process P1 and process P1
will go to second level queue. Time for which process will strictly execute must be
considered in the multiples of 2.

All the processes in second level queue will complete their execution according to round
robin scheduling.
Consider: 1. Queue 2 will be processed after Queue 1 becomes empty.
2. Priority of Queue 2 has lower priority than in Queue 1.

Test case 1: 
Number of process: 5
Time quantum: 4
PID Arrival_TIme Burst_Time Priority:
1 4 6 2
2 5 1 3
3 1 2 4
4 5 3 1
5 3 4 5

Test case 1 Output: 
------------Priority Queue execution started from here -----------
========>  Process ID: P3 , Current CPU time: 1  <========
========>  Process ID: P3 , Current CPU time: 2  <========
========>  Process ID: P5 , Current CPU time: 3  <========
========>  Process ID: P1 , Current CPU time: 4  <========
========>  Process ID: P4 , Current CPU time: 5  <========
========>  Process ID: P4 , Current CPU time: 6  <========
========>  Process ID: P4 , Current CPU time: 7  <========
========>  Process ID: P2 , Current CPU time: 8  <========
------------Round Robin execution started with Time Quantum of 4 -----------
========>  Process ID: P5 , Current CPU time: 10  <========
========>  Process ID: P5 , Current CPU time: 11  <========
========>  Process ID: P5 , Current CPU time: 12  <========
========>  Process ID: P1 , Current CPU time: 13  <========
========>  Process ID: P1 , Current CPU time: 14  <========
========>  Process ID: P1 , Current CPU time: 15  <========
========>  Process ID: P1 , Current CPU time: 16  <========
========>  Process ID: P1 , Current CPU time: 17  <========
