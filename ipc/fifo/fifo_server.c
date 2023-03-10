// NOTE: FIFO can be opened with 2 modes: block or nonblock.
// 	 open() will return and code continue run when read fifo,
//	 however, open() will return error when write fifo.
//	 open() FIFO with block mode, and wait a little time,
//	 for example 1us after writing FIFO, then write and read
//	 process will be synchronized at the position of open(),
//	 so that the data in fifo will be write and read correctly.

// C program to implement one side of FIFO
// This side reads first, then reads
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>

struct mt {
    int num;
    pthread_mutex_t mutex;
    pthread_mutexattr_t mutexattr;
};

#define MUTEX 0

int main(void)
{
    int fd1, ret;

    // FIFO file path
    char * myfifo = "./myfifo";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>,<permission>)
    mkfifo(myfifo, 0666);

    // create shared mutex interprocess
    struct mt *mm;

    mm = mmap(NULL, sizeof(*mm), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);
    memset(mm, 0, sizeof(*mm));

    pthread_mutexattr_init(&mm->mutexattr);                                  //初始化mutex属性对象
    pthread_mutexattr_setpshared(&mm->mutexattr, PTHREAD_PROCESS_SHARED);    //修改属性为进程间共享
    pthread_mutex_init(&mm->mutex, &mm->mutexattr);                          //初始化一把mutex琐

    char str1[80], str2[80];
    int cnt = 0;


    for (int i = 0; i < 1000; i ++) {
#if MUTEX
        if ((ret = pthread_mutex_lock(&mm->mutex)) != 0) {
            printf("s lock failed\n");
            exit(-1);
        }
        printf("%d mutex lock finished\n", __LINE__);
#endif

        // First open in read only and read
        if ((fd1 = open(myfifo, O_RDONLY)) < 0) {
            printf("s open fifo failed\n");
        }

        if ((ret = read(fd1, str1, 80)) < 0) {
            printf("s read failed\n");
        }
        // TODO: spin lock here

        // Print the read string and close
        printf("User1: %s\n", str1);

        if ((ret = close(fd1)) < 0) {
            printf("s close fifo failed\n");
        }

#if MUTEX
        if ((ret = pthread_mutex_unlock(&mm->mutex)) != 0) {
            printf("s unlock failed\n");
            exit(-2);
        }
#endif

        printf("end t: %d\n", i);
        usleep(2);
    }

    return 0;
}

