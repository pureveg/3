#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
bool flag = false;
void alarmhandle(int sig) {
printf("Input time expired\n");
exit(1);
}
int main() {
int a = 0;
printf("Input now in 10 seconds\n");
sleep(1);
alarm(10);
signal(SIGALRM, alarmhandle);
scanf("%d", &a);
printf("You entered %d\n", a);
}


Output:
Input now in 10 seconds
Input time expired
