#include <unistd.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

const int MAXBUF = 1024;

int main (int argC, char* argV[]){
	int filedes[2];
	pid_t childPID;
	char buffer[MAXBUF];

	buffer[0] = '\0';
	buffer[MAXBUF-1] = ~'\0';
	
	if (pipe(filedes) < 0){
		perror("Pipe failed");
		exit(-1);
	}
	
	childPID = fork();
	
	if(childPID < 0){
		perror("Fork failed");
		exit(-1);
	}
	else if(childPID == 0){//Child
		close(filedes[1]);
		for(;;){
			read(filedes[0], buffer, MAXBUF);
			printf("%s", buffer);
		}
	}
	else{//Parent
		close(filedes[0]);
		for(;;){
			fgets(buffer, MAXBUF, stdin);
			write(filedes[1], buffer, MAXBUF);
		}
	}

	
	exit(0);
}
