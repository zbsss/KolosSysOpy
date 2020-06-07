#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_NAME "/kol_shm"
#define MAX_SIZE 1024

int main(int argc, char **argv)
{
    
   if(argc !=2){
    printf("Not a suitable number of program parameters\n");
    return(1);
   }

   /***************************************
   Utworz/otworz posixowy obszar pamieci wspolnej "reprezentowany" przez SHM_NAME
   zapisz tam wartosc przekazana jako parametr wywolania programu
   posprzataj
   *****************************************/

    // tworze klucz na podstawie SHM_NAME
    key_t key = ftok(SHM_NAME, 1);

    // tworze obszar pamici wspoldzielonej na podstawie klucza
    int shm_id = shmget(key, sizeof(int), IPC_CREAT | 0666);
    if(shm_id < 0){
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // podpinam wspoldzielona pamiec pod zmienna value
    // i zapisuje w niej argument programu
    int* value = shmat(shm_id, NULL, 0);
    *value = atoi(argv[1]);
    
    // odpinam zmienna value od pamieci wspoldzielonej
    shmdt(value);

    return 0;
}
