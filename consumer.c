#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h> 
#include <unistd.h> 

int main(int argc, char* argv[]){
	char str[atoi(argv[1])];
	int check = 0;
	while(check < atoi(argv[1])){
		read(0, str, 1);
		check++;
	}
	return 0;
}
