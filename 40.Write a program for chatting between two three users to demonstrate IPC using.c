#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MAX_MSG_SIZE 256

struct msg_buffer {
    long msg_type;
    char msg_text[MAX_MSG_SIZE];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;
    int user_id;

    // Generate a unique key
    key = ftok("msgq_chat", 'A');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Enter user id (1, 2, or 3): ");
    scanf("%d", &user_id);

    while (1) {
        // Send message
        printf("User %d: ", user_id);
        fgets(message.msg_text, MAX_MSG_SIZE, stdin);
        message.msg_type = 1;
        msgsnd(msgid, &message, sizeof(message), 0);

        // Receive messages
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        printf("Received: %s\n", message.msg_text);
    }

    // Remove the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
