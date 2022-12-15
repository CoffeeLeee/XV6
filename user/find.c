#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void dfs(char path[], char filename[]) {
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;
    if ((fd = open(path, 0)) < 0) {
        fprintf(2, "cannot open %s\n", path);
        exit(1);
    }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    char cur[] = ".";
    char prev[] = "..";
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
        if (de.inum == 0)
            continue;
        if (strcmp(de.name, cur) == 0 || strcmp(de.name, prev) == 0)
            continue;
        int len = strlen(de.name);
        memmove(p, de.name, len);
        p[len] = '\0';
        stat(buf, &st);
        if (st.type == T_FILE) {
            if (strcmp(de.name, filename) == 0)
                fprintf(1, "%s\n", buf);
        } else if (st.type == T_DIR) {
            dfs(buf, filename);
        }
    }
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(1, "usage : find [basefile] [filename]\n");
        exit(1);
    }
    char *path = argv[1];
    char *filename = argv[2];
    dfs(path, filename);
    exit(0);
}