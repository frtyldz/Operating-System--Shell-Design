#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h> 
#include <unistd.h> 

int main(int argc, char* argv[]){
	char chooseINSIDE[20] = "qwertyop12iasf67n/c.";
	int randomNum = 0;
	int check = 0;
	while(check < atoi(argv[1])){
        check++;
		randomNum = rand() % 20;
		printf("%c", chooseINSIDE[randomNum]);
	}
	return 0;
}
