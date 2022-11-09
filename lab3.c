#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

int main(void){
	void sigint_handler(int sig);
	void sigtstp_handler(int sig1);
	char s[200];

	if(signal(SIGINT, sigint_handler)==SIG_ERR){
		perror("signal");
		exit(1);
	}
	else if(signal(SIGTSTP, sigtstp_handler)==SIG1_ERR){
		perror("signal");
		exit(2);
	}
	printf("enter a string:\n");

	if(fgets(s, 200, stdin)==NULL)
		perror("gets");
	else
		printf("you entered:%s\n",s);
	
	return 0;
}
void sigint_handler(int sig){
	printf("jangan kacau saya!\n");
}
void sigtstp_handler(int sig1){
	printf("apa awak nak?");
}
