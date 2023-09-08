#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int num_loop_iter = atoi(argv[1]);
    pid_t pid = getpid();
    pid_t ppid = getppid();

    for (int i = 0; i < num_loop_iter; i++){
        printf("WORKER PID:%d PPID:%d Iteration:%d before sleeping\n", pid, ppid, i);
        sleep(1);
        printf("WORKER PID:%d PPID:%d Iteration:%d after sleeping\n", pid, ppid, i);
    }

    return 0;
}