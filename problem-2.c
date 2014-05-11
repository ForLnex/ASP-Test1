#include <unistd.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>

extern int errno;

//Copies a file using forked processes
int main (int argC, char* argV[]){
	pid_t parentID;
	size_t readSize;
	unsigned long fileSize;
	unsigned long start;
	FILE* file;
	FILE* outFile = fopen("forkcopy.txt", "w");

	file = fopen(argV[1], "r");

	fseek(file, 0, SEEK_END);
	fileSize = (unsigned long)ftell(file);

	parentID = getpid();

	start = 0;
	readSize = fileSize/2+1;	

	fork();
	
	//Still in parent process
	if(getpid() == parentID){
		start = fileSize/2;
		readSize = fileSize - readSize +1;	
		fork();
		if(getpid() == parentID)
			while(wait(NULL)>0);

	}
	if(getpid() != parentID){
		char readVals[readSize];
		file = fopen(argV[1], "r");
		fseek(file, start, SEEK_SET);
		fgets(readVals, readSize, file);
		fputs(readVals, outFile);
		fclose(file);
		exit(0);
	}	
	
	exit(0);
}
