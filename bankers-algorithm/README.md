# producer-consumer

A simple C++ program to demonstrate the solution to the popular "banker's algorithm" deadlock avoidance problem.

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

Open a terminal/console and navigate to the folder "CS33211" if cloned or "CS33211-main" if downloaded. Once in the CS33211 directory, navigate to the "bankers-algorithm" directory.

Once in the "bankers-algorithm" directory, you can run the program using following commands as shown below:

```
g++ banker.cpp -o banker
./banker
```

## Example

```
mocha@Ubuntu2:~/Desktop/Github/CS33211/bankers-algorithm$ g++ banker.cpp -o banker
mocha@Ubuntu2:~/Desktop/Github/CS33211/bankers-algorithm$ ./banker

Allocated Resource Table:
0 1 0 
2 0 0 
3 0 2 
2 1 1 
0 0 2 

Max Resource Table:
7 5 3 
3 2 2 
9 0 2 
2 2 2 
4 3 3 

Available Resources:
3 3 2 

Needed Resources:
7 4 3 
1 2 2 
6 0 0 
0 1 1 
4 3 1 

Safe sequence is: 
 P1 to P3 to P4 to P0 to P2
```

