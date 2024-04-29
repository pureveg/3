1.
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
char *args[]={"./EXEC",NULL};
execvp(args[0],args);
printf("Ending\n");
return 0;
}

2.
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid, i, status;

    for (i = 0; i < 5; i++) {
        pid = fork();

        if (pid < 0) {
            printf("Fork failed\n");
            return 1;
        } else if (pid == 0) {
            // Child process
            switch (i) {
                case 0:
                    printf("Child %d: Addition operation\n", getpid());
                    break;
                case 1:
                    printf("Child %d: Subtraction operation\n", getpid());
                    break;
                case 2:
                    printf("Child %d: Multiplication operation\n", getpid());
                    break;
                case 3:
                    printf("Child %d: Division operation\n", getpid());
                    break;
                case 4:
                    printf("Child %d: Modulus operation\n", getpid());
                    break;
            }
            return 0;
        } else {
            // Parent process
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}


3.

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
int main(){
char *args[] = {"./hello", NULL};
pid_t pid = fork();
if(pid < 0){
perror("Fork failed!\n");
}
if(pid==0){
printf("PID of child process = %d\n", getpid());
execv(args[0], args);
} else {
wait(NULL);
printf("PID of parent process = %d\n", getpid());
printf("Child has finished execution\n");
}
return 0;
}


hello.c:
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
int main() {
printf("I am in hello.c\n");
printf("PID of hello.c is %d\n", getpid());
return 0;
}

