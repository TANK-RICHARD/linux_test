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

int main()
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

    //sleep(30);
    for (int i = 0; i < 1; i ++) {
	printf("begin t: %d\n", i);
	if ((ret = pthread_mutex_lock(&mm->mutex)) != 0) {
	    printf("s lock failed\n");
	    exit(-1);
	}
	printf("%d mutex lock finished\n", __LINE__);
	sleep(2);

        // First open in read only and read
        if ((fd1 = open(myfifo, O_RDONLY)) < 0) {
		printf("s open fifo failed\n");
	}

	printf("%d open fifo finished\n", __LINE__);
	sleep(2);
        if ((ret = read(fd1, str1, 80)) < 0) {
	    printf("s read failed\n");
	}

	printf("%d read fifo finished\n", __LINE__);
	sleep(2);
        // Print the read string and close
        printf("User1: %s\n", str1);
        if ((ret = close(fd1)) < 0) {
	    printf("s close fifo failed\n");
	}
	printf("%d close fifo finished\n", __LINE__);
	sleep(2);

	if ((ret = pthread_mutex_unlock(&mm->mutex)) != 0) {
	    printf("s unlock failed\n");
	    exit(-2);
	}

#if 0
        // Now open in write mode and write
        // string taken from user.
        fd1 = open(myfifo, O_WRONLY);
        //fgets(str2, 80, stdin);
	//strcpy(str2, "server");
	sprintf(str2, "server %d", cnt++);
        write(fd1, str2, strlen(str2)+1);
        close(fd1);
#endif
	printf("end t: %d\n", i);
	usleep(10);
    }
    return 0;
}

