#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

#define PIN_LENGTH 4
#define PIN_WAIT_INTERVAL 2

int main(void){
	void sigint_handler(int sig);
	char s[200];

	if(signal(SIGINT, sigint_handler)==SIG_ERR){
		perror("signal");
		exit(1);
	} 
	int i = fork();

	if(i==0){
		printf("Nice to meet you\n");
		printf("Please eneter your name: \n");
	}
	else{
		printf("Hello there user :D\n");
	}

	if(fgets(s, 200, stdin)==NULL)
		perror("gets");
	else
		printf("Hello there %s\n", s);

	return 0;
}
void sigint_handler(int sig){
	printf("BREAK!!\n");
}
