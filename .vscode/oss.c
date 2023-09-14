#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void help(){
        printf("Please use this template for running the program: oss [-h] [-n proc] [-s simul] [-t iter], Where -h is the help command, -n is the amount of children to be deployed, -s is the number of processes running at the same time and -t is the number of iterations worker.c will run. -n, -s, -t all take an integer\n");
}


int main(int argc, char *argv[]){
    int children, iterations, simulations, opt;
    char iter_to_string[3];

    while ((opt = getopt(argc, argv, "hn:t:")) != -1){
        switch(opt) {
            case 'h':
               help();
               exit(0);
            case 'n':
                children = atoi(optarg);
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

   for (int i = 0; i < children; i++){
          pid_t pid = fork();

         if (pid == 0){
                execlp("./worker", "worker", iter_to_string, NULL);
                perror("execlp");
                exit(1);
         }
   }

   for (int i = 0; i < children; i++){
           wait(0);
   }

   printf("All workers are done\n");
   return 0;
}
