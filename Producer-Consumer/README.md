# Producer-Consumer
The producer-consumer problem is a classic problem in computer science. Originally described by Edsger Dijkstra, the problem is simple, yet the solution can
be perplexing. The problem begins with two processes, a producer and a consumer, each with access to the same buffer in memory. The producer must fill this buffer with 
data, and the consumer must consume it. You must ensure mutual exclusion thoughout the entirety of the program, as to make sure the data never becomes
corrupted. This program serves as a visualization of this problem. 

## Usage
To run this program, use the following commands
```cpp
g++ producer.cpp -pthread -lrt -o producer
g++ consumer.cpp -pthread -lrt -o consumer
./producer pathName & ./consumer pathName
```
__"pathName" is the name of the Shared Memory you are creating. It may be named anything, but it must be the same for both processes.__   

_You may use any compiler for C++ you'd like._

### Output
Example program output
```bash
PRODUCING AT INDEX 0...
Table[0] = 1267
PRODUCING AT INDEX 1...
Table[1] = 7612
CONSUMING AT INDEX 0...
Table[0] = 0
CONSUMING AT INDEX 1...
Table[1] = 0
PRODUCING AT INDEX 0...
Table[0] = 315
PRODUCING AT INDEX 1...
Table[1] = 8388
CONSUMING AT INDEX 0...
Table[0] = 0
CONSUMING AT INDEX 1...
Table[1] = 0
...
```
_Actual program output will differ in data values, length, and potentially order of production/consumption_

## Conclusions
This visualization of the producer-consumer problem can be extremely helpful in helping one understand exactly what is happening to make it work. By studying
this code, you will be able to gain a deeper understanding of the solution to this classic problem. 
