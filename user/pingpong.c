#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(){
    int p1[2];
    int p2[2];
    pipe(p1);
    pipe(p2);

    if(fork() == 0){
        char buf[2];
        int n ;
        while(1){
            n = read(p1[0], buf, sizeof(buf));
            if(n)
                break;
        }
        int pid1 = getpid();
        fprintf(1, "%d:reveived ping\n", pid1);
        write(p2[1], "B", 1);
        exit(0);
    }else{
        char buff[2];
        close(p1[0]);
        write(p1[1], "A", 1);
        close(p1[1]);
        wait(0);
        read(p2[0], buff, sizeof(buff));  
        int pid = getpid();
        fprintf(1, "%d:received pong\n", pid);
        exit(0);
    }
    exit(0);
}