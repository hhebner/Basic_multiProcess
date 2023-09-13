#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>


void help(){
        printf("Please use this template for running the program: oss [-h] [-n proc] [-s simul] [-t iter], Where -h is the help command, -n is the amount of children to be deployed, -s is the number of processes running at the same time and -t is the number of iterations worker.c will run. -n, -s, -t all take an integer\n");
}


int main(int argc, char *argv[]){
    int children, iterations, simulations, opt;

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

}