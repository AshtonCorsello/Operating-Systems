#ifndef PROD_CONSUM_H                                                                                      
#define PROD_CONSUM_H                                                                                      
                                                                                                      
#include <sys/mman.h>                                                                                 
#include <sys/stat.h>                                                                                 
#include <sys/shm.h>                                                                                  
#include <fcntl.h>                                                                                    
#include <semaphore.h>                                                                                
#include <stdio.h>                                                                                    
#include <stdlib.h>                                                                                   
#include <unistd.h>                                                                                   
#include <iostream>                                                                                   
                                                                                                      
struct SharedMem {                                                                                    
        int buffer[2];                                                                                
        sem_t semFull;                                                                                
        sem_t semEmpty;                                                                               
        sem_t Mutex;                                                                                  
};                                                                                                    
                                                                                                      
char *pathName;                                                                                       
                                                                                                      
void error(char **msg) {                                                                         
        std::cerr <<"ERROR: " << msg << " failed. Terminating." << std::endl;                         
        exit(1);                                                                                      
}                                                                                                     
                                                                                                      
#endif     
