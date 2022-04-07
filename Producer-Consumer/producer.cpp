#include "prod_consum.hpp"

struct SharedMem *map;          //Shared memory structure containing buffer space and semaphores 

int main(int argc, char *argv[]) {

        srand(time(NULL));

        int BUFFER_SIZE = *(&map->buffer+1) - map->buffer;

        if (argc < 2) {
                std::cerr << "Error: Too few arguments. Please enter pathname. Terminating...";
                return 1;
        }

        pathName = argv[1];     //Path name of shared memory location

        shm_unlink(pathName);     //Unlink in case of previous crash

        int fd = shm_open(pathName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);     //Create shared memory, or open if it alrady exists
        if (fd == -1) {
                error("Produer shared memory");
        }

        int errorcheck = ftruncate(fd, sizeof(SharedMem));     //Alters shared memeory size to size of structure
        if (errorcheck == -1) {
                error("ftruncate");
        }

        map = (SharedMem*)(mmap(NULL, sizeof(*map), PROT_WRITE, MAP_SHARED, fd, 0));     //Map the shared memory to arbitrary place in memory
        if (map == MAP_FAILED) {
                error("Producer memory mapping");
        }

        errorcheck = sem_init(&map->semFull, 1, 0);     //This keeps track of how full the buffer is. Initially set to 0 because the buffer is entirely empty
        if (errorcheck == -1) {
                error("Semaphore 'semFull' initialization");
        }
        errorcheck = sem_init(&map->semEmpty, 1, BUFFER_SIZE);     //This keeps track of how empty the buffer is. Initially set to buffer size because buffer is entirely empty. 
        if (errorcheck == -1) {
                error("Semaphore 'semEmpty' initialization");
        }
        errorcheck = sem_init(&map->Mutex, 1, 1);      //Initialize Mutex to 1. This ensures mutual exclusion between producer and consumer. 
        if (errorcheck == -1) {
                error("Semaphore 'Mutex' initialization");
        }

        
        int index = 0;      //Keeps track of location in buffer
        for (int i = 0; i < 10; i++) {

                int data = rand() % 9999 + 1;     //Gather random data

                sem_wait(&map->semEmpty);     //Wait until the buffer is empty
                sem_wait(&map->Mutex);     //Wait until Mutex is unlocked, locks it

                map->buffer[index] = data;     //Inputs data into buffer
                std::cout << "PRODUCING AT INDEX " << index << "..." << std::endl;
                std::cout << "Table[" << index << "] = " << map->buffer[index] << std::endl;
                index = (index + 1) % BUFFER_SIZE;     //Goes to next location in buffer

                sem_post(&map->Mutex);     //Unlock Mutex
                sem_post(&map->semFull);     //Signal that this buffer location is full


        }
}
