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

    sleep(1);
    int val =0;
    /*******************************************
    Utworz/otworz posixowy obszar pamieci wspolnej "reprezentowany" przez SHM_NAME
    odczytaj zapisana tam wartosc i przypisz ja do zmiennej val
    posprzataj
    *********************************************/

    // tworze klucz na podstawie SHM_NAME
    key_t key = ftok(SHM_NAME, 1);

    // otwieram obszar pamici wspoldzielonej na podstawie klucza
    int shm_id = shmget(key, sizeof(int), 0666);
    if(shm_id < 0){
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    
    // podpinam wspoldzielona pamiec pod zmienna value
    int* value = shmat(shm_id, NULL, 0);
    val = *value;

    // odpinam zmienna value od pamieci wspoldzielonej
    shmdt(value);
    // usuwam obszarm pamieci wspoldzielonej
    shmctl(shm_id, IPC_RMID, NULL);

	printf("%d square is: %d \n",val, val*val);
    return 0;
}
