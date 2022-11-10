#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

int getLUCK(){
	srand(getpid() + getppid());
	int lucky = rand() % 8000;
	return lucky;
}
int main(void){
	void sigint_handler(int sig);
	char s[200];
	int fd[2];
	pipe(fd);
	pid_t pid = fork();

	if(signal(SIGINT, sigint_handler)==SIG_ERR){
		perror("signal");
		exit(1);
	} 
	int i = fork();

	if(pid==0){
		printf("Nice to meet you\n");
		printf("Please enter your name: \n");
		fgets(s, 200, stdin);
		printf("Hello there %s\n", s);
	}
	else{
		printf("Hello there user :D \n");
	}

	//if(fgets(s, 200, stdin)==NULL)
	//	perror("gets");
	//else
	//	printf("Hello there %s\n", s);

	if(pid>0){
		close(0);
		close(fd[1]);
		dup(fd[0]);
	
		int luckynumber;
		size_t readBytes = read(fd[0], &luckynumber, sizeof(luckynumber));

		printf("Processing you lucky number...\n\n");
		wait(NULL);
		printf("Your lucky number is %d\n\n", luckynumber);
	}
	else if(pid==0){
		close(1);
		close(fd[0]);
		dup(fd[1]);

		int lucky = getLUCK();
		write(fd[1], &lucky, sizeof(lucky));
		exit(EXIT_SUCCESS);
	}
	return EXIT_SUCCESS;
}
void sigint_handler(int sig){
	printf("BREAK!!\n");
}
