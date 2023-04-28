# producer-consumer

A simple C program to demonstrate the solution to the popular "producer-consumer" critical section problem. I solved this using semaphores to synchronize the two programs with mutual exclusion.

## Explanation

Topic: Banker’s Algorithm for deadlock avoidance.

Considering a system with five processes P0 through P4 and three resources of type A, B, C. Resource type A has 10 instances, B has 5 instances and type C has 7 instances. Suppose at time t0 following snapshot of the system has been taken:

![image](https://user-images.githubusercontent.com/112535869/235267660-4e30a882-728f-4824-b87b-63fa5fe7a25e.png)

## Problem
Is the system in a safe state? If Yes, then what is the safe sequence?

## Disclaimer

As of right now, this program is only a demonstration of my knowledge on deadlock avoidance for a class homework assignment. In the future, I plan to revisit this project increasing the complexity and usability. Thank you!

## Installation/Download

This program must run in a UNIX/LINUX environment. You will get errors if attempting to run in Windows/MacOS.

You may choose to clone the repository:

```
git clone https://github.com/tdrewek/CS33211.git
```
Or you may choose to download the zip file [here](https://github.com/tdrewek/CS33211/archive/refs/heads/main.zip).

## Usage

Open a terminal/console and navigate to the folder "CS33211" if cloned or "CS33211-main" if downloaded. Once in the CS33211 directory, navigate to the "producer-consumer" directory.

Once in the "producer-consumer" directory, you can run the program by executing three lines as shown below:

```
gcc producer.c -pthread -lrt -o producer
gcc consumer.c -pthread -lrt -o consumer
./producer & ./consumer &
```

## Example

Once the two programs begin running, it will continue until a total of 10 item sets have been completed. An item set is complete once 2 items have been added to the table, and then removed from the table (shown below with comments). After the 10 item sets are complete, it will stop producing items. You can terminate the program after the 10 item sets are complete by using the stop command: "CTRL + C".

```
[33] 12307
[34] 12308
producer added 92    // item set 1
producer added 56
consumer removed 92
consumer removed 56
producer added 56    // item set 2
producer added 37
consumer removed 56
consumer removed 37
producer added 26    // item set 3
producer added 98
consumer removed 26
consumer removed 98
producer added 22    // item set 4
producer added 17
consumer removed 22
consumer removed 17
producer added 69    // item set 5
producer added 1
consumer removed 69
consumer removed 1
producer added 17    // item set 6
producer added 80
consumer removed 17
consumer removed 80
producer added 2     // item set 7
producer added 34
consumer removed 2
consumer removed 34
producer added 15    // item set 8
producer added 14
consumer removed 15
consumer removed 14
producer added 27    // item set 9
producer added 57
consumer removed 27
consumer removed 57
producer added 48    // item set 10
producer added 21
consumer removed 48
consumer removed 21
^C
[33]-  Done                    ./producer
[34]+  Done                    ./consumer
```

