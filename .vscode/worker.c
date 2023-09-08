#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int num_loop_iter = atoi(argv[1]);
    pid_t pid = getpid();
    pid_t ppid = getppid();

    
}