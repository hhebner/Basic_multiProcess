#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int children, iterations, simulations, opt;

    while ((opt = getopt(argc, argv, "hn:s:t:")) != -1){
        switch(opt) {
            case 'h':
               help(); 
               exit(0);
            case 'n':
                children = optarg;
                break;
            case 's':
                simulations = optarg;
                break;
            case 't':
                iterations = optarg;
                break;
            default:
                help();
                exit(1);
        }
    }

}