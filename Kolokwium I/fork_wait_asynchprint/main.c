#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


int main ( int argc, char *argv[] )
{
    int i, pid;

    if(argc != 2){
        printf("Not a suitable number of program arguments");
        exit(2);
    }else {
       for (i = 0; i < atoi(argv[1]); i++) {
        //*********************************************************
        //Uzupelnij petle w taki sposob aby stworzyc dokladnie argv[1] procesow potomnych, bedacych dziecmi
        //   tego samego procesu macierzystego.
           // Kazdy proces potomny powinien:
               // - "powiedziec ktorym jest dzieckiem",
                //-  jaki ma pid,
                //- kto jest jego rodzicem
           //******************************************************

           if(fork() == 0){
               // preparing the string to be printed
               char toprint[100];
               snprintf(toprint, sizeof(toprint), "Child #%d, PID = %d, PPID = %d\n", i+1, getpid(), getppid());
               
               // using write instead of printf beacause printf is not asynch safe
               write(STDOUT_FILENO, toprint, strlen(toprint));
               exit(EXIT_SUCCESS);
           } 
           
           else{
               continue;
           }
        }
        // waiting for all children to finish
        while (wait(NULL) > 0 );
    }
    return 0;
}
