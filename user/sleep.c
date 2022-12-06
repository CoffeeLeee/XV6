#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char *argv[]){
    if(argc <= 1){
        fprintf(2, "usage: sleep pattern [file ...]\n");
        exit(1);
    }
    int count = atoi(argv[1]);
    sleep(count);
    exit(0);
}