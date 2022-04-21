# Bankers-Algorithm
#### Bankers-Algortithm -- developed by Edsger Dijkstra -- is a resource allocation and deadlock avoidance algorithm that determines if a system is safe from the possibility of deadlock given predetermined maximum allowed resources, and returns the sequence of processes that will ensure no deadlock. <br>
#### This algorithm is given its name due to the ability to be used in a banking system to ensure the bank does not run out of resources (remains in a safe state), and can always satisfy its customers needs.

## Usage
To run this program, use the following commands
```cpp
g++ safestate.cpp -o NAME
```
_Any C++ Compiler will work_

#### This program relies on a file named "data.txt" that supplies it with data for the *Allocation*, *Max*, and *Available* matrices. The data in this file is formatted at follows:
```txt
 010200302211002 753322902222433 332
|  ALLOCATION  ||      MAX     ||Available|
```
*Data should be inputted in this format, written left->right and top->down, delimited by one space inbetween each matrix*

### Output
Example program output, given a safe sequence
```cpp
The sequence is safe. The safe sequence = 
P1 P3 P4 P0 P2
```
