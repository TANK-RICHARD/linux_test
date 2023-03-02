#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
  
// structure for message queue
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;
  
int main()
{
    key_t key;
    int msgid;
  
    // ftok to generate unique key
    key = ftok("./prog", 64);
    printf("key s: %d\n", key);
  
    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
  
    for (int i = 0; i < 1000; i ++) {
        // msgrcv to receive message
        msgrcv(msgid, &message, sizeof(message), 1, 0);
      
        // display the message
        printf("Data Received is : %s, i: %d\n", message.mesg_text, i);

        usleep(2);
    }
  
    // to destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);
  
    return 0;
}
