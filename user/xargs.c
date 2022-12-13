#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

/*
contents of xargstest.sh

mkdir a
echo hello > a/b
mkdir c
echo hello > c/b
echo hello > b
find . b | xargs grep hello
*/

int main(int argc, char *argv[]) {
    char *command = argv[1];
    char *ag_arr[MAXARG];
    ag_arr[0] = argv[2];
    int origin_arg = argc - 2;
    char input_arg[128];
    int index = 0;
    char ch;
    while (read(0, &ch, sizeof(char)) == sizeof(char)) {
        if (ch != '\n') {
            input_arg[index++] = ch;
        } else {
            input_arg[index] = 0;
            ag_arr[origin_arg] = input_arg;
            ag_arr[origin_arg + 1] = 0;
            index = 0;
            for(int i = 0; i <= origin_arg; ++i){
                printf("arg %d : %s\n",i,ag_arr[i]);
            }
            if (fork() == 0) {
                printf("%s\nxargs exec\n",input_arg);
                exec(command, ag_arr);
            } else {
                wait(0);
            }
        }
    }
    exit(0);
}