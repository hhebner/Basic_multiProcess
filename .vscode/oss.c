#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void help(){
        printf("Please use this template for running the program: oss [-h] [-n proc] [-s simul] [-t iter], Where -h is the help command, -n is the amount of children to be deployed, -s is the number of processes running at the same time and -t is the number of iterations worker.c will run. -n, -s, -t all take an integer\n");
}


int main(int argc, char *argv[]){
    int children = 0, iterations = 0, simulations = 0, opt;
    int  active_workers = 0, total_workers_launched = 0;
    char iter_to_string[3];

    while ((opt = getopt(argc, argv, "hn:s:t:")) != -1){
        switch(opt) {
            case 'h':
               help();
               exit(0);
            case 'n':
                children = atoi(optarg);
                break;
            case 's':
                simulations = atoi(optarg);
                break;
            case 't':
                iterations = atoi(optarg);
                break;
            default:
                help();
                exit(1);
        }
    }

   sprintf(iter_to_string,"%d", iterations);

   while (total_workers_launched < children || active_workers > 0) {
           if (active_workers < simulations && total_workers_launched < children){
                pid_t fork_pid = fork();
                if (fork_pid == 0) {
                        execlp("./worker", "worker", iter_to_string, NULL);
                        perror("execlp has failed");
                        exit(1);
                } else if (fork_pid > 0) {
                       total_workers_launched++;
                       active_workers++;
                } else {
                       perror("fork has failed");
                       exit(1);
                }
           }

           pid_t wait_pid = waitpid(-1, NULL, WNOHANG);
           if (wait_pid > 0) {
                   active_workers--;
           }
   }


   printf("All workers have finished\n");
   return 0;
}
