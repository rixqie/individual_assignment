#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>

#define  LUCK_LENGTH 4
#define LUCK_WAIT_INTERVAL 2

void getLUCK(char luck[LUCK_LENGTH + 1]){
	srand(getpid() + getpid());

	luck[0] = 49 + rand() % 7;

	for(int i=1; i<LUCK_LENGTH; i++){
		luck[i] = 48 + rand() % 7;
	}
	luck[LUCK_LENGTH] = '\0';
}

int main (void){
	while(1){
		int pipefds[2];
		char luck[LUCK_LENGTH + 1];
		char buffer[LUCK_LENGTH + 1];
		char name[100];
		char s[100];
		void sigint_handler(int sig);
		
		if(signal(SIGINT, sigint_handler)==SIG_ERR){
			perror("signal");
			exit(1);
		}

		pipe(pipefds);

		pid_t pid = fork();

		if(pid==0){
			getLUCK(luck);
			close(pipefds[0]);
			write(pipefds[1], luck, LUCK_LENGTH + 1);
			
			printf("******************WARNING THIS IS A GAMBLING SYSTEM***************\n");
			printf("Hello user, we will give you your number shortly :D\n");
			printf("What is your name?\n");
			fgets(name, 100, stdin);
			printf("Allocating your lucky number...\n");
			printf("Dear mister/miss %s", name);

			sleep(LUCK_WAIT_INTERVAL);

			exit(EXIT_SUCCESS);
		}
		if(pid>0){
			wait(NULL);

			close(pipefds[1]);
			read(pipefds[0], buffer, LUCK_LENGTH + 1);
			close(pipefds[0]);
			printf("Your lucky number is '%s'. Thank you for using this system.\n\n", buffer);
		}
	}
	return 0;
	return EXIT_SUCCESS;
}
void sigint_handler(int sig){
	printf("\nSYSTEM BREAK!!!\n");
}
