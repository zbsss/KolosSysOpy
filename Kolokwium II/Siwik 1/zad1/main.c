#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdint.h>
#include <sys/types.h>
#include <pthread.h>

void* hello(void* arg){
        int indx = *(int*) arg;
        pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);
        sleep(1);
        while(1){
                printf("Hello world from thread number %d\n", indx);
		/****************************************************
			przerwij dzialanie watku jesli bylo takie zadanie
		*****************************************************/
                pthread_testcancel(); //cancelation point

                printf("Hello again world from thread number %d\n", indx);

                pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
                sleep(2); // sleep function is a cancellation point so the program doesn't work like you want it to, Siwik...
                pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);
        }
        return NULL;
}


int main(int argc, char** args){

       if(argc !=3){
	    printf("Not a suitable number of program parameters\n");
    	return(1);
   	}

        int n = atoi(args[1]);

	/**************************************************
	    Utworz n watkow realizujacych funkcje hello
	**************************************************/
        pthread_t *threads = calloc(n, sizeof(pthread_t));

        for(int i=0; i<n; i++){
                pthread_create(&threads[i],  NULL, hello, (void *)&i);
                sleep(1);
        }

        int i = 0;
        while(i++ < atoi(args[2])) {
                printf("Hello from main %d\n",i);
                sleep(2);
        }
        
        
	/*******************************************
	    "Skasuj" wszystke uruchomione watki i poczekaj na ich zakonczenie
	*******************************************/
        for (int i = 0; i < n; i++)
        {
                if(pthread_cancel(threads[i]) != 0){
                        perror("cancel");
                        exit(1);
                }
                void* res;
                int s = pthread_join(threads[i], &res);
                
                if (s != 0){
                        perror("join");
                        exit(2);
                }

                if (res == PTHREAD_CANCELED)
                        printf("main(): thread was canceled\n");
                else
                        printf("main(): thread wasn't canceled (shouldn't happen!)\n");
        }
        printf("DONE");
        
        
        return 0;
}

