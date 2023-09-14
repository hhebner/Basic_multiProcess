//Henry Hebner project 1 9/14/2023
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

//Help message function
void help(){
        printf("Please use this template for running the program: oss [-h] [-n proc] [-s simul] [-t iter], Where -h is the help command, -n is the amount of children to be deployed, -s is the number of processes running at the same time and -t is the number of iterations worker.c will run. -n, -s, -t all take an integer\n");
}


int main(int argc, char *argv[]){
    int children = 0, iterations = 0, simulations = 0, opt;//keeping track of each command line argument and opt
    int  active_workers = 0, total_workers_launched = 0;//These are neccessary for -s command to work. 
    char iter_to_string[3];//execlp does not take in integers so this will be used to store iterations in string format

    //These are the command line arguments the user input is converted to integer becasue the command line takes them in as strings
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
   //This is where we take the value from iterations and store it as a string in iter_to_string 
   sprintf(iter_to_string,"%d", iterations); 

   /*This is where all the logic for running the processes happens. We start with a while loop that 
     will continue to execute as long as the arguments below are kept. This makes sense becasue 
     children is holding the input for our -n command which dictates how many children/workers
     we will be creating. So, if total_workers_launched is equal to children then we stop creating
     new workers or we will stop if the number of active_workers hits zero becasue there should always be 
     some process running while our criteria has not been met yet and we want to make sure that a process
     does not get cut off. The if statement holds the logic for our -s command on whther we can launch
     more workers concurrently. If the current number of active_workers is less than simulations which
     holds our -s input than we can run more workers if it is equal then we cannot. And again we want 
     to make sure the total_workers_launched is less than our children holding the value of -n input.
     Exercise 3.9 in UNIX helped with the idea of keeping track of the workers. */
   while (total_workers_launched < children || active_workers > 0) {
           if (active_workers < simulations && total_workers_launched < children){
                pid_t fork_pid = fork();
                if (fork_pid == 0) { //Then we are working with child process
                        execlp("./worker", "worker", iter_to_string, NULL);//This is sending our number of iterations to worker.c
                        perror("execlp has failed");//if execlp fails for some reason perror will give us a descriptive error message 
                        exit(1);
                } else if (fork_pid > 0) {//In parent process
                       //We increment active_workers and total_workers_launched to keep track of our processes
                       total_workers_launched++;
                       active_workers++;
                } else {
                       perror("fork has failed");
                       exit(1);
                }
           }
           /*I also got this from UNIX example 3.13 but modified it a bit. waitpid is system call that waits
             for a child process to end. -1 mean it is waiting for any child process to end. NULL would keep
             the termination status of child but it is NULL so it does nothing. WNOHANG is a flag that 
             ensures that the parent process will not be blocked while a child process is active. This 
             is neccessary becasue we are keeping track of our workers in the parent process. If wait_pid
             is greater than zero then a child process has ended and we will decrement our active_workers   */
           pid_t wait_pid = waitpid(-1, NULL, WNOHANG);
           if (wait_pid > 0) {
                   active_workers--;
           }
   }

   
   printf("All workers have finished\n");
   return 0;
}
