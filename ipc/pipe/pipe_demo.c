#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>

void child(int *fd)
{
    printf("child process write pipe\n");
    char *buf = "this is child";
    close(fd[0]);
    write(fd[1], buf, strlen(buf));
}

void parent(int *fd)
{
    printf("parent process read pipe\n");
    char buf[64];
    close(fd[1]);
    read(fd[0], buf, sizeof buf);
    printf("read buf: %s\n", buf);
}

int main(void)
{
    int fd[2]; // pipe
    int ret;
    pid_t pid;
    if ((ret = pipe(fd)) < 0) {
        printf("create pipe failed\n");
    }

    pid = vfork();
    if (pid == 0) {
        child(fd);
        exit(0);
    } else if (pid > 0) {
        parent(fd);
    } else {
        printf("create process failed\n");
    }

    return 0;
}

