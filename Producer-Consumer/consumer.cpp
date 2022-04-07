#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "prod_consum.hpp"

struct SharedMem *map;     //Structure for shared memeory space containing buffer and semaphores

int main(int argc, char *argv[]) {

        sleep(1);     //Sleep for 1 second to allow producer to initalize  

        pathName = argv[1];

        int BUFFER_SIZE = *(&map->buffer + 1) - map->buffer;

        int fd = shm_open(pathName, O_RDWR, S_IRUSR | S_IWUSR);     //Open shared memory from producer
        if (fd == -1) {
                error("Consumer shared memory");
        }


        map = (SharedMem*)(mmap(NULL, sizeof(*map), PROT_WRITE, MAP_SHARED, fd, 0));     //Map shared memory 
        if (map == MAP_FAILED) {
                error("Consumer memory mapping");
        }


        int index = 0;     //Keeps track of location in buffer
        for (int i = 0; i < 10; i++) {

                sem_wait(&map->semFull);     //Waits until buffer is full
                sem_wait(&map->Mutex);      //Waits until Mutex is unlocked, locks (ensures mutual exclusion)

                map->buffer[index] = 0;     //Consume data
                std::cout << "CONSUMING AT INDEX " << index << "..." << std::endl;
                std::cout << "Table[" << index << "] = " << map->buffer[index] << std::endl;
                index = (index + 1) % BUFFER_SIZE;     //Move to next location in buffer

                sem_post(&map->Mutex);     //Unlock mutex
                sem_post(&map->semEmpty);      //Signal that buffer is empty


        }

        shm_unlink(pathName);     //Unlink shared memory to prevent further changes
        return 0;
};
