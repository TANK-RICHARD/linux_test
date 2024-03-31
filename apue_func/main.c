#include <stdio.h>
#include <stdint.h>

#if 0
#define is_constexpr(x) \
	(sizeof(int) == sizeof(*(8 ? ((void *)((long)(x) * 0l)) : (int *)8)))

int main(void)
{
    int16_t a = 9;
    char b = 'a';
    int *c = &a;
    int ret_a = is_constexpr(a - b);
    int ret_b = is_constexpr(b);
    int ret_c = is_constexpr(c);

    printf("ret_a: %d\n", ret_a);
    printf("ret_b: %d\n", ret_b);
    printf("ret_c: %d\n", ret_c);

    if (1)
        printf("d\n");

    return 0;
}

#endif

/*----------- perror  --------------*/
#if 0
#include <stdio.h>

int main (void)
{
   FILE *fp;

   /* first rename if there is any file */
   rename("file.txt", "newfile.txt");

   /* now let's try to open same file */
   fp = fopen("file.txt", "r");
   if( fp == NULL ) {
      perror("ERROR: open file failed");
      return(-2);
   }
   fclose(fp);
      
   return(0);
}
#endif

// -----------------------------------------

#if 0

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(void)
{
    int fdOne, fdTwo, fdThree;

    fdOne = open("misc.txt", O_CREAT | O_TRUNC, S_IRWXU);

    if(fdOne < 0){
        printf("Error opening / creating test.txt. ");
        if(errno==EACCES){
            printf("Error #%d (EACCES): Permission denied.\n", EACCES);
            exit(EXIT_FAILURE);
        }
    } else {
        printf("test.txt created / opened ");
        printf("with file descriptor %d.\n", fdOne);
    }

    //lets use the fcntl() function to copy the
    //file descriptor
   if((fdTwo = fcntl(fdOne, F_DUPFD, 0))<0){
       printf("Error duplicating file descriptor.\n");
       exit(EXIT_FAILURE);
   } else {
       printf("File descriptor duplicated. ");
       printf("New file descriptor is %d.\n", fdTwo);
   }

   //set the file descriptor to be a higher number;
   // specify the fdThree is 33, of course it can be
   // change to any other higher num
    if((fdThree = fcntl(fdOne, F_DUPFD, 33))<0){
        printf("Error duplicating file descriptor.\n");
        exit(EXIT_FAILURE);
    } else {
        printf("File descriptor duplicated. ");
        printf("New file descriptor is %d.\n", fdThree);
    }

    close(fdOne);
    close(fdTwo);
    close(fdThree);

    return 0;

}

#endif

// -----------------------------------------
#if 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(void)
{
    
    int fflags, rVal, fd;
    
    if((fd = open("afile", O_CREAT | O_APPEND, S_IRWXU))<0){
        printf("error opening file.\n");
        exit(EXIT_FAILURE);
    } else {
        printf("File opened.\n");
    }
    
    if((rVal = fcntl(fd, F_GETFL))<0){
        printf("Error getting file status flags.\n");
        exit(EXIT_FAILURE);
    } else {
        printf("File status flags retrieved.\n");
    }
    
    //O_ACCMODE has the value of three
    fflags = rVal & O_ACCMODE;
    printf("rVal: %x, accmode: %x\n", rVal, O_ACCMODE);
    printf("rdonly: %x, wronly: %x, rdwr: %x\n", O_RDONLY, O_WRONLY, O_RDWR);

    if(fflags == O_RDONLY){
        printf("File is read only.\n");
    } else if (fflags == O_WRONLY){
        printf("File is write only.\n");
    } else if (fflags == O_RDWR){
        printf("File is read / write.\n");
    } else {
        printf("No idea.\n");
    }

    if(close(fd)<0){
        printf("Error closing file.\n");
        exit(EXIT_FAILURE);
    } else {
        printf("File descriptor closed.\n");
    }
    
    return 0;
}


#endif



// -----------------------------------------
// -----------------------------------------
// -----------------------------------------
// -----------------------------------------
// -----------------------------------------
// -----------------------------------------
// -----------------------------------------
// -----------------------------------------
// -----------------------------------------
// -----------------------------------------
// -----------------------------------------
// -----------------------------------------
// -----------------------------------------
// -----------------------------------------
// -----------------------------------------
// -----------------------------------------
// -----------------------------------------
// -----------------------------------------
// -----------------------------------------
// -----------------------------------------
// -----------------------------------------
// -----------------------------------------
// -----------------------------------------
