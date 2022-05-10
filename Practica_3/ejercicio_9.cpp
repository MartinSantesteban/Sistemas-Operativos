#include <signal.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <semaphore.h>



int main(int argc,char *argv[]){ // main i N
 if(argc != 3){
     perror("Number of arguments should be 2.\n");
     return 1;
 }
 int N = atoi(argv[2]);
 int i = atoi(argv[1]);
 sem_t s[N];                    //defino los N semaforos
 for(int l = 0; l < N; l++){ 
     sem_init(&(s[l]),0,0);
     int value;
     sem_getvalue(&s[l],&value);
     printf("El valor del semaforo %d es %d.\n",l,value);
 }                              // Los seteo en 0
 for(int j = 0; j < N; j++){    //Hago los procesos
     pid_t pid = fork();
     if(pid == 0){
        int value;
        int k;
        if (j == 0){k = N-1;}else{k = j-1;};
        //sem_getvalue(&s[k],&value);
        //printf("El valor del semaforo %d es %d.\n",k,value);
        printf("Hijo %d espera\n.",j);
        sem_wait(&s[k]);       
        printf("Hijo %d ejecuta.\n", j);
        sem_post(&s[j]); 
        return 0;
     }
 }
 int v;
 sem_getvalue(&s[i],&v);
 printf("El valor de s[%d] es %d,\n",i,v); //deberia dar cero
 sem_post(&s[i]);
 sem_getvalue(&s[i],&v);
 printf("El valor de s[%d] es %d,\n",i,v); //deberia dar 1
 return 0;
}
