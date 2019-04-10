//
//  main.c
//  bilshell
//
//  Created by Fırat Yıldız on 2/22/19.
//  Copyright © 2019 Fırat Yıldız. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LIMIT 64
#define SPACE_LENG " \t\r\n\a"
#define READ_END 0
#define WRITE_END 1
#define BUFFER_SIZE 25

char* getLine(int* cont){
    int bufS = 1024;
    int pos = 0;
    char *buffer = malloc(sizeof(char) * bufS);
    int caracter;

   
    while (1) {
        caracter = getchar();
        if( caracter == '|'){
            *cont = 1;
        }
        if (caracter == EOF || caracter == '\n') {
            buffer[pos] = '\0';
            return buffer;
        }
        else {
            buffer[pos] = caracter;
        }
        pos++;

       
        if (pos >= bufS) {
            bufS += 1024;
            buffer = realloc(buffer, bufS);
        }
    }
}

char** returnArr(char* inLine){
    int size = 64, position = 0, arrPos = 0, pos = 0;
    char **retArr = malloc(size * sizeof(char*));
    char *temp;

   
    if(sizeof(inLine)/sizeof(char*) == 0){
        pos++;
        printf("string is empty");
    }

   
    temp = strtok(inLine, SPACE_LENG);
    while (temp != NULL) {
        retArr[position] = temp;
        position++;
        if (position >= size) {
            size += 64;
            temp = realloc(retArr, size * sizeof(char*));
        }
        if(temp == NULL){
            printf("temporal string is empty");
        }
        temp = strtok(NULL, SPACE_LENG);
    }
    retArr[position] = NULL;
    return retArr;
}

int executeInterOne(char** arguments){
    pid_t pid;
    pid = fork();

    if(pid < 0){
        fprintf(stderr, "Error");
    }
    else if( pid == 0){
		printf("%s", arguments[0] );
        execvp(arguments[0],arguments);
        exit(0);
    }

    else {
        wait(NULL);
    }
    return 1;
}

int executeInterMore(char** arguments, int* chSize, int* rSize, int N){
    int fd1[2];
    int fd[2];
    //char write_msg[N];
    char read_msg[N];
    int befNum = 0;
    while(strcmp(arguments[befNum], "|") != 0){
        befNum++;
    }
    char* command = arguments[++befNum];
    arguments[befNum] = NULL;
    arguments[--befNum] = NULL;

    pid_t firstChild, secondChild;

   
    if( pipe(fd) == -1){
        fprintf(stderr, "The pipe cant open");
        return 1;
    }
    if( pipe(fd1) == -1){
        fprintf(stderr, "The pipe cant open");
        return 1;
    }
 
    firstChild = fork();
    if(firstChild == 0){
		printf("child1 process");
		close(fd1[READ_END]);
		close(fd[READ_END]);
		close(fd1[WRITE_END]);
        dup2 (fd[WRITE_END], 1);
        close(fd[WRITE_END]);
        execvp(arguments[0], arguments);
    }
	else{
		secondChild = fork();
		if(secondChild == 0){
			//printf("child2 process");
			close(fd[READ_END]);
			close(fd[WRITE_END]);
			close(fd1[WRITE_END]);
			dup2(fd1[READ_END], 0);
			close(fd1[READ_END]);
			char* str[2];
			str[0] = command;
			str[1] = NULL;
			execvp(str[0], str);
		}
		else if(secondChild > 0){
			//printf("parent2 process");
			close(fd[1]);
			close(fd1[0]);
			int chComp = 1;
			while(chComp > 0){
				chComp = read(fd[READ_END], read_msg, N);
				write(fd1[WRITE_END], read_msg, N);
				*chSize += chComp; 
                *rSize += 1;
                memset(read_msg,0,N);
			}
			close(fd[0]);
			close(fd1[1]);
			wait(NULL);
			wait(NULL);
		}
	}
	
    return 1;
}

int main(int argc, char * argv[]) {
    char* comline;
    char** arrargs;
    //char* arrargs1[2];
    //char** contrArr;
    int N = atoi(argv[1]);
	int cont = 0, rSize = 0, chSize = 1;
    do {
        /*printf("start> ");
        comline = getLine(&cont);
        arrargs = returnArr(comline);*/
        
        if(argv[2] == NULL){
            printf("bilshell -$ > ");
            comline = getLine(&cont);
            arrargs = returnArr(comline);
            if(cont == 0){
                executeInterOne(arrargs);
            }
           else{
                executeInterMore(arrargs, &chSize, &rSize, N);
                cont = 0;
            }
        }
        else{
        printf("girdi");
        FILE *fd = fopen(argv[2], "r");
        char aLine[10];
       
        if (fd == NULL){
        printf("The file could not been found!");
        }

       
       int s = 0;
        int cont1 = 0;   
        while (fgets(aLine, 2000, fd) != NULL){
            arrargs = NULL;
            arrargs = returnArr(aLine);
		    arrargs[9] = NULL;  
			while( arrargs[s] != NULL){
				if(strcmp(arrargs[s],"|") == 0){
					cont1 = 1;
				}
            s++;
			}
            if(cont1 == 0){
                executeInterOne(arrargs);
            }
           else{
                executeInterMore(arrargs, &chSize, &rSize, N);
                cont1 = 0;
            }
        }
        printf("character-count:%d\n", chSize);
        printf("read-call-count:%d\n", rSize);
        fclose(fd);
        exit(1);
    }
	printf("character-count:%d\n", chSize);
	printf("read-call-count:%d\n", rSize);
    rSize = 0;
    chSize = 0;
    
    }while (1);
    
    return 0;
}
