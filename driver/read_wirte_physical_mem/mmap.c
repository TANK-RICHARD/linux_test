#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>//mmap head file
int main (void)
{
    int i;
    int fd;
    char *start;
    char *buf = "butterfly!";

    //open /dev/mem with read and write mode
    fd = open ("/dev/mem", O_RDWR);
    if (fd < 0) {
        printf("cannot open /dev/mem.");
        return -1;
    }

    //map physical memory 0-10 bytes
    start = (char *)mmap(0, 10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 4096);
    if(start < 0) {
        printf("mmap failed.");
        return -1;
    } else {
        printf("start addr: 0x%x\n", start);
    }

    //Read old value
    for (i = 0; i < 10; i++) {
        printf("old mem[%d]:%c\n", i, *(start + i));
    }
    //write memory
    memcpy(start, buf, 10);
    //Read new value
    for (i = 0;i < 10;i++) {
        printf("new mem[%d]:%c\n", i,*(start + i));
    }
    munmap(start, 10); //destroy map memory
    close(fd);   //close file
    return 0;
}
