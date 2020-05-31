#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>


int main()
{
  pid_t child;
  int status, retval;
  if((child = fork()) < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if(child == 0) {
    sleep(1);
    exit(EXIT_SUCCESS);
  }
  else {
/* Proces macierzysty pobiera status  zakończenie potomka child,
 * nie zawieszając swojej pracy. Jeśli proces się nie zakończył, wysyła do dziecka sygnał SIGKILL.
 * Jeśli wysłanie sygnału się nie powiodło, ponownie oczekuje na zakończenie procesu child,
 * tym razem zawieszając pracę do czasu zakończenia sygnału
 * jeśli się powiodło, wypisuje komunikat sukcesu zakończenia procesu potomka z numerem jego PID i statusem zakończenia. */

    retval = waitpid(child, &status, WNOHANG);

    // waitpid returned an error
    if(retval < 0){
      perror("waitpid error");
      exit(EXIT_FAILURE);
    }

    // child process not finished
    if(retval == 0){

      // send SIGKILL
      kill(child, SIGTERM);

      // if KILL not successful wait until child is finished
      // if child was killed just get status
      if(waitpid(child, &status, 0) == -1){
        // return error if waitpid failed
        perror("waitpid error");
        exit(EXIT_FAILURE);
      }
    }

    // print value returned by the child process
    printf("[SUCCESS] PID: %d Returned status: %d\n",child, status);

    // interpret the returned value using macros
    if (WIFEXITED(status)) {
        printf("exited, status=%d\n", WEXITSTATUS(status));
    } else if (WIFSTOPPED(status)) {
        printf("stopped by signal %d\n", WSTOPSIG(status));
    } else if (WIFSIGNALED(status)) {
        printf("killed by signal %d\n", WTERMSIG(status));
    }  

/* koniec*/ 
 } //else
  exit(EXIT_SUCCESS);
}
