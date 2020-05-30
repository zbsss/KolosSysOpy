#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>


void sighandler(int sig, siginfo_t *info, void *ucontext){
    printf("%d\n",info->si_value.sival_int);
    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]) {

    if(argc != 3){
        printf("Not a suitable number of program parameters\n");
        return 1;
    }


    int child = fork();
    if(child == 0) {
        //zablokuj wszystkie sygnaly za wyjatkiem SIGUSR1
        //zdefiniuj obsluge SIGUSR1 w taki sposob zeby proces potomny wydrukowal
        //na konsole przekazana przez rodzica wraz z sygnalem SIGUSR1 wartosc

        // tworze maske do blokowania wszytkiego oprocz SIGUSR1
        sigset_t mask;
        sigfillset(&mask);
        sigdelset(&mask, SIGUSR1);
        sigprocmask(SIG_BLOCK, &mask, NULL);

        // ustawiam obsluge SIGUSR1
        struct sigaction action;
        action.sa_flags = SA_SIGINFO;
        action.sa_sigaction = &sighandler;
        sigfillset(&action.sa_mask);
        sigaction(SIGUSR1, &action, NULL);

        // child czeka na SIGUSR1, inne sygnaly sa ignorowane
        sleep(2);
    }
    else {
        //wyslij do procesu potomnego sygnal przekazany jako argv[2]
        //wraz z wartoscia przekazana jako argv[1]
        
        // czekam az dziecko ustawi obsluge sygnalow
        sleep(1);

        // wysylam podany sygnal z odpowiadnia wartoscia
        union sigval value;
        value.sival_int = atoi(argv[1]);
        sigqueue(child, atoi(argv[2]), value);

        // czekam az dziecko obsluzy sygnal
        wait(NULL);
    }

    return 0;
}
