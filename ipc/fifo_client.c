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

int main()
{
    int fd;
    int ret;

    // FIFO file path
    char *myfifo = "./myfifo";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    //mkfifo(myfifo, 0666);

    // create shared mutex interprocess
    struct mt *mm;

    mm = mmap(NULL, sizeof(*mm), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);
    memset(mm, 0, sizeof(*mm));

    pthread_mutexattr_init(&mm->mutexattr);                                  //初始化mutex属性对象
    pthread_mutexattr_setpshared(&mm->mutexattr, PTHREAD_PROCESS_SHARED);    //修改属性为进程间共享
    pthread_mutex_init(&mm->mutex, &mm->mutexattr);                          //初始化一把mutex琐

    char arr1[80], arr2[80];
    int cnt = 0;
    sprintf(arr2, "client %d", cnt);
    
    sleep(30);
    for (int i = 0; i < 1; i ++)
    {
#if 1
	printf("----- begin client -----\n");
	if ((ret = pthread_mutex_lock(&mm->mutex)) != 0) {
	    //printf("lock failed\n");
	    exit(-1);
	}
	printf("%d mutex lock finished\n", __LINE__);
	sleep(5);

        // Open FIFO for write only
        if ((fd = open(myfifo, O_WRONLY)) < 0) {
	    printf("open fifo file failed\n");
	    exit(-2);
        }
	printf("%d open fifo finished\n", __LINE__);
	sleep(5);

        // Take an input arr2ing from user.
        // 80 is maximum length
	printf("cnt: %d\n", cnt++);
        //fgets(arr2, 80, stdin);
	sprintf(arr2, "client %d", cnt);

	printf("%d sprintf finished\n", __LINE__);
	sleep(5);
	
        // Write the input arr2ing on FIFO
        // and close it
        if ((ret = write(fd, arr2, strlen(arr2)+1)) < 0) {
	    //printf("write fifo failed\n");
	    exit(-3);
	}
	printf("%d write fifo finished\n", __LINE__);
	sleep(5);

        if ((ret = close(fd)) != 0) {
	    //printf("close fd failed\n");
	    exit(-4);
	}
	printf("%d close fifo finished\n", __LINE__);
	sleep(5);
	//sleep(7);

	if ((ret = pthread_mutex_unlock(&mm->mutex)) != 0) {
	    //printf("unlock failed\n");
	    exit(-5);
	}
	printf("----- end client -----\n");
	usleep(10);
#endif
	//printf("client end\n");

#if 0
	for (int i = 0; i < 8; i++) {
		sleep(1);
		printf("sleep %d\n", i);
	}

        // Open FIFO for Read only
	printf("user1: open fifo and read it\n");
        fd = open(myfifo, O_RDONLY);

        // Read from FIFO
        if ((ret = read(fd, arr1, sizeof(arr1))) < 0) {
	   printf("read fifo failed\n");
	}

        // Print the read message
        printf("User2: %s\n", arr1);
        close(fd);
#endif
	//usleep(5);
	//printf("cnt: %d\n", cnt++);
    }

    exit(-6);
    return 0;
}

