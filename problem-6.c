#include <unistd.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
int makeDir(const char* fileName);
int initDirs();


int main (int argC, char* argV[]){
	makeDir("project1");
	chdir("project1");
	makeDir("alice");
	chdir("alice");
	initDirs();	
	chdir("..");
	makeDir("chris");
	chdir("chris");
	initDirs();

	exit(0);
}

int makeDir(const char* fileName){
	return mkdir(fileName, S_IRWXU);
}

int initDirs(){
	if(!makeDir("bin")==0)
		return -1;
	if(!makeDir("include")==0)
		return -1;
	if(!makeDir("lib")==0)
		return -1;
	if(!makeDir("src")==0)
		return -1;
	return 0;
}
