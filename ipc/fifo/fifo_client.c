// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/mman.h>

struct mt {
    int num;
    pthread_mutex_t mutex;
    pthread_mutexattr_t mutexattr;
};

int main(void)
{
    int fd;
    int ret;

    // FIFO file path
    char *myfifo = "./myfifo";

    // Creating the named file(FIFO)
    //mkfifo(<pathname>, <permission>)
    mkfifo(myfifo, 0666);

    // create shared mutex interprocess
    struct mt *mm;

    mm = mmap(NULL, sizeof(*mm), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);
    memset(mm, 0, sizeof(*mm));

    pthread_mutexattr_init(&mm->mutexattr);                                  //初始化mutex属性对象
    pthread_mutexattr_setpshared(&mm->mutexattr, PTHREAD_PROCESS_SHARED);    //修改属性为进程间共享
    pthread_mutex_init(&mm->mutex, &mm->mutexattr);                          //初始化一把mutex琐

    char arr1[80], arr2[80];
    int cnt = 0;
    
    for (int i = 0; i < 1000; i ++) {
#if 0
        printf("----- begin client -----\n");
        if ((ret = pthread_mutex_lock(&mm->mutex)) != 0) {
            //printf("lock failed\n");
            exit(-1);
        }
        printf("%d mutex lock finished\n", __LINE__);
#endif
        // Open FIFO for write only, blocked mode
        if ((fd = open(myfifo, O_WRONLY)) < 0) {
            printf("open fifo file failed\n");
            exit(-2);
        }
        sprintf(arr2, "client %d", cnt);
        printf("cnt: %d\n", cnt++);

        // Write the input arr2ing on FIFO and close it
        if ((ret = write(fd, arr2, strlen(arr2)+1)) < 0) {
            exit(-3);
        }
        // TODO: spin lock here
        printf("cnt: %d\n", cnt++);

        if ((ret = close(fd)) != 0) {
            printf("close fd failed\n");
            exit(-4);
        }
#if 0
        if ((ret = pthread_mutex_unlock(&mm->mutex)) != 0) {
            //printf("unlock failed\n");
            exit(-5);
        }
        printf("----- end client -----\n");
#endif
        usleep(3);
    }

    exit(-6);
    return 0;
}

