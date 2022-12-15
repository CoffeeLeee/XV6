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
    for (int i = 1; i < argc; ++i) {
        ag_arr[i - 1] = argv[i];
    }
    char input_arg[128];
    int index = 0;
    char ch;
    while (read(0, &ch, sizeof(char)) == sizeof(char)) {
        if (ch != '\n') {
            input_arg[index++] = ch;
        } else {
            input_arg[index] = 0;
            ag_arr[argc - 1] = input_arg;
            ag_arr[argc] = 0;
            index = 0;
            if (fork() == 0) {
                exec(command, ag_arr);
            } else {
                wait(0);
            }
        }
    }
    exit(0);
}