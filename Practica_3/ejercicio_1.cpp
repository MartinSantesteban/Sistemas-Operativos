#include <signal.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(){
    pid_t pid = fork();
    int x = 0;
    if(pid == 0){
        x = x + 1;
        printf("%d\n",x);
    }else{
        x = x + 1;
    }
    return 0;
}